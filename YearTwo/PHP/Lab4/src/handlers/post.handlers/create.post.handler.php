<?php

require_once __DIR__ . '/../../services/post.service.php';
require_once __DIR__ . '/../../repositories/post.repository.php';
require_once __DIR__ . '/../../models/post.model.php';

use services\PostService;
use repositories\PostRepository;
use models\Post;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $title = $_POST['title'] ?? '';
    $content = $_POST['content'] ?? '';
    $category = $_POST['category'] ?? '';
    $tags = $_POST['tags'] ?? [];

    if (empty($title) || empty($content) || empty($category)) {
        $statusMessage = 'All fields are required!';
        $statusClass = 'bg-red-500';
        $buttonLink = '/create.post.php';  
    } else {
        try {
            $postRepository = new PostRepository();
            $postService = new PostService($postRepository);
            $postService->createPost($title, $content, $category);

            $statusMessage = 'Post created successfully!';
            $statusClass = 'bg-green-500';
        } catch (Exception $e) {
            $statusMessage = 'Error: ' . $e->getMessage();
            $statusClass = 'bg-red-500';
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Post Creation Status</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-50 min-h-screen flex items-center justify-center p-4 sm:p-8">

    <div class="max-w-lg w-full bg-white rounded-xl shadow-lg p-8">
        <div class="text-center">
            <div class="p-4 rounded-lg text-white <?= $statusClass ?>">
                <h2 class="text-2xl font-bold"><?= $statusMessage ?></h2>
            </div>

            <div class="mt-6">
                <a href="../../../public/index.php" 
                   class="px-6 py-3 rounded-lg bg-blue-500 text-white text-lg font-semibold hover:bg-blue-600 transition-colors duration-200">
                   To posts
                </a>
            </div>
        </div>
    </div>

</body>
</html>