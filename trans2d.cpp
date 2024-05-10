#include <iostream>

int main()
{
    float x, y;
    float scX, scY, trnsX, trnsY, shearX, shearY;
    std::cout << "Enter x and y" << std::endl;
    std::cin >> x, y;
    std::cout << "Enter the scaling factor : " << std::endl;
    std::cin >> scX >> scY;
    std::cout << "Enter the translation amount for x and y";
    std::cin >> trnsX >> trnsY;
    std::cout << "Enter the shearing for x and y";
    std::cin >> shearX >> shearY;
}