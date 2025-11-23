# Lab 5

## Setting up Ansible and Test Server

Create Dockerfile.ansible_agent and Dockerfile.test-server

Install Dependencies and choose as a base image Ubuntu

Then lets create key using ```ssh-keygen -f jenkins_agent_ansible__key```

Then add services to docker-compose.yaml 

```yaml
  ansible-agent:
    build:
      context: .
      dockerfile: Dockerfile.ansible_agent
    container_name: ansible-agent
    ports:
      - "2223:22"
    volumes:
      - ./ansible:/home/ansible/ansible
      - ./secrets:/home/ansible/secrets:ro
    depends_on:
      - jenkins-controller
    networks:
      - jenkins-network

  
  test-server:
    build:
      context: .
      dockerfile: Dockerfile.test_server
    container_name: test-server
    ports:
      - "2222:22"
      - "8088:80"
    networks:
      - jenkins-network
```

lets create ansible playbook for setting up server

```yaml
---
- name: Configure Test Server
  hosts: test_server
  become: yes

  vars:
    project_root: /var/www/php_project
    server_name: testserver.local

  tasks:

    - name: Install Apache2
      apt:
        name: apache2
        state: present
        update_cache: yes

    - name: Enable Apache modules
      command: a2enmod rewrite

    - name: Install PHP and modules
      apt:
        name:
          - php
          - libapache2-mod-php
          - php-cli
          - php-curl
          - php-xml
          - php-mbstring
          - php-zip
          - php-mysql
        state: present

    - name: Create project directory
      file:
        path: "{{ project_root }}"
        state: directory
        owner: www-data
        group: www-data
        mode: "0755"

    - name: Create Apache virtual host
      copy:
        dest: /etc/apache2/sites-available/php_project.conf
        content: |
          <VirtualHost *:80>
              ServerName {{ server_name }}

              DocumentRoot {{ project_root }}

              <Directory {{ project_root }}>
                  AllowOverride All
                  Require all granted
              </Directory>

              ErrorLog ${APACHE_LOG_DIR}/error.log
              CustomLog ${APACHE_LOG_DIR}/access.log combined
          </VirtualHost>

    - name: Disable default Apache vhost
      command: a2dissite 000-default.conf
      notify: Restart Apache

    - name: Enable project vhost
      command: a2ensite php_project.conf
      notify: Restart Apache

  handlers:
    - name: Restart Apache
      service:
        name: apache2
        state: restarted
```

It installs Apache, php and runs app

Run docker-compose and add piplines

```yaml
pipeline {
    agent any

    stages {
        stage('Clone PHP Project') {
            steps {
                sh '''
                    git clone https://github.com/Rengeka/ScriptingLabs.git
                    cp -r ScriptingLabs/Lab04/php-app .
                '''
            }
        }

        stage('Deploy') {
            steps {
                sh '''
                    cd ansible
                    ansible-playbook -i hosts.ini setup_test_server.yml
                '''
            }
        }
    }
}
```

### Test

You may test app on host ```http://localhost:8088```

### Answers

Here are my AI generated answers to questions (My own brain is not working anymore. Hope these answers are not so bad and I won't feel ashamed)

1. What are the advantages of using Ansible for server configuration?

Ansible has several key advantages:

✔ Agentless

Ansible uses SSH to connect to servers, so no agent installation is needed. This reduces administrative overhead and improves security.

✔ Declarative Approach

You define the desired state of the system instead of step-by-step commands.
For example: “Apache should be installed” instead of “run apt install apache2”.

✔ Idempotency

Running the same playbook multiple times does not break the system — Ansible checks if changes are needed.

✔ Easy Scalability

A single playbook can manage dozens or hundreds of servers through inventory.

✔ Large Number of Built-in Modules

Modules exist for package management, file operations, services, databases, networking, and more.

✔ Repeatability and Version Control

Playbooks are stored in Git, making configuration consistent, auditable, and versioned.

✅ 2. What other Ansible modules exist for configuration management?

Ansible has hundreds of modules, here are some common categories:

Package Management: apt, yum, dnf, pip, gem

Service Management: service, systemd, supervisorctl

File Management: copy, template, file, lineinfile

User & Group Management: user, group, authorized_key

Networking: firewalld, ufw, iptables, net_interface

Databases: mysql_db, postgresql_db, mongodb_user

Docker & Containers: docker_container, docker_image

Cloud & Virtualization: ec2, gcp_compute_instance, vmware_guest

Modules allow you to automate almost any system configuration task without writing raw shell commands.

✅ 3. What problems did you encounter when creating the Ansible playbook and how did you solve them?

Some common issues:

1. SSH Key Access

Problem: Ansible agent couldn’t connect to the test server due to missing keys.

Solution: Generated SSH key pair on Ansible agent, copied the public key to the test server’s authorized_keys, and configured inventory to use the private key.

2. Permission Issues

Problem: Playbook failed to install packages or modify directories due to lack of privileges.

Solution: Used become: yes in the playbook to run tasks with elevated privileges (sudo).

3. Idempotency Errors

Problem: Re-running the playbook caused duplicate configurations (e.g., virtual host).

Solution: Used modules like copy and file that are idempotent, ensuring repeated runs don’t break the system.

4. Missing Dependencies

Problem: PHP extensions or Apache modules were missing.

Solution: Explicitly listed all necessary packages in the playbook (apt: name=[...] state=present).