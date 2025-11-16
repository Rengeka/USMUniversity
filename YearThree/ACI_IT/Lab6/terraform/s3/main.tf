resource "aws_s3_bucket" "my-bucket" {
  acl = "private"

  tags = {
    "Name" = "my-simple-bucket-${var.environment}" 
  }
}