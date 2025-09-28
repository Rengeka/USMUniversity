namespace CNMOLab1;

internal class NewtonsMethod
{
    private FunctionDelegate _function;
    private FunctionDelegate _der1;

    public NewtonsMethod(FunctionDelegate function, FunctionDelegate der1)
    {
        _der1 = der1;
        _function = function;
    }

    public double Start(double x0, double accuracy)
    {
        double x1 = 0;
        bool reachedAccuracy = false;

        while (!reachedAccuracy)
        {
            x1 = x0 - (_function.Invoke(x0) / _der1.Invoke(x0));

            var a = _function.Invoke(x0);
            var b = _der1.Invoke(x0);

            if (Math.Abs(x1 - x0) <= (Math.Pow(10, -accuracy)))
            {
                reachedAccuracy = true;
            }
            else
            {
                x0 = x1;
            }
        }

        return x1;
    }
}