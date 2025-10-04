module "vm" {
  source        = "./vm"
  instance_type = var.instance_type
  ami           = var.ami
}