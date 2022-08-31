#pragma once
class IClonable
{
public:
	virtual void* clone() = 0;
};