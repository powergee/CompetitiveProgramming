package main

import "fmt"

var n int
var dp [1000001]int
const MOD int = 15746

func countCases(remain int) int {
	if remain == 0 {
		return 1
	}

	if remain < 0 {
		return 0
	}

	if dp[remain] != -1 {
		return dp[remain]
	}

	dp[remain] = (countCases(remain-1) + countCases(remain-2)) % MOD
	return dp[remain]
}

func main()  {
	fmt.Scan(&n)
	for i := 0; i <= n; i++ {
		dp[i] = -1
	}
	fmt.Print(countCases(n))
}