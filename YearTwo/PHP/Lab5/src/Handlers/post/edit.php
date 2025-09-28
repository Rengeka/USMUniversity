<?php

declare(strict_types=1);

namespace Handlers\Post;

require_once __DIR__ . '/../../../vendor/autoload.php';
require_once __DIR__ . '/../../db.php';


use Services\PostService;
use PDO;
use Repositories\PostRepository;

if ($_SERVER['REQUEST_METHOD'] !== 'PATCH') {
    http_response_code(405);
    echo "Method Not Allowed";
}

$pdo = getPDO();

$repository = new PostRepository($pdo);
$service = new PostService($repository);

$id = isset($_GET['id']) ? (int)$_GET['id'] : 0;
$title = isset($_POST['title']) ? trim($_POST['title']) : '';
$content = isset($_POST['content']) ? trim($_POST['content']) : '';
$category = isset($_POST['category']) ? trim($_POST['category']) : '';

$service->updatePost($id, $title, $content, $category);

header('Location: /Lab5/public/index.php?action=post/show');