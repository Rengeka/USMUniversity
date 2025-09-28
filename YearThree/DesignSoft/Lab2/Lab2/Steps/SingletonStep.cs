namespace Lab2.Steps;

internal class SingletonStep : IPieplineStep<Context>
{
    private static SingletonStep? _instance;
    public static SingletonStep Instance { get => _instance ?? (_instance = new SingletonStep()); }

    private SingletonStep() { }

    public void Execute(Context context)
    {
        Console.WriteLine($"Singleton step");
    }
}