#include "rect.h"

namespace Rect
{
    float mVertices[] = {
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
    };

    uint32_t mIndices[]
    {
        0, 3, 1,
        1, 3, 2
    };

    char* mVertShader = R"(
          #version 460 core
          layout (location = 0) in vec3 position;

          uniform mat4 model = mat4(1.0);
          void main()
          {
              gl_Position = model * vec4(position, 1.0);
          }
      )";

    char* mFragShader = R"(
                #version 460 core
                out vec4 outColor;

                uniform vec3 color;
                void main()
                {
                    outColor = vec4(color, 1.0);
                }
            )";

    std::shared_ptr<Glow::GameObject> CreateRect()
    {
        std::shared_ptr<Glow::Mesh> rectMesh = std::make_shared<Glow::Mesh>(&mVertices[0], 4, 3, &mIndices[0], 6);
        std::shared_ptr<Glow::Shader> shader = std::make_shared<Glow::Shader>(mVertShader, mFragShader);

        auto rect = std::make_shared<Glow::GameObject>(rectMesh, shader);

        rect->SetPos(glm::vec2(0.0f, 0.0f));
        rect->SetSize(glm::vec2(1.0f, 1.0f));

        return rect;
    }
}