# Лабораторная 3 

# Плейбук 1 (Статический сайт через Nginx + распаковка архива)

## 1. **Цель:** ставим nginx, раскладываем свой мини-сайт из архива (`.tar.gz`) в web-директорию.  

1. Установить и запустить `nginx`.
2. Создать каталог для сайта `/var/www/mysite`.
3. Распаковать архив сайта `files/site.tar.gz` в `/var/www/mysite` (модуль `unarchive`).
4. Положить минимальный nginx-vhost и активировать его (перезапуск по handler).

### 1 Установка и запуск nginx

Создаём tar архив

```bash
tar -czf files/site.tar.gz files/index.html
```

Создаём nginx конфиг

```bash
server {
    listen 80;
    listen [::]:80;

    server_name _;

    root /var/www/mysite;
    index index.html;

    access_log /var/log/nginx/mysite_access.log;
    error_log  /var/log/nginx/mysite_error.log;

    location / {
        try_files $uri $uri/ =404;
    }
}
```

Создаём playbook

```yml
---
- name: Deploy static website with Nginx
  hosts: all
  become: yes

  vars:
    web_root: /var/www/mysite
    nginx_conf: /etc/nginx/sites-available/mysite.conf
    nginx_conf_link: /etc/nginx/sites-enabled/mysite.conf

  tasks:
    - name: Ensure nginx is installed
      apt:
        name: nginx
        state: present
        update_cache: yes

    - name: Ensure nginx is running and enabled
      service:
        name: nginx
        state: started
        enabled: yes

    - name: Create website directory
      file:
        path: "{{ web_root }}"
        state: directory
        owner: www-data
        group: www-data
        mode: '0755'

    - name: Extract site archive
      unarchive:
        src: files/site.tar.gz
        dest: "{{ web_root }}"
        remote_src: no
        owner: www-data
        group: www-data
        mode: '0644'

    - name: Copy nginx vhost configuration
      copy:
        src: files/mysite.conf
        dest: "{{ nginx_conf }}"
        owner: root
        group: root
        mode: '0644'
      notify:
        - Reload nginx

    - name: Enable site (create symlink)
      file:
        src: "{{ nginx_conf }}"
        dest: "{{ nginx_conf_link }}"
        state: link
      notify:
        - Reload nginx

  handlers:
    - name: Reload nginx
      service:
        name: nginx
        state: reloaded
```

Создаём inventory.ini

```
[local]
localhost ansible_connection=local
```

Запускаем ```ansible-playbook -i inventory.ini playbooks/01_static_site.yml```

![nginx](./images/1.png)

## Плейбук 2 (Пользователь деплоя + SSH-ключ + sudoers drop-in)

Создаём пользователя

```bash
sudo useradd -m -s /bin/bash deploy
sudo usermod -aG sudo deploy
sudo mkdir -p /home/deploy/.ssh
sudo chmod 700 /home/deploy/.ssh
sudo chown deploy:deploy /home/deploy/.ssh
```

Создаём ключ

```bash
ssh-keygen -t rsa -b 4096 -C "deploy@example.com"
```

Добавляем публичный ключ

```bash
sudo cat /home/rengeka/.ssh/id_rsa.pub | sudo tee -a /home/deploy/.ssh/authorized_keys
sudo chmod 600 /home/deploy/.ssh/authorized_keys
sudo chown deploy:deploy /home/deploy/.ssh/authorized_keys
```

Создаём файл `/etc/sudoers.d/deploy` c правилом `deploy ALL=(ALL) NOPASSWD:ALL`.

```bash
echo "deploy ALL=(ALL) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/deploy
sudo chmod 440 /etc/sudoers.d/deploy
sudo visudo -cf /etc/sudoers.d/deploy
```

Меняем inventory.ini 
```bash
[webservers]
localhost ansible_connection=ssh ansible_user=deploy ansible_ssh_private_key_file=~/.ssh/id_rsa
```

Проверяем 

![nginx](./images/2.png)

Запускаем и проверяем работате ли ansible по ssh

![nginx](./images/3.png)