resource "aws_subnet" "main" {
  vpc_id            = "vpc-08d32386cd5845861"
  cidr_block        = "172.31.1.0/24"
  availability_zone = "eu-central-1a"
}

module "vm" {
  source        = "./vm"
  instance_type = var.instance_type
  ami           = var.ami
  environment   = var.environment
  subnet_id     = aws_subnet.main.id
}

module "s3" {
  source      = "./s3"
  environment = var.environment
}