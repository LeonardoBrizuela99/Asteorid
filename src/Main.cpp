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
const int NAVE_BALAS_MAX = 15;
const int TIEMPO_BALA= 600;


struct circul
{
	float x;
	float y;
	float velocidad_x;
	float velocidad_y;
	float radio;
	int spawnVidaBala;
	bool dispara;
	float rotation;
	
};

//struct Nave
//{
//	float X= SCREEN_WIDTH / 2.0f;
//	float Y= SCREEN_HEIGHT / 2.0f;
//	int Widht=25;
//	int Height=25;
//};
circul bala[NAVE_BALAS_MAX] = { 0 };

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
void Pausa(bool& pausa);
void TextMenu();
void Menu();

void main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ASTEROID");

	bool pausa = false;

	Rectangle nave;
	nave.x = SCREEN_WIDTH / 2.0f;
	nave.y = SCREEN_HEIGHT / 2.0f;
	nave.width = 25;
	nave.height = 25;
	int nave_vida = 3;

	
	for (int i = 0; i < NAVE_BALAS_MAX; i++)
	{
		bala[i].x = 0;
		bala[i].y = 0;
		bala[i].velocidad_x = 0.01f;
		bala[i].velocidad_y = 0.01f;
		bala[i].radio = 2.0f;
		bala[i].dispara = false;
		bala[i].spawnVidaBala = 0;
	}
	
	

	Vector2 pivot;
	pivot.x = nave.width / 2;
	pivot.y = nave.height / 2;

	Vector2 posMouse;
	Vector2 posNave ;
	
	float rotation = 0.0f;
	
	Vector2 Vectordirec;
	Vector2 Vectornormalizado;
	Vector2 Aceleracion{0.01f};
	Vector2 NuevaPosNave{ 0 };

	

	while (!WindowShouldClose())
	{
		Menu();
	
		Pausa(pausa);	

		if (!pausa)
		{
			posMouse = GetMousePosition();

			/*Vectordirec = posMouse - posNave;*/
			Vectordirec.x = posMouse.x - nave.x;
			Vectordirec.y = posMouse.y - nave.y;


			rotation = atan(Vectordirec.y / Vectordirec.x) * 180 / PI;

			/*direccionNormalizada = vectorDireccion /modulo(vectorDireccion)*/
			Vectornormalizado = Vector2Normalize(Vectordirec);
			//check input
			//update

			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				/*aceleracionNave += direccionNormalizada*/
				Aceleracion.x += Vectornormalizado.x * 0.2f;
				Aceleracion.y += Vectornormalizado.y * 0.2f;

				/*nuevaPosNave = posNave + aceleracionNave * tiempoEntreFrames*/

				nave.x = nave.x + Aceleracion.x * GetFrameTime();
				nave.y = nave.y + Aceleracion.y * GetFrameTime();


				Wall(nave);

				/*cout << Aceleracion.x << endl;
				cout << Aceleracion.y << endl;*/

			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				for (int i = 0; i < NAVE_BALAS_MAX; i++)
				{
					if (!bala[i].dispara)
					{
						bala[i].x = nave.x;
						bala[i].y = nave.y;
						bala[i].dispara = true;
						bala[i].velocidad_x = Vectornormalizado.x;
						bala[i].velocidad_y = Vectornormalizado.y;
						bala[i].rotation = rotation;
						break;

						//+sin(rotation * 180 / PI) * (nave.height)
						//	- cos(rotation * 180 / PI) * (nave.height)

					}
				}
			}

			for (int i = 0; i < NAVE_BALAS_MAX; i++)
			{
				if (bala[i].dispara)
				{
					bala[i].spawnVidaBala++;
				}
			}

			for (int i = 0; i < NAVE_BALAS_MAX; i++)
			{
				if (bala[i].dispara)
				{
					//movimiento de la bala
					bala[i].x += bala[i].velocidad_x + Vectornormalizado.x*GetFrameTime();
					bala[i].y += bala[i].velocidad_y + Vectornormalizado.y*GetFrameTime();

					

					//desaparicion de balas cuando sale de la pantalla
					if (bala[i].x > SCREEN_WIDTH )
					{
						bala[i].dispara = false;
						bala[i].spawnVidaBala = 0;
					}
					else if (bala[i].x < 0 )
					{
						bala[i].dispara = false;
						bala[i].spawnVidaBala = 0;
					}
					if (bala[i].y > SCREEN_HEIGHT )
					{
						bala[i].dispara = false;
						bala[i].spawnVidaBala = 0;
					}

					else if (bala[i].y < 0 )
					{
						bala[i].dispara = false;
						bala[i].spawnVidaBala = 0;
					}

					if (bala[i].spawnVidaBala >= TIEMPO_BALA)
					{
						bala[i].x = 0;
						bala[i].y = 0;
						bala[i].velocidad_x = 0;
						bala[i].velocidad_y = 0;
						bala[i].spawnVidaBala = 0;
						bala[i].dispara = false;

					}
				}
			}
		}
		
		BeginDrawing();

		DrawRectanglePro(nave, pivot, rotation, RED);

		for (int i = 0; i < NAVE_BALAS_MAX; i++)
		{
			if (bala[i].dispara)
			{
				DrawCircle(bala[i].x, bala[i].y, bala[i].radio, WHITE);
			}
		}
		
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
void Pausa(bool &pausa)
{
	if (IsKeyPressed('P') || IsKeyPressed('p')||IsKeyPressed(KEY_ESCAPE))
	{
		pausa = !pausa;
		//cout << pause << endl;
		//0 false
		//1 true
	}
}
void DrawMenu(Rectangle Caja,Rectangle Juego, Rectangle Creditos, Rectangle instrucciones)
{
	
	
}

void TextMenu()
{
	DrawText("ASTEROID", GetScreenWidth() / 2-250 , 100, 100, WHITE);
	DrawText("CREDITOS", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 200, 30, WHITE);
	DrawText("REGLAS", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 +70, 30, WHITE);
	DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 -50, 30, WHITE);
}

void Menu() {

	Rectangle Caja = { GetScreenWidth() / 2, GetScreenHeight() / 2, 50, 50 };
	Rectangle Juego = { GetScreenWidth() / 2 - 85, GetScreenHeight() / 2 - 50, 250, 100 };
	Rectangle Creditos = { GetScreenWidth() / 2 + 200, GetScreenHeight() / 2 + 25, 250, 100 };
	Rectangle Instruciones = { GetScreenWidth() / 2 - 370, GetScreenHeight() / 2 + 25, 250, 100 };

	Caja.x = GetMouseX() - Caja.width / 2;
	Caja.y = GetMouseY() - Caja.height / 2;

	DrawMenu(Caja, Juego, Creditos, Instruciones);
	TextMenu();

	/*ActivarReincicios();

	Juego(Caja, Juego);
	Creditos(Caja, Creditos);
	Regla(Caja, Instruciones);*/


}