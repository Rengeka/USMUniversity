-- Insert test data into Authors
INSERT INTO Authors (id, first_name, last_name) VALUES
    (1, 'John', 'Doe'),
    (2, 'Jane', 'Smith'),
    (3, 'Emily', 'Johnson');

-- Insert test data into Publishers
INSERT INTO Publishers (id, title) VALUES
    (1, 'Penguin Books'),
    (2, 'HarperCollins'),
    (3, 'Random House');

-- Insert test data into Categories
INSERT INTO Categories (id, title) VALUES
    (1, 'Science Fiction'),
    (2, 'Fantasy'),
    (3, 'Mystery');

-- Insert test data into Books
INSERT INTO Books (id, title, author_Id, publisher_Id) VALUES
    (1, 'Galactic Adventures', 1, 1),
    (2, 'The Enchanted Forest', 2, 2),
    (3, 'Mystery at the Manor', 3, 3);

-- Insert test data into Books_Categories
INSERT INTO Books_Categories (book_Id, category_Id) VALUES
    (1, 1),
    (2, 2),
    (3, 3);

-- Insert test data into Libraries
INSERT INTO Libraries (id) VALUES
    (1),
    (2),
    (3);

-- Insert test data into Books_Libraries
INSERT INTO Books_Libraries (library_Id, book_Id) VALUES
    (1, 1),
    (1, 2),
    (2, 3),
    (3, 1),
    (3, 3);