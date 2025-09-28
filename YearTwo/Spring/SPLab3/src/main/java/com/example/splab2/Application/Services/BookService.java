
package com.example.splab2.Application.Services;

import com.example.splab2.Application.Dtos.BookDTOS.CreateBookDTO;
import com.example.splab2.Application.Dtos.BookDTOS.UpdateBookDTO;
import com.example.splab2.Domain.Entities.Book;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;


@Service
@RequiredArgsConstructor
public class BookService {

    private final BookHybrRepository bookRepository;
    private final AuthorService authorService;
    private final CategoryService categoryService;
    private final PublisherService publisherService;

    public List<Book> getAllBooks(){
        return bookRepository.findAll();
    }

    public Optional<Book> getBookById(Long id){
        return bookRepository.findById(id);
    }

    public void createBook(CreateBookDTO createBookDTO){
        var book = new Book();

        book.setTitle(createBookDTO.getTitle());
        book.setPublisher(publisherService.findById(createBookDTO.getAuthorId()).get());
        book.setAuthor(authorService.findById(createBookDTO.getAuthorId()).get());
        book.setCategories(new ArrayList<>(categoryService.findAllById(createBookDTO.getCategoryIds())));

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
            book.setAuthor(authorService.findById(updateBookDTO.getAuthorId()).get());
        }

        if(updateBookDTO.getCategoryIds() != null){
            book.setCategories(categoryService.findAllById(updateBookDTO.getCategoryIds()));
        }

        if(updateBookDTO.getPublisherId() != null){
           book.setPublisher(publisherService.findById(updateBookDTO.getPublisherId()).get());
        }

        bookRepository.save(book);
    }
}