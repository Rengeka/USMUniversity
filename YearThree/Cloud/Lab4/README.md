# Lab 3

## Задание

Создать 2 S3 бакета. Приватный и публичный

!["Bucket"](./images/1.png)
!["Bucket"](./images/2.png)
!["Bucket"](./images/3.png)

Задаём Ownership rule

!["Bucket"](./images/4.png)

Загружаем изображения юзеров и проверяем доступны ли они

!["Bucket"](./images/5.png)

Аплоудим лого через CLI и проверяем что оно там

!["Bucket"](./images/6.png)

!["Bucket"](./images/7.png)

Создаём lifecycle rule

!["Bucket"](./images/8.png)

Аналогично pub бакету создаём web бакет с публичным доступом и хостим на нём веб сайт

!["Bucket"](./images/9.png)

Запустим SmapleS3App, приложенную к проекту, заменив в appsettings.json ServiceURL на свой url S3

```json
{
  "Logging": {
    "LogLevel": {
      "Default": "Information",
      "Microsoft.AspNetCore": "Warning"
    }
  },
  "AWS": {
    "ServiceURL": "http://YOUR_S3_HOST_HERE"
  },
  "AllowedHosts": "*"
}
```

Приложение содержит эндпоинт для загрузки файла в публичный S3 бакет с именем sample.

```C#
[ApiController]
[Route("[controller]")]
public class FilesController(IFileStorageClient storage) : ControllerBase
{
  [HttpPost("upload")]
  public async Task<IActionResult> UploadFile(IFormFile file)
  {
    await storage.PutFileAsync(file, file.FileName);
    return Ok();
  }
}
```

```C#
public class S3Client(IAmazonS3 s3Client) : IFileStorageClient
{
  private readonly string _bucketName = "sample";

  public async Task PutFileAsync(IFormFile file, string key)
  {
    using var stream = file.OpenReadStream();
    var request = new PutObjectRequest
    {
      BucketName = _bucketName,
      Key = key,
      InputStream = stream,
      ContentType = file.ContentType
    };

    await s3Client.PutObjectAsync(request);
  }
}
```

После этого файл будет достуен для чтения