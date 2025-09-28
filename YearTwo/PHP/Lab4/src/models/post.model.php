<?php

namespace models;

class Post
{
    public string $title;
    public string $content;
    public string $category;
    public int $timestamp;

    public function __construct(string $title, string $content, string $category) 
    {
        $this->title = $title;
        $this->content = $content;
        $this->category = $category;
        $this->timestamp = time();
    }
}