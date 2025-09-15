#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n_bidders;
    if (!(std::cin >> n_bidders)) {
        std::cout << "NONE\n";
        return 0;
    }

    std::map<int, std::vector<std::string>> bids;
    for (int i = 0; i < n_bidders; ++i) {
        std::string name;
        int price;
        std::cin >> name >> price;
        bids[price].push_back(name);
    }

    std::string winner = "NONE";
    for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
        if (it->second.size() == 1) {
            winner = it->second[0];
            break;
        }
    }

    std::cout << winner << std::endl;

    return 0;
}