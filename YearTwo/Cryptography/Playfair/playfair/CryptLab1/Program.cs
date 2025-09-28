using System;
using System.Collections.Generic;

class Encoder
{
    static void Main()
    {
        char[,] table =
        {
            {'W', 'H', 'E', 'A', 'T'}, 
            {'S', 'O', 'N', 'B', 'C'},
            {'D', 'F', 'G', 'I', 'K'}, 
            {'L', 'M', 'P', 'Q', 'R'}, 
            {'U', 'V', 'X', 'Y', 'Z'}
        };

        Console.WriteLine("Enter string:");
        string input = Console.ReadLine().ToUpper();

        string filteredStr = "";
        foreach (char c in input)
        {
            if (char.IsLetter(c))
            {
                filteredStr += c;
            }
        }

        List<char[]> pairs = new List<char[]>();
        for (int i = 0; i < filteredStr.Length; i++)
        {
            char first = filteredStr[i];
            if (i + 1 < filteredStr.Length)
            {
                char second = filteredStr[i + 1];
                if (first == second)
                {
                    pairs.Add(new char[] { first, 'X' });
                    
                }
                else
                {
                    pairs.Add(new char[] { first, second });
                    i++;
                }
            }
            else
            {
                pairs.Add(new char[] { first, 'X' });
            }
        }
        
        foreach(char[] arr in pairs){
            foreach(char c in arr){
                Console.Write(c);
            }
            Console.WriteLine("");
        }

        string encodedStr = "";
        foreach (var pair in pairs)
        {
            int[] pos1 = FindPosition(table, pair[0]);
            int[] pos2 = FindPosition(table, pair[1]);

            if (pos1[0] == pos2[0])
            {
                encodedStr += table[pos1[0], (pos1[1] + 1) % 5];
                encodedStr += table[pos2[0], (pos2[1] + 1) % 5];
            }
            else if (pos1[1] == pos2[1])
            {
                encodedStr += table[(pos1[0] + 1) % 5, pos1[1]];
                encodedStr += table[(pos2[0] + 1) % 5, pos2[1]];
            }
            else
            {
                encodedStr += table[pos1[0], pos2[1]];
                encodedStr += table[pos2[0], pos1[1]];
            }
        }

        Console.WriteLine($"Encoded String: {encodedStr}");
    }

    static int[] FindPosition(char[,] table, char c)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (table[i, j] == c)
                {
                    return new int[] { i, j };
                }
            }
        }
        throw new Exception("Character not found in table");
    }
}