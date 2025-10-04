<?php

namespace Services;

use Repositories\PostRepository;
use Models\Post;
use Exception;

class PostService
{
    private PostRepository $repository;

    public function __construct(PostRepository $repository)
    {
        $this->repository = $repository;
    }

    /**
     * Create a new post.
     *
     * @param string $title
     * @param string $content
     * @param string $category
     * @return void
     * @throws Exception
     */
    public function createPost(string $title, string $content, string $category): void
    {
        $post = new Post($title, $content, $category, time());
        $this->repository->create($post);
    }

    /**
     * Get paginated posts.
     *
     * @param int $page
     * @param int $perPage
     * @return Post[]
     */
    public function getPosts(int $page = 1, int $perPage = 5): array
    {
        return $this->repository->getPage($page, $perPage);
    }

    /**
     * Get a single post by its ID.
     *
     * @param int $id
     * @return Post|null
     */
    public function getPostById(int $id): ?Post
    {
        return $this->repository->find($id);
    }

    /**
     * Update an existing post.
     *
     * @param int $id
     * @param string $title
     * @param string $content
     * @param string $category
     * @return bool
     */
    public function updatePost(int $id, string $title, string $content, string $category): bool
    {
        $post = new Post($title, $content, $category, time());
        return $this->repository->update($id, $post);
    }

    /**
     * Delete a post by its ID.
     *
     * @param int $id
     * @return bool
     */
    public function deletePost(int $id): bool
    {
        return $this->repository->delete($id);
    }
}