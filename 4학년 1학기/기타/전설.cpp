#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#define COLOR_PADDING 1001
#define NAME_PADDING 1001
#define PSUEDO_NULL ('A')

std::vector<bool> matchToekns(std::string& query, std::vector<std::string>& tokens) {
    int l = 0, r = tokens.size();
    std::vector<bool> result(query.size(), false);
    for (int i = 0; i < query.size(); ++i) {
        auto compare = [=](const std::string& t1, const std::string& t2) -> bool {
            return t1[i] < t2[i];
        };
        auto lower = std::lower_bound(tokens.begin()+l, tokens.begin()+r, query, compare);
        auto upper = std::upper_bound(tokens.begin()+l, tokens.begin()+r, query, compare);
        if (lower == upper) {
            break;
        }
        if (lower->at(i+1) == PSUEDO_NULL) {
            result[i] = true;
        }
        l = lower-tokens.begin();
        r = upper-tokens.begin();
    }
    return result;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int c, n;
    std::cin >> c >> n;

    std::vector<std::string> colors(c);
    for (int i = 0; i < c; ++i) {
        std::cin >> colors[i];
        colors[i].resize(COLOR_PADDING, PSUEDO_NULL);
    }
    std::sort(colors.begin(), colors.end());

    std::vector<std::string> names(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> names[i];
        std::reverse(names[i].begin(), names[i].end());
        names[i].resize(NAME_PADDING, PSUEDO_NULL);
    }
    std::sort(names.begin(), names.end());

    int q;
    std::cin >> q;
    while (q--) {
        std::string query;
        std::cin >> query;
        std::string rev = query;
        std::reverse(rev.begin(), rev.end());

        auto colorMatched = matchToekns(query, colors);
        auto nameMatched = matchToekns(rev, names);
        std::reverse(nameMatched.begin(), nameMatched.end());

        bool yes = false;
        for (int i = 0; i+1 < query.size(); ++i) {
            if (colorMatched[i] && nameMatched[i+1]) {
                yes = true;
            }
        }
        std::cout << (yes ? "Yes\n" : "No\n");
    }

    return 0;
}