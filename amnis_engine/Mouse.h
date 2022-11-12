#pragma once

#include <queue>
#include <optional>
#include "mymath.h"
#include "decl.h"

class Mouse
{
	friend class MainWindow;
public:
	struct RawDelta
	{
		float x, y;
	};
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid
		};

	private:
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		float x = 0;
		float y = 0;

	public:
		Event()
			:
			type(Type::Invalid),
			leftIsPressed(false),
			rightIsPressed(false),
			x(0),
			y(0)
		{};
		Event(Type type, const Mouse& parent)
			:
			type(type),
			leftIsPressed(parent.leftIsPressed),
			rightIsPressed(parent.rightIsPressed),
			x(parent.x),
			y(parent.y)
		{};
		DECL Type GetType() const;
		DECL float2 GetPos() const;
		DECL float GetPosX() const;
		DECL float GetPosY() const;
		DECL bool LeftIsPressed() const;
		DECL bool RightIsPressed() const;
	};

public:
	Mouse() = default;
	DECL float2 GetPos() const;
	DECL RawDelta ReadRawDelta();
	DECL void SetWheelDelta(float delta);
	DECL float GetWheelDelta();
	DECL float GetPosX() const;
	DECL float GetPosY() const;
	DECL bool IsInWindow() const;
	DECL bool LeftIsPressed() const;
	DECL bool RightIsPressed() const;
	DECL Mouse::Event Read();
	DECL bool IsEmpty() const;
	DECL void Clear();
	DECL void EnableRaw();
	DECL void DisableRaw();
	DECL bool RawEnabled() const;

private:
	DECL void OnMouseMove(float x, float y);
	DECL void OnMouseLeave();
	DECL void OnMouseEnter();
	DECL void OnRawDelta(float dx, float dy);
	DECL void OnLeftPressed(float x, float y);
	DECL void OnLeftReleased(float x, float y);
	DECL void OnRightPressed(float x, float y);
	DECL void OnRightReleased(float x, float y);
	DECL void OnWheelUp(float x, float y);
	DECL void OnWheelDown(float x, float y);
	DECL void ClearBuffer();
	DECL void ClearRawInputBuffer();
	DECL void OnWheelDelta(float x, float y, float delta);

private:
	static constexpr unsigned int bufferSize = 16u;
	float x = 0;
	float y = 0;
	bool leftIsPressed = false;
	bool rightIsPressed = false;

	bool rawMouseLeftButtonDown = false;
	bool rawMouseRightButtonDown = false;
	bool rawMouseLeftButtonUp = false;
	bool rawMouseRightButtonUp = false;
	bool rawMouseRightButtonPressed = false;
	bool rawMouseLeftButtonPressed = false;

	bool isInWindow = false;
	float wheelDelta = 0.0f;
	bool rawEnabled = false;
	std::queue<Event> buffer;
	std::queue<RawDelta> rawDeltaBuffer;
};
