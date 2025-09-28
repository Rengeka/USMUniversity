/*

DROP TABLE Books_Categories;
DROP TABLE Books_Libraries
DROP TABLE Libraries
DROP TABLE Categories;
DROP TABLE Books;
DROP TABLE Authors;
DROP TABLE Publishers;
*/


-- DROP TABLE Authors
CREATE TABLE Authors(
   id INT NOT NULL PRIMARY KEY,
   first_name VARCHAR(255) NOT NULL ,
   last_name VARCHAR(255) NOT NULL
);

-- DROP TABLE Publishers
CREATE TABLE Publishers(
    id INT NOT NULL PRIMARY KEY,
    title VARCHAR(255) NOT NULL
);

-- DROP TABLE Categories
CREATE TABLE Categories(
    id INT NOT NULL PRIMARY KEY,
    title VARCHAR(255) NOT NULL
);

-- DROP TABLE Books
CREATE TABLE Books (
    id INT NOT NULL PRIMARY KEY,
    title VARCHAR(255),
    author_Id INT NOT NULL,
    publisher_Id INT NOT NULL,
    CONSTRAINT FK_AUTHOR FOREIGN KEY (author_Id) REFERENCES Authors(id),
    CONSTRAINT FK_PUBLISHER FOREIGN KEY (publisher_Id) REFERENCES Publishers(id)
);

-- DROP TABLE Books_Categories
CREATE TABLE Books_Categories(
    book_Id INT NOT NULL,
    category_Id INT NOT NULL,
    PRIMARY KEY (book_Id, category_Id),
    CONSTRAINT FK_BOOK FOREIGN KEY (book_Id) REFERENCES Books(id),
    CONSTRAINT FK_CATEGORY FOREIGN KEY (category_Id) REFERENCES Categories(id)
);

-- DROP TABLE Libraries
CREATE TABLE Libraries(
    id INT NOT NULL PRIMARY KEY
);

-- DROP TABLE BooksAndLibraries
CREATE TABLE Books_Libraries(
    library_Id INT NOT NULL,
    book_Id INT NOT NULL,
    PRIMARY KEY (library_Id, book_Id),
    CONSTRAINT FK_BOOK FOREIGN KEY (book_Id) REFERENCES Books(id),
    CONSTRAINT FK_LIBRARY FOREIGN KEY (library_Id) REFERENCES Libraries(id)
);