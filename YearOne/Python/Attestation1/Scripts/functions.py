def AddAuthor(authorsDict, authorName):
    if authorName not in authorsDict:
        authorsDict[authorName] = []
    else:
        print("This author does not exist")

def AddBook(authorsDict, authorName, book):
    if authorName in authorsDict:
        authorsDict[authorName].append(book)
        print("Book was successfully added")
    else:
        print("This author does not exist")

def PrintAuthorsData(authorsDict):
    if authorsDict != {} :
        for author in authorsDict:
            if authorsDict[author] == []:
                print(f"{author} : No books found")
            else:
                books = ", ".join(authorsDict[author])  # Чтобы не было [] при выводе списка на экран
                print(f"{author} : {books}")
    else :
        print("No authors found")

def CountBooksForEachAuthor(authorsDict):
    if authorsDict != {}:
        for author in authorsDict:
            print(f"{author} : {len(authorsDict[author])}")
    else :
        print("No authors found")

def DeleteAuthor(authorsDict, authorName):
    if authorName in authorsDict:
        del authorsDict[authorName]
        print("Author was successfully deleted")
    else:
        print("This author does not exist")