#include <iostream>

#include "GlowEngine/engine.h"

int main()
{
    Glow::Engine& engine = Glow::Engine::Instance();
    engine.Run();
}