using Lab1.Application.Contracts.Repositories;
using Lab1.Application.Contracts.Services;
using Lab1.Application.Enums;
using Lab1.Application.Services;
using Lab1.Domain;
using Lab1.Domain.Enums;
using Moq;

namespace Lab1.Application.UnitTests;

public class UserServiceTests
{
    private readonly IUserService _userService;
    private readonly Mock<IUserRepository> _userRepositoryMock;

    public UserServiceTests()
    {
        _userRepositoryMock = new Mock<IUserRepository>();
        _userService = new UserService(_userRepositoryMock.Object);
    }

    [Fact]
    public async Task GetUserAsync_ShouldReturnFieldsAccordingToMask()
    {
        // Arrange
        var user = new User
        {
            Id = Guid.NewGuid(),
            Name = "Alice",
            Age = 30,
            Role = UserRole.Admin,
            AccountBalance = 1000f
        };

        var returnUser = new User
        {
            Id = user.Id,
            Age = user.Age,
        };

        var fieldMask = GetUserFieldMask.Id | GetUserFieldMask.Age;

        _userRepositoryMock
            .Setup(r => r.FindByNameAsync(user.Name, fieldMask, It.IsAny<CancellationToken>()))
            .ReturnsAsync(returnUser);

        // Act
        var result = await _userService.GetUserAsync(user.Name, fieldMask, CancellationToken.None);

        // Assert
        Assert.Equal(user.Id, result.Id);       
        Assert.Equal(user.Age, result.Age);     
        Assert.Null(result.Name);                       
        Assert.Equal(default(UserRole), result.Role);   
        Assert.Equal(0f, result.AccountBalance);        
    }
}