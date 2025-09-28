
from re import L
from sys import getsizeof

# ЗАДАНИЕ 1



# 2



# Список

print('''
   List
      ''');

lis = [1, 4, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 1, 2]
print(lis)



# Вывод элементов
print(lis[0])   # Первое
print(lis[2])   # Третье



# Присваивание значения элементу списка
lis[1] = 2
print(lis)



# Срез с 4 по 11 элементы с шагом в 1 
print(lis[3:10:1]) # 4 элемент включительно, 11 - нет

# Срез с 4 по 10 элементы с шагом в 3
print(lis[3:9:3]) # 4 элемент включительно, 10 - нет

#print(crt[1:]) - с 2 по последний элемент с шагом 1
#print(crt[:4]) - с 0 по 5 элемент с шагом 1
#print(crt[1:4]) - с 2 по 5 элемент с шагом 1



# МЕТОДЫ СПИСКОВ



# Добавление элемента в конец списка
lis.append(20)
print(lis)

# Подсчёт количества вхождений числа элемента в список
print(lis.count(1))

# Получение индекса первого вхождения элемента в список
print(lis.index(2))

# Удаление элемента из список (и возврат его значения) 
# (Если вписать индекс то оно удалит по индексу, если нет то удалит последний элемент)
lis.pop()
print(lis)

# Сортировка списка во возрастанию
lis.sort() # (Может принимать и собственную функцию)
print(lis)



# ФУНКЦИИ ДЛЯ РАБОТЫ СО СПИСКАМИ

# Получение типа списка
print(type(lis))

# Получение длинны список
print(len(lis))

# Удаление списка
del(lis)



# 3



# Кортеж

print('''
   Tuple
      ''');

crt = ("Text", 2, True, 10.5)
print(crt)


# Получение типа кортежа
print(type(crt))

# Получение типа одного из элементов кортежа
print(type(crt[1]))



# Первый и последний элементы
print(crt[0])
print(crt[-1])



# Срез с 2 по 4 элементы с шагом в 1
print(crt[1:3:1]) # 2 элемент включительно, 4 - нет



# МЕТОДЫ КОРТЕЖЕЙ



# Подсчёт вхождений выбранного значения в кортеж
print(crt.count("Text"));

# Возвращает индекс первого элемента со значением, переданным внутрь
print(crt.index(True))



# ФУНКЦИИ ДЛЯ РАБОТЫ С КОРТЕЖАМИ



# Взятие элементво
print(crt)
print(crt[2:4])
print(crt[1:])

# Получение длины
print(len(crt))

# Получение размера
print(getsizeof(crt))

# Удаление
del(crt)

# 4



# Множества

print('''
   Set
      ''');

sett = {1,2,3,4,5}
print(sett)



# ФУНКЦИИ ДЛЯ РАБОТЫ С МНОЖЕСТВАМИ



# Получение длины
print(len(sett))



# МЕТОДЫ ДЛЯ РАБОТЫ С КОРТЕЖАМИ



# Добавление элемента
sett.add(6);
print(sett);

# Удаление элемента
sett.remove(6)
print(sett);



# 5



# Словари

print('''
   Dictionary
      ''');

dictt = {1:10, 2:20, 'key':5}
print(dictt)

# Получение элементов
print(dictt['key'])
print(dictt[1])



# МЕТОДЫ ДЛЯ РАБОТЫ С КОРТЕЖАМИ



# Получение элемента
print(dictt.get(1))

# Удаление элемента
dictt.pop(2)
print(dictt)

# Получение ключей 
print(dictt.keys());



# ФУНКЦИИ ДЛЯ РАБОТЫ С МНОЖЕСТВАМИ



# Получение длины
print(len(dictt))

# Преобразование типа
print(list(dictt))



# ЗАДАНИЕ 2


print('''
   Task 2
      ''');



# 1



_set = [1,2,3]
_another_set = ["PC", "PS5", "XBOX SERIES X"]

print("{} price: ${}".format(_another_set[0], _set[0]))
print("{} price: ${}".format(_another_set[1], _set[1]))
print("{} price: ${}".format(_another_set[2], _set[2]))



# 2



print("Enter your age please")

age = int(input())

print("After 5 years your age will be : " + str(age + 5) + " years")



# 3




_str = "Text"
print('x' in _str)
print('X' in _str)

tpl = (True, 2, "ABC")
print(2 in tpl);

dct = {'A':"Text1", 3:"Text2"}
print(3 in dct)
print("Text1" in dct)