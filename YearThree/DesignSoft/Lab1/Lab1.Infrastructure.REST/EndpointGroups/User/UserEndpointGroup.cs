using Lab1.Infrastructure.REST.EndpointGroups.User.Endpoints;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Routing;

namespace Lab1.Infrastructure.REST.EndpointGroups.User;

[ApiEndpointGroup("user")]
public class UserEndpointGroup : IEndpointGroup
{
    public void MapEndpoints(IEndpointRouteBuilder builder)
    {
        builder.MapGet("", GetUserEndpoint.Handle);
    }
}