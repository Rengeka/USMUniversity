# Лабораторная Работа 2

## Термины

IP-адрес (Internet Protocol Address)

    IP-адрес — это уникальный числовой идентификатор, назначаемый каждому устройству, подключённому к сети, использующей протокол Internet Protocol. Он позволяет устройствам отправлять и получать данные через интернет или локальные сети. Существуют две версии:

    IPv4 (например, 192.168.1.1)

    IPv6 (например, 2001:0db8:85a3::8a2e:0370:7334)

MAC-адрес (Media Access Control Address)

    MAC-адрес — это аппаратный идентификатор, который производитель присваивает сетевой карте (NIC). Он используется для распознавания устройств в локальной сети и обычно записывается в шестнадцатеричном формате, например: 00:1A:2B:3C:4D:5E.
    В отличие от IP-адресов, MAC-адреса не изменяются и уникальны для каждого устройства.

DNS (Domain Name System)

    DNS — система, которая переводит удобочитаемые доменные имена (например, www.example.com
    ) в IP-адреса, которые компьютеры используют для идентификации друг друга в сети. По сути, это «телефонная книга интернета», позволяющая пользователям заходить на сайты без необходимости запоминать числовые IP-адреса.

DHCP (Dynamic Host Configuration Protocol)

    DHCP — это сетевой протокол, автоматически назначающий IP-адреса и другие параметры сети (например, шлюз по умолчанию и DNS-серверы) устройствам в сети. Благодаря этому подключение устройств становится проще, так как пользователям не нужно настраивать параметры вручную.

1. Часть 1 (Базовая диагностика)  
    a. Определить IP и MAC адреса

    Используем ```ip addr```

    ```sh
    1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
        link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
        inet 127.0.0.1/8 scope host lo
        valid_lft forever preferred_lft forever
        inet6 ::1/128 scope host
        valid_lft forever preferred_lft forever
    2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
        link/ether 00:15:5d:2e:42:bb brd ff:ff:ff:ff:ff:ff
        inet 172.26.221.61/20 brd 172.26.223.255 scope global eth0
        valid_lft forever preferred_lft forever
        inet6 fe80::215:5dff:fe2e:42bb/64 scope link
        valid_lft forever preferred_lft forever
    ```

    b. Вывести таблицу маршрутизации

    Используем ```route print```

    ```sh
    ===========================================================================
    Interface List
    10...88 a4 c2 ac 9d b5 ......Realtek PCIe GbE Family Controller
    16...00 15 5d 34 af a6 ......Hyper-V Virtual Ethernet Adapter
    34...00 15 5d 1b d2 7e ......Hyper-V Virtual Ethernet Adapter #2
    22...0a 00 27 00 00 16 ......VirtualBox Host-Only Ethernet Adapter
    4...e2 0a f6 6e 9b 37 ......Microsoft Wi-Fi Direct Virtual Adapter
    9...f2 0a f6 6e 9b 37 ......Microsoft Wi-Fi Direct Virtual Adapter #2
    8...e0 0a f6 6e 9b 37 ......Realtek RTL8852AE WiFi 6 802.11ax PCIe Adapter
    3...e0 0a f6 6e 9b 38 ......Bluetooth Device (Personal Area Network)
    1...........................Software Loopback Interface 1
    ===========================================================================

    ...
    ```

    c. Проверим доступность узла

    Используем ```ping google.com```

    ```sh
    Pinging google.com [216.58.206.46] with 32 bytes of data:
    Reply from 216.58.206.46: bytes=32 time=39ms TTL=119
    Reply from 216.58.206.46: bytes=32 time=39ms TTL=119
    Reply from 216.58.206.46: bytes=32 time=41ms TTL=119
    Reply from 216.58.206.46: bytes=32 time=39ms TTL=119

    Ping statistics for 216.58.206.46:
        Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
    Approximate round trip times in milli-seconds:
    Minimum = 39ms, Maximum = 41ms, Average = 39ms
    ```

    d. Если DNS не работает то пинг не пройдёт т.к не получится сопоставить домен с реальынм IP адресом

2. Часть 2 (Маршруты и трассировка)
    a. Выполняем трассировку 

    Используем ```tracert (Или tracerout для Linux) google.com```

    ```sh
    Tracing route to google.com [172.217.16.206]
    over a maximum of 30 hops:

    1     1 ms     1 ms     1 ms  192.168.100.1
    2     3 ms     2 ms     3 ms  178-168-101-254.starnet.md [178.168.101.254]

    ...
    ```

2. Часть 3 (Порты и соединения)
    a. Стартуем локальынй сервер ```nc -l 12345```

    b. Подключаемся к нему через ```nc localhost 12345```

3. Часть 4 (Работа с DNS)
    a. Запрашиваем IP адрес домена

    Используем ```nslookup google.com``` 

    ```sh
    Server:  UnKnown
    Address:  192.168.100.1

    Non-authoritative answer:
    Name:    google.com
    Addresses:  2a00:1450:4001:806::200e
            172.217.16.206
    ```

    Или ```nslookup -type=ANY google.com```

    ```sh
    Server:  UnKnown
    Address:  192.168.100.1

    Non-authoritative answer:
    google.com      nameserver = ns2.google.com
    google.com      text =

            "cisco-ci-domain-verification=47c38bc8c4b74b7233e9053220c1bbe76bcc1cd33c7acf7acd36cd6a5332004b"
    google.com      text =

            "v=spf1 include:_spf.google.com ~all"
    google.com      AAAA IPv6 address = 2a00:1450:4001:810::200e
    google.com      text =

    ...
    ```

    b. Определяем DNS записи

    Используем ```ipconfig /all```

    ```sh
    Windows IP Configuration

    Host Name . . . . . . . . . . . . : DESKTOP-NS2ETAK
    Primary Dns Suffix  . . . . . . . :
    Node Type . . . . . . . . . . . . : Broadcast
    IP Routing Enabled. . . . . . . . : No
    WINS Proxy Enabled. . . . . . . . : No

    Ethernet adapter Ethernet:

    Media State . . . . . . . . . . . : Media disconnected
    Connection-specific DNS Suffix  . :
    Description . . . . . . . . . . . : Realtek PCIe GbE Family Controller
    Physical Address. . . . . . . . . : 88-A4-C2-AC-9D-B5
    DHCP Enabled. . . . . . . . . . . : Yes
    Autoconfiguration Enabled . . . . : Yes

    ...
    ```

    c. Запрашиваем MX

    Используем ```nslookup -type=MX gmail.com```

    ```sh
    Server:  UnKnown
    Address:  192.168.100.1

    Non-authoritative answer:
    gmail.com       MX preference = 40, mail exchanger = alt4.gmail-smtp-in.l.google.com
    gmail.com       MX preference = 30, mail exchanger = alt3.gmail-smtp-in.l.google.com
    gmail.com       MX preference = 20, mail exchanger = alt2.gmail-smtp-in.l.google.com
    gmail.com       MX preference = 10, mail exchanger = alt1.gmail-smtp-in.l.google.com
    gmail.com       MX preference = 5, mail exchanger = gmail-smtp-in.l.google.com
    ```

4. Часть 5 (Мини проект)

    ```sh
    #!/bin/sh

    SITE=$1
    OUTPUT_FILE="dns_report.txt"

    check_install() {
        CMD_NAME=$1      
        PKG_NAME=$2      

        if ! command -v "$CMD_NAME" >/dev/null 2>&1; then
            echo "$CMD_NAME is not installed, installing..."
            sudo apt update && sudo apt install -y "$PKG_NAME"
        else
            echo "$CMD_NAME is installed"
        fi
    }

    check_install dig bind9-dnsutils
    check_install traceroute traceroute
    check_install nmap nmap
    check_install curl curl

    A_DNS_RECORD=$(dig $SITE A +short | grep -E '^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+$')
    AAAA_DNS_RECORD=$(dig $SITE AAAA +short | grep ':')

    {
        printf "\n===== DNS-report for %s =====\n\n" "$SITE"

        printf "A (IPv4):\n"
        printf "%s\n" "$A_DNS_RECORD"

        printf "\nAAAA (IPv6):\n"
        printf "%s\n" "$AAAA_DNS_RECORD"

        printf "\n===== Traceroute to %s =====\n\n" "$SITE"

        traceroute -n $SITE | while read line; do
            HOP=$(echo $line | awk '{print $1}')
            IP=$(echo $line | awk '{for(i=2;i<=NF;i++) if($i ~ /^[0-9.]+$/) {print $i; exit}}')

            if [ -z "$IP" ]; then
                IP="*"
            fi

            printf "%2s | %s\n" "$HOP" "$IP"
        done

        printf "\n===== Open Ports (nmap) for %s =====\n\n" "$SITE"
        nmap -Pn $SITE | awk '/open/ {print $1, $3}'

        printf "\n===== HTTP headers for %s =====\n\n" "$SITE"
        curl -sS -D - -o /dev/null https://$SITE


        printf "\n===== SSL Certificate for %s =====\n\n" "$SITE"
        echo | openssl s_client -connect $SITE:443 -servername $SITE 2>/dev/null | openssl x509 -noout -dates -issuer -subject


        printf "\n===============================\n"

    } | tee "$OUTPUT_FILE"

    exit 0
    ```

5. Часть 6 (Вопросы)

    a. Чем отличаются частные и публичные IP-адреса?

        Публичные IP-адреса — уникальные адреса в интернете, через которые устройство доступно из любой точки сети (например, 8.8.8.8).

        Частные IP-адреса — используются внутри локальной сети, недоступны напрямую из интернета (например, 192.168.x.x, 10.x.x.x, 172.16.x.x–172.31.x.x).

    b. Для чего нужны порты и какие протоколы их используют?

        Порт — это «выход»/«вход» для конкретного сервиса на устройстве, позволяет одному IP-адресу обслуживать несколько приложений.

    c. Как работает DNS?

        DNS сопоставляет доменное имя (google.com) с реальным IP адресом сервера (xxx.xxx.xxx.xxx)

    d. Как определить, открыт ли порт на удалённом хосте?

    Windows:

        telnet <IP> <порт>

    Linux/macOS:

        nc -zv <IP> <порт>