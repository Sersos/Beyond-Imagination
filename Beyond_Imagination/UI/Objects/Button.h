#ifndef BUTTON_H
#define BUTTON_H

#include "Global.h"
#include "UIObject.h"
#include "HoverableObject.h"

namespace UI
{
	class Button : public UI::Object, public UI::HoverableObject
	{
	public: 
		Button();

		void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		void update(InputManager* inputManager);
		void render(ID3D11DeviceContext* deviceContext);
	};
}

#endif

