<?php

namespace FluetnDI\Http;

enum HttpMethod: string
{
    case Get = 'GET';
    case Post = 'POST';
    case Delete = 'DELETE';
    case Put = 'PUT';
    case Patch = 'PATCH';
    case Trace = 'TRACE';
    case Connect = 'CONNECT';
    case Head = 'HEAD';
    case Options = 'OPTIONS';
}