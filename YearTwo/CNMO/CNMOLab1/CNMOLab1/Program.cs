using CNMOLab1;

var method1 = new DivitionByTwoMethod();
var chordMethod = new ChordMethod();
var newthonsMethod = new NewtonsMethod(Function, Derivative1);
var simpleIteration = new SimpleIteration();

var root = method1.Start(Function, 2.5, 2.6, 6);
Console.WriteLine($"Method dividing by 2 : {root}");

var root2 = newthonsMethod.Start(2.5, 6);
Console.WriteLine($"Newton's method : {root2}");
//root = chordMethod.Start(Function, Derivative1, Derivative2);

var root3 = chordMethod.Start(Function, 2.5, 2.6, 6, Derivative1, Derivative2);
Console.WriteLine($"Chord method : {root3}");

var root4 = simpleIteration.Start(2.5, 6);
Console.WriteLine($"Simple Itteration method : {root4}");

double Function(double x)
{
    double y = 0;

    y = x * x;
    y = Math.Sqrt(y);
    y *= 0.4;
    y = 1.5 - y;
    y -= 0.5 * MathF.Log((float)x);

    return y;
}

double Derivative1(double x)
{
    double y = 0;

    y = x * x;
    y = Math.Sqrt(y);
    y *= -0.4;
    y -= 0.5;
    y /= x;

    return y;
}

double Derivative2(double x)
{
    double y = 0;

    y = 0.5 / (x * x);

    return y;
}