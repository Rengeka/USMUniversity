# Лабораторная 6

### Выполнение

Создадим бакет на aws для хранения state файлов
![tf](./images/1.png)

Создадим aws-provider.tf
```tf
terraform {
  required_version = ">= 1.3.0, < 2.0.0"

  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.0"
    }
  }

  backend "s3" {
    bucket  = "terraform-bucket-lab6"
    key     = "env/prod/terraform.tfstate"
    encrypt = true
    region  = "eu-central-1"              
  }
}

provider "aws" {
  region = var.region
}
```

Укажем переменные в terraform.tfvars
```tf
region        = "eu-central-1"
instance_type = "t3.micro"
ami           = "ami-01f38db8b018d21de" 
environment   = "dev"
```

и variables.tf
```tf
variable "region" {
  description = "AWS region to deploy resources"
  type        = string
}

variable "instance_type" {
  description = "EC2 instance type"
  type        = string
}

variable "ami" {
  description = "AMI ID for EC2"
  type        = string
}

variable "environment" {
  description = "Environment name"
  type        = string
}
```

Создадим два модуля (vm и s3)

Создадим в них main.tf, output.tf и variables.tf

### VM

main.tf
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

    systemctl enable docker
    systemctl start docker

    docker network create main-network

    docker run -d \
      --name sql \
      --network main-network \
      -e MYSQL_ROOT_PASSWORD=rootpassword \
      -e MYSQL_DATABASE=post_db \
      --restart always \
      mysql:latest

    sleep 20

    docker run -d \
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

  tags = {
    Name = "Webserver-${var.environment}"
  }
}
```

ouutput.tf
```tf
output "ec2-ip" {
  value = aws_instance.vm.public_ip
}
```

variables.tf
```tf
variable "instance_type" {
  description = "EC2 instance type"
  type        = string
}

variable "ami" {
  description = "AMI ID for EC2"
  type        = string
}

variable "environment" {
  description = "Environment name"
  type = string
}
```

### S3

main.tf
```tf
resource "aws_s3_bucket" "my-bucket" {
  acl = "private"

  tags = {
    "Name" = "my-simple-bucket-${var.environment}" 
  }
}
```

output.tf
```tf
output "s3-bucket-name" {
  value = aws_s3_bucket.my-bucket.bucket
}
```

variables.tf
```tf
variable "environment" {
  description = "Environment name"
  type = string
}
```

### Запуск

Применяем ```terraform init```, а потом ```terraform plan``` 

Терраформ покажет запланирпованные ресурсы

![tf](./images/2.png)

Применяем ```terraform apply``` (Он снова выполнит terraform plan и далее попросит подтверждение применения изменений)

![tf](./images/3.png)

Проверяем создались ли ресурсы

![tf](./images/4.png)

![tf](./images/5.png)

Проверяем стейт файл

![tf](./images/6.png)

Применяем ```terraform destroy``` чтобы унечтожить ресурсы (Не забываем вручную удалить S3 бакет со стейт файлом)

![tf](./images/7.png)