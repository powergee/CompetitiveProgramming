using System;

namespace 시험_성적
{
    class Program
    {
        static void Main(string[] args)
        {
            int score = int.Parse(Console.ReadLine());

            if (90 <= score && score <= 100)
                Console.Write("당신의 학점은 A입니다!");
            else if (80 <= score && score <= 89)
                Console.Write('B');
            else if (70 <= score && score <= 79)
                Console.Write('C');
            else if (60 <= score && score <= 69)
                Console.Write('D');
            else
                Console.Write('F');
        }
    }
}
