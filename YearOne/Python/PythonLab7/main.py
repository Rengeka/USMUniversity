import datetime
import calendar
import math

def validateDate(dateString):
    try:
        datetime.datetime.strptime(dateString, "%Y-%m-%d")
        return True
    except ValueError:
        return False

def calculateAgeInDays(year, month, day):
    today = datetime.date.today()
    birthday = datetime.date(year, month, day)
    ageInDays = (today - birthday).days
    return ageInDays

def determineWeekday(year, month, day):
    weekdayNum = calendar.weekday(year, month, day)
    weekdays = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
    weekdayText = weekdays[weekdayNum]
    return weekdayText

def calculateFallTime(height):
    g = 9.8
    fallTime = math.sqrt((2 * height) / g)
    return fallTime

def main():
    # Задание 1
    while True:
        birthDate = input("Введите дату рождения в формате ГГГГ-ММ-ДД: ")
        if validateDate(birthDate):
            break
        else:
            print("Неправильный формат даты. Попробуйте снова.")

    yearOfBirth, monthOfBirth, dayOfBirth = map(int, birthDate.split('-'))
    ageInDays = calculateAgeInDays(yearOfBirth, monthOfBirth, dayOfBirth)
    print("Возраст в днях:", ageInDays)

    # Задание 2
    year, month, day = yearOfBirth, monthOfBirth, dayOfBirth
    weekday = determineWeekday(year, month, day)
    print("День недели вашего рождения:", weekday)

    # Задание 3
    while True:
        heightStr = input("Введите высоту объекта в метрах: ")

        try:
            height = float(heightStr)

            if(not math.isnan(height)):
                if height > 0:
                    break
                else:
                    print("Высота должна быть положительным числом.")
            else:
                print("Высота не является числом")
        except ValueError:
            print("Введите числовое значение.")

    fallTime = calculateFallTime(height)
    print("Время падения объекта с высоты {} метров: {:.2f} секунд".format(height, fallTime))

if __name__ == "__main__":
    main()
