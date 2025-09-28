namespace Lab2;

public interface IPieplineStep<TContext>
{
    public void Execute(TContext context);
}