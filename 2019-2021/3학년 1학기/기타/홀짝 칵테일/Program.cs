using System;
using System.Linq;

var nums = Console.ReadLine().Split().Select(int.Parse).ToArray();
bool hasOdd = false;
int oddMul = 1;
int totalMul = 1;
foreach (var n in nums) {
    if (n % 2 != 0) {
        hasOdd = true;
        oddMul *= n;
    }
    totalMul *= n;
}

if (hasOdd) {
    Console.WriteLine(oddMul);
} else {
    Console.WriteLine(totalMul);
}