#!/bin/bash

VPC_ID=$(jq -r '.VPC_ID' variables.json)
SUBNET_ID=$(jq -r '.SUBNET_ID' variables.json)
AWS_ACCESS_KEY_ID=$(jq -r '.AWS_ACCESS_KEY_ID' variables.json)
AWS_SECRET_ACCESS_KEY=$(jq -r '.AWS_SECRET_ACCESS_KEY' variables.json)
AWS_DEFAULT_REGION=$(jq -r '.AWS_DEFAULT_REGION' variables.json)

export AWS_ACCESS_KEY_ID AWS_SECRET_ACCESS_KEY AWS_DEFAULT_REGION

echo "Using VPC_ID=$VPC_ID"
echo "Using SUBNET_ID=$SUBNET_ID"
echo "Using AWS region=$AWS_DEFAULT_REGION"

echo "Creating Key Pair..."
aws ec2 create-key-pair \
  --key-name ec2-key-pair \
  --query 'KeyMaterial' \
  --output text > ~/ec2-key.pem

chmod 400 ~/ec2-key.pem

echo "Creating Security Group..."
GROUP_ID=$(aws ec2 create-security-group \
  --group-name webserver-sg \
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

echo "CIDR : 0.0.0.0/0"
echo "Protocols : tcp"
echo "Ports : all"

echo "Creating EC2 instance"
INSTANCE_ID=$(aws ec2 run-instances \
  --image-id ami-01f38db8b018d21de \
  --count 1 \
  --instance-type t3.micro \
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

echo "Setting EC2 up"
scp -i ~/ec2-key.pem docker-compose.yml ec2-user@$PUBLIC_IP:~/docker-compose.yml
ssh -i ~/ec2-key.pem -o StrictHostKeyChecking=no ec2-user@$PUBLIC_IP <<'EOF'
sudo yum update -y
sudo yum install -y docker
sudo yum install -y python3-pip
sudo pip3 install docker-compose

sudo systemctl enable docker
sudo systemctl start docker

sudo docker network create main-network

sudo docker run -d \
  --name sql \
  --network main-network \
  -e MYSQL_ROOT_PASSWORD=rootpassword \
  -e MYSQL_DATABASE=post_db \
  --restart always \
  mysql:latest

sleep 20

sudo docker run -d \
  --name php \
  --network main-network \
  -p 80:80 \
  -e DB_HOST=sql \
  -e DB_NAME=post_db \
  -e DB_USER=root \
  -e DB_PASS=rootpassword \
  --restart always \
  rengeka/php-test-app:latest

EOF

echo "Waiting for PHP container to start..."
sleep 10

for i in {1..10}; do
  curl -I http://$PUBLIC_IP/post/show && break
  echo "Waiting for web server..."
  sleep 5
done

echo "Done"