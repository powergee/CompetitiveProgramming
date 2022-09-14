package main

import (
	"fmt"
	"bufio"
	"os"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

var n, k int
var value [100]int
var dp [100][10001]int

func countCases(first int, need int) int {
	if (need <= 0) {
		return 1
	}

	if (n <= first) {
		return 0
	}

	if (dp[first][need] != -1) {
		return dp[first][need]
	}

	result := 0
	for i := 0; value[first]*i <= need; i++ {
		result += countCases(first+1, need - value[first]*i)
	}

	dp[first][need] = result
	return result
}

func main()  {
	defer writer.Flush()

	fmt.Fscan(reader, &n, &k)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &value[i])
	}

	for i := 0; i < n; i++ {
		for j := 0; j <= k; j++ {
			dp[i][j] = -1
		}
	}

	fmt.Fprint(writer, countCases(0, k))
}