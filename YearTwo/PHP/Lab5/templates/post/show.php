<?php

require_once '../src/db.php';

use Repositories\PostRepository;
use Services\PostService;

$pdo = getPDO();

$page = isset($_GET['page']) ? (int)$_GET['page'] : 1;

$postRepository = new PostRepository($pdo);
$postService = new PostService($postRepository);

$posts = $postService->getPosts($page);

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Forum Posts</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-100 min-h-screen">
    <div class="container mx-auto px-4 py-8 max-w-2xl">
        <?php foreach ($posts as $post): ?>
            <?php renderPost($post); ?>
        <?php endforeach; ?>

        <div class="text-center mt-8">
            <a href="?action=post/show&&page=<?= $page + 1 ?>" class="px-4 py-2 bg-blue-500 text-white rounded-lg hover:bg-blue-600">
                Next page
            </a>
        </div>
    </div>

    <a href="http://localhost/Lab5/public/index.php/?action=post/create" id="add-post-btn" class="fixed bottom-8 right-8 p-4 bg-blue-500 text-white rounded-full shadow-lg hover:bg-blue-600 transition-colors duration-200">
        <svg class="w-6 h-6" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 4v16m8-8H4"></path>
        </svg>
    </a>
</body>
</html>

<?php

function renderPost($post) {
    ?>
    <div class="bg-white rounded-lg shadow-md mb-6 p-6 hover:shadow-lg transition-shadow duration-200">
        <div class="mb-3">
            <span class="inline-block bg-blue-100 text-blue-800 text-sm font-medium px-2.5 py-0.5 rounded-full">
                <?= htmlspecialchars($post->category) ?>
            </span>
        </div>

        <h2 class="text-xl font-bold text-gray-900 mb-2 hover:text-blue-600 transition-colors duration-200">
            <?= htmlspecialchars($post->title) ?>
        </h2>

        <p class="text-gray-700 mb-4 leading-relaxed">
            <?= htmlspecialchars($post->content) ?>
        </p>

        <div class="flex items-center justify-between text-sm text-gray-500">
            <div class="flex items-center space-x-2">
                <svg class="w-4 h-4" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 8v4l3 3m6-3a9 9 0 11-18 0 9 9 0 0118 0z"></path>
                </svg>
                <span><?= date('M j, Y \a\t g:i a', $post->timestamp) ?></span>
            </div>
            <div class="flex items-center space-x-4">
                <button class="flex items-center hover:text-blue-600 transition-colors duration-200">
                    <svg class="w-5 h-5 mr-1" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M5 15l7-7 7 7"></path>
                    </svg>
                    <span>Upvote</span>
                </button>
                <button class="flex items-center hover:text-blue-600 transition-colors duration-200">
                    <svg class="w-5 h-5 mr-1" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M8 12h.01M12 12h.01M16 12h.01M21 12c0 4.418-4.03 8-9 8a9.863 9.863 0 01-4.255-.949L3 20l1.395-3.72C3.512 15.042 3 13.574 3 12c0-4.418 4.03-8 9-8s9 3.582 9 8z"></path>
                    </svg>
                    <span>Comments</span>
                </button>
                <button class="flex items-center hover:text-blue-600 transition-colors duration-200">
                    <svg class="w-5 h-5 mr-1" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M8.684 13.342C8.886 12.938 9 12.482 9 12c0-.482-.114-.938-.316-1.342m0 2.684a3 3 0 110-2.684m0 2.684l6.632 3.316m-6.632-6l6.632-3.316m0 0a3 3 0 105.367-2.684 3 3 0 00-5.367 2.684zm0 9.316a3 3 0 105.368 2.684 3 3 0 00-5.368-2.684z"></path>
                    </svg>
                    <span>Share</span>
                </button>
            </div>
        </div>
    </div>
    <?php
}
