#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double x1, y1, r1, x2, y2, r2;
    // Read the input for the two circular enclosures.
    std::cin >> x1 >> y1 >> r1;
    std::cin >> x2 >> y2 >> r2;

    const double PI = 3.14159265358979;

    // Calculate the distance between the centers.
    double d = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));

    double area, perimeter;

    // If the radii are different, use the formula for external tangents.
    if (r1 != r2) {
        // Ensure r1 is the larger radius for the angle calculation.
        if (r1 < r2) {
            std::swap(r1, r2);
        }
        
        // Calculate the length of the tangent segments.
        double tangent_length = std::sqrt(std::pow(d, 2) - std::pow(r1 - r2, 2));
        
        // Calculate the angle in radians.
        double theta = std::acos((r1 - r2) / d);
        
        // Calculate the perimeter.
        perimeter = 2 * tangent_length + (2 * PI - 2 * theta) * r1 + 2 * theta * r2;
        
        // Calculate the area.
        area = tangent_length * (r1 + r2) + std::pow(r1, 2) * (PI - theta) + std::pow(r2, 2) * theta;
        
    } else { // If the radii are the same, the tangent calculation is simpler.
        perimeter = 2 * d + 2 * PI * r1;
        area = 2 * r1 * d + PI * std::pow(r1, 2);
    }
    
    // Output the floor of the calculated area and perimeter as specified.
    std::cout << static_cast<long long>(area) <<" " << static_cast<long long>(perimeter) << std::endl;

    return 0;
}