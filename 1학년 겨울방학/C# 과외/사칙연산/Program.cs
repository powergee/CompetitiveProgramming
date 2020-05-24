using System;

namespace 사칙연산
{
    class Program
    {
        static void Main(string[] args)
        {
            string input = Console.ReadLine();
            string[] numbers = input.Split(" ");

            int a = int.Parse(numbers[0]);
            int b = int.Parse(numbers[1]);

            Console.WriteLine(a + b);
            Console.WriteLine(a - b);
            Console.WriteLine(a * b);
            Console.WriteLine(a / b);
            Console.WriteLine(a % b);
        }
    }
}
