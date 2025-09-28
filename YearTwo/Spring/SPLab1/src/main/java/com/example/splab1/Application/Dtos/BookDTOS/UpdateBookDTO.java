package com.example.splab1.Application.Dtos.BookDTOS;

import lombok.Data;

import java.util.List;

@Data
public class UpdateBookDTO {
    private String title;
    private Long authorId;
    private List<Long> categoryIds;
    private Long publisherId;
}