using Amazon.S3.Model;
using SampleS3App.Clients;

namespace SampleS3App.Contracts;

public interface IFileStorageClient
{
    public Task PutFileAsync(IFormFile file, string key);
    public Task<Stream?> GetFileAsync(string key);
    public Task DeleteFileAsync(string key);
}