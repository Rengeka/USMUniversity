namespace CNMOLab1;

public class DivitionByTwoMethod
{
    private Tuple<double, double> _leftEdge;
    private Tuple<double, double> _rightEdge;
    private FunctionDelegate _function;
    private int _accuracy;
    private int _counter;

    public double Start(FunctionDelegate function, double leftSideX, double rightSideX, int accuracy)
    {
        _accuracy = accuracy;
        _counter = 0;
        _function = function;

        _leftEdge = new Tuple<double, double>(leftSideX, _function(leftSideX));
        _rightEdge = new Tuple<double, double>(rightSideX, _function(rightSideX));

        return Iterate();
    }

    private double Iterate()
    {
        //Console.WriteLine($"Iteration {_counter} : ({_leftEdge.Item1}, {_rightEdge.Item1}) [{_leftEdge.Item2}, {_rightEdge.Item2}]");
        _counter++;

        var x1 = (_leftEdge.Item1 + _rightEdge.Item1) / 2;
        var y1 = _function(x1);

        if (y1 * _leftEdge.Item2 < 0)
        {
            _rightEdge = new Tuple<double, double>(x1, y1);

            if (CheckAccuracy())
            {
                return (_leftEdge.Item1 + _rightEdge.Item1) / 2;
            }

            return Iterate();
        }
        else
        {
            _leftEdge = new Tuple<double, double>(x1, y1);

            if (CheckAccuracy())
            {
                return (_leftEdge.Item1 + _rightEdge.Item1) / 2;
            }

            return Iterate();
        }
    }

    private bool CheckAccuracy()
    {
        if ((_leftEdge.Item2 - _rightEdge.Item2) <= (Math.Pow(10, -_accuracy)))
        {
            return true;
        }

        return false;
    }
}