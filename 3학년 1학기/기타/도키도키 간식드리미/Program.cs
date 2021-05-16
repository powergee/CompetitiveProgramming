using System;
using System.Collections.Generic;
using System.Linq;

namespace 도키도키_간식드리미 {
    class Program {
        static void Main(string[] args) {
            int n = int.Parse(Console.ReadLine());
            var stu = Console.ReadLine().Split().Select(int.Parse).ToArray();

            bool nice = true;
            int next = 1;
            Stack<int> side = new Stack<int>();
            Queue<int> hall = new Queue<int>(stu);
            
            while ((hall.Count > 0 || side.Count > 0) && nice) {
                if (hall.Count > 0 && hall.Peek() == next) {
                    hall.Dequeue();
                    next++;
                } else if (side.Count > 0 && side.Peek() == next) {
                    side.Pop();
                    next++;
                } else if (hall.Count > 0) {
                    side.Push(hall.Dequeue());
                } else {
                    nice = false;
                }
            }

            if (nice) {
                Console.WriteLine("Nice");
            } else {
                Console.WriteLine("Sad");
            }
        }
    }
}