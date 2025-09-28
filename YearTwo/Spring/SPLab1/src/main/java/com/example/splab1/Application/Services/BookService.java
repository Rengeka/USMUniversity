package com.example.splab1.Application.Services;

import com.example.splab1.Application.Dtos.BookDTOS.CreateBookDTO;
import com.example.splab1.Application.Dtos.BookDTOS.UpdateBookDTO;
import com.example.splab1.Domain.Entities.Book;
import com.example.splab1.Infrastructure.Repositories.AuthorRepository;
import com.example.splab1.Infrastructure.Repositories.BookRepository;
import com.example.splab1.Application.Dtos.BookDTOS.GetBookDTO;
import com.example.splab1.Infrastructure.Repositories.CategoryRepository;
import com.example.splab1.Infrastructure.Repositories.PublishRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;


@Service
public class BookService {

    @Autowired
    private BookRepository bookRepository;
    @Autowired
    private AuthorRepository authorRepository;
    @Autowired
    private PublishRepository publishRepository;
    @Autowired
    private CategoryRepository categoryRepository;

    public List<GetBookDTO> getAllBooks(){
        var books = bookRepository.findAll();
        return books.stream().map(GetBookDTO::Map).collect(Collectors.toList());
    }

    public GetBookDTO getBookById(Long id){
        var book = bookRepository.findById(id).get();
        return GetBookDTO.Map(book);
    }

    public void createBook(CreateBookDTO createBookDTO){
        var book = new Book();

        book.setTitle(createBookDTO.getTitle());
        book.setPublisher(publishRepository.findById(createBookDTO.getAuthorId()).get());
        book.setAuthor(authorRepository.findById(createBookDTO.getAuthorId()).get());
        book.setCategories(new ArrayList<>(categoryRepository.findAllById(createBookDTO.getCategoryIds())));

        bookRepository.save(book);
    }

    public void deleteBookById(Long id){
        bookRepository.deleteById(id);
    }

    public void updateBook(Long id, UpdateBookDTO updateBookDTO){
        var book = bookRepository.findById(id).get();

        if(updateBookDTO.getTitle() != null){
            book.setTitle(updateBookDTO.getTitle());
        }

        if(updateBookDTO.getAuthorId() != null){
            book.setAuthor(authorRepository.findById(updateBookDTO.getAuthorId()).get());
        }

        if(updateBookDTO.getCategoryIds() != null){
            book.setCategories(categoryRepository.findAllById(updateBookDTO.getCategoryIds()));
        }

        if(updateBookDTO.getPublisherId() != null){
            book.setPublisher(publishRepository.findById(updateBookDTO.getPublisherId()).get());
        }

        bookRepository.save(book);
    }
}