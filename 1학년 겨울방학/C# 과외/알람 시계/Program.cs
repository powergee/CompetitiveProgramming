using System;

namespace 알람_시계
{
    class Program
    {
        static void Main(string[] args)
        {
            string input = Console.ReadLine();
            string[] numbers = input.Split(" ");

            int h = int.Parse(numbers[0]);
            int m = int.Parse(numbers[1]);

            int total = h * 60 + m;
            
            if (total >= 45)
                total -= 45;
            else
                total = 24*60 - (45 - total);

            Console.WriteLine($"{total / 60} {total % 60}");
        }
    }
}
