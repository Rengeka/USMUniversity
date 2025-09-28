from datetime import datetime
import re

class Employee:
    def __init__(self, nameEmployee, phone, bday, email, position):

        if re.match("^[A-Za-z]+$", nameEmployee):
            self.__nameEmployee = nameEmployee
        else:
            raise ValueError("Name must contain only letters")

        if re.match("^\\+373\\d{8}$", phone):
            self.__phone = phone
        else:
            raise ValueError("Phone must match pattern +373xxxxxxxx")

        if re.match(r"^(0[1-9]|[1-2][0-9]|3[0-1])\.(0[1-9]|1[0-2])\.(19[6-9][0-9]|200[0-7])$", bday):
            self.__bday = datetime.strptime(bday, "%d.%m.%Y")
        else:
            raise ValueError("Wrong birth date")

        if re.match(r"^[a-zA-Z0-9._-]{2,20}@[a-zA-Z]{4,7}\.[a-zA-Z]{2,4}$", email):
            self.__email = email
        else:
            raise ValueError("Wrong email address")

        if re.match("^[A-Za-z]{4,20}$", position):
            self.__position = position
        else:
            raise ValueError("Specialty must contain only letters and be between 4 and 20 characters long")

    def calculateAge(self):
        today = datetime.now()
        age = today.year - self.__bday.year - ((today.month, today.day) < (self.__bday.month, self.__bday.day))
        return age

    def calculateSalary(self):
        pass

    @property
    def nameEmployee(self):
        return self.__nameEmployee

    @nameEmployee.setter
    def nameEmployee(self, value):
        self.__nameEmployee = value

    @property
    def phone(self):
        return self.__phone

    @phone.setter
    def phone(self, value):
        self.__phone = value

    @property
    def bday(self):
        return self.__bday

    @bday.setter
    def bday(self, value):
        self.__bday = value

    @property
    def email(self):
        return self.__email

    @email.setter
    def email(self, value):
        self.__email = value

    @property
    def position(self):
        return self.__position

    @position.setter
    def position(self, value):
        self.__position = value

class HourlyEmployee(Employee):
    def __init__(self, nameEmployee, phone, bday, email, position, nmbrOfHour, hourlyPay):
        super().__init__(nameEmployee, phone, bday, email, position)
        self.__nmbrOfHour = nmbrOfHour
        try:
            self.__nmbrOfHour = int(nmbrOfHour)
        except:
            raise ValueError("Wrong number of hours")

        try:
            self.__hourlyPay = int(hourlyPay)
        except:
            raise ValueError("Wrong payment per hour")


    def calculateSalary(self):
        return self.__nmbrOfHour * self.__hourlyPay

class SalaryEmployee(Employee):
    def __init__(self, nameEmployee, phone, bday, email, position, salary):
        super().__init__(nameEmployee, phone, bday, email, position)

        try:
            self.__salary = int(salary)
        except:
            raise ValueError("Wrong salary")


    def calculateSalary(self):
        return self.__salary


"""employee1 = Employee("JohnDoe", "+37312345678", "01.01.1980", "john@example.com", "Developer")
hourlyEmployee1 = HourlyEmployee("JaneSmith", "+37376543212", "15.06.1990", "jane@example.com", "Designer", 10, 40)
salaryEmployee1 = SalaryEmployee("AliceJohnson", "+37398765431", "05.03.1985", "alice@example.com", "Manager", 3000)
"""

def GetEmplInput():
    name = input()
    phone = input()
    bday = input()
    email = input()
    position = input()

    return {
        "name": name,
        "phone": phone,
        "bday": bday,
        "email": email,
        "position": position
    }

def GetHrlEmplInput():
    data = GetEmplInput()
    numberOfHours = input()
    hourlyPay = input()
    data['numberOfHours'] = numberOfHours
    data['hourlyPay'] = hourlyPay
    return data

def GetSalaryEmplInput():
    data = GetEmplInput()
    salary = input()
    data['salary'] = salary
    return data

data = GetEmplInput()
employee2 = Employee(data["name"], data["phone"], data["bday"], data["email"], data["position"])
print("Employee Salary:", employee2.calculateSalary())

data = GetHrlEmplInput()
hourlyEmployee2 = HourlyEmployee(data["name"], data["phone"], data["bday"], data["email"], data["position"], data['numberOfHours'], data['hourlyPay'])
print("Hourly Employee Salary:", hourlyEmployee2.calculateSalary())

data = GetSalaryEmplInput()
salaryEmployee2 = SalaryEmployee(data["name"], data["phone"], data["bday"], data["email"], data["position"], data['salary'])
print("Salary Employee Salary:", salaryEmployee2.calculateSalary())
