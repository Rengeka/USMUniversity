package com.example.splab1;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RestController;


@SpringBootApplication
@RestController
public class SpLab1Application {

    public static void main(String[] args) {
        SpringApplication.run(SpLab1Application.class, args);
    }
}
