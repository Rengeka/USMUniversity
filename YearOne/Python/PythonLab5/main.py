import re


def StartMenu():
    while True:
        print("\nМеню:")
        print("1. Ввод данных в файл")
        print("2. Просмотр данных о детях сотрудников")
        print("3. Вывод списка бездетных сотрудников")
        print("4. Выход из программы")
        choice = input("Выберите опцию: ")

        if choice == '1':
            InputData()
        elif choice == '2':
            PrintData()
        elif choice == '3':
            PrintChildlessEmployees()
        elif choice == '4':
            print("Выход из программы")
            break
        else:
            print("Неверная опция. Пожалуйста попробуйте снова")


def InputData():
    while True:
        surname = input("Введите фамилию сотрудника: ")

        if not re.match(r'^[a-zA-Z]+(?:-[a-zA-Z]+)?$', surname):
            print("Фамилия должна содержать только буквы и может содержать один знак '-'")
            continue

        name = input("Введите имя сотрудника: ")
        if not re.match(r'^[a-zA-Z]+(?:-[a-zA-Z]+)?$', name):
            print("Имя должно содержать только буквы и может содержать один знак '-'")
            continue

        department = input("Введите отдел, в котором работает сотрудник: ")
        if not re.match(r'^[a-zA-Z0-9]+$', department):
            print("Название отдела должно состоять из букв, цифр и пробелов")
            continue

        try:
            children = int(input("Введите количество детей младше 18 лет: "))
            if not (0 <= children <= 19):
                print("Количество детей должно быть от 0 до 19")
                continue
        except ValueError:
            print("Количество детей должно быть целым числом")
            continue

        with open("data.txt", "a") as file:
            file.write(f"{surname}\\t{name}\\t{department}\\t{children}\n")

        print("Данные успешно сохранены.")
        break


def PrintData():
    total_children = 0

    with open("data.txt", "r") as file:
        for line in file:
            if line:
                surname, name, department, children = line.strip().split('\\t')
                total_children += int(children)
                print(f"{surname} {name} работает в отделе {department} и имеет {children} детей.")
    print(f"Общее количество детей: {total_children}")



def PrintChildlessEmployees():
    childless = []

    with open("data.txt", "r") as file:
        for line in file:
            if line:
                surname, name, department, children = line.strip().split('\\t')

                if(int(children) == 0):
                    childless.append((surname, name))

    if childless:
        print("\nСписок бездетных сотрудников:")
        for surname, name in childless:
            print(f"{surname} {name}")
    else:
        print("Нет бездетных сотрудников.")

StartMenu()