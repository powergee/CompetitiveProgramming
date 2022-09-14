using System;
using System.Diagnostics;
using System.IO;

namespace Disks_Arrangement
{
    class Program
    {
        static readonly string ALG_PATH = @"C:\Users\Hyeoun\OneDrive - 서울시립대학교\알림\백준 코드\1학년 2학기\기타\Disks Arrangement\Disk Arrangement.exe";
        static readonly string GEN_PATH = @"C:\Users\Hyeoun\OneDrive - 서울시립대학교\알림\백준 코드\1학년 2학기\기타\Disks Arrangement\Disk Arrangement Test.exe";

        static void Main(string[] args)
        {
            Random r = new Random();

            string numList;
            string genAnswer;
            string algAnswer;

            ProcessStartInfo algStart = new ProcessStartInfo();
            ProcessStartInfo genStart = new ProcessStartInfo();

            algStart.UseShellExecute = false;
            algStart.RedirectStandardInput = true;
            algStart.RedirectStandardOutput = true;
            algStart.FileName = ALG_PATH;

            genStart.UseShellExecute = false;
            genStart.RedirectStandardInput = true;
            genStart.RedirectStandardOutput = true;
            genStart.FileName = GEN_PATH;

            for (int i = 1; ; ++i)
            {
                int N = r.Next(1, 11);
                Console.WriteLine($"{i}회차 : N = {N}");

                using (Process algProc = new Process())
                using (Process genProc = new Process())
                {
                    genStart.ArgumentList.Clear();
                    genStart.ArgumentList.Add(N.ToString());
                    genProc.StartInfo = genStart;
                    genProc.Start();
                    genProc.WaitForExit();

                    genProc.StandardOutput.ReadLine();
                    numList = genProc.StandardOutput.ReadLine();
                    genAnswer = genProc.StandardOutput.ReadLine();

                    Console.WriteLine(numList);
                    Console.WriteLine($"Gen 응답 : {genAnswer}");

                    algProc.StartInfo = algStart;
                    algProc.Start();

                    algProc.StandardInput.WriteLine(N.ToString());
                    algProc.StandardInput.WriteLine(numList);
                    algProc.WaitForExit();
                    
                    algAnswer = algProc.StandardOutput.ReadLine();
                    Console.WriteLine($"Alg 응답 : {algAnswer}");

                    double error = Math.Abs(double.Parse(genAnswer) - double.Parse(algAnswer));
                    Console.WriteLine($"차 : {error}");
                    if (error >= 1e-5)
                    {
                        Console.WriteLine("오차가 큽니다!");
                        break;
                    }

                    Console.WriteLine();
                }
            }
        }
    }
}
