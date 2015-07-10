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

#include "Nave.h"

/**
 * Constructor de la clase Nave
 * @param width Ancho de la ventana
 * @param height Altura de la ventana
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
Nave::Nave(int w, int h) {
	energia = 10;
	velocidad = 1;
	rect.w = 60;
	rect.h = 69;
	rect.x = (w-rect.w)/2;
	rect.y = h - rect.h;
	screen_w = w;
	screen_h = h;
	rayo = (SDL_Rect) {0, 0, 0, 0};
}

/**
 * Método que mueve la nave según la o las teclas que se hayan presionado
 * @param keystates Estado de las teclas que se han mantenido presionadas
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
void Nave::mover(const Uint8 *keystates) {
	// mover hacia arriba
	if (keystates[SDL_SCANCODE_UP]) {
		rect.y -= velocidad;
		if (rect.y<0)
			rect.y = 0;
	}
	// mover hacia abajo
	if (keystates[SDL_SCANCODE_DOWN]) {
		rect.y += velocidad;
		if ((rect.y+rect.h)>screen_h)
			rect.y = screen_h - rect.h;
	}
	// mover hacia la izquierda
	if (keystates[SDL_SCANCODE_LEFT]) {
		rect.x -= velocidad;
		if (rect.x<0)
			rect.x = 0;
	}
	// mover hacia la derecha
	if (keystates[SDL_SCANCODE_RIGHT]) {
		rect.x += velocidad;
		if ((rect.x+rect.w)>screen_w)
			rect.x = screen_w - rect.w;
	}
}

/**
 * Método que pone el rayo en la posición inicial y le asigna tamaño para que
 * sea utilizado
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
void Nave::disparar() {
	rayo = (SDL_Rect) {(rect.x+(rect.w-1)/2), rect.y+2, 3, 8};
}

/**
 * Método que mueve el rayo hacia la parte superior de la pantalla y lo hace
 * desaparecer en caso que se haya salido de la misma
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
void Nave::moverRayo() {
	if (rayo.w)
		rayo.y--;
	if (rayo.y<0)
		rayo = (SDL_Rect) {0, 0, 0, 0};
}
