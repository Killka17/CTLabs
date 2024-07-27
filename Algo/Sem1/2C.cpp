#include <iostream>
#include <iomanip>

int main() {
    int n;
    double a;
    std::cin >> n >> a;

    double min_razn = 1;
    double max_razn = 999.99999999;
    double h[1000];

    while (max_razn - min_razn > 1e-8) {
        int f = 0;
        double med = min_razn + (max_razn - min_razn) / 2;
        // Максимальный размер массива
        h[0] = a;
        h[1] = med;

        for (int i = 1; i < n - 1; ++i) {
            h[i + 1] = 2 * h[i] + 2 - h[i - 1];
            if (h[i + 1] <= 0) {
                f = 1;
                break;
            }
        }

        if (f) {
            min_razn = med;
        } else {
            max_razn = med;
        }
    }

    std::cout << std::fixed << std::setprecision(2) << h[n - 1] << std::endl;

    return 0;
}