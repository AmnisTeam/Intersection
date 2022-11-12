#include "pch.h"
#include "Keyboard.h"

bool Keyboard::Event::IsPress() const
{
	return type == Type::Press;
}

bool Keyboard::Event::IsRelease() const
{
	return type == Type::Release;
}

unsigned char Keyboard::Event::GetCode() const
{
	return code;
}

bool Keyboard::KeyIsPressed(unsigned char keycode) const
{
	return keyStates[keycode];
}

Keyboard::Event Keyboard::ReadKey()
{
	if (keyQueue.size() > 0u)
	{
		Keyboard::Event e = keyQueue.front();
		keyQueue.pop();
		return e;
	}
	else
		return Keyboard::Event();
}

bool Keyboard::KeyIsEmpty() const
{
	return keyQueue.empty();
}

char Keyboard::ReadChar()
{
	if (charQueue.size() > 0u)
	{
		unsigned char charcode = charQueue.front();
		charQueue.pop();
		return charcode;
	}
	else
		return 0;
}

bool Keyboard::CharIsEmpty() const
{
	return charQueue.empty();
}

void Keyboard::ClearKey()
{
	keyQueue = std::queue<Event>();
}

void Keyboard::ClearChar()
{
	charQueue = std::queue<char>();
}

void Keyboard::ClearKeyFlash()
{
	ClearKey();
	ClearChar();
}

void Keyboard::EnableAutorepeat()
{
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat()
{
	autorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const
{
	return autorepeatEnabled;
}


void Keyboard::OnKeyPressed(unsigned char keycode)
{
	keyStates[keycode] = true;
	keyQueue.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
	TrimQueue(keyQueue);
}

void Keyboard::OnKeyReleased(unsigned char keycode)
{
	keyStates[keycode] = false;
	keyQueue.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
	TrimQueue(keyQueue);
}

void Keyboard::OnChar(char character)
{
	charQueue.push(character);
	TrimQueue(charQueue);
}

void Keyboard::ClearState()
{
	keyStates.reset();
}

template<typename T>
void Keyboard::TrimQueue(std::queue<T>& buffer)
{
	while (buffer.size() > queueSize)
	{
		buffer.pop();
	}
}