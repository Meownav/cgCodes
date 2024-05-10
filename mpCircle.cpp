#include <iostream>

int main()
{
    float x, y, r, p;
    std::cout << "Enter the radius: ";
    std::cin >> r;
    x = 0;
    y = r;
    p = 1 - y;
    std::cout << x << " " << y << std::endl;

    while (x < y)
    {
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
        std::cout << x << " " << y << std::endl;
        std::cout << -x << " " << y << std::endl;
        std::cout << x << " " << -y << std::endl;
        std::cout << -x << " " << -y << std::endl;
        std::cout << y << " " << x << std::endl;
        std::cout << y << " " << -x << std::endl;
        std::cout << -y << " " << x << std::endl;
        std::cout << -y << " " << -x << std::endl;
    }
    return 0;
}
