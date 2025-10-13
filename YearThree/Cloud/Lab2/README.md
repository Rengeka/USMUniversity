# Lab 2

### This lab requires either Ubuntu or Ubuntu wsl distro

### How to start (Bash)

0. [Optionaly] run ubuntu-setup.sh for downloading all the required tools

Do not forget to enable docker desktop WSL integration with Ubuntu if using Windows!

1. Copy variables-sample.json and rename it to variables.json

2. Add your ids to variables.json your ids

3. run init.sh

### How to start (Terraform)

1. Run terraform init in terraform folder

2. Run terraform apply

### Report

1. Creating EC2

a. With Web GUI

Opening aws website and navigating to EC2->Instances->Launch an instance 

![WEB GUI](./images/EC2.jpeg)

b. With AWS CLI

Creating key-pair
```bash
aws ec2 create-key-pair \
  --key-name ec2-key-pair \
  --query 'KeyMaterial' \
  --output text > ~/ec2-key.pem

chmod 400 ~/ec2-key.pem
```

Creating security group
```bash
GROUP_ID=$(aws ec2 create-security-group \
  --group-name webserver-sg \
  --description "Allow SSH from my IP" \
  --vpc-id $VPC_ID \
  --query 'GroupId' \
  --output text)
```

Creating EC2 instance
```bash
aws ec2 authorize-security-group-ingress \
  --group-id $GROUP_ID \
  --protocol tcp \
  --port 0-65535 \
  --cidr 0.0.0.0/0

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
```

Setting up and checking vm using ssh and scp
```bash
aws ec2 wait instance-running --instance-ids $INSTANCE_ID

PUBLIC_IP=$(aws ec2 describe-instances \
  --instance-ids $INSTANCE_ID \
  --query 'Reservations[0].Instances[0].PublicIpAddress' \
  --output text)

scp -i ~/ec2-key.pem docker-compose.yml ec2-user@$PUBLIC_IP:~/docker-compose.yml
ssh -i ~/ec2-key.pem -o StrictHostKeyChecking=no ec2-user@$PUBLIC_IP <<'EOF'
sudo yum update -y
sudo yum install -y docker
...

sudo docker network create main-network

sudo docker run -d \
  --name sql \
  ...

sleep 20

sudo docker run -d \
  --name php \
  ...

EOF

echo "Waiting for PHP container to start..."
sleep 10

for i in {1..10}; do
  curl -I http://$PUBLIC_IP/post/show && break
  echo "Waiting for web server..."
  sleep 5
done
```

c. With Terraform

Downloading my own terraform [template](https://github.com/Rengeka/USMUniversity.git)

It contains provider .tf file
```tf
terraform {
    required_version = ">= 1.3.0, < 2.0.0"

    required_providers {
        aws = {
        source  = "hashicorp/aws"
        version = "~> 4.0"
        }
    }
    }

    provider "aws" {
    region = var.region
}
```

Creating vm and vm/vm.tf and vm/variables.tf instead of nginx directory

Setting up security group and EC2 instance
```tf
resource "aws_security_group" "webserver_sg" {
  name        = "webserver-sg-tf"

  ingress {
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

   ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 65535
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_instance" "vm" {
  ami                    = var.ami
  instance_type          = var.instance_type
  vpc_security_group_ids = [aws_security_group.webserver_sg.id]

  user_data = <<-EOF
    #!/bin/bash
    yum update -y
    yum install -y docker

    ...
  EOF
}
```

Calling module from main.tf
```tf
module "vm" {
  source        = "./vm"
  instance_type = var.instance_type
  ami           = var.ami
}
```

Running ```terraform apply```

Site is available now at http://63.177.94.114/?action=post/show&page=2

![Site](./images/site.png)