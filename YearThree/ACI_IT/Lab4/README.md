Технически задание ещё не готово. Просто сдал чтобы уложиться в срок :D

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