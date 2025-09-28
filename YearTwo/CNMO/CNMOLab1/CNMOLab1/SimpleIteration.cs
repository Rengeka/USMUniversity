namespace CNMOLab1;

internal class SimpleIteration
{
    public double Start(double x0, double accuracy)
    {
        const int maxIterations = 1000;
        int iteration = 0;
        double x1 = x0;

        do
        {
            x0 = x1;
            x1 = 3.75 - 1.25 * Math.Log(x0);
            iteration++;

            if (Math.Abs(x1 - x0) < (Math.Pow(10, -(accuracy + 1)))) break;
        }
        while (iteration < maxIterations);

        return x1;
    }
}