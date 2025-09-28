<?php
session_start();
require_once __DIR__ . '/../src/services/test.service.php';

use services\TestService;

$id = $_GET["id"];

$testService = new TestService();
$test = $testService->GetTest($id);
?>

<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Test</title>
</head>
<body>
    <h2><?php echo ($test['title']) ?></h2>
    <form id="quiz-form" method="POST" action="result.php">
        <input type="hidden" name="id" value="<?php echo $test['id']; ?>">
        <input name="username">

        <?php foreach ($test['questions'] as $qIndex => $question) { ?> 
            <div class="question">
                <p><?php echo ($question['text']); ?></p>
                
                <?php 
                $type = count($question['correct']) === 1 ? 'radio' : 'checkbox';
                foreach ($question['options'] as $oIndex => $option) { 
                ?>
                    <label>
                        <input type="<?php echo $type; ?>" name="answers[<?php echo $qIndex; ?>][]" value="<?php echo $oIndex; ?>">
                            <?php echo ($option); ?>
                    </label><br>
                <?php } ?>
            </div>
        <?php } ?>

        <br><button type="submit">Finish</button>
    </form>
</body>
</html>
<?php 
