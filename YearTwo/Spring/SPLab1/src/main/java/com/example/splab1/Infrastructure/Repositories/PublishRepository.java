package com.example.splab1.Infrastructure.Repositories;

import com.example.splab1.Domain.Entities.Publisher;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface PublishRepository extends JpaRepository<Publisher, Long> { }