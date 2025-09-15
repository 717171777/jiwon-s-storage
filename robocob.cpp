#include <iostream>
#include <vector>
#include <cmath>

// Point 구조체는 x, y 좌표를 저장합니다.
struct Point {
    long long x, y;
};

int main() {
    // 입출력 속도 최적화
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int K;
    std::cin >> K;

    std::vector<Point> vertices(K);
    for (int i = 0; i < K; ++i) {
        std::cin >> vertices[i].x >> vertices[i].y;
    }

    std::vector<long long> timePoints(5);
    for (int i = 0; i < 5; ++i) {
        std::cin >> timePoints[i];
    }

    // 각 변의 길이를 저장하는 벡터
    std::vector<long long> segmentLengths(K);
    long long totalPerimeter = 0;

    for (int i = 0; i < K; ++i) {
        Point current = vertices[i];
        Point next = vertices[(i + 1) % K]; //K번째 점 다음은 첫 번째 점
        long long length = std::abs(current.x - next.x) + std::abs(current.y - next.y);
        segmentLengths[i] = length;
        totalPerimeter += length;
    }

    // 각 시간 지점(time point)에 대한 로봇 위치 계산 및 출력
    for (long long t : timePoints) {  //timePoints 벡터의 각 시간을 t에 대응하고 그 시간에 대해 반복
        // 둘레를 기준으로 나머지 연산을 통해 실제 이동할 거리를 계산
        long long distanceToTravel = t % totalPerimeter;
        
        long long currentDistance = 0;
        Point currentPosition = vertices[0];
        
        for (int i = 0; i < K; ++i) {
            long long segmentLength = segmentLengths[i];

            // 현재 변에서 로봇의 위치를 찾음
            if (currentDistance + segmentLength >= distanceToTravel) {
                long long remainingDistance = distanceToTravel - currentDistance;
                Point nextPosition = vertices[(i + 1) % K];
                
                // 수직 또는 수평 이동 방향에 따라 좌표 계산
                if (currentPosition.x == nextPosition.x) { // 수직 이동
                    if (nextPosition.y > currentPosition.y) {
                        currentPosition.y += remainingDistance;
                    } else {
                        currentPosition.y -= remainingDistance;
                    }
                } else { // 수평 이동
                    if (nextPosition.x > currentPosition.x) {
                        currentPosition.x += remainingDistance;
                    } else {
                        currentPosition.x -= remainingDistance;
                    }
                }
                
                std::cout << currentPosition.x << " " << currentPosition.y << "\n";
                break;
            }
            
            // 다음 변으로 이동
            currentDistance += segmentLength;
            currentPosition = vertices[(i + 1) % K];
        }
    }

    return 0;
}
