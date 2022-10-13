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
const int METEORO_VELOCIDAD= 250;

enum  SCREEN
{
	MENU,
	JUGAR,
	CREDITOS,
	SALIR,
	 

};


struct BALA
{
	Vector2 position;
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


BALA bala[NAVE_BALAS_MAX] = { 0 };
Meteoro meteoroGrande[MAX_METEORO_GRANDE] = { 0 };
Meteoro meteoroMediano[MAX_METEORO_MEDIANO] = { 0 };
Meteoro meteoroChico[MAX_METEORO_CHICO] = { 0 };




void Wall(Rectangle& nave);
void Pausa(bool& pausa, int& pantalla,bool& reinicio_pausa);
void TextMenu();
void Menu(int& pantalla);
void DrawMenu(Rectangle cursor, Rectangle juego, Rectangle creditos, Rectangle instrucciones);
void Jugar(Rectangle juego, Rectangle cursor,int& pantalla);
void SalirDelJuego(Rectangle instrucciones, Rectangle cursor,int& pantalla);
void Creditos(Rectangle creditos, Rectangle cursor, int& pantalla);
Rectangle Cursor(Rectangle& cursor);
void reiniciar(int& puntaje, int& nave_vida, int& posx, int& posy, bool& rangocorrecto, float& velx, float& vely, bool& gameOver, Rectangle& nave, int& contadorMeteorosDestruido, int& contadorMeterorosChicos, int& contadorMeterorosMedianos);




int main()
{
	InitWindow(static_cast <int>(SCREEN_WIDTH), static_cast <int>(SCREEN_HEIGHT), "ASTEROID");

	Rectangle regresarMenu = { static_cast<int>(GetScreenWidth())-980.0f, static_cast<int>(GetScreenHeight()) -135.0f,250, 100 };
	Rectangle cursor = { 0 };
	
	int posx, posy = 0;
	float velx, vely = 0;
	bool rangocorrecto = 0;
	int pantalla= MENU;
	
	int puntaje = 0;
	


	int contadorMeteorosDestruido = 0;
	int contadorMeterorosChicos = 0;
	int contadorMeterorosMedianos = 0;
	InitAudioDevice();
	
	Texture2D texturaNave = LoadTexture("res/playerShip2_orange.png");
	Texture2D texturaLaser = LoadTexture("res/laserRed02.png");
	Texture2D texturaMeteoroGrande = LoadTexture("res/meteorBrown_big1.png");
	Texture2D texturaMeteoroMediano = LoadTexture("res/meteorBrown_med1.png");
	Texture2D texturaMeteoroChico = LoadTexture("res/meteorBrown_small2.png");
	Texture2D texturaVida = LoadTexture("res/playerLife2_orange.png");
	Texture2D texturaMuerte = LoadTexture("res/laserRed08.png");
	Sound sonidoLaser = LoadSound("res/sfx_laser1.ogg");
	Sound sonidoMeteoro = LoadSound("res/503554__robinhood76__08191-heavy-stones-falling.wav");
	Sound sonidoMuerte = LoadSound("res/446759__ianlyanx__chicle-explotando.wav");
	Sound musica = LoadSound("res/650556__stephiequeen__communicate-song-loop.ogg");
	//Music musica = LoadMusicStream("res/ 650556__stephiequeen__communicate - song - loop.ogg");
	

	bool pausa = false;
	bool gameOver = false;
	bool salirJuego = false;
;
	Rectangle nave;
	nave.x = SCREEN_WIDTH / 2.0f;
	nave.y = SCREEN_HEIGHT / 2.0f;
	nave.width = 25;
	nave.height = 25;
	int nave_vida = 3;

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

		velx = (float)GetRandomValue(-(METEORO_VELOCIDAD) , (METEORO_VELOCIDAD));
		vely = (float)GetRandomValue(-(METEORO_VELOCIDAD) , (METEORO_VELOCIDAD));

		if (velx==0 && vely==0)
		{
			velx = (float)GetRandomValue(-(METEORO_VELOCIDAD), (METEORO_VELOCIDAD));
			vely = (float)GetRandomValue(-(METEORO_VELOCIDAD), (METEORO_VELOCIDAD));
				
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
		bala[i].position.x = 0;
		bala[i].position.y = 0;
		bala[i].velocidad_x = 0.01f;
		bala[i].velocidad_y = 0.01f;
		bala[i].radio = 2.0f;
		bala[i].dispara = false;
		bala[i].spawnVidaBala = 0;
	}
	
	
	
	bool reinicio_pausa = false;
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

	PlaySound(musica);


	while (!WindowShouldClose()&&!salirJuego)
	{
		
	 
		switch (pantalla)
		{

		 case MENU:
		
			Menu(pantalla);
			


			if (nave_vida == 0)
			{
				reiniciar(puntaje, nave_vida, posx, posy, rangocorrecto, velx, vely, gameOver, nave, contadorMeteorosDestruido, contadorMeterorosChicos, contadorMeterorosMedianos);

			}
			break;
		 case JUGAR:
			
			
			 if (!gameOver)
			 {
				
				 
				 if (!pausa)
				 {
					
					 if (contadorMeteorosDestruido >= MAX_METEORO_CHICO + MAX_METEORO_GRANDE + MAX_METEORO_MEDIANO)
					 {
						 for (int i = 0; i < MAX_METEORO_GRANDE; i++)
						 {
							 posx = GetRandomValue(0, static_cast <int>(SCREEN_WIDTH));

							 while (!rangocorrecto)
							 {
								 if (posx > SCREEN_WIDTH / 2 - 150 && posx < SCREEN_WIDTH / 2 + 150)
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

							 velx = (float)GetRandomValue(-(METEORO_VELOCIDAD), (METEORO_VELOCIDAD));
							 vely = (float)GetRandomValue(-(METEORO_VELOCIDAD), (METEORO_VELOCIDAD));

							 if (velx == 0 && vely == 0)
							 {
								 velx = (float)GetRandomValue(-(METEORO_VELOCIDAD),(METEORO_VELOCIDAD));
								 vely = (float)GetRandomValue(-(METEORO_VELOCIDAD),(METEORO_VELOCIDAD));

							 }
							 else
							 {
								 rangocorrecto = false;
							 }

							 meteoroGrande[i].velocidad.x = static_cast <float>(velx);
							 meteoroGrande[i].velocidad.y = static_cast <float>(vely);
							 meteoroGrande[i].radio = 40.0f;
							 meteoroGrande[i].activo = true;
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

						 /*for (int i = 0; i < NAVE_BALAS_MAX; i++)
						 {
							 bala[i].position.x = 0;
							 bala[i].position.y = 0;
							 bala[i].velocidad_x = 0.01f;
							 bala[i].velocidad_y = 0.01f;
							 bala[i].radio = 2.0f;
							 bala[i].dispara = false;
							 bala[i].spawnVidaBala = 0;
						 }*/
						 contadorMeterorosMedianos = 0;
						 contadorMeterorosChicos = 0;
						 contadorMeteorosDestruido = 0;
						 

					 }


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
								 PlaySound(sonidoLaser);
								 bala[i].position.x = nave.x;
								 bala[i].position.y = nave.y;
								 bala[i].dispara = true;
								 bala[i].velocidad_x = Vectornormalizado.x * 0.5f;//0.08f
								 bala[i].velocidad_y = Vectornormalizado.y * 0.5f;//0.08f
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
							 bala[i].position.x += bala[i].velocidad_x + Vectornormalizado.x * GetFrameTime();
							 bala[i].position.y += bala[i].velocidad_y + Vectornormalizado.y * GetFrameTime();



							 //desaparicion de balas cuando sale de la pantalla
							 if (bala[i].position.x > SCREEN_WIDTH)
							 {
								 bala[i].dispara = false;
								 bala[i].spawnVidaBala = 0;
							 }
							 else if (bala[i].position.x < 0)
							 {
								 bala[i].dispara = false;
								 bala[i].spawnVidaBala = 0;
							 }
							 if (bala[i].position.y > SCREEN_HEIGHT)
							 {
								 bala[i].dispara = false;
								 bala[i].spawnVidaBala = 0;
							 }

							 else if (bala[i].position.y < 0)
							 {
								 bala[i].dispara = false;
								 bala[i].spawnVidaBala = 0;
							 }

							 if (bala[i].spawnVidaBala >= TIEMPO_BALA)
							 {
								 bala[i].position.x = 0;
								 bala[i].position.y = 0;
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
							 meteoroGrande[i].position.x += meteoroGrande[i].velocidad.x * GetFrameTime();
							 meteoroGrande[i].position.y += meteoroGrande[i].velocidad.y * GetFrameTime();

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
							 meteoroMediano[i].position.x += meteoroMediano[i].velocidad.x * GetFrameTime();
							 meteoroMediano[i].position.y += meteoroMediano[i].velocidad.y * GetFrameTime();

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
							 meteoroChico[i].position.x += meteoroChico[i].velocidad.x * GetFrameTime();
							 meteoroChico[i].position.y += meteoroChico[i].velocidad.y * GetFrameTime();

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



					 //colision de nave con meteoro
					 for (int i = 0; i < MAX_METEORO_GRANDE; i++)
					 {
						 if (CheckCollisionCircleRec(meteoroGrande[i].position, meteoroGrande[i].radio, nave) && meteoroGrande[i].activo)
						 {
							 nave_vida--;
							 nave.x = SCREEN_WIDTH / 2.0f;
							 nave.y = SCREEN_HEIGHT / 2.0f;
							 PlaySound(sonidoMuerte);
							 PlaySound(sonidoMuerte);
							 DrawTexture(texturaMuerte, static_cast <int>(nave.x)-25, static_cast <int>(nave.y)-50,RAYWHITE);
						 }

					 }
					 for (int i = 0; i < MAX_METEORO_MEDIANO; i++)
					 {
						 if (CheckCollisionCircleRec(meteoroMediano[i].position, meteoroMediano[i].radio, nave) && meteoroMediano[i].activo)
						 {
							 nave_vida--;
							 nave.x = SCREEN_WIDTH / 2.0f;
							 nave.y = SCREEN_HEIGHT / 2.0f;
							 PlaySound(sonidoMuerte);
							 DrawTexture(texturaMuerte, static_cast <int>(nave.x)-25, static_cast <int>(nave.y)-50, RAYWHITE);


						 }

					 }
					 for (int i = 0; i < MAX_METEORO_CHICO; i++)
					 {
						 if (CheckCollisionCircleRec(meteoroChico[i].position, meteoroChico[i].radio, nave) && meteoroChico[i].activo)
						 {
							 nave_vida--;
							 nave.x = SCREEN_WIDTH / 2.0f;
							 nave.y = SCREEN_HEIGHT / 2.0f;
							 PlaySound(sonidoMuerte);
							 DrawTexture(texturaMuerte, static_cast <int>(nave.x)-25, static_cast <int>(nave.y)-50, RAYWHITE);


						 }

					 }

					 for (int i = 0; i < NAVE_BALAS_MAX; i++)
					 {
						 if ((bala[i].dispara))
						 {
							 for (int a = 0; a < MAX_METEORO_GRANDE; a++)
							 {
								 if (meteoroGrande[a].activo && CheckCollisionCircles(bala[i].position, bala[i].radio, meteoroGrande[a].position, meteoroGrande[a].radio))
								 {
									 bala[i].dispara = false;
									 bala[i].spawnVidaBala = 0;
									 meteoroGrande[a].activo = false;
									 puntaje +=10;
									

									 for (int j = 0; j < 2; j++)
									 {
										 if (contadorMeterorosMedianos % 2 == 0)
										 {
											 meteoroMediano[contadorMeterorosMedianos].position = (meteoroGrande[a].position);
											 meteoroMediano[contadorMeterorosMedianos].velocidad = { cos(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD * -1, sin(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD * -1 };
										 }
										 else
										 {
											 meteoroMediano[contadorMeterorosMedianos].position = (meteoroGrande[a].position);
											 meteoroMediano[contadorMeterorosMedianos].velocidad = { cos(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD, sin(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD };

										 }
										 meteoroMediano[contadorMeterorosMedianos].activo = true;
										 contadorMeterorosMedianos++;
									 }
									 contadorMeteorosDestruido++;
									
									 PlaySound(sonidoMeteoro);
									 a = MAX_METEORO_GRANDE;
								 }
							 }

							 for (int b = 0; b < MAX_METEORO_MEDIANO; b++)
							 {
								 if (meteoroMediano[b].activo && CheckCollisionCircles(bala[i].position, bala[i].radio, meteoroMediano[b].position, meteoroMediano[b].radio))
								 {
									 bala[i].dispara = false;
									 bala[i].spawnVidaBala = 0;
									 meteoroMediano[b].activo = false;
									 puntaje += 20;

									 for (int j = 0; j < 2; j++)
									 {
										 if (contadorMeterorosChicos % 2 == 0)
										 {
											 meteoroChico[contadorMeterorosChicos].position = (meteoroMediano[b].position);
											 meteoroChico[contadorMeterorosChicos].velocidad = { cos(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD * -1, sin(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD * -1 };
										 }
										 else
										 {
											 meteoroChico[contadorMeterorosChicos].position = (meteoroMediano[b].position);
											 meteoroChico[contadorMeterorosChicos].velocidad = { cos(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD, sin(bala[i].rotation * DEG2RAD) * METEORO_VELOCIDAD };

										 }
										 meteoroChico[contadorMeterorosChicos].activo = true;
										 contadorMeterorosChicos++;

									 }
									 contadorMeteorosDestruido++;
									
									 PlaySound(sonidoMeteoro);


									 b = MAX_METEORO_MEDIANO;
								 }
							 }

							 for (int c = 0; c < MAX_METEORO_CHICO; c++)
							 {
								 if (meteoroChico[c].activo && CheckCollisionCircles(bala[i].position, bala[i].radio, meteoroChico[c].position, meteoroChico[c].radio))
								 {
									 bala[i].dispara = false;
									 bala[i].spawnVidaBala = 0;
									 meteoroChico[c].activo = false;
									 contadorMeteorosDestruido++;
									 PlaySound(sonidoMeteoro);
									 c = MAX_METEORO_CHICO;
									 puntaje += 50;
									 
									

								 }
							 }

						 }
					 }
				 }
				 
				 if (nave_vida <= 0)
				 {
					 gameOver = true;
					 pantalla = MENU;

				 }
			 }
		
			break;
		

		case CREDITOS:

			

			cursor = Cursor(cursor);

			DrawText("CREDITOS:", GetScreenWidth() / 2-300, GetScreenHeight()/2-350, 30, WHITE);
			DrawText("SONIDO METEORO Robinhood76 ", 0, GetScreenHeight() / 2 -200, 20, WHITE);
			DrawText("PAGINA PRINCIPAL:",0, GetScreenHeight() / 2 -150, 20, WHITE);
			DrawText("https://freesound.org/people/Robinhood76/",0, GetScreenHeight() / 2 -100, 20, WHITE);
			DrawText("PAGINA DEL SONIDO DESCARGADO:",0, GetScreenHeight() / 2 -50, 20, WHITE);
			DrawText(" https://freesound.org/people/Robinhood76/sounds/503554/",0, GetScreenHeight() / 2 -20, 20, WHITE);
			DrawText("MUSICA: StephieQueen", 0 , GetScreenHeight() / 2 , 20, WHITE);
			DrawText("PAGINA PRINCIPAL:",0, GetScreenHeight() / 2 +20, 20, WHITE);
			DrawText("https://freesound.org/people/StephieQueen/",0, GetScreenHeight() / 2+50 , 20, WHITE);
			DrawText("PAGINA DE LA MUSICA: ", 0, GetScreenHeight() / 2 +80, 20, WHITE);
			DrawText(" https://freesound.org/people/StephieQueen/sounds/650556/", 0, GetScreenHeight() / 2 +100, 20, WHITE);
			DrawText("ASSETS:https://kenney.nl/assets/space-shooter-redux", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 + 150, 20, WHITE);
			DrawText("CODIGO: LEONARDO BRIZUELA", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2+250, 20, WHITE);

			
			DrawRectangleRec(regresarMenu, PURPLE);
			DrawText("VOLVER AL MENU", GetScreenWidth()-970, GetScreenHeight() - 100, 26, WHITE);

			if (CheckCollisionRecs(regresarMenu, cursor))
			{

				DrawRectangleRec(regresarMenu, VIOLET);
				DrawText("VOLVER AL MENU", GetScreenWidth()-970, GetScreenHeight() - 100, 26, WHITE);

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{

					DrawRectangleRec(regresarMenu, DARKPURPLE);
					DrawText("VOLVER AL MENU", GetScreenWidth()-970 , GetScreenHeight()-100, 26, WHITE);

					pantalla = MENU;


				}

			}

			break;

		case SALIR:
				salirJuego = true;
			break;
		
		default:
			break;
		}
		
		BeginDrawing();

	
		

		if (pantalla==JUGAR)
		{
			DrawRectanglePro(nave, pivot, rotation, RED);
			//DrawTexturePro(texture, nave,static_cast<Rectangle>(nave.width/2+nave.height/2),pivot,rotation, RAYWHITE);
			DrawTexture(texturaNave, static_cast <int>(nave.x)-55, static_cast <int> (nave.y)-55, WHITE);
			
		

			for (int i = 0; i < NAVE_BALAS_MAX; i++)
			{
				if (bala[i].dispara)
				{
					//DrawCircle(static_cast <int>(bala[i].position.x), static_cast <int>(bala[i].position.y), bala[i].radio, WHITE);
					DrawTexture(texturaLaser, static_cast <int>(bala[i].position.x), static_cast <int>(bala[i].position.y)-20, RAYWHITE);

				}
			}

			for (int i = 0; i < MAX_METEORO_GRANDE; i++)
			{
				if (meteoroGrande[i].activo)
				{
					//DrawCircle(static_cast <int>(meteoroGrande[i].position.x), static_cast <int>(meteoroGrande[i].position.y), meteoroGrande[i].radio, WHITE);
					DrawTexture(texturaMeteoroGrande,static_cast <int>(meteoroGrande[i].position.x)-50, static_cast <int>(meteoroGrande[i].position.y)-36, WHITE);
				}

			}
			for (int i = 0; i < MAX_METEORO_MEDIANO; i++)
			{
				if (meteoroMediano[i].activo)
				{
					//DrawCircle(static_cast <int>(meteoroMediano[i].position.x), static_cast <int>(meteoroMediano[i].position.y), meteoroMediano[i].radio, WHITE);
					DrawTexture(texturaMeteoroMediano,static_cast <int>(meteoroMediano[i].position.x)-25, static_cast <int>(meteoroMediano[i].position.y)-17, WHITE);
				}

			}
			for (int i = 0; i < MAX_METEORO_CHICO; i++)
			{
				if (meteoroChico[i].activo)
				{
					//DrawCircle(static_cast <int>(meteoroChico[i].position.x), static_cast <int>(meteoroChico[i].position.y), meteoroChico[i].radio, WHITE);
					DrawTexture(texturaMeteoroChico,static_cast <int>(meteoroChico[i].position.x)-14, static_cast <int>(meteoroChico[i].position.y)-8, WHITE);
				}

			}

			for (int i = 0; i < nave_vida; i++)
			{
				if (nave_vida == 3)
				{
					DrawTexture(texturaVida, 0, 0, RAYWHITE);
					DrawTexture(texturaVida, 40, 0, RAYWHITE);
					DrawTexture(texturaVida, 80, 0, RAYWHITE);

					//DrawRectangle(0, 0, 10, 10, RED);
					//DrawRectangle(50, 0, 10, 10, RED);
					//DrawRectangle(90, 0, 10, 10, RED);
				}
				else if (nave_vida == 2)
				{
					//DrawRectangle(0, 0, 10, 10, RED);
					//DrawRectangle(25, 0, 10, 10, RED);

					DrawTexture(texturaVida, 0, 0, RAYWHITE);
					DrawTexture(texturaVida, 40, 0, RAYWHITE);

				}
				else if (nave_vida == 1)
				{
					DrawTexture(texturaVida, 0, 0, RAYWHITE);
					//DrawRectangle(0, 0, 10, 10, RED);

				}

			}
			DrawText(TextFormat("PUNTOS: %4i", puntaje), static_cast <int>(SCREEN_WIDTH-200),0,25,YELLOW);
			
			
			Pausa(pausa, pantalla, reinicio_pausa);
		}
		
		
		ClearBackground(BLACK);
		EndDrawing();

		
    }
	UnloadTexture(texturaNave);
	UnloadTexture(texturaLaser);
	UnloadTexture(texturaMeteoroGrande);
	UnloadTexture(texturaMeteoroMediano);
	UnloadTexture(texturaMeteoroChico);
	UnloadTexture(texturaVida);
	UnloadTexture(texturaMuerte);
	
		
		
		 
	CloseAudioDevice();
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
void Pausa(bool &pausa, int& pantalla, bool& reinicio_pausa)
{
	if (pausa == true)
	{
		Rectangle caja_pausa = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 350, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) - 90, 250, 100 }; 
		Rectangle volverMenu = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) + 100, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) - 90,250, 100 };
		Rectangle cursor = { 0 };
	
		cursor = Cursor(cursor);

		DrawRectangleRec(caja_pausa, PURPLE);
		DrawText("PAUSA", GetScreenWidth() / 2 - 280, GetScreenHeight() / 2 - 50, 30, WHITE);

		
		if (CheckCollisionRecs(caja_pausa,cursor))
		{
			
			DrawRectangleRec(caja_pausa, VIOLET);
			DrawText("PAUSA", GetScreenWidth() / 2 - 280, GetScreenHeight() / 2 - 50, 30, WHITE);

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				
				DrawRectangleRec(caja_pausa, DARKPURPLE);
				DrawText("PAUSA", GetScreenWidth() / 2 - 280, GetScreenHeight() / 2 - 50, 30, WHITE);
				pausa = !pausa;

			}

		}
		DrawRectangleRec(volverMenu, PURPLE);
		DrawText("VOLVER AL MENU", GetScreenWidth() / 2 +110, GetScreenHeight() / 2 - 50, 26, WHITE);

		if (CheckCollisionRecs(volverMenu, cursor))
		{

			DrawRectangleRec(volverMenu, VIOLET);
			DrawText("VOLVER AL MENU", GetScreenWidth() / 2 +110, GetScreenHeight() / 2 -50,26, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{

				DrawRectangleRec(volverMenu, DARKPURPLE);
				DrawText("VOLVER AL MENU", GetScreenWidth() / 2 +110, GetScreenHeight() / 2 -50, 26, WHITE);	

				pantalla = MENU;
				reinicio_pausa = !reinicio_pausa;
				

			}

		}

	}
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
	DrawRectangleRec(cursor, PURPLE);
	DrawRectangleRec(juego, PURPLE);
	DrawRectangleRec(creditos, PURPLE);
	DrawRectangleRec(instrucciones, PURPLE);

}

void TextMenu()
{
	DrawText("ASTEROID", GetScreenWidth() / 2 -290, 100, 100, WHITE);
	DrawText("SALIR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 200, 30, WHITE);
	DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 30, WHITE);
	DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 -50, 30, WHITE);
	

}

void Menu(int& pantalla) {

	Rectangle juego = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) - 90, 250, 100 };
	Rectangle salir = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 160, 250, 100 };
	Rectangle creditos = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 35, 250, 100 };
	

	Rectangle cursor = { 0 };
	cursor=Cursor(cursor);

	DrawMenu(cursor, juego, creditos, salir);
	
	TextMenu();

	
	SalirDelJuego(salir, cursor, pantalla);
	Jugar(juego, cursor, pantalla);
	Creditos( creditos, cursor, pantalla);

}

void Jugar(Rectangle juego, Rectangle caja, int& pantalla)
{
	if (CheckCollisionRecs(juego, caja))
	{ 
		DrawRectangleRec(juego, VIOLET);
		DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 - 50, 30, WHITE);
		
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			pantalla = JUGAR;
			DrawRectangleRec(juego, DARKPURPLE);
			DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 - 50, 30, WHITE);
			
		}
		
	}
}

void SalirDelJuego(Rectangle salir, Rectangle caja, int& pantalla)
{
	if (CheckCollisionRecs(salir, caja))
	{
		
		DrawRectangleRec(salir, VIOLET);
		DrawText("SALIR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 200, 30, WHITE);

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(salir, DARKPURPLE);
			DrawText("SALIR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 200, 30, WHITE);
			pantalla = SALIR;
		}


	}
}

void Creditos(Rectangle creditos, Rectangle cursor, int& pantalla)
{
	if (CheckCollisionRecs(creditos, cursor))
	{ 
		
		DrawRectangleRec(creditos, VIOLET);
		DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 30, WHITE);
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(creditos, DARKPURPLE);
			DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 30, WHITE);
			pantalla = CREDITOS;
		}

	}
}

Rectangle Cursor(Rectangle& cursor)
{
	Rectangle _cursor = {static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 250, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 200, 5, 5 };
	cursor.x = GetMouseX() - cursor.width / 2;
	cursor.y = GetMouseY() - cursor.height / 2;
	return cursor;

}


void reiniciar(int& puntaje, int& nave_vida,int& posx,int& posy,bool& rangocorrecto,float& velx,float& vely,bool& gameOver, Rectangle& nave,int& contadorMeteorosDestruido,int& contadorMeterorosChicos, int& contadorMeterorosMedianos)
{
	posx, posy = 0;																													
	velx, vely = 0;
	puntaje = 0;

    contadorMeteorosDestruido = 0;
    contadorMeterorosChicos   = 0;
    contadorMeterorosMedianos = 0;

	
	gameOver = false;
	rangocorrecto = false;
	
	nave.x = SCREEN_WIDTH / 2.0f;
	nave.y = SCREEN_HEIGHT / 2.0f;
	nave.width = 25;
	nave.height = 25;
	nave_vida = 3;

	for (int i = 0; i < MAX_METEORO_GRANDE; i++)
	{
		posx = GetRandomValue(0, static_cast <int>(SCREEN_WIDTH));

		while (!rangocorrecto)
		{
			if (posx > SCREEN_WIDTH / 2 - 150 && posx < SCREEN_WIDTH / 2 + 150)
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

		velx = (float)GetRandomValue(-/*static_cast <int>*/(METEORO_VELOCIDAD), /*static_cast <int>*/(METEORO_VELOCIDAD));
		vely = (float)GetRandomValue(-/*static_cast <int>*/(METEORO_VELOCIDAD), /*static_cast <int>*/(METEORO_VELOCIDAD));

		if (velx == 0 && vely == 0)
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
		meteoroGrande[i].activo = true;
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
		bala[i].position.x = 0;
		bala[i].position.y = 0;
		bala[i].velocidad_x = 0.01f;
		bala[i].velocidad_y = 0.01f;
		bala[i].radio = 2.0f;
		bala[i].dispara = false;
		bala[i].spawnVidaBala = 0;
	}
	
}

//void InitGame()
//{
/*
* 
* musica
* https://freesound.org/people/StephieQueen/sounds/650556/
* 
https://kenney.nl/assets/space-shooter-redux
sonido de meteoro
https://freesound.org/people/Robinhood76/sounds/503554/
sonido de muerte
https://freesound.org/people/IanLyanx/sounds/446759/#
*/