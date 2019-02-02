#pragma once
#include "../Graphics/Graphics.h"
#include "MovableObject.h"
#include "Camera.h"
#include "../Keyboard/KeyboardClass.h"
#include "../Mouse/MouseClass.h"

class PlayerController {
public:
	enum class View {
		free,
		first,
		third,
	};

	PlayerController();

	void Initialize(Graphics* pGraphics);
	
	void ScanInputs(double dt);
	void KeyWPressed(double dt);
	void KeyAPressed(double dt);
	void KeySPressed(double dt);
	void KeyDPressed(double dt);
	void KeyZPressed(double dt);
	void KeySpacePressed(double dt);
	void KeyCPressed(double dt);
	
	void MouseMove(double dt, double x, double y);

	~PlayerController();

	Camera* mainCamera;
private:
	Graphics* graphics;
	MovableObject* controlledObject;
	View view;
};

