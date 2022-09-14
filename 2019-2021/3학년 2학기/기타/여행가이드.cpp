#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

struct Client {
    double x, y, v, a;

    std::tuple<double, double, double, double> toTuple() const {
        return std::tie(x, y, v, a);
    }

    bool operator<(const Client& c) const {
        return toTuple() < c.toTuple();
    }
};

double solveQuadratic(double a, double b, double c) {
    double s1 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
    double s2 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
    return s1 >= 0 ? s1 : s2;
}

int main() {
    int n;
    scanf("%d", &n);

    double vm;
    scanf("%lf", &vm);

    std::vector<Client> clients(n);
    for (int i = 0; i < n; ++i) {
        double x, y, v, a;
        scanf("%lf %lf %lf %lf", &x, &y, &v, &a);
        clients[i] = { x, y, v, a };
    }
    std::sort(clients.begin(), clients.end());

    double answer = INT64_MAX;
    do {
        auto c = clients;
        double xm = 0, ym = 0;
        double elapsed = 0;
        double total = 0;

        for (int i = 0; i < n; ++i) {
            c[i].x += elapsed * c[i].v * cos(c[i].a);
            c[i].y += elapsed * c[i].v * sin(c[i].a);

            double A = c[i].v * cos(c[i].a);
            double B = c[i].v * sin(c[i].a);
            double Dx = c[i].x - xm;
            double Dy = c[i].y - ym;
            
            double t = solveQuadratic(c[i].v*c[i].v - vm*vm, 2*(A*Dx + B*Dy), Dx*Dx + Dy*Dy);
            elapsed += t;

            c[i].x += t * c[i].v * cos(c[i].a);
            c[i].y += t * c[i].v * sin(c[i].a);
            xm = c[i].x;
            ym = c[i].y;
            total = std::max(total, elapsed+sqrt(c[i].x*c[i].x + c[i].y*c[i].y) / c[i].v);
        }

        answer = std::min(answer, total);
    } while (std::next_permutation(clients.begin(), clients.end()));

    printf("%d", (int)round(answer));

    return 0;
}