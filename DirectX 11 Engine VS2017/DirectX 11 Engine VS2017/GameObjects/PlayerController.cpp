#include "PlayerController.h"



PlayerController::PlayerController() : view(View::free) {}

void PlayerController::Initialize(Graphics * pGraphics) {
	this->graphics = pGraphics;
	this->mainCamera = &pGraphics->scene.camera;
	this->controlledObject = &this->graphics->scene.camera;
}


void PlayerController::ScanInputs(double dt) {
	if (KeyboardClass::KeyIsPressed('W')) {
		if (this->view == View::free) {
			this->controlledObject->MoveForward(dt);
		}
		else {
			static_cast<Car*>(this->controlledObject)->Accelerate(dt);
		}
	}
	if (KeyboardClass::KeyIsPressed('S')) {
		if (this->view == View::free) {
			this->controlledObject->MoveBackward(dt);
		}
		else {
			static_cast<Car*>(this->controlledObject)->Accelerate(-dt);
		}
	}
	if (KeyboardClass::KeyIsPressed('A')) {
		if (this->view == View::free) {
			this->controlledObject->MoveLeft(dt);
		}
		else {
			static_cast<Car*>(this->controlledObject)->TurnRight(-1);
		}
	}
	if (KeyboardClass::KeyIsPressed('D')) {
		if (this->view == View::free) {
			this->controlledObject->MoveRight(dt);
		}
		else {
			static_cast<Car*>(this->controlledObject)->TurnRight(1);
		}
	}
	if (!KeyboardClass::KeyIsPressed('A') && !KeyboardClass::KeyIsPressed('D')) {
		if (this->view != View::free) {
			static_cast<Car*>(this->controlledObject)->TurnRight(0);
		}
	}
	if (KeyboardClass::KeyIsPressed(VK_SPACE)) {
			this->KeySpacePressed(dt);
	}
	if (KeyboardClass::KeyIsPressed('Z')) {
		this->KeyZPressed(dt);
	}
	while (!KeyboardClass::KeyBufferIsEmpty()) {
		auto ke = KeyboardClass::ReadKey();
		if (ke.GetKeyCode() == 'C' && ke.IsPress()) {
			this->KeyCPressed(dt);
		}
	}

	while (!MouseClass::EventBufferIsEmpty()) {
		MouseEvent me = MouseClass::ReadEvent();
		if (MouseClass::IsRightDown()) {
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE) {
				this->MouseMove(dt, me.GetPosX(), me.GetPosY());
			}
		}
	}
}

void PlayerController::KeyWPressed(double dt) {
	this->controlledObject->MoveForward(dt);
}

void PlayerController::KeyAPressed(double dt) {
	if (this->view == View::free) {
		this->controlledObject->MoveLeft(dt);
	}
	else {
		this->controlledObject->RotateLeft(dt);
	}
}

void PlayerController::KeySPressed(double dt) {
	this->controlledObject->MoveBackward(dt);
}

void PlayerController::KeyDPressed(double dt) {
	if (this->view == View::free) {
		this->controlledObject->MoveRight(dt);
	}
	else {
		this->controlledObject->RotateRight(dt);
	}
}

void PlayerController::KeyZPressed(double dt) {
	this->controlledObject->MoveUp(dt);
}

void PlayerController::KeySpacePressed(double dt) {
	this->controlledObject->MoveDown(dt);
}

void PlayerController::KeyCPressed(double dt) {
	switch (view) {
	case View::free:
		view = View::first;
		this->controlledObject = this->graphics->scene.actors.at("car").get();
		this->mainCamera = &static_cast<Car*>(this->controlledObject)->firstPerspective;
		break;
	case View::first:
		view = View::third;
		this->controlledObject = this->graphics->scene.actors.at("car").get();
		this->mainCamera = &static_cast<Car*>(this->controlledObject)->thirdPerspective;
		break;
	case View::third:
		view = View::free;
		this->controlledObject = &this->graphics->scene.camera;
		this->mainCamera = &this->graphics->scene.camera;
		break;
	}
}

void PlayerController::MouseMove(double dt, double x, double y) {
	if (view == View::free) {
		this->controlledObject->AdjustRotation((float)y * 0.01f, (float)x * 0.01f, 0);
	}
}


PlayerController::~PlayerController() {}
