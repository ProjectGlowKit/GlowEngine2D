#pragma once
#include <memory>

namespace Glow
{
	class Mesh;
	class Shader;
	class FrameBuffer;

	class RenderCommand
	{
	public:
		virtual void Execute() = 0;
		virtual ~RenderCommand(){}
	};

	class RenderMesh : public RenderCommand
	{
	public:
		RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader)
			: mMesh(mesh),
			  mShader(shader)
		{}
		virtual void Execute() override;
	private:
		std::weak_ptr<Mesh> mMesh;
		std::weak_ptr<Shader> mShader;
	};

	class PushFrameBuffer : public RenderCommand
	{
	public:
		PushFrameBuffer(std::weak_ptr<FrameBuffer> framebuffer) : mFrameBuffer(framebuffer) {}
		virtual void Execute() override;
	private:
		std::weak_ptr<FrameBuffer> mFrameBuffer;
	};

	class PopFrameBuffer : public RenderCommand
	{
	public:
		PopFrameBuffer() {}
		virtual void Execute() override;
	};
}