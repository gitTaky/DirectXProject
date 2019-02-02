#include "MouseClass.h"

std::queue<MouseEvent> MouseClass::eventBuffer;
bool MouseClass::leftIsDown = false;
bool MouseClass::rightIsDown = false;
bool MouseClass::mbuttonDown = false;
int MouseClass::x = 0;
int MouseClass::y = 0;

void MouseClass::OnLeftPressed(int x, int y)
{
	MouseClass::leftIsDown = true;
	MouseEvent me(MouseEvent::EventType::LPress, x, y);
	MouseClass::eventBuffer.push(me);
}

void MouseClass::OnLeftReleased(int x, int y)
{
	MouseClass::leftIsDown = false;
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));
}

void MouseClass::OnRightPressed(int x, int y)
{
	MouseClass::rightIsDown = true;
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, x, y));
}

void MouseClass::OnRightReleased(int x, int y)
{
	MouseClass::rightIsDown = false;
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
}

void MouseClass::OnMiddlePressed(int x, int y)
{
	MouseClass::mbuttonDown = true;
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, x, y));
}

void MouseClass::OnMiddleReleased(int x, int y)
{
	MouseClass::mbuttonDown = false;
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
}

void MouseClass::OnWheelUp(int x, int y)
{
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void MouseClass::OnWheelDown(int x, int y)
{
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void MouseClass::OnMouseMove(int x, int y)
{
	MouseClass::x = x;
	MouseClass::y = y;
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
}

void MouseClass::OnMouseMoveRaw(int x, int y)
{
	MouseClass::eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, x, y));
}

bool MouseClass::IsLeftDown()
{
	return MouseClass::leftIsDown;
}

bool MouseClass::IsMiddleDown()
{
	return MouseClass::mbuttonDown;
}

bool MouseClass::IsRightDown()
{
	return MouseClass::rightIsDown;
}

int MouseClass::GetPosX()
{
	return MouseClass::x;
}

int MouseClass::GetPosY()
{
	return MouseClass::y;
}

MousePoint MouseClass::GetPos()
{
	return{ MouseClass::x, MouseClass::y };
}

bool MouseClass::EventBufferIsEmpty()
{
	return MouseClass::eventBuffer.empty();
}

MouseEvent MouseClass::ReadEvent()
{
	if (MouseClass::eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent e = MouseClass::eventBuffer.front(); //Get first event from buffer
		MouseClass::eventBuffer.pop(); //Remove first event from buffer
		return e;
	}
}