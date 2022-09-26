// #include "game.h"
//
//void main ()
//{
//	RunGame();
//	return 0;
//}

#include "raylib.h"
#include "iostream"
#include "raymath.h"

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
void Wall(Rectangle& nave);

void main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ASTEROID");

	Rectangle nave;
	nave.x = SCREEN_WIDTH / 2.0f;
	nave.y = SCREEN_HEIGHT / 2.0f;
	nave.width = 25;
	nave.height = 25;

	Vector2 pivot;
	pivot.x = nave.width / 2;;
	pivot.y = nave.height / 2;

	Vector2 posMouse;
	Vector2 posNave ;
	
	float rotation = 0.0f;

	Vector2 Vectordirec;
	Vector2 Vectornormalizado;
	Vector2 Aceleracion{0.01f};
	Vector2 NuevaPosNave;

	

	while (!WindowShouldClose())
	{
		//check input
		//update
		
		posMouse = GetMousePosition();

		/*Vectordirec = posMouse - posNave;*/
		Vectordirec.x = posMouse.x - nave.x;
		Vectordirec.y = posMouse.y - nave.y;

		
		rotation = atan(Vectordirec.y / Vectordirec.x)*180/ PI;

		/*direccionNormalizada = vectorDireccion /modulo(vectorDireccion)*/
		Vectornormalizado= Vector2Normalize(Vectordirec);

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			    /*aceleracionNave += direccionNormalizada*/
				Aceleracion.x += Vectornormalizado.x * 0.5f;
				Aceleracion.y += Vectornormalizado.y * 0.5f;

				/*nuevaPosNave = posNave + aceleracionNave * tiempoEntreFrames*/

				nave.x = nave.x + Aceleracion.x * GetFrameTime();
				nave.y = nave.y + Aceleracion.y * GetFrameTime();

			
				Wall(nave);

				cout << Aceleracion.x << endl;
				cout << Aceleracion.y << endl;
			
			
			
			
		}


		BeginDrawing();

		DrawRectanglePro(nave, pivot, rotation, RED);
		
		ClearBackground(BLACK);
		EndDrawing();

		/*Draw();*/
	}

	CloseWindow();
}

void Draw()
{
	
}

void Wall(Rectangle &nave)
{
	if (nave.x > SCREEN_WIDTH + nave.height)
	{
		nave.x = -nave.height;
	}
	else if (nave.x < -nave.height)
	{
		nave.x = SCREEN_WIDTH + nave.height;
	}
	if (nave.y > (SCREEN_HEIGHT + nave.height))
	{
		nave.y = -nave.height;
	}
	else if (nave.y < -(nave.height))
	{
		nave.y = SCREEN_HEIGHT + nave.height;
	}
}