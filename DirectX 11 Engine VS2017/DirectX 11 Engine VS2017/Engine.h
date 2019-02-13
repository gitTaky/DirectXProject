#pragma once
#include "WindowContainer.h"
#include "Utils/Timer.h"
#include "GameObjects/PlayerController.h"

class Engine : WindowContainer
{
public:
	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	void Update();
	void RenderFrame();
private:
	Timer timer;
	PlayerController playerController;
};