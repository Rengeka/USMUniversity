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

variable "subnet_id" {
  type = string
}