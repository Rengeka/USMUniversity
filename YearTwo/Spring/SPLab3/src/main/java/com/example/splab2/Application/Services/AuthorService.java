package com.example.splab2.Application.Services;

import com.example.splab2.Application.Dtos.AuthorDTOS.CreateAuthorDTO;
import com.example.splab2.Application.Dtos.AuthorDTOS.UpdateAuthorDTO;
import com.example.splab2.Infrastructure.Repositories.Hybrnate.AuthorJDBCRepository;
import jakarta.transaction.Transactional;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
@Transactional
public class AuthorService {

    private final AuthorJDBCRepository authorRepository;

    public Optional<Author> findById(Long id) {
        return authorRepository.findById(id);
    }

    public List<Author> findAll() {
        return authorRepository.findAll();
    }

    public void createAuthor(CreateAuthorDTO createAuthorDTO) {
        var author = new Author();

        author.setFirstName(createAuthorDTO.getFirstName());
        author.setLastName(createAuthorDTO.getLastName());

        authorRepository.save(author);
    }

    public void deleteAuthorById(Long id){
        authorRepository.deleteById(id);
    }

    public void updateAuthor(Long id, UpdateAuthorDTO updateAuthorDTO) {
        var author = authorRepository.findById(id).get();

        if(updateAuthorDTO.getFirstName() != null){
            author.setFirstName(updateAuthorDTO.getFirstName());
        }

        if(updateAuthorDTO.getLastName() != null){
            author.setLastName(updateAuthorDTO.getLastName());
        }

        authorRepository.save(author);
    }
}