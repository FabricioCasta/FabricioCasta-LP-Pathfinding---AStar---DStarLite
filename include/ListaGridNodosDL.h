#pragma once
// Contenido del gridcell.h
#include "gridcell.h"
#include "GridNodeDL.h"
#include <cmath>


class ListaGridNodosDL {
public:
    int cant;
    GridNodeDL* inicio;

    // Constructor
    ListaGridNodosDL();

    // Destructor
    ~ListaGridNodosDL();

    // Setters y Getters
    // Devolver el valor de X en funcion a su posicion;
    int getXporPos(int pos);
    // Devolver el valor de Y en funcion a su posicion;
    int getYporPos(int pos);
    // Devolver el valor de G en funcion a su posicion;
    int getGporPos(int pos);
    // Devolver el valor de H en funcion a su posicion;
    int getHporPos(int pos);
    // Devolver el valor de RHS en funcion a su posicion;
    int getRHSporPos(int pos);

    // Funciones
    // Imprimir un Nodo en funcion a la posicion
    void imprimirNodo(int pos);
    // Verificar si la lista esta vacia
    bool esVacia();
    // Agregar GridNode al inicio de la lista
    void agregarInicio(GridNodeDL* otro);
    // Eliminar un GridNode en funcion a la posicion
    void eliminarPos(int pos);
    // Encontrar un GridNode en funcion a su elemento "x" e "y"
    int encontrarPos(int posX, int posY);
    // Agregar una lista de GridNodo al final de la lista;
    void agregarListAlFinal(ListaGridNodosDL* listaNueva);
    //Sacar un GridNodo de la lista por posicion 
    GridNodeDL* sacarNodo(int pos);///hecha
    //agrega un padre
    void agregarPadre(int pos, GridNodeDL* nodo);
    //Insertar OpenList por KEY
    void InsertarXkey(GridNodeDL* otro);
    // Agregar GridNode al final de la lista
    void agregarFinal(GridNodeDL* otro);
    // Agregar un GridNode en funcion a la posicion
    // void agregarXPos(GridNode* otro, int pos);
    // Sacar el GridNodo en funcion a su posicion;
    //void sacarNodoAgregarFinal(ListaGridNodos* listaSacar, int pos);
    void Imprimir();
    void ImprimirPath();
};


ListaGridNodosDL* dStarLitePathfinding(GridCell** gridcell, int gridSize, int StartX, int StartY, int GoalX, int GoalY);
void CalcularVecinos(ListaGridNodosDL* vecinos, GridCell** grid, GridNodeDL* nodoActual ,GridNodeDL* fin,  int gridSize);
