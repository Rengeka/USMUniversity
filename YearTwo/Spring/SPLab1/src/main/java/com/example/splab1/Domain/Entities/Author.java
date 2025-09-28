package com.example.splab1.Domain.Entities;

import jakarta.persistence.*;
import lombok.Data;

import java.util.List;

@Entity
@Table(name = "authors")
@Data
public class Author {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    public Long id;

    @Column( name = "first_name")
    private String firstName;

    @Column( name = "last_name")
    private String lastName;

    @OneToMany(mappedBy = "author")
    private List<Book> books;
}