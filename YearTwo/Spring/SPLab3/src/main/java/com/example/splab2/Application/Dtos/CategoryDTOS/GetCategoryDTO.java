package com.example.splab2.Application.Dtos.CategoryDTOS;

import com.example.splab2.Domain.Entities.Category;
import lombok.Data;

@Data
public class GetCategoryDTO {
    private Long id;
    private String title;

    public static GetCategoryDTO Map(Category category)
    {
        var getCategoryDTO = new GetCategoryDTO();

        getCategoryDTO.setId(category.getId());
        getCategoryDTO.setTitle(category.getTitle());

        return getCategoryDTO;
    }
}