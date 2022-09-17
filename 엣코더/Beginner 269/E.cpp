#include <iostream>
#include <vector>

int query(int a, int b, int c, int d) {
    std::cout << "? " << a << " " << b << " " << c << " " << d << "\n";
    std::cout.flush();
    int res;
    std::cin >> res;
    return res;
}

int main() {
    int n;
    std::cin >> n;
    int ansR, ansC;

    {
        int l = 1, r = n;
        while (l < r) {
            int m = (l+r) / 2;
            int count = query(1, n, 1, m);
            if (count < m) {
                r = m;
            } else {
                l = m+1;
            }
        }
        ansC = l;
    }

    {
        int l = 1, r = n;
        while (l < r) {
            int m = (l+r) / 2;
            int count = query(1, m, 1, n);
            if (count < m) {
                r = m;
            } else {
                l = m+1;
            }
        }
        ansR = l;
    }

    std::cout << "! " << ansR << " " << ansC << "\n";

    return 0;
}