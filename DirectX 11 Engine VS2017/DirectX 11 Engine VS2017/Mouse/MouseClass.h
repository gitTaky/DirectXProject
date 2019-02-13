#pragma once
#include "MouseEvent.h"
#include <queue>

//=========================
//Mouse input buffer
//=========================
class MouseClass
{
public:
	MouseClass() = delete;
	static void OnLeftPressed(int x, int y);
	static void OnLeftReleased(int x, int y);
	static void OnRightPressed(int x, int y);
	static void OnRightReleased(int x, int y);
	static void OnMiddlePressed(int x, int y);
	static void OnMiddleReleased(int x, int y);
	static void OnWheelUp(int x, int y);
	static void OnWheelDown(int x, int y);
	static void OnMouseMove(int x, int y);
	static void OnMouseMoveRaw(int x, int y);

	static bool IsLeftDown();
	static bool IsMiddleDown();
	static bool IsRightDown();

	static int GetPosX();
	static int GetPosY();
	static MousePoint GetPos();

	static bool EventBufferIsEmpty();
	static MouseEvent ReadEvent();

private:
	static std::queue<MouseEvent> eventBuffer;
	static bool leftIsDown;
	static bool rightIsDown;
	static bool mbuttonDown;
	static int x;
	static int y;
};