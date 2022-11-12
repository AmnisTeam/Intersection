#pragma once
#include <queue>
#include <bitset>
#include <optional>
#include "decl.h"

class Keyboard
{
	friend class MainWindow;
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid,
		};

	private:
		Type type;
		unsigned char code;

	public:
		Event()
			:
			type(Type::Invalid),
			code(0u)
		{};
		Event(Type type, unsigned char code)
			:
			type(type),
			code(code)
		{};
		DECL bool IsPress() const;
		DECL bool IsRelease() const;
		DECL unsigned char GetCode() const;
	};

public:
	Keyboard() = default;

	// key event
	DECL bool KeyIsPressed(unsigned char keycode) const;
	DECL Event ReadKey();
	/*std::optional<Event> ReadKey();*/
	DECL bool KeyIsEmpty() const;
	DECL void ClearKey();

	// char event
	DECL char ReadChar();
	/*std::optional<char> ReadChar();*/
	DECL bool CharIsEmpty() const;
	DECL void ClearChar();
	DECL void ClearKeyFlash();

	// autorepeat control
	DECL void EnableAutorepeat();
	DECL void DisableAutorepeat();
	DECL bool AutorepeatIsEnabled() const;

private:
	DECL void OnKeyPressed(unsigned char keycode);
	DECL void OnKeyReleased(unsigned char keycode);
	DECL void OnChar(char character);
	DECL void ClearState();

	template<typename T>
	static void TrimQueue(std::queue<T>& queue);

private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int queueSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyQueue;
	std::queue<char> charQueue;
};