package com.example.splab1.Presentation.Controllers;

import com.example.splab1.Application.Dtos.CategoryDTOS.CreateCategoryDTO;
import com.example.splab1.Application.Dtos.CategoryDTOS.GetCategoryDTO;
import com.example.splab1.Application.Dtos.CategoryDTOS.UpdateCategoryDTO;
import com.example.splab1.Application.Services.CategoryService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/categories")
public class CategoryController {

    @Autowired
    CategoryService categoryService;

    @GetMapping
    public ResponseEntity<List<GetCategoryDTO>> getCategories(){
        return ResponseEntity.ok(categoryService.getAllCategories());
    }

    @GetMapping("/{id}")
    public ResponseEntity<GetCategoryDTO> getCategory(@PathVariable Long id) {
        return ResponseEntity.ok(categoryService.getCategoryById(id));
    }

    @PostMapping
    public ResponseEntity<String> createCategory(@RequestBody CreateCategoryDTO createCategoryDTO) {
        categoryService.createCategory(createCategoryDTO);
        return ResponseEntity.ok("Category was successfully created");
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<String> deleteCategory(@PathVariable Long id) {
        categoryService.deleteCategoryById(id);
        return ResponseEntity.ok("Category was successfully deleted");
    }

    @PatchMapping("/{id}")
    public ResponseEntity<String> updateBook(@PathVariable Long id, @RequestBody UpdateCategoryDTO updateCategoryDTO) {
        categoryService.updateCategory(id, updateCategoryDTO);
        return ResponseEntity.ok("Category was successfully updated");
    }
}