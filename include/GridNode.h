#pragma once
#include "gridcell.h"
#include <cmath>

class GridNode {
public:
    int x;  // Coordenada x del nodo
    int y;  // Coordenada y del nodo
    int g;  // Costo del camino desde el nodo de inicio hasta este nodo
    int h;  // Heurística estimada del costo restante desde este nodo hasta el objetivo
    int f;  // Suma de g y h
    GridNode* siguiente;
    GridNode* padre;

    // Constructor
    GridNode(int x, int y);

    // Destructor
    ~GridNode();

    // FUNCIONES
    // Imprimir un Nodo
    void imprimirNodo();
    // Función para calcular la distancia de Manhattan entre este nodo y otro nodo
    int manhattanDistancia(GridNode* otro);
    // Función para calcular la distancia de Manhattan del nodo
    void calcularDistancia(GridNode* nodoActual, GridNode* fin);
};