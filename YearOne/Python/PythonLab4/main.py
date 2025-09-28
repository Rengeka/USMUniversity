import functions as funcs

age = funcs.EnterAge()
height = funcs.EnterHeight()
gender = funcs.EnterGender()
current_weight = funcs.EnterWeight()

maleIdealWeight = lambda height, current_weight, age: height - 100 - ((height - 150) / 4 + (age - 20) / 4)
maleIdealWeight(1,2,"M")


if gender == "M":
    weight = height - 100 - ((height - 150) / 4 + (age - 20) / 4)
else:
    weight = height - 100 - ((height - 150) / 2.5 + (age - 20) / 6)

print(f"Your target weight is : {weight}kg")

if current_weight > weight:
    print("You'd better to stop eating cakes!")
elif current_weight < weight:
    print("Start eating cakes!")
else:
    print("You are perfect!")
