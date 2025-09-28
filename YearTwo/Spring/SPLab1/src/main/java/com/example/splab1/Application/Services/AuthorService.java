package com.example.splab1.Application.Services;

import com.example.splab1.Application.Dtos.AuthorDTOS.CreateAuthorDTO;
import com.example.splab1.Application.Dtos.AuthorDTOS.GetAuthorDTO;
import com.example.splab1.Application.Dtos.AuthorDTOS.UpdateAuthorDTO;
import com.example.splab1.Domain.Entities.Author;
import com.example.splab1.Infrastructure.Repositories.AuthorRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;


@Service
public class AuthorService {

    @Autowired
    private AuthorRepository authorRepository;

    public GetAuthorDTO getAuthorById(Long id) {
        var author = authorRepository.findById(id).get();
        return GetAuthorDTO.Map(author);
    }

    public List<GetAuthorDTO> getAllAuthors() {
        var authors = authorRepository.findAll();
        return authors.stream().map(GetAuthorDTO::Map).collect(Collectors.toList());
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