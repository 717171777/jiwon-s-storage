#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int findBenchIndex(const std::vector<std::vector<int>>& waitroom, int p) {
    if (waitroom.empty() || (waitroom.size() == 1 && waitroom[0].empty())) return 0;
    int target_idx = -1, predecessor = -1;
    for (int i = 0; i < waitroom.size(); ++i) {
        for (int num : waitroom[i]) {
            if (num < p && num > predecessor) {
                predecessor = num;
                target_idx = i;
            }
        }
    }
    if (target_idx != -1) return target_idx;
    int successor = -1, successor_bench_idx = -1;
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
            if (waitroom.empty()) waitroom.push_back({});
            
            int bench_idx = findBenchIndex(waitroom, p);
            auto& target_bench = waitroom[bench_idx];

            if (target_bench.size() >= max_capacity_before_split) {
                std::vector<int> temp_bench = target_bench;
                temp_bench.insert(std::lower_bound(temp_bench.begin(), temp_bench.end(), p), p);
                
                std::vector<int> new_bench1(temp_bench.begin(), temp_bench.begin() + k);
                std::vector<int> new_bench2(temp_bench.begin() + k, temp_bench.end());
                
                waitroom[bench_idx] = new_bench1;
                waitroom.insert(waitroom.begin() + bench_idx + 1, new_bench2);
            } else {
                target_bench.insert(std::lower_bound(target_bench.begin(), target_bench.end(), p), p);
            }
        } 
        else if (command == '-') {
            for (auto& bench : waitroom) {
                auto it = std::find(bench.begin(), bench.end(), p);
                if (it != bench.end()) {
                    bench.erase(it);
                    break; 
                }
            }
            waitroom.erase(std::remove_if(waitroom.begin(), waitroom.end(), 
                [](const auto& v){ return v.empty(); }), waitroom.end());
        }
    }

    for (const auto& bench : waitroom) {
        if (!bench.empty()) {
            std::cout << bench[0] << "\n";
        }
    }
    return 0;
}