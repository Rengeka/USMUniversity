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