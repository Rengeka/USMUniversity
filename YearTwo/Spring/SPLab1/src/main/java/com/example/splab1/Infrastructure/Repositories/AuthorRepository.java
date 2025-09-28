package com.example.splab1.Infrastructure.Repositories;

import com.example.splab1.Domain.Entities.Author;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface AuthorRepository extends JpaRepository<Author, Long> { }