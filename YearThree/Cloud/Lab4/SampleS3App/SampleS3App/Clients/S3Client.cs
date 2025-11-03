using Amazon.S3;
using SampleS3App.Contracts;
using Amazon.S3.Model;

namespace SampleS3App.Clients;

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

    public async Task<Stream?> GetFileAsync(string key)
    {
        var response = await s3Client.GetObjectAsync(_bucketName, key);
        return response.ResponseStream;
    }

    public async Task DeleteFileAsync(string key)
    {
        await s3Client.DeleteObjectAsync(_bucketName, key);
    }
}