package com.example.splab2.Infrastructure.Repositories.Hybrnate;

import com.example.splab2.Application.Dtos.AuthorDTOS.CreateAuthorDTO;
import com.example.splab2.Application.Dtos.CategoryDTOS.CreateCategoryDTO;
import com.example.splab2.Domain.Entities.Author;
import com.example.splab2.Domain.Entities.Category;
import lombok.RequiredArgsConstructor;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
@RequiredArgsConstructor
public class CategoryHybrRepository {

    private final SessionFactory sessionFactory;

    public Optional<Category> findById(Long id) {
        var session = sessionFactory.openSession();
        var category = session.get(Category.class, id);

        session.close();

        return Optional.ofNullable(category);
    }

    public List<Category> findAll(){
        var session = sessionFactory.openSession();
        var categories = session.createQuery("FROM Category ", Category.class).getResultList();

        session.close();

        return categories;
    }

    public List<Category> findAllById(List<Long> ids){
        var session = sessionFactory.openSession();
        var categories = session.createQuery("FROM Category WHERE Category.id in :ids", Category.class)
                .setParameterList("ids", ids)
                .getResultList();

        session.close();

        return categories;
    }

    public void deleteById(Long id){
        var session = sessionFactory.openSession();
        var category = findById(id).get();

        var transaction = session.beginTransaction();

        try {
            session.remove(category);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }

    public void createCategory(CreateCategoryDTO dto){
        var category = new Category();
        var session = sessionFactory.openSession();

        category.setTitle(dto.getTitle());

        var transaction = session.beginTransaction();

        try{
            session.persist(category);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }

    public void updateCategory(){
    }

    public void save(Category category){
        var session = sessionFactory.openSession();

        var transaction = session.beginTransaction();

        try{
            session.save(category);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }
}