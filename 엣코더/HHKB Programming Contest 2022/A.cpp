#include <iostream>
#include <string>

int main() {
    int input;
    std::cin >> input;
    
    int d1 = input / 100;
    int d2 = (input / 10) % 10;
    int d3 = input % 10;
    std::cout << 111*(d1+d2+d3);

    return 0;
}