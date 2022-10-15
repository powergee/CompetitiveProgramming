#include <iostream>
#include <vector>
#include <tuple>

char transform(int v) {
    switch (v) {
    case 1:  return '1';
    case 2:  return '5';
    case 5:  return '2';
    case 8:  return '8';
    default: return '?';
    }
}

int main() {
    char d;
    int n;
    std::cin >> d >> n; 
    
    char matrix[20][41] = {0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int v;
            std::cin >> v;
            char trans = transform(v);
            auto [ni, nj] = std::make_tuple(
                d == 'U' || d == 'D' ? n-1-i : i,
                d == 'L' || d == 'R' ? n-1-j : j
            );
            matrix[ni][2*nj] = trans;
            matrix[ni][2*nj+1] = ' ';
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << matrix[i] << "\n";
    }

    return 0;
}