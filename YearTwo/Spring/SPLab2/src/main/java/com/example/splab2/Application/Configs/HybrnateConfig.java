package com.example.splab2.Application.Configs;

import com.example.splab2.Domain.Entities.*;
import org.hibernate.SessionFactory;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.jdbc.DataSourceBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
//import org.springframework.jdbc.datasource.DriverManagerDataSource;


import javax.sql.DataSource;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.SQLFeatureNotSupportedException;
import java.util.logging.Logger;
//import javax.sql.DataSource;


@Configuration
public class HybrnateConfig {

    @Bean(name="entityManagerFactory")
    public SessionFactory sessionFactory(DataSource dataSource) {
        org.hibernate.cfg.Configuration configuration = new org.hibernate.cfg.Configuration();

        configuration.setProperty("hibernate.dialect", "org.hibernate.dialect.PostgreSQLDialect");
        configuration.setProperty("hibernate.show_sql", "true");
        configuration.setProperty("hibernate.format_sql", "true");
        configuration.setProperty("hibernate.hbm2ddl.auto", "update");

        configuration.addAnnotatedClass(Book.class);
        configuration.addAnnotatedClass(Author.class);
        configuration.addAnnotatedClass(Category.class);
        configuration.addAnnotatedClass(Library.class);
        configuration.addAnnotatedClass(Publisher.class);

        StandardServiceRegistryBuilder builder = new StandardServiceRegistryBuilder()
                .applySettings(configuration.getProperties())
                .applySetting("hibernate.connection.datasource", dataSource);

        return configuration.buildSessionFactory(builder.build());
    }

    @Bean
    @Primary
    public DataSource dataSource() {
        return DataSourceBuilder.create()
                .type(org.postgresql.ds.PGSimpleDataSource.class)
                .url("jdbc:postgresql://localhost:5432/postgres")
                .username("postgres")
                .password("1234")
                .build();
    }

}