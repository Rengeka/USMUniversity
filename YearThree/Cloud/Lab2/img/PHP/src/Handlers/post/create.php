<?php

declare(strict_types=1);

namespace Handlers\Post;

require_once __DIR__ . '/../../../vendor/autoload.php';
require_once __DIR__ . '/../../db.php';


use Services\PostService;
use PDO;
use Repositories\PostRepository;

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405);
    echo "Method Not Allowed";
}

$pdo = getPDO();

$repository = new PostRepository($pdo);
$service = new PostService($repository);

$title = trim($_POST['title'] ?? '');
$content = trim($_POST['content'] ?? '');
$category = trim($_POST['category'] ?? '');

$service->createPost($title, $content, $category);

header('Location: http://localhost/Lab5/public/index.php/?action=post/show');