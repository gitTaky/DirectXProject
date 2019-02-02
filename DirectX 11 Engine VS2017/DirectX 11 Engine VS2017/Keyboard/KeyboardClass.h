#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass
{
public:
	KeyboardClass() = delete;
	static bool KeyIsPressed(const unsigned char keycode);
	static bool KeyBufferIsEmpty();
	static bool CharBufferIsEmpty();
	static KeyboardEvent ReadKey();
	static unsigned char ReadChar();
	static void OnKeyPressed(const unsigned char key);
	static void OnKeyReleased(const unsigned char key);
	static void OnChar(const unsigned char key);
	static void EnableAutoRepeatKeys();
	static void DisableAutoRepeatKeys();
	static void EnableAutoRepeatChars();
	static void DisableAutoRepeatChars();
	static bool IsKeysAutoRepeat();
	static bool IsCharsAutoRepeat();
private:
	static bool autoRepeatKeys;
	static bool autoRepeatChars;
	static bool keyStates[256];
	static std::queue<KeyboardEvent> keyBuffer;
	static std::queue<unsigned char> charBuffer;
};