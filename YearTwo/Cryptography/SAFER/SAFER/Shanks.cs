using System;
using System.Collections.Generic;
using System.Numerics;

public class BabyStepGiantStep
{
    // Возвращает x, где base^x ≡ result (mod p)
    public static BigInteger DiscreteLog(BigInteger baseValue, BigInteger result, BigInteger p)
    {
        // Определяем размер m
        BigInteger m = (BigInteger)Math.Ceiling(Math.Sqrt((double)p));

        // Создаем словарь для хранения значений base^j mod p
        Dictionary<BigInteger, BigInteger> valueTable = new Dictionary<BigInteger, BigInteger>();

        // Вычисляем base^j для j = 0, 1, ..., m-1 и сохраняем в словарь
        BigInteger currentValue = 1;
        for (BigInteger j = 0; j < m; j++)
        {
            valueTable[currentValue] = j;
            currentValue = (currentValue * baseValue) % p;
        }

        // Вычисляем обратное значение base^-m mod p
        BigInteger baseInverse = ModInverse(BigInteger.ModPow(baseValue, m, p), p);

        currentValue = result;
        for (BigInteger i = 0; i < m; i++)
        {
            if (valueTable.ContainsKey(currentValue))
            {
                // Если нашли совпадение, возвращаем ответ
                return i * m + valueTable[currentValue];
            }
            currentValue = (currentValue * baseInverse) % p;
        }

        // Если не нашли решения
        return -1;
    }

    // Вычисление обратного по модулю с использованием расширенного алгоритма Евклида
    public static BigInteger ModInverse(BigInteger a, BigInteger m)
    {
        BigInteger m0 = m, t, q;
        BigInteger x0 = 0, x1 = 1;

        if (m == 1)
            return 0;

        while (a > 1)
        {
            q = a / m;
            t = m;

            // m теперь остаток
            m = a % m;
            a = t;
            t = x0;

            x0 = x1 - q * x0;
            x1 = t;
        }

        if (x1 < 0)
            x1 += m0;

        return x1;
    }
}
