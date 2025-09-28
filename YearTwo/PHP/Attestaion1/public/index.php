<?php

require_once __DIR__ . '/../src/services/test.service.php';

use services\TestService;

$testService = new TestService();
$tests = $testService->GetTests();

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <a href="dashboard.php">
        <h2>View dashboard</h2>
    </a>
    <div>
        <?php foreach ($tests as $test) {?>
            <a href="test.php?id=<?php echo $test['id']?>">
                <h2><?php echo $test['title']?></h2>  
            </a>
        <?php } ?>
    </div>
</body>
</html>
<?php
