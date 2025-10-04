<?php

namespace Repositories;

use Models\Post;
use PDO;

class PostRepository
{
    private PDO $pdo;

    public function __construct(PDO $pdo)
    {
        $this->pdo = $pdo;
    }

    /**
     * Get posts for a specific page.
     * 
     * @param int $page Page number (1-based).
     * @param int $perPage Number of posts per page.
     * @return Post[] Array of posts for the requested page.
     */
    public function getPage(int $page = 1, int $perPage = 5): array
    {
        $offset = ($page - 1) * $perPage;
        
        $stmt = $this->pdo->prepare("
            SELECT * 
            FROM posts 
            ORDER BY timestamp DESC 
            LIMIT :limit OFFSET :offset
        ");
        
        // Bind parameters with explicit type casting
        $stmt->bindValue(':limit', $perPage, PDO::PARAM_INT);
        $stmt->bindValue(':offset', $offset, PDO::PARAM_INT);

        $stmt->execute();
        $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

        return array_map(function($row) {
            return Post::fromArray([
                'title' => $row['title'],
                'content' => $row['content'],
                'category' => $row['category'],
                'timestamp' => $row['timestamp']
            ]);
        }, $rows);
    }

    /**
     * Find post by ID
     * @param int $id
     * @return Post|null
     */
    public function find(int $id): ?Post
    {
        $stmt = $this->pdo->prepare("SELECT * FROM posts WHERE id = :id");
        $stmt->execute(['id' => $id]);
        $post = $stmt->fetch(PDO::FETCH_ASSOC);
        return $post ? Post::fromArray($post) : null;
    }

    /**
     * Create a new post
     * @param Post $post
     * @return int ID of the newly created post
     */
    public function create(Post $post): int
    {
        $stmt = $this->pdo->prepare(
            "INSERT INTO posts (title, content, category, timestamp) VALUES (:title, :content, :category, :timestamp)"
        );
        $stmt->execute([
            'title' => $post->title,
            'content' => $post->content,
            'category' => $post->category,
            'timestamp' => date('Y-m-d H:i:s', $post->timestamp),
        ]);
        return (int) $this->pdo->lastInsertId();
    }

    /**
     * Update an existing post
     * @param int $id
     * @param Post $post
     * @return bool
     */
    public function update(int $id, Post $post): bool
    {
        $stmt = $this->pdo->prepare(
            "UPDATE posts SET title = :title, content = :content, category = :category WHERE id = :id"
        );
        return $stmt->execute([
            'id' => $id,
            'title' => $post->title,
            'content' => $post->content,
            'category' => $post->category
        ]);
    }

    /**
     * Delete a post by ID
     * @param int $id
     * @return bool
     */
    public function delete(int $id): bool
    {
        $stmt = $this->pdo->prepare("DELETE FROM posts WHERE id = :id");
        return $stmt->execute(['id' => $id]);
    }
}