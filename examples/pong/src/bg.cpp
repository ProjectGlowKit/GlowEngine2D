#include "bg.h"

namespace BG
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
          out vec2 fragCoord;
          void main()
          {
              gl_Position = model * vec4(position, 1.0);
              fragCoord = position.xy * 0.5 + 0.5;
          }
      )";

    char* mFragShader = R"(
      #version 460 core
      out vec4 outColor;

      uniform vec3 mainColor;
      uniform vec3 waveColor;
      uniform vec2 waveCenter;
      uniform float frame;

      in vec2 fragCoord;

      void main()
      {
          // Calculate distance from the wave center
          float dist = distance(fragCoord, waveCenter);

          // Wave properties
          float waveSpeed = 0.015;     // Slower speed for wave expansion
          float waveWidth = 0.01;    // Thinner thickness for the wave ring
          float time = frame;         // Frame directly used as time for smoother control

          float mixFactor = 1.0f;

          // Calculate the current wave radius (starting small and expanding slowly)
          float waveRadius = min(waveSpeed * time, 0.45f);

          // Create wave effect: highlight the ring region
          float edge = smoothstep(waveRadius - waveWidth, waveRadius, dist) *
                         (1.0 - smoothstep(waveRadius, waveRadius + waveWidth, dist));

          mixFactor = 1.0 - (waveRadius / 0.45f);  // Decrease mixFactor as waveRadius increases
          mixFactor = 1.0f - (time * 0.02);
          mixFactor = clamp(mixFactor, 0.0, 1.0);

          // Mix the colors based on wave intensity
          vec3 color = mix(mainColor, waveColor, edge * mixFactor);

          outColor = vec4(color, 1.0);
      }
    )";

    std::shared_ptr<Glow::GameObject> CreateBG()
    {
        std::shared_ptr<Glow::Mesh> bgMesh = std::make_shared<Glow::Mesh>(&mVertices[0], 4, 3, &mIndices[0], 6);
        std::shared_ptr<Glow::Shader> shader = std::make_shared<Glow::Shader>(mVertShader, mFragShader);

        auto bg = std::make_shared<Glow::GameObject>(bgMesh, shader);

        bg->SetPos(glm::vec2(0.0f, 0.0f));
        bg->SetSize(glm::vec2(1.0f, 1.0f));

        return bg;
    }
}