#include "pch.h"
#include "Mouse.h"
#include "MainWindow.h"

Mouse::Event::Type Mouse::Event::GetType() const
{
	return type;
}

float2 Mouse::Event::GetPos() const
{
	return{ x,y };
}

float Mouse::Event::GetPosX() const
{
	return x;
}

float Mouse::Event::GetPosY() const
{
	return y;
}

bool Mouse::Event::LeftIsPressed() const
{
	return leftIsPressed;
}

bool Mouse::Event::RightIsPressed() const
{
	return rightIsPressed;
}





Mouse::Mouse(MainWindow *mainWindow)
{
	this->mainWindow = mainWindow;
}

float2 Mouse::GetPos() const
{
	return { x,y };
}

void Mouse::SetWheelDelta(float delta)
{
	wheelDelta = delta;
}

float Mouse::GetPosX() const
{
	return x;
}

float Mouse::GetPosY() const
{
	return y;
}

void Mouse::SetPosX(float x)
{
	this->x = x;
}

void Mouse::SetPosY(float y)
{
	this->y = y;
}

bool Mouse::IsInWindow() const
{
	return isInWindow;
}

bool Mouse::LeftIsPressed() const
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const
{
	return rightIsPressed;
}

Mouse::Event Mouse::Read()
{
	if (buffer.size() > 0u)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else {
		return Mouse::Event();
	}
}

bool Mouse::IsEmpty() const
{
	return buffer.empty();
}

void Mouse::Clear()
{
	buffer = std::queue<Event>();
}

void Mouse::EnableRaw()
{
	rawEnabled = true;
}

void Mouse::DisableRaw()
{
	rawEnabled = false;
}

bool Mouse::RawEnabled() const
{
	return rawEnabled;
}

void Mouse::captureCursor(bool state)
{
	if (state)
	{
		confineCursor();
		hideCursor();
		isCursorCaptured = true;
	}
	else
	{
		freeCursor();
		showCursor();
		isCursorCaptured = false;
	}
}

void Mouse::confineCursor()
{
	RECT rect;
	GetClientRect(mainWindow->hwnd, &rect);
	MapWindowPoints(mainWindow->hwnd, nullptr, (POINT*)&rect, 2);
	ClipCursor(&rect);
}

void Mouse::freeCursor()
{
	ClipCursor(nullptr);
}

void Mouse::hideCursor()
{
	//while (ShowCursor(false) >= 0);
}

void Mouse::showCursor()
{
	while (ShowCursor(true) <= 0);
}

void Mouse::setCursorState(bool isCursorCaptured)
{
	this->isCursorCaptured = isCursorCaptured;
}

bool Mouse::getCursorState() const
{
	return isCursorCaptured;
}

void Mouse::SetRawMouseDelta(float x, float y)
{
	rawDeltaBuffer.push({ x,y });
	ClearBuffer();
}

float2 Mouse::GetRawMouseDelta() 
{
	if (rawDeltaBuffer.empty())
	{
		return {0,0};
	}
	const float2 r = rawDeltaBuffer.front();
	rawDeltaBuffer.pop();
	return r;
}

void Mouse::ResizeRawInputData(LPARAM lParam, UINT size) {
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) == -1)
		throw;
	rawInputBuffer.resize(size);
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, rawInputBuffer.data(), &size, sizeof(RAWINPUTHEADER)) != size)
		throw;
}


void Mouse::OnMouseMove(float newx, float newy)
{
	x = newx;
	y = newy;

	buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	ClearBuffer();
}

void Mouse::OnMouseLeave()
{
	isInWindow = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
	ClearBuffer();
}

void Mouse::OnMouseEnter()
{
	isInWindow = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
	ClearBuffer();
}

void Mouse::OnLeftPressed(float x, float y)
{
	leftIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
	ClearBuffer();
}

void Mouse::OnLeftReleased(float x, float y)
{
	leftIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
	ClearBuffer();
}

void Mouse::OnRightPressed(float x, float y)
{
	rightIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
	ClearBuffer();
}

void Mouse::OnRightReleased(float x, float y)
{
	rightIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
	ClearBuffer();
}

void Mouse::OnWheelUp(float x, float y)
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
	ClearBuffer();
}

void Mouse::OnWheelDown(float x, float y)
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
	ClearBuffer();
}

void Mouse::ClearBuffer()
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

void Mouse::ClearRawInputBuffer()
{
	while (rawDeltaBuffer.size() > bufferSize)
	{
		rawDeltaBuffer.pop();
	}
}

float Mouse::GetWheelDelta()
{
	return wheelDelta;
}

void Mouse::OnWheelDelta(float x, float y, float delta)
{
	wheelDelta += delta;
	// generate events for every 120 
	/*while (wheelDelta >= WHEEL_DELTA)
	{
		wheelDelta -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (wheelDelta <= -WHEEL_DELTA)
	{
		wheelDelta += WHEEL_DELTA;
		OnWheelDown(x, y);
	}*/
}