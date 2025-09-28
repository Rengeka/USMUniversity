using Lab1.Application.Enums;
using Lab1.Domain;

namespace Lab1.Application.Contracts.Services;

public interface IUserService
{
    public Task<User?> GetUserAsync(string name, GetUserFieldMask fieldMask, CancellationToken cancellationToken);
}