def EnterAge():

    while (True):

        age = input("Enter your age : ")
        try:
            return int(age)
        except ValueError:
            print("Invalid age. Please try again")

def EnterWeight():

    while (True):

        weight = input("Enter your current weight : ")
        try:
            return int(weight)
        except ValueError:
            print("Invalid weight. Please try again")

def EnterHeight():

    while (True):

        height = input("Enter your height (cm) : ")
        try:
            return int(height)
        except ValueError:
            print("Invalid height. Please try again")

def EnterGender():

    while (True):

        gender = input("Enter your gender : ")
        if gender == "M" or gender == "F":
            return gender
        else:
            print("Invalid gender. Please try again")
