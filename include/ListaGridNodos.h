#pragma once
// Contenido del gridcell.h
#include "gridcell.h"
#include "GridNode.h"
#include <cmath>


class ListaGridNodos {
public:
    int cant;
    GridNode* inicio;

    // Constructor
    ListaGridNodos();

    // Destructor
    ~ListaGridNodos();

    // Setters y Getters
    // Devolver el valor de X en funcion a su posicion;
    int getXporPos(int pos);
    // Devolver el valor de Y en funcion a su posicion;
    int getYporPos(int pos);
    // Devolver el valor de G en funcion a su posicion;
    int getGporPos(int pos);
    // Devolver el valor de H en funcion a su posicion;
    int getHporPos(int pos);
    // Devolver el valor de F en funcion a su posicion;
    int getFporPos(int pos);

    // Funciones
    // Imprimir un Nodo en funcion a la posicion
    void imprimirNodo(int pos);
    // Verificar si la lista esta vacia
    bool esVacia();
    // Agregar GridNode al inicio de la lista
    void agregarInicio(GridNode* otro);
    // Eliminar un GridNode en funcion a la posicion
    void eliminarPos(int pos);
    // Encontrar un GridNode en funcion a su elemento "x" e "y"
    int encontrarPos(int posX, int posY);
    // Agregar una lista de GridNodo al final de la lista;
    void agregarListAlFinal(ListaGridNodos* listaNueva);
    //Sacar un GridNodo de la lista por posicion 
    GridNode* sacarNodo(int pos);///hecha
    //agrega un padre
    void agregarPadre(int pos, GridNode* nodo);

    // Agregar GridNode al final de la lista
    //void agregarFinal(GridNode* otro);
    // Agregar un GridNode en funcion a la posicion
    //void agregarXPos(GridNode* otro, int pos);
    // Sacar el GridNodo en funcion a su posicion;
    //void sacarNodoAgregarFinal(ListaGridNodos* listaSacar, int pos);
};


ListaGridNodos* aStarPathfinding(GridCell** grid, int gridSize, GridNode* inicio, GridNode* fin);
void CalcularVecinos(ListaGridNodos* vecinos, GridCell** grid, GridNode* nodoActual ,GridNode* fin,  int gridSize);
