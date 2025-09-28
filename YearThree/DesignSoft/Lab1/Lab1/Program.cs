using Lab1.Extentions;
using Lab1.Infrastructure.REST.EndpointGroups.User.Endpoints;
using Lab1.Infrastructure.REST.Extentions;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddServices();

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

app.MapEndpointGroups(typeof(GetUserEndpoint).Assembly);

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.Run();