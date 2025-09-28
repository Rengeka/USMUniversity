package com.example.splab2.Application.Services;

import com.example.splab2.Domain.Entities.Publisher;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
@RequiredArgsConstructor
public class PublisherService {

    private final PublisherHybrRepository publisherRepository;

    public Optional<Publisher> findById(Long id){
        return publisherRepository.findById(id);
    }
}