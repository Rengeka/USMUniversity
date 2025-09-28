namespace CNMOLab1;

public class ChordMethod
{
    private FunctionDelegate _function;
    private FunctionDelegate _der1;
    private FunctionDelegate _der2;
    private double _accuracy;
    private double _a, _b;

    public double Start(
        FunctionDelegate function, 
        double a, 
        double b, 
        double accuracy, 
        FunctionDelegate der1,
        FunctionDelegate der2
        )
    {
        _function = function;
        _a = a;
        _b = b;
        _accuracy = accuracy;

        _der1 = der1;
        _der2 = der2;

        if (_der1(a) *_der2(a) > 0)
        {
            return Iterate(b);
        }
        else
        {
            return Iterate(a);
        }
    }

    private double Iterate(double x0)
    {
        double x1;

        do
        {
            x1 = x0 - (_function(x0) * (_b - x0)) / (_function(_b) - _function(x0));

            if (Math.Abs( x1 - x0) < (Math.Pow(10, -_accuracy)))
                return x1;

            _a = _b;
            _b = x1;
            x0 = _a;

        } while (true);
    }
}