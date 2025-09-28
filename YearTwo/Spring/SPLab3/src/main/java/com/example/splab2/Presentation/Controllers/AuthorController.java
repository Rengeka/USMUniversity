package com.example.splab2.Presentation.Controllers;

import com.example.splab2.Application.Dtos.AuthorDTOS.CreateAuthorDTO;
import com.example.splab2.Application.Dtos.AuthorDTOS.GetAuthorDTO;
import com.example.splab2.Application.Dtos.AuthorDTOS.UpdateAuthorDTO;
import com.example.splab2.Application.Services.AuthorService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/api/authors")
@RequiredArgsConstructor
public class AuthorController {

    private final AuthorService authorService;

    @GetMapping
    public ResponseEntity<List<GetAuthorDTO>> getAuthors(){
        var authors = authorService.findAll();
        return ResponseEntity.ok(authors.stream().map(GetAuthorDTO::Map).collect(Collectors.toList()));
    }

    @GetMapping("/{id}")
    public ResponseEntity<GetAuthorDTO> getAuthor(@PathVariable Long id) {
        var author = authorService.findById(id);
        return ResponseEntity.ok(GetAuthorDTO.Map(author.get()));
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