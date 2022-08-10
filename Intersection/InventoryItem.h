#pragma once

class InventoryItem {
private:
	int image;
public: 
	virtual void handleClick() = 0;
};
