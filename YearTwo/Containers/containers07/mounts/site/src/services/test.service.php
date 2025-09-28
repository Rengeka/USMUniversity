<?php

namespace services;

require_once __DIR__ . '/../../src/repositories/test.json.repository.php';

use repositories\TestJsonRepository;

/**
 * Service class responsible for managing test data.
 * This class provides methods to fetch individual tests, all tests, and correct answers for a test.
 */
class TestService {
    /**
     * Instance of the TestJsonRepository to interact with the test data.
     *
     * @var TestJsonRepository
     */
    private $repository;

    /**
     * Constructor for the TestService class.
     * Initializes the TestJsonRepository instance for interacting with the test data.
     */
    public function __construct() {
        $this->repository = new TestJsonRepository();
    }

    /**
     * Retrieves a specific test by its ID.
     * 
     * This method delegates the task of fetching the test by ID to the repository and returns the test.
     *
     * @param int $id The ID of the test.
     * 
     * @return array|null Returns an array containing the test data, or null if the test is not found.
     */
    public function GetTest(int $id) {
        $test = $this->repository->GetTest($id);
        return $test;
    }

    /**
     * Retrieves all available tests.
     * 
     * This method delegates the task of fetching all tests to the repository and returns them.
     *
     * @return array Returns an array containing all the tests.
     */
    public function GetTests(){
        $tests = $this->repository->GetTests();
        return $tests;
    }

    /**
     * Retrieves the correct answers for a specific test.
     * 
     * This method delegates the task of fetching the correct answers to the repository and returns them.
     *
     * @param int $id The ID of the test.
     * 
     * @return array Returns an array containing the correct answers for the specified test.
     */
    public function GetCorrect(int $id) {
        $correct = $this->repository->GetCorrect($id);
        return $correct;
    }
}