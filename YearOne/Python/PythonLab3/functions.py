def AddProduct(element, lst):
    lst.append(element)

def DeleteProduct(element, lst):
    try:
        lst.remove(element)
    except:
        print("Sorry, but there is no such element")

def PrintAllElements(lst):
    i = 1
    print()
    for x in lst:
        print (str(i) + "." + x)
        i += 1