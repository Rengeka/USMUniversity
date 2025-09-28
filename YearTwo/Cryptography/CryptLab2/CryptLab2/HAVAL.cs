namespace CryptLab2;

public static class HAVAL
{
    public static int Iterations;
    public static int HashSize;
    
    private static readonly uint[] IV = {
        0x243F6A88, 0x85A308D3, 0x13198A2E, 0x03707344,
        0xA4093822, 0x299F31D0, 0x082EFA98, 0xEC4E6C89
    };

    public static byte[] GetHash(byte[] input)
    {
        uint[] state = new uint[8]; 
        Array.Copy(IV, state, IV.Length);
        
        int blockSize = 128; // 1024 бита
        int paddedLength = ((input.Length + blockSize - 1) / blockSize) * blockSize;
        byte[] paddedInput = new byte[paddedLength];
        Array.Copy(input, paddedInput, input.Length);
        
        paddedInput[input.Length] = 0x80;
        Array.Copy(BitConverter.GetBytes(input.Length * 8), 0, paddedInput, paddedLength - 4, 4);
        
        for (int i = 0; i < paddedInput.Length; i += blockSize)
        {
            ProcessBlock(paddedInput, i, state, Iterations);
        }
        
        return FinalizeHash(state, HashSize);
    }
    
    private static void ProcessBlock(byte[] block, int offset, uint[] state, int rounds)
    {
        uint[] words = new uint[32];
        for (int i = 0; i < 32; i++)
        {
            words[i] = BitConverter.ToUInt32(block, offset + i * 4);
        }
        
        for (int round = 0; round < rounds; round++)
        {
            for (int i = 0; i < 8; i++)
            {
                state[i] = NonLinearFunction(state[i], words, i);
            }
        }
    }
    
    // Should change every round
    private static uint NonLinearFunction(uint x, uint[] words, int index)
    {
        return (x ^ words[index]) + RotateLeft(x, index + 1);
    }
    
    private static uint RotateLeft(uint x, int n)
    {
        return (x << n) | (x >> (32 - n));
    }
    
    private static byte[] FinalizeHash(uint[] state, int hashSize)
    {
        int byteSize = hashSize / 8;
        byte[] hash = new byte[byteSize];

        for (int i = 0; i < byteSize / 4; i++)
        {
            Array.Copy(BitConverter.GetBytes(state[i]), 0, hash, i * 4, 4);
        }

        return hash;
    }
}