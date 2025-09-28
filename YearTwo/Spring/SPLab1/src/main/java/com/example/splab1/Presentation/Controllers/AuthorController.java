package com.example.splab1.Presentation.Controllers;

import com.example.splab1.Application.Dtos.AuthorDTOS.CreateAuthorDTO;
import com.example.splab1.Application.Dtos.AuthorDTOS.GetAuthorDTO;
import com.example.splab1.Application.Dtos.AuthorDTOS.UpdateAuthorDTO;
import com.example.splab1.Application.Services.AuthorService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/authors")
public class AuthorController {

    @Autowired
    private AuthorService authorService;

    @GetMapping
    public ResponseEntity<List<GetAuthorDTO>> getAuthors(){
        return ResponseEntity.ok(authorService.getAllAuthors());
    }

    @GetMapping("/{id}")
    public  ResponseEntity<GetAuthorDTO> getAuthor(@PathVariable Long id) {
        return ResponseEntity.ok(authorService.getAuthorById(id));
    }

    @PostMapping
    public ResponseEntity<String> createAuthor(@RequestBody CreateAuthorDTO createAuthorDTO) {
        authorService.createAuthor(createAuthorDTO);
        return ResponseEntity.ok("Author was successfully created");
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<String> deleteAuthor(@PathVariable Long id){
        authorService.deleteAuthorById(id);
        return ResponseEntity.ok("Author was successfully deleted");
    }

    @PatchMapping("/{id}")
    public ResponseEntity<String> updateAuthor(@PathVariable Long id, @RequestBody UpdateAuthorDTO updateAuthorDTO) {
        authorService.updateAuthor(id, updateAuthorDTO);
        return ResponseEntity.ok("Author was successfully updated");
    }
}