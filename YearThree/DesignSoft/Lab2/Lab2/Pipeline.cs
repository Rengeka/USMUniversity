namespace Lab2;

public class Pipeline<TContext> where TContext : new()
{
    private readonly TContext _context;
    private readonly List<IPieplineStep<TContext>> _steps;

    public Pipeline()
    {
        _context = new TContext();
        _steps = new List<IPieplineStep<TContext>>();
    }

    public void AddStep(IPieplineStep<TContext> step)
    {
        _steps.Add(step);   
    }

    public void Execute(TContext context)
    {
        foreach (var step in _steps)
        {
            step.Execute(context);
        }
    }
}