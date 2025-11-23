# Lab 4

## Project description

This laboratory work requires setting up jenkins and creating a pipline for simple php app

## Setting up Jenkins Controller

Creating docker-compsoe.yaml
```yaml
services:
  jenkins-controller:
    image: jenkins/jenkins:lts
    container_name: jenkins-controller
    ports:
      - "8080:8080"
      - "50000:50000"
    volumes:
      - jenkins_home:/var/jenkins_home
    networks:
      - jenkins-network

volumes:
  jenkins_home:
  jenkins_agent_volume:

networks:
  jenkins-network:
    driver: bridge
```

## Setting up SSH agent

Createing ssh key with ```ssh-keygen -f jenkins_agent_ssh_key```

Creating dockerfile for ssh-agent
```dockerfile
FROM jenkins/ssh-agent

RUN apt-get update && apt-get install -y php-cli
```

And adding ssh-agent to docker compose

```yaml
...

ssh-agent:
    build:
      context: .
      dockerfile: Dockerfile
    container_name: ssh-agent
    environment:
      - JENKINS_AGENT_SSH_PUBKEY=${JENKINS_AGENT_SSH_PUBKEY}
    volumes:
      - jenkins_agent_volume:/home/jenkins/agent
    depends_on:
      - jenkins-controller
    networks:
      - jenkins-network
```

Creating .env with JENKINS_AGENT_SSH_PUBKEY=<generated public key here>

And starting containers via ```docker-compose up```

Unlocking jenkins with code, logged in container

![wordpress](./images/1.png)

Setting up admin

![wordpress](./images/2.png)

Addign SSH key 

![wordpress](./images/3.png)

Configuring Node

![wordpress](./images/4.png)

![wordpress](./images/5.png)

## Creating Jenkins pipeline

Firstly lets ask AI to create a simple php app with unit tests

![wordpress](./images/6.png)

And create a pipeline

![wordpress](./images/7.png)

Final pipeline here
```yaml
pipeline {
    agent { label 'php-agent' }

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/Rengeka/ScriptingLabs.git'
            }
        }

        stage('Install Dependencies') {
            steps {
                dir('Lab04/php-app') {
                    sh '''
                        echo "Current dir: $(pwd)"
                        ls -la
                        composer install
                    '''
                }
            }
        }

        stage('Test') {
            steps {
                dir('Lab04/php-app') {
                    sh 'vendor/bin/phpunit'
                }
            }
        }
    }

    post {
        always { echo 'Pipeline completed.' }
        success { echo 'All stages completed successfully!' }
        failure { echo 'Errors detected in the pipeline.' }
    }
}
```

I have also added additional dependenccies to dockerfile
```dockerfile
FROM jenkins/ssh-agent

RUN apt-get update && apt-get install -y \
    php-cli \
    php-xml \
    php-mbstring \
    unzip \
    git \
    curl

RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer
```

## Questions

Here are my AI generated answers to questions (My own brain is not working anymore. Hope these answers are not so bad and I won't feel ashamed)

### Advantages of using Jenkins for DevOps task automation

- **Continuous Integration / Continuous Delivery (CI/CD)**: Jenkins allows automatic building, testing, and deployment of projects on every code change, speeding up release cycles.  
- **Automation of repetitive tasks**: Builds, tests, deployments, and other routine tasks can be automated, reducing manual work and errors.  
- **Extensibility and plugins**: Jenkins has over 2000 plugins to integrate with tools like Docker, GitHub, Slack, Jira, and many more.  
- **Support for multiple languages and technologies**: Jenkins works with Java, PHP, Python, Node.js, .NET, and other technologies.  
- **Monitoring and reporting**: Jenkins maintains build logs, tracks errors, sends notifications, and can generate test reports.  

### Types of Jenkins agents

Jenkins supports several types of agents, depending on how they connect and use resources:

- **Permanent Agent (Static Agent)**: A permanently connected agent configured once.  
- **Docker Agent**: Runs inside a Docker container for the duration of a build.  
- **SSH Agent**: Connects to a remote machine via SSH to run tasks on an external server.  
- **Cloud Agents**: Dynamically created in cloud environments (AWS EC2, Azure, Google Cloud) and destroyed after the build.  
- **Label-based Agents**: Jobs are assigned to agents based on labels to use the appropriate resources for specific projects.  

### Problems encountered and solutions

- **SSH key permission issue**: Private key had too open permissions (`0777`). Fixed with `chmod 600 .vagrant/machines/vm2/virtualbox/private_key`.  
- **VM did not start (vm1)**: Likely issues with VirtualBox networking. Solved with `vagrant reload vm1` and checking network settings.  
- **Composer not found in agent container**: Installed PHP CLI and Composer via Dockerfile.  
- **Missing PHP extensions**: PHPUnit required `ext-dom`. Fixed by installing `php-xml` and `php-mbstring` in the agent container.  
- **Pipeline could not find project files**: Added a Git checkout stage before running `composer install` to ensure the repository is cloned into the agent workspace.