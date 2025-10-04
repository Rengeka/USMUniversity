<?php

$dotenv = Dotenv\Dotenv::createImmutable(__DIR__ . '/../');
$dotenv->load();

function getPDO(): PDO {
    $config = require __DIR__ . '/../config/db.php';

    try {
        $pdo = new PDO($config['dsn'], $config['username'], $config['password']);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        return $pdo;
    } catch (PDOException $e) {
        die("Couldn't connect to database " . $e->getMessage());
    }
}