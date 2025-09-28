
package com.example.splab2.Application.Services;

import com.example.splab2.Application.Dtos.CategoryDTOS.CreateCategoryDTO;
import com.example.splab2.Application.Dtos.CategoryDTOS.UpdateCategoryDTO;
import com.example.splab2.Domain.Entities.Category;
import com.example.splab2.Infrastructure.Repositories.Hybrnate.CategoryHybrRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class CategoryService {

    private final CategoryHybrRepository categoryRepository;

    public Optional<Category> findById(Long id){
        return categoryRepository.findById(id);
    }

    public List<Category> findAll(){
        return categoryRepository.findAll();
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

    public List<Category> findAllById(List<Long> ids){
        return categoryRepository.findAllById(ids);
    }
}