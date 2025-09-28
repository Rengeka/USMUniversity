using System.Numerics;

string strKey = "CSABCDEF";
byte[] key = new byte[8];

for (int i = 0; i < 8; i++)
{
    key[i] = Convert.ToByte(strKey[i]);
}

string strMessage = "LIVELONG";
byte[] message = new byte[8];

for (int i = 0; i < 8; i++)
{
    message[i] = Convert.ToByte(strMessage[i]);
}

SAFER.key = key;
SAFER.rounds = 8;

Console.WriteLine("Encrypting");
var encryptedResult = SAFER.Encrypt(message);

Console.WriteLine();
Console.WriteLine("Encrypted result");

foreach (var value in encryptedResult)
{
    Console.Write(Convert.ToChar(value));
}

Console.WriteLine();

Console.WriteLine("\nDecrypting");
var res = SAFER.Decrypt(encryptedResult);

Console.WriteLine();
Console.WriteLine("Decrypted result");

foreach (var value in res)
{
    Console.Write(Convert.ToChar(value));
}

Console.WriteLine();

static class SAFER
{
    public static byte[] key { get; set; }
    public static int rounds { get; set; }

    public static byte[] Encrypt(byte[] message)
    {
        Console.WriteLine("Starting with : ");
        foreach (var v in message)
        {
            Console.Write(v + " ");
        }
        Console.WriteLine();
        
        for (int i = 0; i < rounds; i++)
        {
            Console.WriteLine($"Round {i}");

            /*for (int j = 0; j < 8; j += 2)
            {
                message[j] = ModuloSum(message[j], key[j]);
                message[j + 1] ^= key[j + 1];

                message[j] = (byte)BigInteger.ModPow(45, message[j], 257);
                message[j + 1] = (byte)BabyStepGiantStep.DiscreteLog(45, message[j + 1], 257);

                message[j] ^= key[j];
                message[j + 1] = ModuloSum(message[j + 1], key[j + 1]);
            }*/

            for (int j = 0; j < 8; j += 2)
            {
                message[j] = ModuloSum(message[j], key[j]);
                message[j + 1] ^= key[j + 1];
            }

            foreach (var v in message)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();
            
            for (int j = 0; j < 8; j += 2)
            {
                message[j] = (byte)BigInteger.ModPow(45, message[j], 257);
                message[j + 1] = (byte)BabyStepGiantStep.DiscreteLog(45, message[j + 1], 257);
            }
            
            foreach (var v in message)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();

            for (int j = 0; j < 8; j += 2)
            {
                message[j] ^= key[j];
                message[j + 1] = ModuloSum(message[j + 1], key[j + 1]);
            }
            
            foreach (var v in message)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();

            for (int j = 0; j < 8; j += 2)
            {
                message[j + 1] = ModuloSum(message[j], message[j + 1]);
                message[j] = ModuloSum(message[j], message[j + 1]);
            }

            foreach (var v in message)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();

            byte b = ModuloSum(message[0], message[2]);
            byte a = ModuloSum(message[0], b);

            byte f = ModuloSum(message[1], message[3]);
            byte e = ModuloSum(message[1], f);

            byte h = ModuloSum(message[5], message[7]);
            byte g = ModuloSum(message[5], h);

            byte d = ModuloSum(message[4], message[6]);
            byte c = ModuloSum(message[4], d);

            message[0] = a;
            message[1] = b;
            message[2] = c;
            message[3] = d;
            message[4] = e;
            message[5] = f;
            message[6] = g;
            message[7] = h;

            foreach (var v in message)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();

            b = ModuloSum(a, c);
            a = ModuloSum(a, b);
            d = ModuloSum(e, g);
            c = ModuloSum(e, d);
            f = ModuloSum(message[1], message[3]);
            e = ModuloSum(message[1], f);
            h = ModuloSum(h, message[5]);
            g = ModuloSum(h, message[5]);

            message[0] = a;
            message[1] = b;
            message[2] = c;
            message[3] = d;
            message[4] = e;
            message[5] = f;
            message[6] = g;
            message[7] = h;

            foreach (var v in message)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();
        }

        return message;
    }

    public static byte[] Decrypt(byte[] encryptedMessage)
    {
        Console.WriteLine("Starting with : ");
        foreach (var v in encryptedMessage)
        {
            Console.Write(v + " ");
        }
        Console.WriteLine();
        
        for (int i = 0; i < rounds; i++)
        {
            
            
            Console.WriteLine($"Round {i}");

            byte a = encryptedMessage[0];
            byte b = encryptedMessage[1];
            byte c = encryptedMessage[2];
            byte d = encryptedMessage[3];
            byte e = encryptedMessage[4];
            byte f = encryptedMessage[5];
            byte g = encryptedMessage[6];
            byte h = encryptedMessage[7];

            a = ModuloDiff(a, b);
            b = ModuloDiff(b, a);
            c = ModuloDiff(c, d);
            d = ModuloDiff(d, c);
            e = ModuloDiff(e, f);
            f = ModuloDiff(f, e);
            g = ModuloDiff(g, h);
            h = ModuloDiff(h, g);

            byte t = b;
            b = e;
            e = c;
            c = t;
            t = d;
            d = f;
            f = t;
            t = g;
            g = f;
            f = t;

            Console.Write(a + " ");
            Console.Write(b + " ");
            Console.Write(c + " ");
            Console.Write(d + " ");
            Console.Write(e + " ");
            Console.Write(f + " ");
            Console.Write(g + " ");
            Console.WriteLine(h);

            encryptedMessage[4] = ModuloDiff(c, d);
            encryptedMessage[6] = ModuloDiff(d, encryptedMessage[4]);

            encryptedMessage[5] = ModuloDiff(g, h);
            encryptedMessage[7] = ModuloDiff(h, encryptedMessage[5]);

            encryptedMessage[1] = ModuloDiff(e, f);
            encryptedMessage[3] = ModuloDiff(f, encryptedMessage[1]);

            encryptedMessage[0] = ModuloDiff(a, b);
            encryptedMessage[2] = ModuloDiff(b, encryptedMessage[0]);

            foreach (var v in encryptedMessage)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();

            for (int j = 0; j < 8; j += 2)
            {
                encryptedMessage[j] = ModuloDiff(encryptedMessage[j], encryptedMessage[j + 1]);
                encryptedMessage[j + 1] = ModuloDiff(encryptedMessage[j + 1], encryptedMessage[j]);
            }

            foreach (var v in encryptedMessage)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();


            /*for (int j = 0; j < 8; j += 2)
            {
                encryptedMessage[j] ^= key[j];
                encryptedMessage[j + 1] = ModuloDiff(encryptedMessage[j + 1], key[j + 1]);

                encryptedMessage[j + 1] = (byte)BigInteger.ModPow(45, encryptedMessage[j + 1], 257);
                encryptedMessage[j] = (byte)BabyStepGiantStep.DiscreteLog(45, encryptedMessage[j], 257);

                encryptedMessage[j] = ModuloDiff(encryptedMessage[j], key[j]);
                encryptedMessage[j + 1] ^= key[j + 1];
            }*/
            
            for (int j = 0; j < 8; j += 2)
            {
                encryptedMessage[j] ^= key[j];
                encryptedMessage[j + 1] = ModuloDiff(encryptedMessage[j + 1], key[j + 1]);
            }
            
            foreach (var v in encryptedMessage)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();
            
            for (int j = 0; j < 8; j += 2)
            {
                encryptedMessage[j + 1] = (byte)BigInteger.ModPow(45, encryptedMessage[j + 1], 257);
                encryptedMessage[j] = (byte)BabyStepGiantStep.DiscreteLog(45, encryptedMessage[j], 257);
            }
            
            foreach (var v in encryptedMessage)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();
            
            for (int j = 0; j < 8; j += 2)
            {
                encryptedMessage[j] = ModuloDiff(encryptedMessage[j], key[j]);
                encryptedMessage[j + 1] ^= key[j + 1];
            }

            foreach (var v in encryptedMessage)
            {
                Console.Write(v + " ");
            }
            Console.WriteLine();
        }

        return encryptedMessage;
    }

    public static byte ModuloSum(byte a, byte b)
    {
        return (byte)((a + b) % 256);
    }

    public static byte ModuloDiff(byte c, byte b)
    {
        return (byte)(((c - b) < 0) ? (c - b) + 256 : c - b);
    }
}