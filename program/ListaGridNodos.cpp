#include "ListaGridNodos.h"
#include "GridNode.h"


// Constructor de la lista de GridNodos
ListaGridNodos::ListaGridNodos()
{
    cant = 0;
    inicio = nullptr;
}

// Destructor de la lista de GridNodos
ListaGridNodos::~ListaGridNodos()
{
    while (cant != 0)
    {
        GridNode* aux = inicio;
        inicio = inicio->siguiente;
        delete aux;
        cant--;
    }
}


// Setters y Getters
// Devolver el valor de X en funcion a su posicion;
int ListaGridNodos::getXporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->x;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNode* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        return temp->x;
    }
    return -1;
}
// Devolver el valor de Y en funcion a su posicion;
int ListaGridNodos::getYporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->y;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNode* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        return temp->y;
    }
    return -1;
}
// Devolver el valor de G en funcion a su posicion;
int ListaGridNodos::getGporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->g;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNode* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        return temp->g;
    }
    return -1;
}
// Devolver el valor de H en funcion a su posicion;
int ListaGridNodos::getHporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->h;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNode* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        return temp->h;
    }
    return -1;
}
// Devolver el valor de F en funcion a su posicion;
int ListaGridNodos::getFporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->f;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNode* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        return temp->f;
    }
    return -1;
}


// Funciones
// Imprimir un Nodo en funcion a la posicion
void ListaGridNodos::imprimirNodo(int pos)
{
    if (cant == 0)
    {
        std::cout << "NO HAY NODO QUE MOSTRAR" << std::endl;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNode* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        std::string textoDevolver = 
        "GridNodo " + std::to_string(pos) + " [" +
        "X: " + std::to_string(temp->x) + ", "
        "Y: " + std::to_string(temp->y) + ", "
        "G: " + std::to_string(temp->g) + ", "
        "H: " + std::to_string(temp->h) + ", "
        "F: " + std::to_string(temp->f) + "]";
        
        std::cout << textoDevolver  << std::endl;
    }
    else
    {
        std::cout << "POSICION INVALIDA" << std::endl;
    }
}

// Verificar si la lista esta vacia
bool ListaGridNodos::esVacia()
{
    return (cant == 0);
}

// Agregar GridNode al Inicio de la lista
void ListaGridNodos::agregarInicio(GridNode* otro)
{
    if (inicio == nullptr)
    {
        inicio = otro;
    }else{
        otro->siguiente = inicio;
        inicio = otro;
    }
    cant++;
}

// Saca un nodo de una posicion dada
GridNode* ListaGridNodos::sacarNodo(int pos)
{
    if (pos < cant)
    {
        GridNode* aux = inicio;
        GridNode* auxAnterior = nullptr;
        for (int i = 0; i < pos; i++)
        {
            auxAnterior = aux;
            aux= aux->siguiente;
        }
        if (auxAnterior == nullptr)
        {
            inicio = inicio->siguiente;
        }else{
            auxAnterior->siguiente = aux->siguiente;
        }
        aux->siguiente = nullptr;
        cant--;
        return aux;
    }
    else
    {
        return nullptr;
    }
}

// Eliminar un GridNode en funcion a la posicion
void ListaGridNodos::eliminarPos(int pos)
{
    if (inicio == nullptr) {
        return;
    } else if (pos==0 && inicio->siguiente == nullptr)
    {
        cant--;
        delete inicio;
    }else if (pos == 0 && inicio->siguiente != nullptr) {
        GridNode* temp = inicio;
        inicio = inicio->siguiente;
        cant--;
        delete temp;
    } else if (pos < cant) {
        GridNode* temp = inicio;
        GridNode* anterior = nullptr;

        for (int i = 0; i < pos; i++)
        {
            anterior = temp;
            temp = temp->siguiente;
        }
        anterior->siguiente = temp->siguiente;
        temp->siguiente = nullptr;
        delete temp;
        cant--;
    }
}


// Encontrar un GridNode en funcion a su elemento "x" e "y"
int ListaGridNodos::encontrarPos(int posX, int posY)
{
    GridNode* temp = inicio;
    int indice = 0;
    while (temp != nullptr)
    {
        if (temp->x == posX && temp->y == posY)
        {
            return indice;
        }
        temp = temp->siguiente;
        indice++;
    }
    return -1;
}

// Agregar una lista de GridNodo al final de la lista;
void ListaGridNodos::agregarListAlFinal(ListaGridNodos* listaNueva)
{
    if (inicio == nullptr)
    {
        // Si la lista actual está vacía, se actualiza el inicio con la lista nueva
        inicio = listaNueva->inicio;
    }
    else
    {
        // Si la lista actual no está vacía, se busca el último nodo y se le asigna el inicio de la lista nueva
        GridNode* temp = inicio;
        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = listaNueva->inicio;
    }
    cant += listaNueva->cant;

    // Limpiar la lista nueva
    listaNueva->inicio = nullptr;
    listaNueva->cant = 0;
}

void ListaGridNodos::agregarPadre(int pos, GridNode* nodo)
{
    GridNode* aux = inicio;
    for (int i = 0; i < pos; i++)
    {
        aux = aux->siguiente;
    }
    aux->padre = nodo;
}




/*
// Agregar un GridNode en funcion a la posicion
void ListaGridNodos::agregarXPos(GridNode* otro, int pos)
{
    if (pos == 0) {
        otro->siguiente = inicio;
        inicio = otro;
        cant++;
    } else if (pos<cant) {
        GridNode* temp = inicio;
        GridNode* anterior = nullptr;

        for (int i = 0; i < pos; i++)
        {
            anterior = temp;
            temp = temp->siguiente;
        }

        otro->siguiente = temp;
        anterior->siguiente = otro;
        cant++;
    }
}
*/

/*
// Agregar GridNode al Final de la lista
void ListaGridNodos::agregarFinal(GridNode* otro)
{
    if (inicio != nullptr) {
        GridNode* temp = inicio;
        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = otro;
        cant++;
    } else {
        inicio = otro;
        cant++;
    }
}
*/


