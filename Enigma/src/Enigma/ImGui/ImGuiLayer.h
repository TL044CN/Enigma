#pragma once
#include "Enigma/Core/Layer.h"

#include "Enigma/Events/KeyEvent.h"
#include "Enigma/Events/MouseEvent.h"
#include "Enigma/Events/ApplicationEvent.h"

namespace Enigma {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
