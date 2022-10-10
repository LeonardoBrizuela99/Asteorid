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

const float SCREEN_HEIGHT = 786;
const float SCREEN_WIDTH = 1024;
const int NAVE_BALAS_MAX = 15;
const int TIEMPO_BALA= 60000;

const int MAX_METEORO_GRANDE = 4;
const int MAX_METEORO_MEDIANO = 8;
const int MAX_METEORO_CHICO= 16;
const int METEORO_VELOCIDAD= 1;
bool gameplay = false;



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

struct Meteoro
{
	Vector2 position;
	Vector2 velocidad;
	float radio;
	bool activo;
};

//struct Nave
//{
//	float X= SCREEN_WIDTH / 2.0f;
//	float Y= SCREEN_HEIGHT / 2.0f;
//	int Widht=25;
//	int Height=25;
//};
circul bala[NAVE_BALAS_MAX] = { 0 };
Meteoro meteoroGrande[MAX_METEORO_GRANDE] = { 0 };
Meteoro meteoroMediano[MAX_METEORO_MEDIANO] = { 0 };
Meteoro meteoroChico[MAX_METEORO_CHICO] = { 0 };

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
void DrawMenu(Rectangle cursor, Rectangle juego, Rectangle creditos, Rectangle instrucciones);
void Jugar(Rectangle juego, Rectangle cursor);
void Reglas(Rectangle instrucciones, Rectangle cursor);
void Creditos(Rectangle creditos, Rectangle cursor);



int main()
{
	InitWindow(static_cast <int>(SCREEN_WIDTH), static_cast <int>(SCREEN_HEIGHT), "ASTEROID");

	int posx, posy = 0;
	float velx, vely = 0;
	bool rangocorrecto = 0;

	//int contadorMeteorosDestruido = 0;
	//int cotadorMeterorosPequeños = 0;
	//int cotadorMeterorosMedioanos = 0;

	//Texture2D texture = LoadTexture("res/ufoBlue.png");
	bool pausa = false;
;
	Rectangle nave;
	nave.x = SCREEN_WIDTH / 2.0f;
	nave.y = SCREEN_HEIGHT / 2.0f;
	nave.width = 25;
	nave.height = 25;
	/*int nave_vida = 3;*/

	for (int i = 0; i < MAX_METEORO_GRANDE; i++)
	{
		posx = GetRandomValue(0, static_cast <int>(SCREEN_WIDTH));

		while (!rangocorrecto)
		{
			if (posx>SCREEN_WIDTH/2-150&& posx<SCREEN_WIDTH/2+150) 
			{
				posx = GetRandomValue(0, static_cast <int>(SCREEN_WIDTH));
			}
			else
			{
				rangocorrecto = true;
			}
		}
		rangocorrecto = false;
		posy = GetRandomValue(0, static_cast <int> (SCREEN_HEIGHT));
		while (!rangocorrecto)
		{
			if (posy > SCREEN_HEIGHT / 2 - 150 && posy < SCREEN_HEIGHT / 2 + 150)
			{
				posy = GetRandomValue(0, static_cast <int>(SCREEN_HEIGHT));
			}
			else
			{
				rangocorrecto = true;
			}
		}
		meteoroGrande[i].position.x = static_cast <float>(posx);
		meteoroGrande[i].position.y = static_cast <float>(posy);

		rangocorrecto = false;

		velx = (float)GetRandomValue(-/*static_cast <int>*/(METEORO_VELOCIDAD) , /*static_cast <int>*/(METEORO_VELOCIDAD));
		vely = (float)GetRandomValue(-/*static_cast <int>*/(METEORO_VELOCIDAD) , /*static_cast <int>*/(METEORO_VELOCIDAD));

		if (velx==0 && vely==0)
		{
			velx = (float)GetRandomValue(-/*static_cast <int>*/(METEORO_VELOCIDAD), /*static_cast <int>*/(METEORO_VELOCIDAD));
			vely = (float)GetRandomValue(-/*static_cast <int>*/(METEORO_VELOCIDAD), /*static_cast <int>*/(METEORO_VELOCIDAD));
				
		}
		else
		{
			rangocorrecto = false;
		}

		meteoroGrande[i].velocidad.x = static_cast <float>(velx);
		meteoroGrande[i].velocidad.y = static_cast <float>(vely);
		meteoroGrande[i].radio = 40.0f;
		meteoroGrande[i].activo=true;
	}
	for (int i = 0; i < MAX_METEORO_MEDIANO; i++)
	{
		meteoroMediano[i].position.x = -100;
		meteoroMediano[i].position.y = -100;
		meteoroMediano[i].velocidad.x = 0;
		meteoroMediano[i].velocidad.y = 0;
		meteoroMediano[i].radio = 20.0f;
		meteoroMediano[i].activo = false;
	}
	for (int i = 0; i < MAX_METEORO_CHICO; i++)
	{
		meteoroChico[i].position.x = -100;
		meteoroChico[i].position.y = -100;
		meteoroChico[i].velocidad.x = 0;
		meteoroChico[i].velocidad.y = 0;
		meteoroChico[i].radio = 10.0f;
		meteoroChico[i].activo = false;
	}

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
	/*cotadorMeterorosMedioanos = 0;
	cotadorMeterorosPequeños = 0;*/
	
	

	Vector2 pivot;
	pivot.x = nave.width / 2;
	pivot.y = nave.height / 2;

	Vector2 posMouse{ 0};
	Vector2 posNave{ 0 };
	
	float rotation = 0.0f;
	
	Vector2 Vectordirec;
	Vector2 Vectornormalizado;
	Vector2 Aceleracion{0.01f};
	Vector2 NuevaPosNave{ 0 };

	

	while (!WindowShouldClose())
	{
		Menu();
	
		

		
		while (gameplay==true)
		{
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



					Wall(nave);


				}

				//sacandolo del if de arriba la nave ahora posee inercia a la hora de dejar de mantener presionado el click
				/*nuevaPosNave = posNave + aceleracionNave * tiempoEntreFrames*/
				nave.x = nave.x + Aceleracion.x * GetFrameTime();
				nave.y = nave.y + Aceleracion.y * GetFrameTime();

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					for (int i = 0; i < NAVE_BALAS_MAX; i++)
					{
						if (!bala[i].dispara)
						{
							bala[i].x = nave.x;
							bala[i].y = nave.y;
							bala[i].dispara = true;
							bala[i].velocidad_x = Vectornormalizado.x * 0.08f;
							bala[i].velocidad_y = Vectornormalizado.y * 0.08f;
							bala[i].rotation = rotation;
							break;

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
						bala[i].x += bala[i].velocidad_x + Vectornormalizado.x * GetFrameTime();
						bala[i].y += bala[i].velocidad_y + Vectornormalizado.y * GetFrameTime();



						//desaparicion de balas cuando sale de la pantalla
						if (bala[i].x > SCREEN_WIDTH)
						{
							bala[i].dispara = false;
							bala[i].spawnVidaBala = 0;
						}
						else if (bala[i].x < 0)
						{
							bala[i].dispara = false;
							bala[i].spawnVidaBala = 0;
						}
						if (bala[i].y > SCREEN_HEIGHT)
						{
							bala[i].dispara = false;
							bala[i].spawnVidaBala = 0;
						}

						else if (bala[i].y < 0)
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
				for (int i = 0; i < MAX_METEORO_GRANDE; i++)
				{
					if (meteoroGrande[i].activo)
					{
						meteoroGrande[i].position.x += meteoroGrande[i].velocidad.x;
						meteoroGrande[i].position.y += meteoroGrande[i].velocidad.y;

						if (meteoroGrande[i].position.x > SCREEN_WIDTH + meteoroGrande[i].radio)
						{
							meteoroGrande[i].position.x = -(meteoroGrande[i].radio);
						}
						else if (meteoroGrande[i].position.x < 0 - meteoroGrande[i].radio)
						{
							meteoroGrande[i].position.x = SCREEN_WIDTH + meteoroGrande[i].radio;
						}

						if (meteoroGrande[i].position.y > SCREEN_HEIGHT + meteoroGrande[i].radio)
						{
							meteoroGrande[i].position.y = -(meteoroGrande[i].radio);
						}
						else if (meteoroGrande[i].position.y < 0 - meteoroGrande[i].radio)
						{
							meteoroGrande[i].position.y = SCREEN_HEIGHT + meteoroGrande[i].radio;
						}
					}
				}

				for (int i = 0; i < MAX_METEORO_MEDIANO; i++)
				{
					if (meteoroMediano[i].activo)
					{
						meteoroMediano[i].position.x += meteoroMediano[i].velocidad.x;
						meteoroMediano[i].position.y += meteoroMediano[i].velocidad.y;

						if (meteoroMediano[i].position.x > SCREEN_WIDTH + meteoroMediano[i].radio)
						{
							meteoroMediano[i].position.x = -(meteoroMediano[i].radio);
						}
						else if (meteoroMediano[i].position.x < 0 - meteoroMediano[i].radio)
						{
							meteoroMediano[i].position.x = SCREEN_WIDTH + meteoroMediano[i].radio;
						}

						if (meteoroMediano[i].position.y > SCREEN_HEIGHT + meteoroMediano[i].radio)
						{
							meteoroMediano[i].position.y = -(meteoroMediano[i].radio);
						}
						else if (meteoroMediano[i].position.y < 0 - meteoroMediano[i].radio)
						{
							meteoroMediano[i].position.y = SCREEN_HEIGHT + meteoroMediano[i].radio;
						}
					}

				}
				for (int i = 0; i < MAX_METEORO_CHICO; i++)
				{
					if (meteoroChico[i].activo)
					{
						meteoroChico[i].position.x += meteoroChico[i].velocidad.x;
						meteoroChico[i].position.y += meteoroChico[i].velocidad.y;

						if (meteoroChico[i].position.x > SCREEN_WIDTH + meteoroChico[i].radio)
						{
							meteoroChico[i].position.x = -(meteoroChico[i].radio);
						}
						else if (meteoroChico[i].position.x < 0 - meteoroChico[i].radio)
						{
							meteoroChico[i].position.x = SCREEN_WIDTH + meteoroChico[i].radio;
						}

						if (meteoroChico[i].position.y > SCREEN_HEIGHT + meteoroChico[i].radio)
						{
							meteoroChico[i].position.y = -(meteoroChico[i].radio);
						}
						else if (meteoroChico[i].position.y < 0 - meteoroChico[i].radio)
						{
							meteoroChico[i].position.y = SCREEN_HEIGHT + meteoroChico[i].radio;
						}
					}

				}
		}
		
	}
		
		


		
		BeginDrawing();

	
		//DrawTexture(texture, static_cast<int>(SCREEN_HEIGHT) / 2, static_cast<int>(SCREEN_WIDTH) / 2, WHITE);

		DrawRectanglePro(nave, pivot, rotation, RED);

		for (int i = 0; i < NAVE_BALAS_MAX; i++)
		{
			if (bala[i].dispara)
			{
				DrawCircle(static_cast <int>(bala[i].x), static_cast <int>(bala[i].y), bala[i].radio, WHITE);
			}
		}

		for (int i = 0; i < MAX_METEORO_GRANDE; i++)
		{
			if (meteoroGrande[i].activo)
			{
				DrawCircle(static_cast <int>(meteoroGrande[i].position.x), static_cast <int>(meteoroGrande[i].position.y), meteoroGrande[i].radio, WHITE);
			}
			
		}
		for (int i = 0; i < MAX_METEORO_MEDIANO; i++)
		{
			if (meteoroMediano[i].activo)
			{
				DrawCircle(static_cast <int>(meteoroMediano[i].position.x), static_cast <int>(meteoroMediano[i].position.y), meteoroMediano[i].radio, WHITE);
			}

		}
		for (int i = 0; i < MAX_METEORO_CHICO; i++)
		{
			if (meteoroChico[i].activo)
			{
				DrawCircle(static_cast <int>(meteoroChico[i].position.x), static_cast <int>(meteoroChico[i].position.y), meteoroChico[i].radio, WHITE);
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
void DrawMenu(Rectangle cursor, Rectangle juego, Rectangle creditos, Rectangle instrucciones)
{
	DrawRectangleRec(cursor, RED);
	DrawRectangleRec(juego, RED);
	DrawRectangleRec(creditos, RED);
	DrawRectangleRec(instrucciones, RED);

}

void TextMenu()
{
	DrawText("ASTEROID", GetScreenWidth() / 2 -290, 100, 100, WHITE);
	DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 200, 30, WHITE);
	DrawText("REGLAS", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 +70, 30, WHITE);
	DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 -50, 30, WHITE);
	

}

void Menu() {

	Rectangle cursor = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2)-250, static_cast<int>(GetScreenHeight()) / static_cast <float>(2)+200, 5, 5 };
	Rectangle juego = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) - 90, 250, 100 };
	Rectangle instruciones = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 35, 250, 100 };
	Rectangle creditos = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 160, 250, 100 };

	cursor.x = GetMouseX() - cursor.width / 2;
	cursor.y = GetMouseY() - cursor.height / 2;

	DrawMenu(cursor, juego, creditos, instruciones);
	TextMenu();

	
	Reglas(instruciones, cursor);
	Jugar(juego, cursor);
	Creditos( creditos, cursor);

}

void Jugar(Rectangle juego, Rectangle caja)
{
	if (CheckCollisionRecs(juego, caja))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(juego, YELLOW);
			DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 - 50, 30, WHITE);
			gameplay = true;
		}
		
	}
}

void Reglas(Rectangle instrucciones, Rectangle caja)
{
	if (CheckCollisionRecs(instrucciones, caja))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(instrucciones, YELLOW);
			DrawText("REGLAS", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 70, 30, WHITE);
		}

	}
}

void Creditos(Rectangle creditos, Rectangle cursor)
{
	if (CheckCollisionRecs(creditos, cursor))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(creditos, YELLOW);
			DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 200, 30, WHITE);
		}

	}
}