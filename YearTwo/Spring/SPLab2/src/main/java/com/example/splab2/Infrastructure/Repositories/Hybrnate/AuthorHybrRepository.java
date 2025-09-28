package com.example.splab2.Infrastructure.Repositories.Hybrnate;

import com.example.splab2.Application.Dtos.AuthorDTOS.CreateAuthorDTO;
import com.example.splab2.Domain.Entities.Author;
import lombok.RequiredArgsConstructor;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
@RequiredArgsConstructor
public class AuthorHybrRepository {

    private final SessionFactory sessionFactory;

    public Optional<Author> findById(Long id) {
        var session = sessionFactory.openSession();
        var author = session.get(Author.class, id);

        session.close();

        return Optional.ofNullable(author);
    }

    public List<Author> findAll(){
        var session = sessionFactory.openSession();
        var authors = session.createQuery("FROM Author", Author.class).getResultList();

        session.close();

        return authors;
    }

    public void deleteById(Long id){
        var session = sessionFactory.openSession();
        var author = findById(id).get();

        var transaction = session.beginTransaction();

        try {
            session.remove(author);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }

    public void createAuthor(CreateAuthorDTO dto){
        var author = new Author();
        var session = sessionFactory.openSession();

        author.setFirstName(dto.getFirstName());
        author.setLastName(dto.getLastName());

        var transaction = session.beginTransaction();

        try{
            session.persist(author);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }


    public void save(Author author){
        var session = sessionFactory.openSession();

        var transaction = session.beginTransaction();

        try{
            session.save(author);
            transaction.commit();
        } catch (Exception e) {
            transaction.rollback();
        }

        session.close();
    }
}
