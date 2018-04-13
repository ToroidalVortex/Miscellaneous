#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <string>
#include "Snake.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoXY(vector<int> position);
void drawMap(int height, int width);
void updateScore(int score, vector<int> score_pos);
vector<int> randomApplePosition(int height, int width, Snake snake);

int main()
{
	srand(time(0));
	bool playGame = true;
	int height = 20, width = 40;
	int x = width/2, y = height/2;
	Snake snake(x, y);
	int score = 0;
	vector<int> apple_pos = {0,0};
	vector<int> score_pos = { 0, height + 2 };
	vector<int> last_pos = snake.Tail();

	apple_pos = randomApplePosition(height, width, snake);

	snake.SetDirection("Down"); // Always start going down, I guess
	drawMap(height, width);

	while (playGame == true) {
		
		gotoXY(snake.CurrentPosition()); cout << "*";
		gotoXY(last_pos); cout << " "; // erases no-longer existent parts of snake
		gotoXY(apple_pos); cout << "@";
		updateScore(score, score_pos);
		
		// End game if player hits enter
		if (GetAsyncKeyState(VK_RETURN)) playGame = false;

		// Store last position to erase during updates
		// Set player direction based on keyboard input
		// Then move player in that direction
		last_pos = snake.Tail();
		snake.SetDirection(snake.UserInput());
		snake.Move();
		cout << "Length: " << snake.Length() << endl;

		// if the player is at the same position as an apple
		// collect apple and find new apple position
		if (snake.HitObject(apple_pos))
		{
			snake.CollectApple();

			// find new position for apple
			apple_pos = randomApplePosition(height, width, snake);

			score += 25;
		}
		
		// End game if the player runs into theirself
		else if (snake.HitSelf()) playGame = false;

		// End game if the player hits the horizontal or vertiacal walls
		else if ((snake.CurrentPosition()[0] == 0) || (snake.CurrentPosition()[0] > width)) playGame = false;
		else if ((snake.CurrentPosition()[1] == 0) || (snake.CurrentPosition()[1] > height)) playGame = false;

		// Time between frames 
		Sleep(100);
	}

	cout << "Game Over!\n" << endl;

	system("pause");
	return 0;
}

void gotoXY(vector<int> position)
{
	CursorPosition.X = position[0];	// x coordinate
	CursorPosition.Y = position[1];	// y coordiniate
	SetConsoleCursorPosition(console, CursorPosition);
}

void drawMap(int height, int width)
{
	cout << "+";	// top-left corner
	for (int i = 0; i < width; i++)
		cout << "-";
	cout << "+" << endl;	// top-right corner

	for (int i = 0; i < height; i++)
	{
		cout << "|"; cout.width(width+1); cout << "|" << endl;
	}

	cout << "+";	// bottom left corner
	for (int i = 0; i < width; i++)
		cout << "-";
	cout << "+" << endl;	// bottom right corner
}

void updateScore(int score, vector<int> score_pos)
{
	gotoXY(score_pos);
	cout << "Score: " << score << endl;
}

vector<int> randomApplePosition(int height, int width, Snake snake)
{
	vector<int> apple_pos = {0,0};
	do
	{
		apple_pos[0] = 1 + rand() % width;
		apple_pos[1] = 1 + rand() % height;
	}
	while (snake.HitObject(apple_pos));

	return apple_pos;
}