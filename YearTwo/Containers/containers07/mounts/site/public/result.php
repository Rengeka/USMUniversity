<?php
require_once __DIR__ . '/../src/services/result.service.php';
require_once __DIR__ . '/../src/services/test.service.php';

use services\ResultService;
use services\TestService;

$resultService = new ResultService();
$testService = new TestService();

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $testId = $_POST['id'];
    $userAnswers = $_POST['answers'];
    
    $test = $testService->GetTest($testId);
    $totalQuestions = count($test['questions']);
    $correctAnswers = 0;

    foreach ($test['questions'] as $qIndex => $question) {
        $userAnswer = $userAnswers[$qIndex];
        $userAnswer = is_array($userAnswer) ? $userAnswer : [$userAnswer];
        
        if (array_values($userAnswer) == $question['correct']) {
            $correctAnswers++;
        }
    }

    $resultService->PostResult($_POST['id'], $_POST['username'], $_POST['answers'],);
    $percentage = round(($correctAnswers / $totalQuestions) * 100);
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Result</title>
</head>
<body>
    <?php if (isset($correctAnswers)): ?>
        <h2>Your result:</h2>
        <p>Correct answers: <?php echo $correctAnswers ?> from <?php echo $totalQuestions ?></p>
        <p>Percentage: <?php echo $percentage ?>%</p>
    <?php else: ?>
        <p>Result not found</p>
    <?php endif; ?>
    <a href="index.php">Return to main page</a>
</body>
</html>
<?php
