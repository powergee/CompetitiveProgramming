using System;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            int init = int.Parse(Console.ReadLine());
            int result = init;
            int count = 0;

            do
            {
                int n1 = result % 10;
                int n10 = (result - n1) / 10;
                int sum = n1 + n10;

                result = n1 * 10 + (sum % 10);
                ++count;
            } while (init != result);

            Console.WriteLine(count);
        }
    }
}