<?php

namespace repositories;

/**
 * Repository for results stored in json
 */
class ResultRepository {
    /**
     * Path separator constant for file system compatibility.
     * Ensures cross-platform compatibility.
     */
    private const sep = DIRECTORY_SEPARATOR;
    /**
     * Path to the JSON file containing the results database.
     *
     * @var string
     */
    private $path;

    /**
     * Constructor for the class.
     * Sets the path to the results database JSON file.
     */
    public function __construct() {
        $this->path = __DIR__ . self::sep . '..' . self::sep . '..' . self::sep . 'db' . self::sep . 'results.db.json';
    }

    /**
     * Retrieves all results from the database.
     * 
     * This method reads the entire JSON file, decodes it into an array,
     * and returns the list of all results.
     *
     * @return array Returns an array of all results stored in the database.
     */
    public function GetResults() {
        $jsonData = file_get_contents($this->path);
        $results = json_decode($jsonData, true);

        return $results;
    }

    /**
     * Creates a new result entry and adds it to the results database.
     * 
     * This method appends a new result (with the provided test ID, username, and answers)
     * to the existing results data and saves it back to the JSON file.
     *
     * @param int $id The ID of the test.
     * @param string $username The username of the person who took the test.
     * @param array $answers An array of answers provided by the user.
     * 
     * @return void This method does not return a value.
     */
    public function CreateResult(int $id, string $username, array $answers){
        $results = $this->GetResults();

        $newResult = [
            'id' => $id, 
            'username' => $username,
            'answers' => $answers
        ];
        array_push($results, $newResult);

        file_put_contents($this->path, json_encode($results, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE));
    }
}