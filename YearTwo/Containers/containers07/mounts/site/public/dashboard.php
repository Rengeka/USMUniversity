<?php

require_once __DIR__ . '/../src/services/result.service.php';

use services\ResultService;

$resultService = new ResultService();
$results = $resultService->GetResults();

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <div>
        <?php foreach ($results as $result) { ?>
            <div>
                <?php
                    $formattedAnswers = array_map(
                        fn($answer) => "[" . implode(", ", $answer) . "]", 
                        $result['answers']
                    );
                    echo "ID: {$result['id']}, User: {$result['username']}, Answrs: " . implode(" | ", $formattedAnswers);
                ?>
            </div>
        <?php }; ?>
    </div>
</body>
</html>
<?php
