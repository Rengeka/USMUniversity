namespace Lab2.Steps;

public class TestStep : IPieplineStep<Context>
{
    public void Execute(Context context)
    {
        Console.WriteLine($"Step for context {context.ToString()}");
    }
}