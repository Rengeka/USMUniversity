package com.example.splab1.Domain.Entities;

import jakarta.persistence.*;

import java.util.List;

@Entity
public class Library {

    @Id
    @GeneratedValue(strategy= GenerationType.AUTO)
    private int id;

    @ManyToMany(mappedBy = "libraries", fetch = FetchType.LAZY)
    private List<Book> books;
}