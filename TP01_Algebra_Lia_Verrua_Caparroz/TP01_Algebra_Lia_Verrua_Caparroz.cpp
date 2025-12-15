#include "MainLoopManager.h"

//------------------------------------------------------------------------------------
//							Instrucciones
// 
// 
// Utilizando el mouse se pueden crear y mover poligonos.
// Si hay una interseccion esta se marcara con un punto magenta
// al ser sobrepuestas, se mostraran las intersecciones con un punto de color
// si un poligono no permite terminarse o no se puede seguir dibujando, usar la tecla Borrar
// 
// 
//							Controles
// 
//	Click izquierdo				->		poner punto para el poligono actual
//	Mantener clic izquierdo		->		hacer curvas
//	Click derecho				->		seleccionar poligono
//	Enter						->		terminar el poligono actual
//	Borrar (sin seleccion)		->		eliminar el ultimo punto puesto (mantener para eliminar varios)
//	Borrar (con seleccion)		->		elimina el poligono seleccionado
//
//------------------------------------------------------------------------------------

void main()
{
	mainLoop();
}