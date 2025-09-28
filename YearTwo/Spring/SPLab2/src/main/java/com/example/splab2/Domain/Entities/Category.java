package com.example.splab2.Domain.Entities;

import jakarta.persistence.*;
import lombok.Data;

import java.util.List;

@Entity
@Table(name = "categories")
@Data
public class Category {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;

    @Column(name = "title")
    private String title;

    @ManyToMany(mappedBy = "categories", fetch = FetchType.LAZY)
    private List<Book> books;
}