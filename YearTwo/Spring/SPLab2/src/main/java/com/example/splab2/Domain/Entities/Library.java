package com.example.splab2.Domain.Entities;

import jakarta.persistence.*;
import lombok.Data;

import java.util.List;

@Entity
@Table(name = "libraries")
@Data
public class Library {

    @Id
    @GeneratedValue(strategy= GenerationType.AUTO)
    private int id;

    @ManyToMany(mappedBy = "libraries", fetch = FetchType.LAZY)
    private List<Book> books;
}