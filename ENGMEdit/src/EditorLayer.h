#pragma once

#include "Enigma.h"

class EditorLayer : public Enigma::Layer {
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Enigma::Timestep t) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Enigma::Event& e) override;

private:
	Enigma::OrthographicCameraController m_CameraController;

	Enigma::Ref<Enigma::VertexArray> m_SquareVA;
	Enigma::Ref<Enigma::Shader> m_FlatColorShader;
	Enigma::Ref<Enigma::Framebuffer> m_Framebuffer;

	Enigma::Ref<Enigma::Texture2D> m_MissingTexture;

	bool m_ViewportFocused = false;
	bool m_ViewportHovered = false;
	glm::vec2 m_ViewportSize = { 0.0f,0.0f };

	glm::vec4 m_SquareColor = { 0.8f, 0.5f, 0.3f, 1.0f };
};