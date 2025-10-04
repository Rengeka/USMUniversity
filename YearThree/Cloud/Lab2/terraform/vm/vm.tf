resource "aws_key_pair" "ec2_key" {
  key_name   = "ec2-key"
  public_key = file("${path.module}/keys/ec2-key.pub")
}

resource "aws_security_group" "webserver_sg" {
  name        = "webserver-sg"

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
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_instance" "vm" {
  ami                    = var.ami
  instance_type          = var.instance_type
  key_name               = aws_key_pair.ec2_key.key_name
  vpc_security_group_ids = [aws_security_group.webserver_sg.id]

  user_data = <<-EOF
    #!/bin/bash
    yum update -y
    yum install -y docker.io docker-compose
    systemctl start docker

    cat <<EOT > /home/ubuntu/docker-compose.yml
    version: '3.9'

    services:
      sql:
        image: mysql:latest
        container_name: sql
        restart: always
        environment:
          MYSQL_ROOT_PASSWORD: rootpassword
          MYSQL_DATABASE: mydatabase
        networks:
          - main-network

      php:
        image: rengeka/php-test-app:latest
        container_name: php
        restart: always
        ports:
          - "80:80"
        environment:
          DB_HOST: sql
          DB_NAME: mydatabase
          DB_USER: root
          DB_PASS: rootpassword
        depends_on:
          - sql
        networks:
          - main-network
        volumes:
          - ./public:/var/www/html   

    networks:
      main-network:
        driver: bridge
    EOT

    cd /home/ubuntu
    docker-compose up -d
  EOF

  tags = {
    Type = "VirtualMachine"
  }
}