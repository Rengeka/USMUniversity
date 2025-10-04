<?php

return [
    'dsn' => "mysql:host={$_ENV['DB_HOST']};port={$_ENV['DB_PORT']};dbname={$_ENV['DB_NAME']};charset=utf8mb4",
    'username' => $_ENV['DB_USER'],
    'password' => $_ENV['DB_PASS'],
];