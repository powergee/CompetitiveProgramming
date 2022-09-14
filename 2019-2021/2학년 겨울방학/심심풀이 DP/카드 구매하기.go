package main

import (
	"fmt"
	"bufio"
	"os"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

var n int
var arr [1001]int
var dp [1001]int

func getMax(need int) int {
	if need <= 0 {
		return 0
	}

	if dp[need] != -1 {
		return dp[need]
	}

	for i := 1; i <= need; i += 1 {
		current := getMax(need - i) + arr[i]
		if dp[need] < current {
			dp[need] = current
		}
	}

	return dp[need];
}

func main() {
	fmt.Fscan(reader, &n)

	for i := 1; i <= n; i += 1 {
		fmt.Fscan(reader, &arr[i])
		dp[i] = -1
	}

	fmt.Fprintln(writer, getMax(n))
	writer.Flush()
}