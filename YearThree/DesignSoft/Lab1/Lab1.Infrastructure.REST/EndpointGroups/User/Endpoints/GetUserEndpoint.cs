using Lab1.Application.Contracts.Services;
using Lab1.Application.Enums;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace Lab1.Infrastructure.REST.EndpointGroups.User.Endpoints;

public static class GetUserEndpoint
{
    public static async Task<IResult> Handle(
        [FromQuery] string name, 
        [FromQuery] GetUserFieldMask fieldMask,
        [FromServices] IUserService userService,
        CancellationToken cancellationToken)
    {
        var result = await userService.GetUserAsync(name, fieldMask, cancellationToken);
        return Results.Ok(result);
    }
}