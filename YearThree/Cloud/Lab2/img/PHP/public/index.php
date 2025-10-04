<?php

require_once __DIR__ . '/../vendor/autoload.php'; 

$action = $_GET['action'] ?? '404.php';

$templates = [
    'post/create' => '/../templates/post/create.php',
    'post/show' => '/../templates/post/show.php',
    'post/edit' => '/../templates/post/edit.php',
];

$page = $templates[$action] ?? '/404.php';

include_once __DIR__ . '/../templates/layout.php';