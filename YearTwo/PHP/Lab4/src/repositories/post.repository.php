<?php

namespace repositories;

require_once __DIR__ . '/../../src/models/post.model.php';

use models\Post;
use Exception;

class PostRepository
{
    private string $filePath;

    public function __construct()
    {
        $this->filePath = __DIR__ . '/../../storage/posts.json';
    }

    /**
     * @return Post[]
     * @throws Exception
     */
    public function findAll(): array
    {
        if (!file_exists($this->filePath)) {
            throw new Exception("Posts file not found");
        }

        $content = file_get_contents($this->filePath);
        if ($content === false) {
            throw new Exception("Could not read posts file");
        }

        $data = json_decode($content, true);
        if (json_last_error() !== JSON_ERROR_NONE) {
            throw new Exception("Invalid JSON format in posts file");
        }

        return array_map(function(array $postData) {
            return new Post(
                $postData['title'],
                $postData['content'],
                $postData['category']
            );
        }, $data);
    }

    /**
     * @return Post[]
     * @throws Exception
     */
    public function findLatest(int $count = 5): array
    {
        $posts = $this->findAll();
        usort($posts, fn($a, $b) => $b->timestamp <=> $a->timestamp);
        return array_slice($posts, 0, $count);
    }

    public function findPaginated(int $page = 1, int $perPage = 5): array
    {
        $posts = $this->findAll();
        usort($posts, fn($a, $b) => $b->timestamp <=> $a->timestamp);

        $offset = ($page - 1) * $perPage;
        return array_slice($posts, $offset, $perPage);
    }

    /**
     * @throws Exception
     */
    public function save(Post $post): void
    {
        $posts = $this->findAll();
        $posts[] = $post;
        $this->saveAll($posts);
    }

    /**
     * @param Post[] $posts
     * @throws Exception
     */
    public function saveAll(array $posts): void
    {
        $data = array_map(fn(Post $post) => [
            'title' => $post->title,
            'content' => $post->content,
            'category' => $post->category,
            'timestamp' => $post->timestamp
        ], $posts);

        $result = file_put_contents(
            $this->filePath,
            json_encode($data, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE)
        );

        if ($result === false) {
            throw new Exception("Could not save posts to file");
        }
    }
}