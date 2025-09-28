using Lab1.Application.Contracts.Repositories;
using Lab1.Application.Enums;
using Lab1.Domain;
using Lab1.Domain.Enums;
using Lab1.Infrastructure.DataAccess.Extentions;

namespace Lab1.Infrastructure.DataAccess;

public class UserRepository : IUserRepository
{
    // Async just to make this repo look like the real one
    public async Task<User?> FindByNameAsync(string name, GetUserFieldMask fieldMask, CancellationToken cancellationToken)
    {
        var user = _users.FirstOrDefault(u => u.Name == name);

        if (user is null)
        {
            return null;
        }

        return await Task.FromResult(user.GetUserFields(fieldMask));
    }

    // Just a sample data instead of connecting a real database
    private readonly List<User> _users =
    [
        new()
        {
            Id = Guid.NewGuid(),
            Name = "Alice Johnson",
            Age = 25,
            Role = UserRole.None,
            AccountBalance = 120.50f
        },
        new()
        {
            Id = Guid.NewGuid(),
            Name = "Bob Smith",
            Age = 32,
            Role = UserRole.Admin,
            AccountBalance = 1024.99f
        },
        new()
        {
            Id = Guid.NewGuid(),
            Name = "Charlie Brown",
            Age = 28,
            Role = UserRole.Support,
            AccountBalance = 250.00f
        },
        new()
        {
            Id = Guid.NewGuid(),
            Name = "Diana Prince",
            Age = 40,
            Role = UserRole.Admin,
            AccountBalance = 5000.75f
        },
        new()
        {
            Id = Guid.NewGuid(),
            Name = "Ethan Hunt",
            Age = 35,
            Role = UserRole.None,
            AccountBalance = 0.0f
        }
    ];


}