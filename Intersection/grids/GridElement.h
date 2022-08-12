#pragma once
class GridElement
{
public:
	GridElement();

	void setBuild(void* build);
	void setObstacle(bool haveObstacle);

	void* getBuild() const;
	bool getObstacle() const;
private:
	void* build = nullptr;
	bool haveObstacle = false;

};

