#include <iostream>
#include <vector>

/*
n=1: 
n=2: 
n=3: 
n=4: { 1 2 1 0 } { 2 0 2 0 } 
n=5: { 2 1 2 0 0 } 
n=6: 
n=7: { 3 2 1 1 0 0 0 } 
n=8: { 4 2 1 0 1 0 0 0 } 
n=9: { 5 2 1 0 0 1 0 0 0 }
*/

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        switch (n)
        {
        case 1: case 2: case 3: case 6:
            std::cout << "0\n";
            break;
        case 4:
            std::cout << "2\n";
            break;

        default:
            std::cout << "1\n";
            break;
        }
    }

    return 0;
}