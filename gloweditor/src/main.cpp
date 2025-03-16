#include <iostream>

#include "GlowEngine/engine.h"

int main()
{
    std::cout << "Hello World!" << '\n';
    std::cout << Glow::Add(5, 5) << '\n';
    std::cout << Glow::Sub(25, 5) << '\n';
    std::cin.get();
}