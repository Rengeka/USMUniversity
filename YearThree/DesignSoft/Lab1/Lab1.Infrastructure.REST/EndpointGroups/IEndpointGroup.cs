using Microsoft.AspNetCore.Routing;

namespace Lab1.Infrastructure.REST.EndpointGroups;

internal interface IEndpointGroup
{
    public void MapEndpoints(IEndpointRouteBuilder builder);
}