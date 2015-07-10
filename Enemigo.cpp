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

#include "Enemigo.h"

/**
 * Constructor de la clase Enemigo
 * @param width Ancho de la ventana
 * @param height Altura de la ventana
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
Enemigo::Enemigo(int w, int h) {
	id = 0;
	rect.w = 47;
	rect.h = 40;
	screen_w = w;
	screen_h = h;
	reset();
}

/**
 * Método que mueve al enemigo
 * @return =true si el  enemigo salió de la pantalla
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
bool Enemigo::mover() {
	rect.y += velocidad;
	if (rect.y>screen_h)
		return true;
	return false;
}

/**
 * Método que reinicia al enemigo cargando "el siguiente"
 * @author Esteban De La Fuente Rubio, DeLaF (esteban[at]delaf.cl)
 * @version 2015-07-10
 */
void Enemigo::reset() {
	id++;
	velocidad = 1;
	rect.x = rand() % (screen_w-rect.w+1);
	rect.y = -rect.h;
}
