#pragma once
#include "gridcell.h"
#include <cmath>

class GridNodeDL{
public:
    int x;  // Coordenada x del nodo
    int y;  // Coordenada y del nodo
    int g;  // Costo del camino desde el nodo de inicio hasta este nodo
    int h;  // Heurística estimada del costo restante desde este nodo hasta el objetivo
    int rhs;  
    int k1;
    int k2;
    bool bloqueado;
    GridNodeDL* siguiente;
    GridNodeDL* padre;

    // Constructor
    GridNodeDL();

    // Destructor
    ~GridNodeDL();

    // FUNCIONES
    // Imprimir un Nodo
    void imprimirNodo();
    // Función para calcular la distancia de Manhattan entre este nodo y otro nodo
    int manhattanDistancia(GridNodeDL* otro);
    // Función para calcular la distancia de Manhattan del nodo
    double calcularDistancia(GridNodeDL* nodoActual, GridNodeDL* fin);
    //Calcular llaves
    void CalcKey(GridNodeDL* start);
};