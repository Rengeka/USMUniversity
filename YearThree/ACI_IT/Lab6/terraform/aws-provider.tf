terraform {
  required_version = ">= 1.3.0, < 2.0.0"

  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 4.0"
    }
  }

  # backend "s3" {
  #   bucket  = "terraform-bucket-lab6"
  #   key     = "env/prod/terraform.tfstate"
  #   encrypt = true
  #   region  = "eu-central-1"              
  # }
}

provider "aws" {
  region = var.region
}