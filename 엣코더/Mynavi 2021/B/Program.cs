using System;
using System.Collections.Generic;

namespace B {
    class Program {
        static void Main(string[] args) {
            int n = int.Parse(Console.ReadLine());
            List<KeyValuePair<int, string>> mountains = new List<KeyValuePair<int, string>>();
            for (int i = 0; i < n; ++i) {
                var tokens = Console.ReadLine().Split();
                mountains.Add(new KeyValuePair<int, string>(int.Parse(tokens[1]), tokens[0]));
            }

            mountains.Sort((a, b) => {
                return a.Key.CompareTo(b.Key);
            });
            Console.WriteLine(mountains[mountains.Count-2].Value);
        }
    }
}
