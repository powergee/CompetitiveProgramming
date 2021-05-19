using System;
using System.Linq;

namespace A {
    class Program {
        static void Main(string[] args) {
            int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
            Array.Sort(a);
            if (a[1] - a[0] == a[2] - a[1]) {
                Console.WriteLine("Yes");
            } else {
                Console.WriteLine("No");
            }
        }
    }
}
