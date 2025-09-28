<?php

namespace services;

require_once __DIR__ . '/../../src/repositories/post.repository.php';

use repositories\PostRepository;
use models\Post;

class PostService {

    private PostRepository $repository;

    public function __construct(PostRepository $repository) {
        $this->repository = $repository;
    }

    /**
     * Create new post
     * 
     * @param string $title
     * @param string $content
     * @param string $category
     * @return void
     * @throws Exception
     */
    public function createPost(string $title, string $content, string $category): void {
        $post = new Post($title, $content, $category);
        $this->repository->save($post);
    }

    public function getPosts(int $page = 1, int $perPage = 5): array{
        return $this->repository->findPaginated($page, $perPage);
    }

}