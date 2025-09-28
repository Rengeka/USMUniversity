package com.example.splab1.Application.Configs;

import com.example.splab1.Application.Services.AuthorService;
import com.example.splab1.Application.Services.BookService;
import com.example.splab1.Application.Services.CategoryService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class ServiceConfigs {

    @Bean
    public BookService bookService() {
        return new BookService();
    }

    @Bean
    public AuthorService authorService() {
        return new AuthorService();
    }

    @Bean
    public CategoryService categoryService() {
        return new CategoryService();
    }
}