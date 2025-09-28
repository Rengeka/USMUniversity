"""import module_manager

manager1 = module_manager.manager("Name", 123)
print(manager1.budget)
print(manager1.get_project_name())
manager1.set_project_name("New Name")
print(manager1.get_project_name())


manager2 = module_manager.manager("man2", "123")
print(manager2.budget)
print(manager2.get_project_name())
manager2.set_project_name("Mannnn2")
print(manager2.get_project_name())"""


my_data = [(1,3), (2,9)]

print(type(my_data))
print(len(my_data))
print(my_data[2:])

for i in my_data:
    print(i, end='')
    print("**", end='')

print()

my_data.append((8,3))
print(my_data)