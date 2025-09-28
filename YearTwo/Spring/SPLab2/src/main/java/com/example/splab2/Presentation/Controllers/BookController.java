
package com.example.splab2.Presentation.Controllers;

import com.example.splab2.Application.Dtos.BookDTOS.CreateBookDTO;
import com.example.splab2.Application.Dtos.BookDTOS.GetBookDTO;
import com.example.splab2.Application.Dtos.BookDTOS.UpdateBookDTO;
import com.example.splab2.Application.Services.BookService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/api/books")
@RequiredArgsConstructor
public class BookController {

    private final BookService bookService;

    @GetMapping
    public ResponseEntity<List<GetBookDTO>> getBooks(){
        var books = bookService.getAllBooks();
        return ResponseEntity.ok(books.stream().map(GetBookDTO::Map).collect(Collectors.toList()));
    }

    @GetMapping("/{id}")
    public ResponseEntity<GetBookDTO> getBook(@PathVariable Long id){
        var book = bookService.getBookById(id);
        return ResponseEntity.ok(GetBookDTO.Map(book.get()));
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