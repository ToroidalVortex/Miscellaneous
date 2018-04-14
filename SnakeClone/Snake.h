#pragma once

#include <vector>
#include <string>
#include <Windows.h>

class Snake
{
private:
	std::vector<std::vector<int>> coordinates;
	std::vector<int> current_pos;
	int direction;
	int length = 1;
	bool collected_apple = false;
	
public:
	Snake(int x, int y);
	virtual ~Snake();

	void Move();
	int Length();
	bool HitSelf();
	int UserInput();
	void CollectApple();
	std::vector<int> Tail();
	std::string Direction();
	void SetDirection(int key);
	void SetDirection(std::string dir);
	std::vector<int> CurrentPosition();
	bool HitObject(std::vector<int> obj_pos);
	std::vector<std::vector<int>> Coordinates();
};

