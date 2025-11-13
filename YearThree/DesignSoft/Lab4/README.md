Пример Http контекста в ASP.NET 

```C#
/// <summary>
/// Encapsulates all HTTP-specific information about an individual HTTP request.
/// </summary>
[DebuggerDisplay("{DebuggerToString(),nq}")]
[DebuggerTypeProxy(typeof(HttpContextDebugView))]
public abstract class HttpContext
{
    ...

    /// <summary>
    /// Gets or sets a key/value collection that can be used to share data within the scope of this request.
    /// </summary>
    public abstract IDictionary<object, object?> Items { get; set; }

    /// <summary>
    /// Gets or sets the <see cref="IServiceProvider"/> that provides access to the request's service container.
    /// </summary>
    public abstract IServiceProvider RequestServices { get; set; }

    ...
}

```

Собственная реализация через Dictionary и публичную ReadOnlyDictionary

```C#
public class MyContext
{
    private readonly Dictionary<string, object> _items;
    public ReadOnlyDictionary<string, object> Items => new(_items);

    public MyContext() 
    {
        _items = new Dictionary<string, object>();
        _items.Add("sample", new
        {
            Name = "Sample",
            Value = ("Sample").GetHashCode()
        });
    }
}

[HttpGet(Name = "Sample")]
public void Get(HttpContext context, MyContext myContext)
{
    var anItem = context.Items["AnItem"];
    var sample = myContext.Items["Sample"];
}
```