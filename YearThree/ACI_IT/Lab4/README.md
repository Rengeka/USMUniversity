Создадим docker-compose.yml с многокнтейнерным приложением

```yml
version: '3.9'

services:
  db:
    image: mysql:8.0
    container_name: mysql_db
    restart: always
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword
      MYSQL_DATABASE: wordpress
      MYSQL_USER: wp_user
      MYSQL_PASSWORD: wp_pass
    volumes:
      - db_data:/var/lib/mysql

  wordpress:
    image: wordpress:latest
    container_name: wordpress_app
    restart: always
    ports:
      - "8080:80"
    environment:
      WORDPRESS_DB_HOST: db:3306
      WORDPRESS_DB_USER: wp_user
      WORDPRESS_DB_PASSWORD: wp_pass
      WORDPRESS_DB_NAME: wordpress
    depends_on:
      - db

volumes:
  db_data:
```

![wordpress](./images/1.png)

Создадим install_docker.yml

```yml
---
- name: Install Docker and Docker Compose
  hosts: docker_hosts
  become: true
  vars:
    docker_users:
      - "{{ ansible_user }}"  
  tasks:
    - name: Update apt cache
      apt:
        update_cache: yes

    - name: Install required packages
      apt:
        name:
          - apt-transport-https
          - ca-certificates
          - curl
          - gnupg
          - lsb-release
        state: present

    - name: Add Docker GPG key
      ansible.builtin.apt_key:
        url: https://download.docker.com/linux/ubuntu/gpg
        state: present

    - name: Add Docker repository
      apt_repository:
        repo: "deb [arch=amd64] https://download.docker.com/linux/ubuntu {{ ansible_lsb.codename }} stable"
        state: present

    - name: Install Docker packages
      apt:
        name:
          - docker-ce
          - docker-ce-cli
          - containerd.io
        state: present
        update_cache: yes

    - name: Add user to docker group
      user:
        name: "{{ item }}"
        groups: docker
        append: yes
      loop: "{{ docker_users }}"

    - name: Install Docker Compose plugin
      shell: |
        mkdir -p ~/.docker/cli-plugins
        curl -SL https://github.com/docker/compose/releases/download/v2.22.0/docker-compose-linux-x86_64 -o ~/.docker/cli-plugins/docker-compose
        chmod +x ~/.docker/cli-plugins/docker-compose
      args:
        executable: /bin/bash

    - name: Verify Docker installation
      command: docker --version
      register: docker_version

    - name: Show Docker version
      debug:
        var: docker_version.stdout

    - name: Verify Docker Compose installation
      command: docker compose version
      register: compose_version

    - name: Show Docker Compose version
      debug:
        var: compose_version.stdout
```

Запустим WSL и установим ansible
```bash
wsl -d Ubuntu
sudo apt update
sudo apt install ansible -y
```

Создадим Vagrantfile через ```vargant up```

И укажем две виртуалки
```bash
Vagrant.configure("2") do |config|

  config.vm.box = "ubuntu/jammy64"
  config.vm.provider "virtualbox" do |vb|
    vb.memory = 4096 
    vb.cpus = 2
  end

  config.vm.define "vm1" do |vm1|
    vm1.vm.hostname = "vm1"
    vm1.vm.network "private_network", ip: "192.168.56.10"
  end

   config.vm.define "vm2" do |vm2|
    vm2.vm.hostname = "vm2"
    vm2.vm.network "private_network", ip: "192.168.56.11"
  end
end
```

Создадим ```hosts.ini``` файл 
```bash
[docker_hosts]
192.168.56.10 ansible_user=vagrant ansible_ssh_private_key_file=.vagrant/machines/vm1/virtualbox/private_key
192.168.56.11 ansible_user=vagrant ansible_ssh_private_key_file=.vagrant/machines/vm2/virtualbox/private_key
```

Создадим deploy_compose.yml
```yml
---
- name: Deploy Docker Compose Application
  hosts: docker_hosts
  become: true
  vars:
    compose_file_src: ./docker-compose.yml
    compose_file_dest: /home/{{ ansible_user }}/docker-compose.yml
  tasks:
    - name: Copy docker-compose.yml to remote host
      copy:
        src: "{{ compose_file_src }}"
        dest: "{{ compose_file_dest }}"
        owner: "{{ ansible_user }}"
        group: "{{ ansible_user }}"
        mode: '0644'

    - name: Launch Docker Compose application
      shell: docker compose -f {{ compose_file_dest }} up -d
      args:
        chdir: "/home/{{ ansible_user }}"
      register: compose_up

    - name: Show docker compose up output
      debug:
        var: compose_up.stdout_lines

    - name: Verify running containers
      command: docker ps
      register: running_containers

    - name: Show running containers
      debug:
        var: running_containers.stdout_lines
```

Запускаем всё
```bash
vagrant up
vagrant status

wsl -d Ubuntu

ansible -i hosts.ini docker_hosts -m ping
ansible-playbook -i hosts.ini install_docker.yml

ansible-playbook -i hosts.ini deploy_compose.yml
```

![wordpress](./images/2.png)

