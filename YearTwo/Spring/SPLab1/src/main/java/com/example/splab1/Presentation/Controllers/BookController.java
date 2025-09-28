package com.example.splab1.Presentation.Controllers;

import com.example.splab1.Application.Dtos.BookDTOS.CreateBookDTO;
import com.example.splab1.Application.Dtos.BookDTOS.UpdateBookDTO;
import com.example.splab1.Application.Services.BookService;
import com.example.splab1.Application.Dtos.BookDTOS.GetBookDTO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/books")
public class BookController {

    @Autowired
    private BookService bookService;

    @GetMapping
    public ResponseEntity<List<GetBookDTO>> getBooks(){
        return ResponseEntity.ok(bookService.getAllBooks());
    }

    @GetMapping("/{id}")
    public ResponseEntity<GetBookDTO> getBook(@PathVariable Long id){
        return ResponseEntity.ok(bookService.getBookById(id));
    }

    @PostMapping
    public ResponseEntity<String> createBook(@RequestBody CreateBookDTO createBookDto){
        bookService.createBook(createBookDto);
        return ResponseEntity.ok("Book was successfully created");
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<String> deleteBook(@PathVariable Long id){
        bookService.deleteBookById(id);
        return ResponseEntity.ok("Book was successfully deleted");
    }

    @PatchMapping("/{id}")
    public ResponseEntity<String> updateBook(@PathVariable Long id, @RequestBody UpdateBookDTO updateBookDto) {
        bookService.updateBook(id, updateBookDto);
        return ResponseEntity.ok("Book was successfully updated");
    }
}