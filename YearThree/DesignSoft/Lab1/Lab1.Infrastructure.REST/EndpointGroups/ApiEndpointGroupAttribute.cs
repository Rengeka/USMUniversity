namespace Lab1.Infrastructure.REST.EndpointGroups;

internal class ApiEndpointGroupAttribute(string route) : Attribute
{
    public string Route { get; set; } = route;
}