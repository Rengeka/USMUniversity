using Lab1.Application.Contracts.Repositories;
using Lab1.Application.Contracts.Services;
using Lab1.Application.Services;
using Lab1.Infrastructure.DataAccess;

namespace Lab1.Extentions;

public static class IServiceCollectionExtention
{
    public static IServiceCollection AddServices(this IServiceCollection services)
    {
        // Services
        services.AddScoped<IUserService, UserService>();

        // Repositories
        services.AddScoped<IUserRepository, UserRepository>();

        return services;
    }
}