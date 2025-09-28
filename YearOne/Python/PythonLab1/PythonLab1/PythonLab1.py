
from asyncio.windows_events import NULL

# Task 1

# (3)
print("Greetings. Please, enter your name")
name = input()
print("Your name is : " + name)

# (4)
integer_variable = 20
float_variable = 20.2
short_text_variable = "TeXt"
multiline_text_variable = """Text that
is text"""

# (5)
print("\nType of integer_variable is :", type(integer_variable))
print("Type of multiline_text_variable is :", type(multiline_text_variable))

# (6)
print("Size of short_text_variable (" + short_text_variable + ") is : ", len(short_text_variable))

# (7)
print(short_text_variable.lower())
print(short_text_variable.upper())

# (8)
print(multiline_text_variable[2:9])

# Task 2

# (a)
txt = "More results from text..."
print(txt);
substr = txt[4:12]
print(substr)
print(substr.strip())

# (b)
print(txt.split()) 

# (c)
age = 36
size = 170
txt2 = "My name is Mary, and I am {} {}"
print(txt2.format(age, size))



