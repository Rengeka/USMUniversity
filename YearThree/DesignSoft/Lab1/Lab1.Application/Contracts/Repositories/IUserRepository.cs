using Lab1.Application.Enums;
using Lab1.Domain;

namespace Lab1.Application.Contracts.Repositories;

public interface IUserRepository
{
    public Task<User?> FindByNameAsync(string name, GetUserFieldMask fieldMask, CancellationToken cancellationToken);
}