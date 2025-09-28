package com.example.splab2.Infrastructure.Repositories.Hybrnate;

import com.example.splab2.Domain.Entities.Publisher;
import lombok.RequiredArgsConstructor;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
@RequiredArgsConstructor
public class PublisherHybrRepository {

    private final SessionFactory sessionFactory;

    public Optional<Publisher> findById(Long id) {
        var session = sessionFactory.openSession();
        var publisher = session.get(Publisher.class, id);

        session.close();

        return Optional.ofNullable(publisher);
    }

}