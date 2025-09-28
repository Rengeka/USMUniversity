package com.example.splab2.Application.Dtos.BookDTOS;

import com.example.splab2.Domain.Entities.Book;
import com.example.splab2.Domain.Entities.Category;
import lombok.Data;

import java.util.List;

@Data
public class GetBookDTO {
    private Long id;
    private String title;
    private String authorName;
    private List<String> categories;

    public static GetBookDTO Map(Book book) {
        var getBookDTO = new GetBookDTO();

        getBookDTO.setId(book.getId());
        getBookDTO.setTitle(book.getTitle());
        getBookDTO.setAuthorName(book.getAuthor().getFirstName() + " " + book.getAuthor().getLastName());
        getBookDTO.setCategories(book.getCategories().stream().map(Category::getTitle).toList());

        return getBookDTO;
    }
}