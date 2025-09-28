package com.example.splab1.Application.Dtos.AuthorDTOS;

import com.example.splab1.Domain.Entities.Author;
import lombok.Data;

@Data
public class GetAuthorDTO {
    private Long id;
    private String fullName;

    public static GetAuthorDTO Map(Author author) {
        var getAuthorDTO = new GetAuthorDTO();

        getAuthorDTO.setId(author.getId());
        getAuthorDTO.setFullName(author.getFirstName() + ' ' + author.getLastName());

        return getAuthorDTO;
    }
}