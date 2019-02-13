#include "Engine.h"

//================================
//	Initialize window
//	graphic
//	playerController
//================================
bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	timer.Start();

	if (!this->render_window.Initialize(this, hInstance, window_title, window_class, width, height))
		return false;

	if (!gfx.Initialize(this->render_window.GetHWND(), width, height))
		return false;

	this->playerController.Initialize(&this->gfx);

	return true;
}

bool Engine::ProcessMessages()
{
	return this->render_window.ProcessMessages();
}

void Engine::Update()
{
	auto dt = timer.GetMilisecondsElapsed();
	timer.Restart();

	this->gfx.scene.Tick(dt);
	this->playerController.ScanInputs(dt);
}

void Engine::RenderFrame()
{
	this->gfx.RenderFrame(&this->gfx.scene, this->playerController.mainCamera);
}

