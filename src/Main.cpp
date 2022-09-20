// #include "game.h"
//
//void main ()
//{
//	RunGame();
//	return 0;
//}

#include "raylib.h"
#include "iostream"
#include "cmath"

using namespace std;

const int SCREEN_HEIGHT = 786;
const int SCREEN_WIDTH = 1024;

//struct Nave
//{
//	float X= SCREEN_WIDTH / 2.0f;
//	float Y= SCREEN_HEIGHT / 2.0f;
//	int Widht=25;
//	int Height=25;
//};


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

	Rectangle nave;
	nave.x = SCREEN_WIDTH / 2.0f;
	nave.y = SCREEN_HEIGHT / 2.0f;
	nave.width = 25;
	nave.height = 25;

	float posNave_x = nave.x;
	float posNave_y = nave.y;

	Vector2 pivot;
	pivot.x = nave.width / 2;;
	pivot.y = nave.height / 2;

	Vector2 posMouse;
	Vector2 posNave ;
	
	float rotation = 0.0f;

	Vector2 Vectordirec;

	

	while (!WindowShouldClose())
	{
		//check input
		//update
		/*Vectordirec = posMouse - posNave;*/
		posMouse = GetMousePosition();
		posNave = { posNave_x, posNave_y };
		Vectordirec.x = posMouse.x - posNave.x;
		Vectordirec.y = posMouse.y - posNave.y;

		
		rotation = atan(Vectordirec.y / Vectordirec.x)*180/ PI;


		BeginDrawing();
		DrawRectanglePro(nave, pivot, rotation, RED);
		//DrawRectangle(posNave_x, posNave_y, nave.width, nave.height, RED);
		ClearBackground(BLACK);
		EndDrawing();

		/*Draw();*/
	}

	CloseWindow();
}
void Draw()
{
	
}