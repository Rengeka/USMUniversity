import functions as menu

# Задание 1

# a

i = sum = 0   # Инициализация
while i <= 4: # Производит 5 иттераций
    sum += i
    i = i+1
print(sum)

# b

for char in 'PYTHON STRING':
  if char == ' ':
      break           # Выход из цикла
  print(char, end='') # Параметр end даёт перейти на новую строку
  if char == 'O':
      continue        # Переход на следующую иттерацию
  print('*', end='')

# Задание 2

# a

print("\nChoose one: paper, rock or scissors")
inp = input()

if inp == "paper":
    print("AI had chosen scissors. You've lost")
elif inp == "rock":
    print("AI had chosen paper. You've lost")
elif inp == "scissors":
    print("AI had chosen rock. You've lost")
else :
    print("Sorry, you've chosen an not allowed option")

# b

ls = [1,2,3,"string", 4.5, "2", 2, 1, 2]
dc = {"Mustang":"Ford", "Camara":"Chovrolet", "Challanger":"Dodge", "Escape":"Ford", "Focus":"Ford", "Golf":"Volkswagen"}

count = 0
i = 0

while i < len(ls):         #  Подсчёт количества въождений 2 в список
    if ls[i] == 2:
        count += 1
    i += 1

print(count)
count = 0

for x in dc:               # Подсчёт количества въождений "Ford" в словарь
    if dc[x] == "Ford":
        count += 1

print(count)

# c

ToCube = lambda x: x*x*x   # Лямбда функция, которая возводит в куб
print(ToCube(3))

# Задание 3

# a

lst = ["Milk", "Coffe", "Chocolate", "Strawberry", "Apple", "Pineapple", "Potato"]

input("\nPress any key to continue...")

# b

b = 1
while(b) :
    print()
    print("1.Print list of products")
    print("2.Add a product to list")
    print("3.Delete a product from list")
    print("4.Exit")

    inpt = input("\nEnter your choice: ")

    if inpt == '1':
        menu.PrintAllElements(lst)
    elif inpt == '2':
        menu.AddProduct(input("\nEnter element: "), lst)
    elif inpt == '3':
        menu.DeleteProduct(input("\nEnter element: "), lst)
    elif inpt == '4':
        b = 0