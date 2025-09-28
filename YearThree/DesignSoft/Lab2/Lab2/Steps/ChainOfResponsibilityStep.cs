namespace Lab2.Steps;

internal class ChainOfResponsibilityStep(IPieplineStep<Context> _next = null) : IPieplineStep<Context>
{
    private static bool IsDone = false;

    public void Execute(Context context)
    {
        if (IsDone)
        {
            Console.WriteLine("COR is done");
            return;
        }

        Console.WriteLine("COR is not done yet");
        IsDone = true;
        _next?.Execute(context); 
    }
}