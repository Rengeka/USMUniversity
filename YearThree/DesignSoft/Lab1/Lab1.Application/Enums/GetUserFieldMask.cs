namespace Lab1.Application.Enums;

[Flags]
public enum GetUserFieldMask : byte
{
    Id = 0,
    Name = 1,
    Age = 2,
    Role = 4,
    AccountBalance = 8
}