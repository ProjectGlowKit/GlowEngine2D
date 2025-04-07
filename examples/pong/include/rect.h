#pragma once
#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"
#include "GlowEngine/Game/GameObject.h"

#include <memory>

namespace Rect
{
    std::shared_ptr<Glow::GameObject> CreateRect();
}