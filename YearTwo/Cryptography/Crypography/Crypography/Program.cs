
using System.Numerics;

int n = 578;  
int b = 1182; 

EuclAlg(2187, 1482);
Alg1();
EuclAlg2(1237, 2239);

void EuclAlg2(int n, int b)
{
    int n0 = n;
    int b0 = b;
    int t0 = 0;
    int t = 1;
    int i = 0;
    
    Console.WriteLine("--------------------------------------------------------------");
    Console.WriteLine("| i  |  n0   |  b0   |  q   |  r   |  t0   |   t   |  temp   |");
    Console.WriteLine("--------------------------------------------------------------");
    
    int q = n0 / b0;
    int r = n0 - q * b0;

    while (r > 0)
    {
        int temp = t0 - q * t;
        
        if (temp >= 0)
        {
            temp = temp % n;
        }
        else
        {
            temp = n - ((-temp) % n);
        }
        
        Console.WriteLine($"| {i,2} | {n0,5} | {b0,5} | {q,4} | {r,4} | {t0,5} | {t,5} | {temp,7} |");
        i++;
        
        n0 = b0;
        b0 = r;
        t0 = t;
        t = temp;
        
        q = n0 / b0;
        r = n0 - q * b0;
    }
    
    Console.WriteLine("--------------------------------------------------------------");
    
    if (b0 != 1)
    {
        Console.WriteLine($"Обратного элемента для {b} по модулю {n} не существует.");
    }
    else
    {
        Console.WriteLine($"Обратный элемент для {b} по модулю {n} = {t}");
    }
}

void EuclAlg(int n, int b)
{
    int n0 = n;
    int b0 = b;
    int t0 = 0;
    int t = 1;
    int i = 0;
    
    Console.WriteLine("---------------------------------------------------");
    Console.WriteLine("| i  |  n0  |  b0  |  q  |  r  |  t0  |  t  |  temp |");
    Console.WriteLine("---------------------------------------------------");

    int q = n0 / b0;
    int r = n0 - q * b0;

    while (r > 0)
    {
        int temp = t0 - q * t;
        
        if (temp >= 0)
        {
            temp = temp % n;
        }
        else
        {
            temp = n - ((-temp) % n);
        }
        
        Console.WriteLine($"| {i,2} | {n0,4} | {b0,4} | {q,3} | {r,3} | {t0,4} | {t,3} | {temp,5} |");
        i++;
        
        n0 = b0;
        b0 = r;
        t0 = t;
        t = temp;
        
        q = n0 / b0;
        r = n0 - q * b0;
    }
    
    if (b0 != 1)
    {
        Console.WriteLine($"Обратного элемента для {b} по модулю {n} не существует.");
    }
    else
    {
        Console.WriteLine($"Обратный элемент для {b} по модулю {n} = {t}");
    }
}

void Alg1()
{
    int x = 1567;
    int c = 2417;
    int n = 8461;

    BigInteger z = 1;

    string binary = Convert.ToString(c, 2).PadLeft(12, '0');
    
    Console.WriteLine(" ------------------------------------------");
    Console.WriteLine("|  i  |  Ci  |            Z                |");
    Console.WriteLine(" ------------------------------------------");
    
    for (int i = 11; i >= 0; i--)
    {
        int index = 12 - i;
        char Ci = binary[11 - i]; 
        
        z = (z * z) % n;
        
        if (Ci == '1')
        {
            z = (z * x) % n;
        }
        
        Console.WriteLine($"| {index,3} |  {Ci,3} | {z,27} |");
    }
    
    Console.WriteLine(" ------------------------------------------");
    
    Console.WriteLine($"Результат: {z}");
}

string IntToString(int value, char[] baseChars)
{
    string result = string.Empty;
    int targetBase = baseChars.Length;

    do
    {
        result = baseChars[value % targetBase] + result;
        value = value / targetBase;
    } 
    while (value > 0);

    return result;
}