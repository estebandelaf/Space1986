/**
 * Space1986
 * Copyright (C) 2015 Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 *
 * Este programa es software libre: usted puede redistribuirlo y/o modificarlo
 * bajo los términos de la Licencia Pública General GNU publicada
 * por la Fundación para el Software Libre, ya sea la versión 3
 * de la Licencia, o (a su elección) cualquier versión posterior de la misma.
 *
 * Este programa se distribuye con la esperanza de que sea útil, pero
 * SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita
 * MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO.
 * Consulte los detalles de la Licencia Pública General GNU para obtener
 * una información más detallada.
 *
 * Debería haber recibido una copia de la Licencia Pública General GNU
 * junto a este programa.
 * En caso contrario, consulte <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#include "Space1986.h"

/**
 * Función principal del juego
 * @param argc Cantidad de parámetros pasados al programa
 * @param argv Parámetros pasados al programa
 * @return =0 si todo fue ok
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
int main (int argc, char** argv) {
	SDL_Window* window = SDL::createWindow(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	bool salir = false;
	SDL_Event event;
	const Uint8 *keystates = SDL_GetKeyboardState(NULL);
	char info1[100];
	char info2[100];
	int enemigos = 20;
	int avance = 0;
	int puntaje = 0;
	TTF_Font *fuente = SDL::loadFont(FONT_NAME, FONT_SIZE, FONT_STYLE);
	SDL_Surface* background = SDL::loadImage("data/image/background.png", screen->format);
	Nave nave(SCREEN_WIDTH, SCREEN_HEIGHT);
	nave.sprite = SDL::loadImage("data/image/viper_mark.png", screen->format);
	Enemigo enemigo(SCREEN_WIDTH, SCREEN_HEIGHT);
	enemigo.sprite = SDL::loadImage("data/image/wraith.png", screen->format);
	srand (time(NULL));
	// ciclo para ir refrescando la pantalla del juego
	while (!salir) {
		// manejar eventos pendientes
		while (SDL_PollEvent(&event)!=0) {
			if (event.type==SDL_QUIT) {
				salir = true;
			}
			else if (event.type==SDL_KEYDOWN) {
				if (event.key.keysym.sym==SDLK_ESCAPE)
					salir = true;
			}
		}
		// dibujar fondo
		SDL_BlitSurface(background, NULL, screen, NULL);
		// nave
		if (nave.energia && avance!=100) {
			nave.mover(keystates);
			if (keystates[SDL_SCANCODE_SPACE])
				nave.disparar();
			nave.moverRayo();
			if (nave.rayo.w && SDL::collision(nave.rayo, enemigo.rect)) {
				puntaje++;
				nave.rayo = (SDL_Rect) {0, 0, 0, 0};
				enemigo.reset();
			}
			SDL_BlitSurface(nave.sprite, NULL, screen, &nave.rect);
			if (nave.rayo.w)
				SDL_FillRect(screen, &nave.rayo, SDL_MapRGBA(screen->format,255,255,0,0));
			// enemigo
			if (enemigo.mover() || SDL::collision(nave.rect, enemigo.rect)) {
				nave.energia--;
				enemigo.reset();
			}
			SDL_BlitSurface(enemigo.sprite, NULL, screen, &enemigo.rect);
		}
		// información del juego
		avance = (int)(((enemigo.id-1)*100)/enemigos);
		sprintf(info1, "Energia: %2d Avance: %2d Puntaje: %2d", nave.energia, avance, puntaje);
		SDL::print(screen, info1, 10, 0, fuente, (SDL_Color) {255,255,255,0});
		if (!nave.energia) {
			sprintf(info2, "GAME OVER!");
			SDL::print(screen, info2, 10, 16, fuente, (SDL_Color) {255,255,255,0});
		} else if (avance==100) {
			sprintf(info2, "GANASTE!");
			SDL::print(screen, info2, 10, 16, fuente, (SDL_Color) {255,255,255,0});
		}
		// actualizar pantalla
		SDL_UpdateWindowSurface(window);
	}
	// terminar ejecución
	SDL_DestroyWindow(window); // destruir ventana
	SDL_Quit(); // terminar SDL
	return 0; // retornar todo ok
}
