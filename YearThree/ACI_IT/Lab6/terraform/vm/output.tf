output "ec2-ip" {
  value = aws_instance.vm.public_ip
}