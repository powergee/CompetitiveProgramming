using System;
using System.Collections.Generic;

namespace Two_Machines {
    class Job {
        public int A { get; set; }
        public int B { get; set; }
    }

    class Program {
        static int n, aTotal, bTotal;
        static List<Job> jobs = new();
        static int[,] bTime;
        
        static int GetMaxRestingOfB(int start, int aRunning) {
            if (aRunning == 0 || start == n) {
                return 0;
            }

            ref int result = ref bTime[start, aRunning];
            if (result != int.MinValue) {
                return result;
            }

            if (jobs[start].A <= aRunning) {
                result = Math.Max(result, GetMaxRestingOfB(start+1, aRunning-jobs[start].A) + jobs[start].B);
            }
            result = Math.Max(result, GetMaxRestingOfB(start+1, aRunning));

            return result;
        }

        static void Main(string[] args) {
            n = int.Parse(Console.ReadLine());
            aTotal = bTotal = 0;

            for (int i = 0; i < n; ++i) {
                var tokens = Console.ReadLine().Split();
                var (a, b) = (int.Parse(tokens[0]), int.Parse(tokens[1]));
                aTotal += a;
                bTotal += b;
                jobs.Add(new Job() { A=a, B=b });
            }

            bTime = new int[n, aTotal+1];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j <= aTotal; ++j) {
                    bTime[i, j] = int.MinValue;
                }
            }

            int answer = int.MaxValue;
            for (int aRunning = 1; aRunning <= aTotal; ++aRunning) {
                int bRunning = bTotal - GetMaxRestingOfB(0, aRunning);
                answer = Math.Min(answer, Math.Max(aRunning, bRunning));
            }
            Console.WriteLine(answer);
        }
    }
}
