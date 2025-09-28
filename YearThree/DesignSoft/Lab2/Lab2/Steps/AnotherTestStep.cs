namespace Lab2.Steps;

public class AnotherTestStep : IPieplineStep<Context>
{
    public void Execute(Context context)
    {
        Console.WriteLine($"Another step for context {context.ToString()}");
    }
}