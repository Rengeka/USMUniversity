<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Recipe Book</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-100 min-h-screen">
    <header class="bg-blue-500 text-white p-4">
        <div class="container mx-auto text-center">
            <h1 class="text-3xl font-bold">Post</h1>
        </div>
    </header>

    <main class="container mx-auto px-4 py-8">
        <?php require_once __DIR__ . $page; ?>
    </main>

    <footer class="bg-blue-500 text-white p-4 mt-8 text-center">
        <p>&copy; <?= date('Y') ?> Post. All rights reserved.</p>
    </footer>
</body>
</html>
