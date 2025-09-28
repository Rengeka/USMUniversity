<?php

namespace repositories;

/**
 * Repository for tests stored in json
 */
class TestJsonRepository {
    /**
     * Path separator constant for file system compatibility.
     * This ensures cross-platform compatibility.
     */
    private const sep = DIRECTORY_SEPARATOR;
    /**
     * Path to the JSON file containing the test database.
     *
     * @var string
     */
    private $path;

    /**
     * Constructor for the class.
     * Sets the path to the test database JSON file.
     */
    public function __construct() {
        $this->path = __DIR__ . self::sep . '..' . self::sep . '..' . self::sep . 'db' . self::sep . 'tests.db.json';
    }

    /**
     * Retrieves a test by its ID.
     * 
     * This method reads the JSON file, decodes it into an array, then filters
     * the tests by the provided ID and returns the corresponding test.
     *
     * @param int $id The ID of the test to find.
     * @return array|null Returns an associative array with the test data, or null if no test was found.
     */
    public function GetTest(int $id) {
        $jsonData = file_get_contents($this->path);
        $tests = json_decode($jsonData, true);

        $filtered = array_filter($tests, fn($test) => ($test['id'] ?? null) == $id);
        return reset($filtered);
    }

    /**
     * Retrieves all tests from the database.
     *
     * This method reads the entire JSON file, decodes it, and returns the array
     * of all tests.
     *
     * @return array Returns an array of all tests.
     */
    public function GetTests(){
        $jsonData = file_get_contents($this->path);
        $tests = json_decode($jsonData, true);
        
        return $tests;
    }

    /**
     * Retrieves the correct answers for a test by its ID.
     * 
     * This method extracts the correct answers from the questions of the
     * test with the given ID.
     *
     * @param int $id The ID of the test to find the correct answers for.
     * @return array Returns an array of correct answers for each question in the test.
     */
    public function GetCorrect(int $id) {
        //copy paste :(
        $jsonData = file_get_contents($this->path);
        $tests = json_decode($jsonData, true);

        $questions = array_filter($tests, fn($test) => $test['id'] === $id)[0]['questions'];
        $correct = array_map(fn($question) => $question['correct'], $questions);

        return $correct;
    }
}