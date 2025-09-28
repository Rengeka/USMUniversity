using System.Text;
using CryptLab2;

string inputString = "SCHELLOHAVALHASH";
HAVAL.HashSize = 128;
HAVAL.Iterations = 3;
byte[] inputBytes = Encoding.UTF8.GetBytes(inputString);

var hash = HAVAL.GetHash(inputBytes);

foreach (var block in hash)
{
    Console.Write((char)block);
}



