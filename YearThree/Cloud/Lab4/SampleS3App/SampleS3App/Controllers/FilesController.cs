using Microsoft.AspNetCore.Mvc;
using SampleS3App.Contracts;

namespace SampleS3App.Controllers
{
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
}