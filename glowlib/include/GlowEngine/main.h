#pragma once
#include "GlowEngine/engine.h"
#include "GlowEngine/app.h"
#include <iostream>

//Needs to be implemented by client
//Pointer ownership belongs to GlowEngine
//Usage:
//class ClientApp : public Glow::App {};
//Glow::App* CreateApp() { return new ClientApp(); }
Glow::App* CreateApp();

int main()
{
    Glow::App* app = CreateApp();
    Glow::Engine::Instance().Run(app);
    delete app;
    
    //std::cin.get();
    return 0;
}