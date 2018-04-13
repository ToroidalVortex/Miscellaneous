#include "Snake.h"


Snake::Snake(int x, int y)
{
	current_pos = { x,y };
	coordinates.push_back(current_pos);
}

Snake::~Snake()
{
	coordinates.clear();
}

void Snake::Move()
{
	switch (direction)
	{
	case 0:
		current_pos[1] --;
		break;
	case 1:
		current_pos[1] ++;
		break;
	case 2:
		current_pos[0] --;
		break;
	case 3:
		current_pos[0] ++;
		break;
	}

	coordinates.push_back(current_pos);

	if (!collected_apple)
		coordinates.erase(coordinates.begin());
	else
	{
		length++;
		collected_apple = false;
	}
		
}

void Snake::SetDirection(int key)
{
	switch (key)
	{
	case VK_UP:
		direction = 0;
		break;
	case VK_DOWN:
		direction = 1;
		break;
	case VK_LEFT:
		direction = 2;
		break;
	case VK_RIGHT:
		direction = 3;
		break;
	}
}

void Snake::SetDirection(std::string dir)
{
	if (dir == "Up") direction = 0;
	else if (dir == "Down") direction = 1;
	else if (dir == "Left") direction = 2;
	else if (dir == "Right") direction = 3;
}

std::string Snake::Direction()
{
	std::string dir;
	switch (direction)
	{
	case 0:
		dir = "Up";
		break;
	case 1:
		dir = "Down";
		break;
	case 2:
		dir = "Left";
		break;
	case 3:
		dir = "Right";
		break;
	}

	return dir;
}

int Snake::UserInput()
{
	if (GetAsyncKeyState(VK_UP)) return VK_UP;
	else if (GetAsyncKeyState(VK_DOWN)) return VK_DOWN;
	else if (GetAsyncKeyState(VK_RIGHT)) return VK_RIGHT;
	else if (GetAsyncKeyState(VK_LEFT)) return VK_LEFT;
	else return -1;
}

std::vector<int> Snake::CurrentPosition()
{
	return current_pos;
}

int Snake::Length()
{
	return length;
}

std::vector<std::vector<int>> Snake::Coordinates()
{
	return coordinates;
}

bool Snake::HitSelf()
{
	for (int i = 0; i < length - 1; i++)
	{
		if (current_pos == coordinates[i])
			return true;
	}
	return false;
}

bool Snake::HitObject(std::vector<int> obj_pos)
{
	for (int i = 0; i < length; i++)
	{
		if (obj_pos == coordinates[i])
			return true;
	}
	return false;
}

std::vector<int> Snake::Tail()
{
	return coordinates[0];
}

void Snake::CollectApple()
{
	collected_apple = true;
}