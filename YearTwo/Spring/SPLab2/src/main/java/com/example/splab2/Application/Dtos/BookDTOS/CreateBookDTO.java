package com.example.splab2.Application.Dtos.BookDTOS;

import lombok.Data;

import java.util.List;

@Data
public class CreateBookDTO {
    private String title;
    private Long authorId;
    private Long publisherId;
    private List<Long> categoryIds;
}