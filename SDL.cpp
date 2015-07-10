/**
 * SDL
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

#include "SDL.h"

/**
 * Método para inicializar SDL y crear ventana
 * @param title Título que se pondrá a la ventana
 * @param width Ancho de la ventana
 * @param height Altura de la ventana
 * @return Ventaba creada
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
SDL_Window* SDL::createWindow(std::string title, int width, int height) {
	/*if (SDL_Init(SDL_INIT_EVERYTHING)<0) {
		printf("[error] SDL no inició: %s\n", SDL_GetError());
		return NULL;
	}*/
	/*if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("[error] SDL Image no inicio: %s\n", IMG_GetError());
		return NULL;
	}*/
	if (TTF_Init()==-1) {
		printf("[error] SDL TTF no inició: %s \n", TTF_GetError());
		return NULL;
	}
	/*if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
		printf("[error] SDL Mix no inició\n");
		return NULL;
	}*/
	SDL_Window* window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_SHOWN
	);
	if (window==NULL) {
		printf("[error] Ventana no se creó: %s\n", SDL_GetError());
		return NULL;
	}
	return window;
}

/**
 * Método que permite cargar una imagen desde un archivo
 * @param path Ruta hacia el archivo con la imagen
 * @param format Formato de la pantalla (ej: screen->format)
 * @param height Altura de la ventana
 * @return Superficie con la imagen
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
SDL_Surface* SDL::loadImage(std::string path, SDL_PixelFormat* format) {
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface==NULL) {
		printf(
			"[error] Imagen %s no se cargó: %s\n",
			path.c_str(),
			IMG_GetError()
		);
		return NULL;
	}
	optimizedSurface = SDL_ConvertSurface(loadedSurface, format, 0);
	if (optimizedSurface==NULL) {
		printf(
			"[error] Imagen %s no se optimizó: %s\n",
			path.c_str(),
			SDL_GetError()
		);
		return NULL;
	}
	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}

/**
 * Método que permite cargar una fuente TTF desde un archivo
 * @param path Ruta hacia el archivo con la fuente TTF
 * @param size Tamaño de la fuente
 * @param style Estilo que se deberá aplicar a la fuente
 * @return Fuente
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
TTF_Font* SDL::loadFont(std::string path, short int size, Uint8 style) {
	TTF_Font *fuente = TTF_OpenFont(path.c_str(), size);
	if (fuente==NULL) {
		printf("[error] Fuente %s: %s\n", path.c_str(), TTF_GetError());
		return NULL;
	}
	TTF_SetFontStyle(fuente, style);
	return fuente;
}

/**
 * Método que permite imprimir texto en la pantalla a través de SDL
 * @param screen Superficie donde se desea imprimir
 * @param txt Texto que se quiere renderizar
 * @param x Posición en coordenada X del inicio del texto
 * @param y Posición en coordenada Y del inicio del texto
 * @param font Fuente TTF a utilizar
 * @param color Color que se aplicará a la fuente
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
void SDL::print(SDL_Surface *screen, char *txt, int x, int y, TTF_Font *font, SDL_Color color) {
	SDL_Surface *surface = TTF_RenderText_Blended(font, txt, color);
	SDL_Rect rect = (SDL_Rect) {x, y, 0, 0};
	SDL_BlitSurface(surface, NULL, screen, &rect);
	SDL_FreeSurface(surface);
}

/**
 * Método que revisa si dos rectángulos están en colisión
 * @param rect1 Rectángulo 1
 * @param rect2 Rectángulo 2
 * @return =true si rect1 está colisionando con rect2
 * @author http://headerphile.blogspot.com/2014/04/part-5-game-programming-in-sdl2.html
 * @version 2014-04-29
 */
bool SDL::collision(SDL_Rect rect1, SDL_Rect rect2) {
	// buscar esquinas rectángulo 1
	int left1 = rect1.x;
	int right1 = rect1.x + rect1.w;
	int top1 = rect1.y;
	int bottom1 = rect1.y + rect1.h;
	// buscar esquinas rectángulo 2
	int left2 = rect2.x;
	int right2 = rect2.x + rect2.w;
	int top2 = rect2.y;
	int bottom2 = rect2.y + rect2.h;
	// verificar esquinas
	if (left1>right2 || right1<left2 || top1>bottom2 || bottom1 < top2)
		return false;
	return true; 
}
