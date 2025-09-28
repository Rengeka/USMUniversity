namespace Lab2.Steps;

internal class DecoratorStep(IPieplineStep<Context> _step) : IPieplineStep<Context>
{
    public void Execute(Context context)
    {
        Console.WriteLine("Before executing step");
        _step.Execute(context);
        Console.WriteLine("After executing step");
    }
}