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
    Type = "VirtualMachine"
  }
}