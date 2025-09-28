USE post_db; 


DROP TABLE IF EXISTS posts;

CREATE TABLE posts (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    content TEXT NOT NULL,
    category ENUM('Sport_Health', 'Food', 'Lifestyle', 'IT') NOT NULL,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT INTO posts (title, content, category, timestamp) VALUES
('Introduction to PHP', 
'PHP is a popular server-side scripting language...', 
'IT', 
'2024-03-01 10:00:00'),

('Healthy Eating Habits', 
'Eating balanced meals is crucial for maintaining good health...', 
'Food', 
'2024-03-05 14:30:00'),

('Morning Exercise Routine', 
'Start your day with these simple exercises...', 
'Sport_Health', 
'2024-03-10 08:15:00'),

('Digital Detox Tips', 
'Learn how to unplug and improve your mental health...', 
'Lifestyle', 
'2024-03-12 16:45:00'),

('Latest Web Development Trends', 
'Explore modern web development practices...', 
'IT', 
'2024-03-15 11:20:00'),

('Yoga for Beginners', 
'Basic yoga poses to improve flexibility...', 
'Sport_Health', 
'2024-03-18 09:00:00'),

('Mediterranean Diet Guide', 
'Discover the benefits of Mediterranean cuisine...', 
'Food', 
'2024-03-20 12:45:00'),

('Minimalist Living', 
'Simplify your life with these minimalist principles...', 
'Lifestyle', 
'2024-03-22 15:30:00'),

('Cybersecurity Basics', 
'Essential tips for online safety...', 
'IT', 
'2024-03-25 10:15:00'),

('Meal Prep Ideas', 
'Weekly meal preparation strategies...', 
'Food', 
'2024-03-28 17:00:00');

INSERT INTO posts (title, content, category, timestamp)
SELECT 
    CONCAT('Sample Post ', n) AS title,
    CONCAT('Content for sample post number ', n) AS content,
    ELT(FLOOR(1 + RAND() * 4), 'Sport_Health', 'Food', 'Lifestyle', 'IT') AS category,
    DATE_SUB(NOW(), INTERVAL FLOOR(RAND() * 30) DAY) AS timestamp
FROM (
    SELECT 11 AS n UNION SELECT 12 UNION SELECT 13 UNION SELECT 14 UNION SELECT 15
) numbers;