
package com.example.splab2.Presentation.Controllers;

import com.example.splab2.Application.Dtos.CategoryDTOS.CreateCategoryDTO;
import com.example.splab2.Application.Dtos.CategoryDTOS.GetCategoryDTO;
import com.example.splab2.Application.Dtos.CategoryDTOS.UpdateCategoryDTO;
import com.example.splab2.Application.Services.CategoryService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/api/categories")
@RequiredArgsConstructor
public class CategoryController {

    private final CategoryService categoryService;

   @GetMapping
    public ResponseEntity<List<GetCategoryDTO>> getCategories(){
        var categories = categoryService.findAll();
        return ResponseEntity.ok(categories.stream().map(GetCategoryDTO::Map).collect(Collectors.toList()));
    }

    @GetMapping("/{id}")
    public ResponseEntity<GetCategoryDTO> getCategory(@PathVariable Long id) {
        var category = categoryService.findById(id).get();
        return ResponseEntity.ok(GetCategoryDTO.Map(category));
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