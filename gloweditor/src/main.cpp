#include "GlowEngine/engine.h"
#include "GlowEngine/app.h"
#include "GlowEngine/main.h"
#include "GlowEngine/Core/window.h"
#include "GlowEngine/log.h"

#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"
#include "GlowEngine/Graphics/framebuffer.h"

#include "GlowEngine/Events/mouse.h"
#include "GlowEngine/Events/keyboard.h"

#include "thirdparty/ImGui/imgui.h"
#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"

class Editor : public Glow::App
{
private:
    glm::fvec4 mClearColor = glm::fvec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImVec2 mGameWindowSize;

    std::shared_ptr<Glow::Mesh> mMesh;
    std::shared_ptr<Glow::Shader> mShader;
    glm::vec2 mRectPos, mRectSize;

    float mXNorm, mYNorm;
public:
    Glow::WindowProperties SetWindowProperties() override
    {
        Glow::WindowProperties props;
        props.title = "GlowEngine";
        GWE_INFO("{}x{}", props.size.x, props.size.y)
        props.flags = Glow::WindowFlags::Resizable;
        props.ImGuiProps.isViewportEnabled = true;
        props.ImGuiProps.isDockingEnabled = true;
        return props;
    }

    void Init() override
    {
        GWE_TRACE("Editor Initialized!")
        Glow::Engine::Instance().GetRenderer().SetClearColor(glm::vec4(1.0f));
            // Test mesh
            float vertices[]
        {
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        uint32_t indices[]
        {
            0, 3, 1,
            1, 3, 2
        };


        mMesh = std::make_shared<Glow::Mesh>(&vertices[0], 4, 3, &indices[0], 6);

        //Test Shader
        const char* vertexShader = R"(
                #version 460 core
                layout (location = 0) in vec3 position;

                out vec3 vpos;
                uniform vec2 offset;
                uniform mat4 model = mat4(1.0);
                void main()
                {
                    vpos = position + vec3(offset, 0);
                    gl_Position = model * vec4(position, 1.0);
                }
            )";

        const char* fragmentShader = R"(
                #version 460 core
                out vec4 outColor;
                in vec3 vpos;

                uniform vec3 color;
                void main()
                {
                    outColor = vec4(vpos, 1.0);
                }
            )";

        mShader = std::make_shared<Glow::Shader>(vertexShader, fragmentShader);

        mShader->SetUniformFloat3("color", 1.0, 0, 0);

        mRectPos = glm::vec2(0.0f);
        mRectSize = glm::vec2(1.0f);
    }

    void Shutdown() override
    {
        GWE_TRACE("Editor Shutdown!")
    }

    void Update() override
    {
        if (Glow::Keyboard::Key(GWE_EVENT_KEY_UP)) {
            mRectPos.y += 0.001f;
        }
        if (Glow::Keyboard::Key(GWE_EVENT_KEY_DOWN)) {
            mRectPos.y -= 0.001f;
        }
        if (Glow::Keyboard::Key(GWE_EVENT_KEY_LEFT)) {
            mRectPos.x -= 0.001f;
        }
        if (Glow::Keyboard::Key(GWE_EVENT_KEY_RIGHT)) {
            mRectPos.x += 0.001f;
        }

        mShader->SetUniformFloat2("offset", mXNorm, mYNorm);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, { mRectPos, 0.0f });
        model = glm::scale(model, {mRectSize, 0.0f});
        mShader->SetUniformMat4("model", model);

        //Debug
        //GWE_TRACE("width: {} | height: {}", windowW, windowH);
        /*GWE_TRACE("Mouse: x{} | y{}", Mouse::X(), Mouse::Y())*/
        /*GWE_TRACE("Mouse: {} | {} | {} | {} | {}",
            Mouse::Button(GWE_EVENT_MOUSE_LEFT),
            Mouse::Button(GWE_EVENT_MOUSE_MIDDLE),
            Mouse::Button(GWE_EVENT_MOUSE_RIGHT),
            Mouse::Button(GWE_EVENT_MOUSE_X1),
            Mouse::Button(GWE_EVENT_MOUSE_X2))*/
        /*GWE_TRACE("Keyboard: W:{} | S:{} | A:{} | D:{}",
            Keyboard::Key(GWE_EVENT_KEY_W),
            Keyboard::Key(GWE_EVENT_KEY_S),
            Keyboard::Key(GWE_EVENT_KEY_A),
            Keyboard::Key(GWE_EVENT_KEY_D))*/
    }

    void Render() override
    {
        auto command = std::make_unique<Glow::RenderMesh>(mMesh, mShader);
        Glow::Engine::Instance().GetRenderer().Submit(std::move(command));
        Glow::Engine::Instance().GetRenderer().Flush();
    }

    void RenderImGui() override
    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

        ImGui::Begin("Settings window");
        float clearColor[3] = { mClearColor.r, mClearColor.g, mClearColor.b};
        if (ImGui::ColorEdit3("Clear color", clearColor, ImGuiColorEditFlags_Float))
        {
            mClearColor.r = clearColor[0];
            mClearColor.g = clearColor[1];
            mClearColor.b = clearColor[2];
            Glow::Engine::Instance().GetWindow().GetFrameBuffer()->SetClearColor(mClearColor);
        }
        ImGui::Separator();
        float rectSize[2] = { mRectSize.x, mRectSize.y };
        if (ImGui::InputFloat2("Rect size", rectSize))
        {
            mRectSize.x = rectSize[0];
            mRectSize.y = rectSize[1];
        }
        ImGui::End();

        ImGui::Begin("Debuger window");
        auto& window = Glow::Engine::Instance().GetWindow();
        ImVec2 mousePos = ImGui::GetMousePos();

        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("Window size:       Width: %.i     Height: %.i", window.GetSize().x, window.GetSize().y);
        ImGui::Text("Game Window size:  Width: %.1f    Height: %.1f", mGameWindowSize[0], mGameWindowSize[1]);
        ImGui::Text("Abs Mouse pos:         X: %.1f         Y: %.1f", mousePos[0], mousePos[1]);
        ImGui::Separator();
        ImGui::Text("Rect Pos:              X: %.2f         Y: %.2f", mRectPos.x, mRectPos.y);
        ImGui::Text("Rect Size:             X: %.2f         Y: %.2f", mRectSize.x, mRectSize.y);
        ImGui::Text("Rect Color offset:     X: %.2f         Y: %.2f", mXNorm, mYNorm);

        ImGui::End();

        if (ImGui::Begin("GamePlayer"))
        {
            if (ImGui::IsWindowHovered())
            {
                ImGui::SetNextFrameWantCaptureMouse(false);
            }
            mGameWindowSize = ImGui::GetContentRegionAvail();

            ImVec2 gameWindowPos = ImGui::GetWindowPos();
            ImVec2 mousePos = ImGui::GetMousePos();
            ImVec2 relativeMousePos = ImVec2(mousePos.x - gameWindowPos.x, mousePos.y - gameWindowPos.y);

            if (relativeMousePos.x >= 0 && relativeMousePos.x <= mGameWindowSize.x &&
                relativeMousePos.y >= 0 && relativeMousePos.y <= mGameWindowSize.y)
            {
                relativeMousePos.y = mGameWindowSize.y - relativeMousePos.y;

                mXNorm = relativeMousePos.x / mGameWindowSize.x;
                mYNorm = relativeMousePos.y / mGameWindowSize.y;
            }

            auto& window = Glow::Engine::Instance().GetWindow();
            ImVec2 uv0 = { 0, 1 };
            ImVec2 uv1 = { 1, 0 };
            ImGui::Image(window.GetFrameBuffer()->GetTexID(), mGameWindowSize, uv0, uv1);
        }
        ImGui::End();
    }
};

Glow::App* CreateApp() { return new Editor(); }