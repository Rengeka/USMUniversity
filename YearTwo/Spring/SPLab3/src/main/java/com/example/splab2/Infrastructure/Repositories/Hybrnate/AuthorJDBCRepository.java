package com.example.splab2.Infrastructure.Repositories.Hybrnate;

import com.example.splab2.Application.Dtos.AuthorDTOS.GetAuthorDTO;
import lombok.RequiredArgsConstructor;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

@RequiredArgsConstructor
@Repository
public class AuthorJDBCRepository {

    private final JdbcTemplate jdbcTemplate;

    public GetAuthorDTO getAuthorById(int id) {
        return jdbcTemplate.queryForObject();
    }

}
