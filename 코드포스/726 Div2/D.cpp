/*
Theorem 0: If you get an odd number, the only thing you can do is subtracting an odd number, resulting in an even number which is not a power of 2 and you will lose.
*/

/*
Theorem 1: If you get an even number which is not a power of 2, subtracting the odd number on every moves works and you will win.

Premise 0: If he or she receive an odd number, the only thing to do is subtracting an odd number, resulting in an even number.
Premise 1: Primes are losing.
Premise 2: Every prime is odd or 2.

It works to give the other player an odd number or a prime number.
	- because it will either be a prime(the other player loses), or they will make a move and give you another even number that is not 2.
		* (Why not 2?) It is impossible to receive 2. even number(-odd) -> odd number(-odd) -> 2
	- You can continue this process because you will never land on a losing number and because the game must end after a finite number of moves, your opponent must always lose.
*/

/*
Theorem 2: If you get a power of 2, you win if and only if log2(n) is even.

You can subtract an another power of 2. In other words, you will halve that number or make an even number which is not a power of 2. The latter one is not beneficial because of Theorem 1, so the only option is to halve it.

After long ping-pong, the one who get 2 will lose. As a result, you will win if and only if log2(n) is even.
*/

#include <iostream>

int log2(int n) {
    int result = 0;
    while (n > 1) {
        ++result;
        n /= 2;
    }
    return result;
}

bool canWin(int n) {
    if (n % 2) {
        return false;
    } else if (__builtin_popcount(n) == 1) {
        return log2(n) % 2 == 0;
    } else {
        return true;
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        printf(canWin(n) ? "Alice\n" : "Bob\n");
    }

    return 0;
}