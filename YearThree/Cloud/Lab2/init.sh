#!/bin/bash

VPC_ID=$(jq -r '.VPC_ID' config.json)
SUBNET_ID=$(jq -r '.SUBNET_ID' config.json)

echo "Using VPC_ID=$VPC_ID"
echo "Using SUBNET_ID=$SUBNET_ID"

echo "Creating Key Pair..."
aws ec2 create-key-pair \
  --key-name ec2-key-pair \
  --query 'KeyMaterial' \
  --output text > ec2-key.pem

chmod 400 ec2-key.pem

echo "Creating Security Group..."
GROUP_ID=$(aws ec2 create-security-group \
  --group-name my-ssh-access \
  --description "Allow SSH from my IP" \
  --vpc-id $VPC_ID \
  --query 'GroupId' \
  --output text)

echo "Security Group created: $GROUP_ID"

echo "Adding inbound rules..."
aws ec2 authorize-security-group-ingress \
  --group-id $GROUP_ID \
  --protocol tcp \
  --port 0-65535 \ 
  --cidr 0.0.0.0/0

git clone https://github.com/Rengeka/USMUniversity/tree/main/YearTwo/PHP/Lab5
docker image build -f dockerfile.php .

docker login
docker push rengeka/php-test-app:latest

INSTANCE_ID=$(aws ec2 run-instances \
  --image-id ami-043339ea831b48099 \
  --count 1 \
  --instance-type t3.nano \
  --key-name ec2-key-pair \
  --security-group-ids $GROUP_ID \
  --subnet-id $SUBNET_ID \
  --tag-specifications 'ResourceType=instance,Tags=[{Key=Name,Value=MyInstance}]' \
  --query 'Instances[0].InstanceId' \
  --output text)

aws ec2 wait instance-running --instance-ids $INSTANCE_ID

PUBLIC_IP=$(aws ec2 describe-instances \
  --instance-ids $INSTANCE_ID \
  --query 'Reservations[0].Instances[0].PublicIpAddress' \
  --output text)

ssh -i ec2-key.pem -o StrictHostKeyChecking=no ec2-user@$PUBLIC_IP \
  "sudo yum update -y && \
   sudo yum install -y git docker && \
   sudo systemctl start docker && \
   sudo docker network create my-network || true && \
   sudo docker pull rengeka/php-test-app:latest && \
   sudo docker pull mysql:latest && \
   sudo docker run -d --name sql --network my-network -e MYSQL_ROOT_PASSWORD=rootpassword mysql:latest && \
   sudo docker run -d --name php --network my-network -p 80:80 rengeka/php-test-app:latest"

echo "Waiting for PHP container to start..."
sleep 10

for i in {1..10}; do
  curl -I http://$PUBLIC_IP/post/show && break
  echo "Waiting for web server..."
  sleep 5
done

echo "✅ Done!"