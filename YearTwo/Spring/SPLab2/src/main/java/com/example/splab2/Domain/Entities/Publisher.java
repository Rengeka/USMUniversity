package com.example.splab2.Domain.Entities;

import jakarta.persistence.*;
import lombok.Data;

import java.util.List;

@Entity
@Table( name = "publishers")
@Data
public class Publisher {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private int id;

    @Column( name = "title")
    private String title;

    @OneToMany(mappedBy = "publisher")
    private List<Book> books;
}