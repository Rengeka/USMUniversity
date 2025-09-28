<?php 

namespace Models;

class Post
{
    public string $title;
    public string $content;
    public string $category;
    public string $timestamp; 

    public function __construct(
        string $title, 
        string $content, 
        string $category, 
        string $timestamp 
    ) {
        $this->title = $title;
        $this->content = $content;
        $this->category = $category;
        $this->timestamp = $timestamp;
    }

    public static function fromArray(array $data): Post {
        return new Post(
            $data['title'] ?? '',
            $data['content'] ?? '',
            $data['category'] ?? '',
            isset($data['timestamp']) ? strtotime($data['timestamp']) : time()
        );
    }
}