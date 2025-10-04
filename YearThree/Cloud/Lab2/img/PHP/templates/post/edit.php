<?php 

require_once '../src/db.php';

use Repositories\PostRepository;
use Services\PostService;

$pdo = getPDO();

$id = isset($_GET['id']) ? (int)$_GET['id'] : 1;

$postRepository = new PostRepository($pdo);
$postService = new PostService($postRepository);

$post = $postService->getPostById($id);

?>

<div class="max-w-2xl mx-auto bg-white p-8 rounded-2xl shadow-md">
    <h1 class="text-2xl font-bold mb-6 text-center text-gray-800">Редактировать пост</h1>

    <form action="/Lab5/src/Handlers/post/edit.php?id=<?= $id ?>" method="POST" class="space-y-4">
        <div>
            <label for="title" class="block text-gray-700 font-semibold mb-1">Заголовок</label>
            <input
                type="text"
                id="title"
                name="title"
                value="<?= htmlspecialchars($post->title) ?>"
                class="w-full border border-gray-300 p-3 rounded-xl focus:outline-none focus:ring-2 focus:ring-blue-400"
                required
            >
        </div>

        <div>
            <label for="content" class="block text-gray-700 font-semibold mb-1">Содержание</label>
            <textarea
                id="content"
                name="content"
                rows="6"
                class="w-full border border-gray-300 p-3 rounded-xl focus:outline-none focus:ring-2 focus:ring-blue-400"
                required
            ><?= htmlspecialchars($post->content) ?></textarea>
        </div>

        <div>
            <label for="category" class="block text-gray-700 font-semibold mb-1">Категория</label>
            <input
                type="text"
                id="category"
                name="category"
                value="<?= htmlspecialchars($post->category) ?>"
                class="w-full border border-gray-300 p-3 rounded-xl focus:outline-none focus:ring-2 focus:ring-blue-400"
                required
            >
        </div>

        <div class="flex justify-between mt-6">
            <a href="/lab5/public/index.php?action=post/show" class="text-blue-600 hover:underline">Отмена</a>
            <button
                type="submit"
                class="bg-blue-600 text-white px-6 py-2 rounded-xl hover:bg-blue-700 transition-colors"
            >
                Сохранить
            </button>
        </div>
    </form>
</div>