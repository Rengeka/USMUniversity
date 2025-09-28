package com.example.splab1.Application.Services;

import com.example.splab1.Application.Dtos.CategoryDTOS.CreateCategoryDTO;
import com.example.splab1.Application.Dtos.CategoryDTOS.GetCategoryDTO;
import com.example.splab1.Application.Dtos.CategoryDTOS.UpdateCategoryDTO;
import com.example.splab1.Domain.Entities.Category;
import com.example.splab1.Infrastructure.Repositories.CategoryRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
public class CategoryService {

    @Autowired
    private CategoryRepository categoryRepository;

    public GetCategoryDTO getCategoryById(Long id){
        var category = categoryRepository.findById(id).get();
        return GetCategoryDTO.Map(category);
    }

    public List<GetCategoryDTO> getAllCategories(){
        var categories = categoryRepository.findAll();
        return categories.stream().map(GetCategoryDTO::Map).collect(Collectors.toList());
    }

    public void createCategory(CreateCategoryDTO createCategoryDTO){
        var category = new Category();
        category.setTitle(createCategoryDTO.getTitle());
    }

    public void deleteCategoryById(Long id){
        categoryRepository.deleteById(id);
    }

    public void updateCategory(Long id, UpdateCategoryDTO updateCategoryDTO) {
        var category = categoryRepository.findById(id).get();

        if(updateCategoryDTO.getTitle() != null){
            category.setTitle(updateCategoryDTO.getTitle());
        }

        categoryRepository.save(category);
    }
}