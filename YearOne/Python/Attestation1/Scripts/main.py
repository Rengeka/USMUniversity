
import functions as menu

authors = {}

IsExecuting = 1

while(IsExecuting) :

    print("\n1.Print list of authors")
    print("2.Count books for each author")
    print("3.Add an author")
    print("4.Add a book to author")
    print("5.Delete an author")
    print("6.Exit")

    inpt = input("\nEnter your choice: ")

    if inpt == '1':
        menu.PrintAuthorsData(authors)

    elif inpt == '2':
        menu.CountBooksForEachAuthor(authors)

    elif inpt == '3':

        print("Enter author please")
        authorName = input()

        if authorName != "":
            menu.AddAuthor(authors, authorName)
        else:
            print("You've entered an incorrect author name")

    elif inpt == '4':
        print("Enter author please")
        authorName = input()

        print("Enter book please")
        book = input()

        if book != "" and authorName != "":
            menu.AddBook(authors, authorName, book)
        else:
            print("You've entered an incorrect book or author names")

    elif inpt == '5':
        print("Enter author please")
        authorName = input()

        if authorName != "":
            menu.DeleteAuthor(authors, "Stephen King")
        else:
            print("You've entered an incorrect author name")

    elif inpt == '6':
        IsExecuting = 0
        print("Thank you for using my program!")

    else :
        print("You've entered an not allowed option. Please try again")