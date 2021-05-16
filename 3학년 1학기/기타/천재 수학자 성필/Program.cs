using System;
using System.Collections.Generic;

namespace 천재_수학자_성필
{
    class Program
    {
        static void Main(string[] args)
        {
            string exp = Console.ReadLine();
            Stack<int> s = new Stack<int>();

            foreach (char ch in exp) {
                if ('0' <= ch && ch <= '9') {
                    s.Push((int)(ch-'0'));
                } else {
                    int b = s.Pop();
                    int a = s.Pop();
                    switch (ch) {
                        case '+':
                            s.Push(a+b);
                            break;
                        case '-':
                            s.Push(a-b);
                            break;
                        case '*':
                            s.Push(a*b);
                            break;
                        case '/':
                            s.Push(a/b);
                            break;
                    }
                }
            }

            Console.WriteLine(s.Pop());
        }
    }
}
