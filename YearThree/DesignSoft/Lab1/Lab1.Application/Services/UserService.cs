using Lab1.Application.Contracts.Repositories;
using Lab1.Application.Contracts.Services;
using Lab1.Application.Enums;
using Lab1.Domain;

namespace Lab1.Application.Services;

public class UserService(IUserRepository userRepository) : IUserService
{
    public async Task<User?> GetUserAsync(string name, GetUserFieldMask fieldMask, CancellationToken cancellationToken) 
    {
        return await userRepository.FindByNameAsync(name, fieldMask, cancellationToken);
    }
}