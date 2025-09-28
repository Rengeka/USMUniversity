using Lab1.Domain.Enums;

namespace Lab1.Domain;

public class User
{
    public Guid Id { get; set; }
    public string Name { get; set; }
    public int Age { get; set; }
    public UserRole Role { get; set; }
    public float AccountBalance { get; set; }
}