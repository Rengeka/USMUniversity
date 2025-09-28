using Lab1.Application.Enums;
using Lab1.Domain;

namespace Lab1.Infrastructure.DataAccess.Extentions;

internal static class UserExtentions
{
    internal static User GetUserFields(this User user, GetUserFieldMask mask)
    {
        var resultUser = new User();

        if (mask.HasFlag(GetUserFieldMask.Id))
        {
            resultUser.Id = user.Id;
        }

        if (mask.HasFlag(GetUserFieldMask.Name))
        {
            resultUser.Name = user.Name;
        }

        if (mask.HasFlag(GetUserFieldMask.AccountBalance))
        {
            resultUser.AccountBalance = user.AccountBalance;
        }

        if (mask.HasFlag(GetUserFieldMask.Age))
        {
            resultUser.Age = user.Age;
        }

        if (mask.HasFlag(GetUserFieldMask.Role))
        {
            resultUser.Role = user.Role;
        }

        return resultUser;
    }
}