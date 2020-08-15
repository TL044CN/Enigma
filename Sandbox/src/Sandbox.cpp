#include "engmpch.h"
#include <Enigma.h>
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

class TestLayer : public Enigma::Layer {
public:
	TestLayer()
	: Layer("Test"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraRotation(0.0f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(Enigma::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Enigma::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Enigma::VertexBuffer::Create(vertices, sizeof(vertices)));
		Enigma::BufferLayout layout = {
			{ Enigma::ShaderDataType::Float3, "a_Position" },
			{ Enigma::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Enigma::IndexBuffer> indexBuffer;
		indexBuffer.reset(Enigma::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Enigma::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Enigma::VertexBuffer> squareVB;
		squareVB.reset(Enigma::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Enigma::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Enigma::IndexBuffer> squareIB;
		squareIB.reset(Enigma::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Enigma::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Enigma::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Enigma::Timestep ts) override {
		if (Enigma::Input::IsKeyPressed(ENGM_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Enigma::Input::IsKeyPressed(ENGM_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Enigma::Input::IsKeyPressed(ENGM_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Enigma::Input::IsKeyPressed(ENGM_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Enigma::Input::IsKeyPressed(ENGM_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Enigma::Input::IsKeyPressed(ENGM_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Enigma::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,1.0f });
		Enigma::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Enigma::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

		for(int y=0; y<20;y++)
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Enigma::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}

		Enigma::Renderer::Submit(m_Shader, m_VertexArray);

		Enigma::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

	void OnEvent(Enigma::Event& event) override {

	}

private:
	std::shared_ptr<Enigma::Shader> m_Shader;
	std::shared_ptr<Enigma::VertexArray> m_VertexArray;

	std::shared_ptr<Enigma::Shader> m_BlueShader;
	std::shared_ptr<Enigma::VertexArray> m_SquareVA;

	Enigma::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 3.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public Enigma::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}

	~Sandbox() {

	}

};

Enigma::Application* Enigma::CreateApplication() {
	return new Sandbox();
}