#pragma once

class IBuild
{
public:
	virtual int getGridSizeX() const = 0;
	virtual int getGridSizeY() const = 0;
	virtual void* getBuild() const = 0;
};