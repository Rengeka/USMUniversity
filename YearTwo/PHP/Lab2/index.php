<?php
    define('notWorkingDay', 'Not working day');

    define('Sunday', 1);
    define('Monday', 2);
    define('Tuesday', 3);
    define('Wednesday', 4);
    define('Friday', 5);
    define('Thursday', 6);
    define('Saturday', 7);

    $data = [
        ['John', 'Syles', [Monday, Wednesday, Thursday], '8:00 - 12:00'],
        ['Jane', 'Doe', [Tuesday, Friday, Saturday], '12:00 - 16:00']
    ];
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        table {
            width: 100%;
            border-collapse: collapse;
        }
        table, th, td {
            border: 1px solid black;
        }
        th, td {
            padding: 8px;
            text-align: left;
        }
    </style>
</head>
<body>
    <table>
        <?php for ($i = 0; $i < count($data); $i++){ ?>
            <tr>
                <td>
                    <?php echo $i ?>
                </td>
                <td>
                    <?php echo $data[$i][0] . ' ' . $data[$i][1]?>
                </td>
                <td>
                    <?php 
                        if(in_array(date("N"), $data[$i][2])){
                            echo $data[$i][3];
                        }
                        else{
                            echo notWorkingDay;
                        }
                    ?>
                </td>
            </tr>
        <?php } ?>
    </table>
</body>
</html>

<?php

$a = 0;
$b = 0;

?><div>for</div><?php

for ($i = 0; $i <= 5; $i++) {
   $a += 10;
   $b += 5; ?>

   <div><?php echo "a = $a, b = $b"; ?></div>
<?php
}

$a = 0;
$b = 0;
$i = 0;

?><div>while</div><?php

while($i <= 5){
    $i++;

    $a += 10;
    $b += 5;?>

    <div><?php echo "a = $a, b = $b"; ?></div>
<?php
}

$a = 0;
$b = 0;
$i = 0;

?><div>do while</div><?php

do {
    $i++;
    
    $a += 10;
    $b += 5;?>

    <div><?php echo "a = $a, b = $b"; ?></div>
<?php
}
while($i <= 5);


