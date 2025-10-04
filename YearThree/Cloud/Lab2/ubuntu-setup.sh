sudo apt update -y
sudo apt upgrade -y

sudo apt install -y jq git curl unzip zip wget software-properties-common

curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
rm awscliv2.zip
sudo ./aws/install
aws --version