package com.example.splab2.Infrastructure.Repositories.Hybrnate;


import com.example.splab2.Application.Dtos.AuthorDTOS.CreateAuthorDTO;
import com.example.splab2.Domain.Entities.Author;
import com.example.splab2.Domain.Entities.Book;
import lombok.RequiredArgsConstructor;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
@RequiredArgsConstructor
public class BookHybrRepository {

    private final SessionFactory sessionFactory;

    public Optional<Book> findById(Long id) {
        var session = sessionFactory.openSession();
        var book = session.get(Book.class, id);

        session.close();

        return Optional.ofNullable(book);
    }

    public List<Book> findAll(){
        var session = sessionFactory.openSession();
        var books = session.createQuery("FROM Book", Book.class).getResultList();

        session.close();

        return books;
    }

    public void deleteById(Long id){
        var session = sessionFactory.openSession();
        var book = findById(id).get();

        var transaction = session.beginTransaction();

        try {
            session.remove(book);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }

    public void save(Book book) {
        var session = sessionFactory.openSession();

        var transaction = session.beginTransaction();

        try{
            session.save(book);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }
}