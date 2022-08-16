#include <iostream>

int main() {
    long long n, m, a, k;
    std::cin >> n >> m >> a >> k;
    
    long long maxTeams = std::min(n-1, a-k) + 1;
    long long minTeams = (a-k)/m + (((a-k)%m) ? 1 : 0) + 1;

    std::cout << maxTeams << " " << minTeams;

    return 0;
}