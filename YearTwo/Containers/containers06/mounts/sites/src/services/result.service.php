<?php

namespace services;

require_once __DIR__ . '/../../src/repositories/result.repository.php';

use repositories\ResultRepository;

/**
 * Service class responsible for managing test results.
 * This class acts as a layer between the controller and the repository,
 * providing methods to get and store results.
 */
class ResultService {
    /**
     * Instance of the ResultRepository to interact with the results data.
     *
     * @var ResultRepository
     */
    private $repository;

    /**
     * Constructor for the ResultService class.
     * Initializes the ResultRepository instance for interacting with the database.
     */
    public function __construct() {
        $this->repository = new ResultRepository();
    }

    /**
     * Retrieves all results from the repository.
     * 
     * This method delegates the task of fetching results to the repository and returns the results.
     *
     * @return array Returns an array of all test results from the repository.
     */
    public function GetResults() {
        $results = $this->repository->GetResults();
        return $results;
    }

    /**
     * Posts a new result to the repository.
     * 
     * This method delegates the task of storing a new result (including the test ID, username, and answers)
     * to the repository.
     *
     * @param int $id The ID of the test.
     * @param string $username The username of the person who took the test.
     * @param array $answers The answers provided by the user.
     * 
     * @return void This method does not return a value.
     */
    public function PostResult(int $id, string $username, array $answers) {
        $this->repository->CreateResult($id,  $username, $answers);
    }
} 