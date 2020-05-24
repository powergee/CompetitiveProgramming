using System;

namespace 윤년
{
    class Program
    {
        static void Main(string[] args)
        {
            int year = int.Parse(Console.ReadLine());

            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                Console.Write('1');
            else Console.Write('0');
        }
    }
}
