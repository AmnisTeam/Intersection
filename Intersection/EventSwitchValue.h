#pragma once
#include <Event.h>

template<class T>
class EventSwitchValue : public Event
{
public:
	EventSwitchValue(T* variable, T value1, T value2)
	{
		this->variable = variable;
		this->values[0] = value1;
		this->values[1] = value2;
	}

	EventSwitchValue(T* variable, T value2)
	{
		this->variable = variable;
		this->values[0] = *variable;
		this->values[1] = value2;
	}

	virtual void execute() override
	{
		valuesState = !valuesState;
		*variable = values[valuesState];
	}
private:
	bool valuesState = false;
	T* variable;
	T values[2];
};

