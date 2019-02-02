#include "KeyboardClass.h"

bool KeyboardClass::autoRepeatChars = false;
bool KeyboardClass::autoRepeatKeys = false;
bool KeyboardClass::keyStates[256] = { false };
std::queue<KeyboardEvent> KeyboardClass::keyBuffer;
std::queue<unsigned char> KeyboardClass::charBuffer;

bool KeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return KeyboardClass::keyStates[keycode];
}

bool KeyboardClass::KeyBufferIsEmpty()
{
	return KeyboardClass::keyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty()
{
	return KeyboardClass::charBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if (KeyboardClass::keyBuffer.empty()) //If no keys to be read?
	{
		return KeyboardEvent(); //return empty keyboard event
	}
	else
	{
		KeyboardEvent e = KeyboardClass::keyBuffer.front(); //Get first Keyboard Event from queue
		KeyboardClass::keyBuffer.pop(); //Remove first item from queue
		return e; //Returns keyboard event
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (KeyboardClass::charBuffer.empty()) //If no keys to be read?
	{
		return 0u; //return 0 (NULL char)
	}
	else
	{
		unsigned char e = KeyboardClass::charBuffer.front(); //Get first char from queue
		KeyboardClass::charBuffer.pop(); //Remove first char from queue
		return e; //Returns char
	}
}

void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	KeyboardClass::keyStates[key] = true;
	KeyboardClass::keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	KeyboardClass::keyStates[key] = false;
	KeyboardClass::keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	KeyboardClass::charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	KeyboardClass::autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	KeyboardClass::autoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChars()
{
	KeyboardClass::autoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars()
{
	KeyboardClass::autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat()
{
	return KeyboardClass::autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat()
{
	return KeyboardClass::autoRepeatChars;
}