#include "ball.h"

#include "rect.h"

namespace Ball
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
          out vec3 pos;
          uniform mat4 model = mat4(1.0);
          void main()
          {
              pos = position;
              gl_Position = model * vec4(position, 1.0);
          }
      )";

    char* mFragShader = R"(
                #version 460 core
                out vec4 outColor;
                in vec3 pos;
                uniform vec3 color;
                void main()
                {
                    if (length(pos) > 0.5) discard;
                    outColor = vec4(color, 1.0);
                }
            )";

    std::shared_ptr<Ball> CreateBall()
    {
        std::shared_ptr<Glow::Mesh> rectMesh = std::make_shared<Glow::Mesh>(&mVertices[0], 4, 3, &mIndices[0], 6);
        std::shared_ptr<Glow::Shader> shader = std::make_shared<Glow::Shader>(mVertShader, mFragShader);

        auto ball = std::make_shared<Ball>(rectMesh, shader);

        return ball;
    }
}