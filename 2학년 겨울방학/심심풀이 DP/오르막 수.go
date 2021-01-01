package main

import (
	"fmt"
)

var n int
var dp [1001][10]int
const MOD int = 10007

func countCases(remain int, before int) int {
	if remain <= 0 {
		return 1
	}

	if dp[remain][before] != 0 {
		return dp[remain][before]
	}

	result := 0
	for i := before; i <= 9; i += 1 {
		result += countCases(remain - 1, i)
		result %= MOD
	}

	dp[remain][before] = result
	return result
}

func main() {
	fmt.Scanf("%v", &n);
	fmt.Println(countCases(n, 0))
}