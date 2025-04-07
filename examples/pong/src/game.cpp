#include "GlowEngine/engine.h"
#include "GlowEngine/main.h"
#include "GlowEngine/Core/window.h"

#include "GlowEngine/Graphics/framebuffer.h"
#include "GlowEngine/Game/GameObject.h"
#include "GlowEngine/Events/keyboard.h"

#include "thirdparty/ImGui/imgui.h"

#include "rect.h"
#include "ball.h"
#include "bg.h"

#include <memory>
#include <iostream>

class Game : public Glow::App
{
private:
	Glow::WindowProperties mWindowProps;
	
	std::shared_ptr<Glow::GameObject> mRectTop, mRectBottom;
	int mHPTop, mHPBottom;
	float speed = 0.001f;
	std::shared_ptr<Ball::Ball> mBall;

	std::shared_ptr<Glow::GameObject> mBG;

	bool mWaveActive = false;
	float mWaveFrame = 0.0f;
public:
	Glow::WindowProperties SetWindowProperties() override
	{
		mWindowProps.title = "Pong";
		mWindowProps.flags = Glow::WindowFlags::Resizable;
		return mWindowProps;
	}

	void Init() override
	{
		Glow::Engine::Instance().GetRenderer().SetClearColor(glm::vec4(0.67f, 0.32f, 0.88f, 1.0f));
		Glow::Engine::Instance().GetWindow().GetFrameBuffer()->SetClearColor(glm::vec4(0.67f, 0.32f, 0.88f, 1.0f));

		mHPTop = 3;
		mHPBottom = 3;

		mBG = BG::CreateBG();
		mRectTop = Rect::CreateRect();
		mRectBottom = Rect::CreateRect();
		mBall = Ball::CreateBall();

		mBG->SetSize(glm::vec2(2.0f, 2.0f));
		mRectTop->SetSize(glm::vec2(0.4f, 0.1f));
		mRectBottom->SetSize(glm::vec2(0.4f, 0.1f));
		mBall->SetSize(glm::vec2(0.075f, 0.1f));

		mBG->GetShader()->SetUniformFloat3("mainColor", glm::vec3(0.67f, 0.32f, 0.88f));
		mBG->GetShader()->SetUniformFloat3("waveColor", glm::vec3(1.0f));
		mBG->GetShader()->SetUniformFloat2("waveCenter", glm::vec2(1.0f));
		mBG->GetShader()->SetUniformFloat("frame", 0.0f);

		mRectTop->GetShader()->SetUniformFloat3("color", glm::vec3(1, 1, 1));
		mRectBottom->GetShader()->SetUniformFloat3("color", glm::vec3(1, 1, 1));
		mBall->GetShader()->SetUniformFloat3("color", glm::vec3(1, 1, 1));

		glm::vec2 pos = glm::vec2(0.0f, 0.0f);
		mBG->SetPos(pos);
		pos = glm::vec2(0.0f, 1.0f);
		mRectTop->SetPos(pos);
		pos = glm::vec2(0.0f, -1.0f);
		mRectBottom->SetPos(pos);
		pos = glm::vec2(0.0f, 0.0f);
		mBall->SetPos(pos);

		mBall->SetVelocity(glm::vec2(0.0005f, 0.0005f));
	}

	void Shutdown() override
	{
		
	}

	void Update() override
	{
		if (Glow::Keyboard::Key(GWE_EVENT_KEY_A))		{ mRectTop->AddPos(glm::vec2(-speed, 0)); }
		if (Glow::Keyboard::Key(GWE_EVENT_KEY_D))		{ mRectTop->AddPos(glm::vec2(speed, 0)); }
		if (Glow::Keyboard::Key(GWE_EVENT_KEY_LEFT))	{ mRectBottom->AddPos(glm::vec2(-speed, 0)); }
		if (Glow::Keyboard::Key(GWE_EVENT_KEY_RIGHT))	{ mRectBottom->AddPos(glm::vec2(speed, 0)); }

		mBall->AddPos(mBall->GetVelocity());

		float ballMaxX = 1 - mBall->GetSize().x / 2;
		float ballMinX = -1 + mBall->GetSize().x / 2;
		if (mBall->GetPos().x >= ballMaxX ||
			mBall->GetPos().x <= ballMinX)
		{
			mBall->VelocityFlipX();
		}
		else if (IsColliding(mBall->GetPos(), mBall->GetSize(), mRectTop->GetPos(), mRectTop->GetSize()) ||
				 IsColliding(mBall->GetPos(), mBall->GetSize(), mRectBottom->GetPos(), mRectBottom->GetSize()))
		{
			mBall->VelocityFlipY();
			mBall->SetVelocity(mBall->GetVelocity() * glm::vec2(1.1f, 1.1f));

			glm::vec2 waveOrigin = (mBall->GetPos() + glm::vec2(1.0f)) * 0.5f;
			mBG->GetShader()->SetUniformFloat2("waveCenter", waveOrigin);
			mWaveActive = true;
			mWaveFrame = 0.0f;
		}
		else if (mBall->GetPos().y - mBall->GetSize().y / 2 < -1.0f) 
		{ 
			mHPBottom--; 
			Reset();
		}
		else if (mBall->GetPos().y - mBall->GetSize().y / 2 > 1.0f) 
		{ 
			mHPTop--; 
			Reset();
		}

		if (mWaveActive)
		{
			mWaveFrame += 0.1f;

			mBG->GetShader()->SetUniformFloat("frame", mWaveFrame);

			if (mWaveFrame > 180.0f)
			{
				mWaveActive = false;
				mBG->GetShader()->SetUniformFloat("frame", 0.0f);
			}
		}
	}

	void Render() override
	{
		mBG->Render();
		mRectTop->Render();
		mRectBottom->Render();
		mBall->Render();
	}

	void RenderImGui() override
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

		if (ImGui::Begin("GamePlayer", nullptr,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse))
		{
			if (ImGui::IsWindowHovered())
			{
				ImGui::SetNextFrameWantCaptureMouse(false);
			}

			auto& window = Glow::Engine::Instance().GetWindow();
			ImVec2 size = ImGui::GetContentRegionAvail();
			ImVec2 uv0 = { 0, 1 };
			ImVec2 uv1 = { 1, 0 };
			ImGui::Image(window.GetFrameBuffer()->GetTexID(), size, uv0, uv1);
		}
		ImGui::End();

		ImVec2 windowSize = ImGui::GetIO().DisplaySize;

		glm::vec2 bottomPos = mRectBottom->GetPos();
		ImVec2 screenPos = WorldToScreen(bottomPos, windowSize);
		screenPos.y -= 50.0f;
		screenPos.x -= 10.0f;
		ImGui::SetNextWindowPos(screenPos, ImGuiCond_Always);

		ImGui::Begin("ScoreBottom", nullptr,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("%.i", mHPBottom);
		ImGui::End();

		glm::vec2 topPos = mRectTop->GetPos();
		screenPos = WorldToScreen(topPos, windowSize);
		screenPos.y += 20.0f;
		screenPos.x -= 10.0f;
		ImGui::SetNextWindowPos(screenPos, ImGuiCond_Always);

		ImGui::Begin("ScoreTop", nullptr,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("%.i", mHPTop);
		ImGui::End();
	}

private:
	bool IsColliding(const glm::vec2& pos1, const glm::vec2& size1,
					 const glm::vec2& pos2, const glm::vec2& size2)
	{
		float left_1	= pos1.x - size1.x / 2;
		float right_1	= pos1.x + size1.x / 2;
		float up_1		= pos1.y + size1.y / 2;
		float down_1	= pos1.y - size1.y / 2;

		float left_2	= pos2.x - size2.x / 2;
		float right_2	= pos2.x + size2.x / 2;
		float up_2		= pos2.y + size2.y / 2;
		float down_2	= pos2.y - size2.y / 2;

		return (
			left_1 < right_2 && right_1 > left_2 &&
			up_1 > down_2 && down_1 < up_2
		);
	}

	ImVec2 WorldToScreen(glm::vec2 worldPos, ImVec2 windowSize)
	{
		float x = (worldPos.x + 1.0f) * 0.5f;
		float y = (1.0f - (worldPos.y + 1.0f) * 0.5f);

		return ImVec2(x * windowSize.x, y * windowSize.y);
	}

	void Reset()
	{
		if (mHPBottom <= 0 || mHPTop <= 0)
		{
			Glow::Engine::Instance().Quit();
		}
		glm::vec2 pos = glm::vec2(0.0f, 1.0f);
		mRectTop->SetPos(pos);
		pos = glm::vec2(0.0f, -1.0f);
		mRectBottom->SetPos(pos);
		pos = glm::vec2(0.0f, 0.0f);
		mBall->SetPos(pos);

		mBall->SetVelocity(glm::vec2(0.0005f, 0.0005f));
	}
};

Glow::App* CreateApp()
{
	return new Game();
}