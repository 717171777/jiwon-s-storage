#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int findBenchIndex(const std::vector<std::vector<int>>& waitroom, int p) {
    if (waitroom.empty() || (waitroom.size() == 1 && waitroom[0].empty())) {
        return 0;
    }
    int target_idx = -1;
    int predecessor = -1;
    for (int i = 0; i < waitroom.size(); ++i) {
        for (int num : waitroom[i]) {
            if (num < p && num > predecessor) {
                predecessor = num;
                target_idx = i;
            }
        }
    }
    if (target_idx != -1) return target_idx;
    int successor = -1;
    int successor_bench_idx = -1;
    for (int i = 0; i < waitroom.size(); ++i) {
        for (int num : waitroom[i]) {
            if (num > p) {
                if (successor == -1 || num < successor) {
                    successor = num;
                    successor_bench_idx = i;
                }
            }
        }
    }
    if (successor_bench_idx != -1) return successor_bench_idx;
    return waitroom.size() - 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, k;
    std::cin >> N >> k;

    int max_capacity_before_split = 2 * k - 1;
    std::vector<std::vector<int>> waitroom;
    
    for (int i = 0; i < N; ++i) {
        char command;
        int p;
        std::cin >> command >> p;

        if (command == '+') {
            if (waitroom.empty()) {
                waitroom.push_back({});
            }
            int bench_idx = findBenchIndex(waitroom, p);
            if (waitroom.size() == 1 && waitroom[0].empty()) {
                bench_idx = 0;
            }
            auto& target_bench = waitroom[bench_idx];

            if (target_bench.size() >= max_capacity_before_split) {
                std::vector<int> temp_bench = target_bench;
                auto it = std::lower_bound(temp_bench.begin(), temp_bench.end(), p);
                temp_bench.insert(it, p);

                std::vector<int> new_bench1, new_bench2;

                for (int j = 0; j < k; ++j) {
                    new_bench1.push_back(temp_bench[j]);
                }
                for (int j = 0; j < k; ++j) {
                    new_bench2.push_back(temp_bench[k + j]);
                }
                
                waitroom[bench_idx] = new_bench1;
                waitroom.insert(waitroom.begin() + bench_idx + 1, new_bench2);

            } else {
                auto it = std::lower_bound(target_bench.begin(), target_bench.end(), p);
                target_bench.insert(it, p);
            }
        } 
        else if (command == '-') {
            bool found = false;
            for (size_t bench_idx = 0; bench_idx < waitroom.size(); ++bench_idx) {
                for (size_t person_idx = 0; person_idx < waitroom[bench_idx].size(); ++person_idx) {
                    if (waitroom[bench_idx][person_idx] == p) {
                        waitroom[bench_idx].erase(waitroom[bench_idx].begin() + person_idx);
                        
                        if (waitroom[bench_idx].empty()) {
                            waitroom.erase(waitroom.begin() + bench_idx);
                        }
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
    }

    for (const auto& bench : waitroom) {
        if (!bench.empty()) {
            std::cout << bench[0] << "\n";
        }
    }

    return 0;
}