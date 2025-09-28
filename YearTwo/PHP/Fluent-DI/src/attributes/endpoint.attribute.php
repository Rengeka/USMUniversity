<?php

namespace FluetnDI\Http;

use Attribute;
use FluetnDI\Http\HttpMethod; 

#[Attribute(Attribute::TARGET_CLASS)]
class Endpoint
{
    public string $path;
    public HttpMethod $method;

    public function __construct(string $path, HttpMethod $method) 
    {
        $this->path = $path;
        $this->method = $method;
    }
}