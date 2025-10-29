<?php

// upload.php

require 'vendor/autoload.php';

use Aws\S3\S3Client;

define('BUCKET_NAME', 'bucket-name');

$s3 = new S3Client([
    'region'  => 'us-central-1',
]);

// Получение файла из формы
$file = $_FILES['fileToUpload']['tmp_name'];
$filename = $_FILES['fileToUpload']['name'];

// Поместить в "папку" avatars (S3 использует префиксы в ключах)
$destinationKey = 'avatars/' . basename($filename);

// Загрузка файла в S3
try {
    $result = $s3->putObject([
        'Bucket'     => BUCKET_NAME,
        'Key'        => $destinationKey,
        'SourceFile' => $file
    ]);

    echo "File uploaded successfully. URL: " . $result['ObjectURL'];
} catch (Aws\Exception\AwsException $e) {
    echo "Error uploading file: " . $e->getMessage();
}