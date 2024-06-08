#pragma once
// Contenido del raylib.h
// Incluimos raylib.h
#include "raylib.h"
#include <iostream>
// ...

struct GridCell
{
    bool bloqueado = false;  // Indica si la casilla está bloqueada o desbloqueada
    Color color = CLITERAL(Color){184, 237, 255, 255};   // Color de la casilla
    bool origen = false;
    bool destino = false;
    bool camino = false;
    bool caminoCerrado = false;
    bool volverOri = false;
};


void ponerBloqueoODesbloqueo (GridCell** grid, float cellSizeX, float cellSizeY, bool* pOrigen, bool* pDestino, bool* pEjecuto);
void ponerOrigenODestino(GridCell** grid, float cellSizeX, float cellSizeY, int gridSize, bool* pOrigen, bool* pDestino, bool* pEjecuto);
void reiniciarSeleccion(GridCell** grid, int gridSize);
void reiniciarCamino(GridCell** grid, int gridSize);
void ejecutarAstar(GridCell** grid, int gridSize);
void ejecutarDstarLite(GridCell** grid, int gridSize);
void pasoapaso(GridCell** grid, int gridSize);