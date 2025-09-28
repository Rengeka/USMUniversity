<?php

$dir = 'image/';
$files = scandir($dir);

if ($files === false) {
   return;
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
<div class="container" style="display: grid; grid-template-columns: repeat(3, 1fr); gap: 10px; width: 300px;">
        <?php 
        for ($i = 0; $i < count($files); $i++) {
        if (($files[$i] != ".") && ($files[$i] != "..")) {
            $path = $dir . $files[$i]; ?>                  
            <img border='1' src=<?php echo $path?>>    
        <?php
            }
        }
        ?>
    </div>
</body>
</html>