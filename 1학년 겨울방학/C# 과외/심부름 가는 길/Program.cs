using System;

namespace 심부름_가는_길
{
    class Program
    {
        static void Main(string[] args)
        {
            int t1 = int.Parse(Console.ReadLine());
            int t2 = int.Parse(Console.ReadLine());
            int t3 = int.Parse(Console.ReadLine());
            int t4 = int.Parse(Console.ReadLine());

            int total = t1+t2+t3+t4;

            Console.WriteLine(total / 60);
            Console.WriteLine(total % 60);
        }
    }
}
