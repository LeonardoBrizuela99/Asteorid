// #include "game.h"
//
//void main ()
//{
//	RunGame();
//	return 0;
//}

#include "raylib.h"
#include "iostream"

using namespace std;

const int SCREEN_HEIGHT = 786;
const int SCREEN_WIDTH = 1024;

struct Nave
{
	float X= SCREEN_WIDTH / 2.0f;
	float Y= SCREEN_HEIGHT / 2.0f;
	int Widht=25;
	int Height=25;
};


//void init()
//{
//	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ASTEROID");
//
//}
//Vector2 GetMousePosition()
//{
//
//}

void main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ASTEROID");
	Nave nave;
	float posNave_x = nave.X;
	float posNave_y = nave.Y;
	Vector2 posMouse = GetMousePosition();
	Vector2 posNave = { posNave_x, posNave_y};
	

	Vector2 Vectordirec ;

	while (!WindowShouldClose())
	{
		//check input
		//update
		/*Vectordirec = posMouse - posNave;*/

		BeginDrawing();
		DrawRectangle(posNave_x, posNave_y, nave.Widht, nave.Height, RED);
		ClearBackground(BLACK);
		EndDrawing();

		/*Draw();*/
	}

	CloseWindow();
}
void Draw()
{
	
}