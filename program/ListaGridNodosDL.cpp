#include "ListaGridNodosDL.h"
#include "GridNodeDL.h"


// Constructor de la lista de GridNodos
ListaGridNodosDL::ListaGridNodosDL()
{
    cant = 0;
    inicio = nullptr;
}

// Destructor de la lista de GridNodos
ListaGridNodosDL::~ListaGridNodosDL()
{
    while (cant != 0)
    {
        GridNodeDL* aux = inicio;
        inicio = inicio->siguiente;
        delete aux;
        cant--;
    }
}


// Setters y Getters
// Devolver el valor de X en funcion a su posicion;
int ListaGridNodosDL::getXporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->x;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNodeDL* temp = inicio;
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
int ListaGridNodosDL::getYporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->y;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNodeDL* temp = inicio;
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
int ListaGridNodosDL::getGporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->g;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNodeDL* temp = inicio;
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
int ListaGridNodosDL::getHporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->h;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNodeDL* temp = inicio;
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
int ListaGridNodosDL::getRHSporPos(int pos)
{
    if (pos == 0)
    {
        return inicio->rhs;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNodeDL* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        return temp->rhs;
    }
    return -1;
}


// Funciones
// Imprimir un Nodo en funcion a la posicion
void ListaGridNodosDL::imprimirNodo(int pos)
{
    if (cant == 0)
    {
        std::cout << "NO HAY NODO QUE MOSTRAR" << std::endl;
    }
    else if (pos < cant)
    {
        int indice = 0;
        GridNodeDL* temp = inicio;
        while (indice < pos)
        {
            temp = temp->siguiente;
            indice++;
        }
        std::string textoDevolver = 
        "GridNodo " + std::to_string(pos) + " [" +
        "X: " + std::to_string(temp->x) + ", "
        "Y: " + std::to_string(temp->y)+ "]"// + ", "
        //"G: " + std::to_string(temp->g) + ", "
        //"H: " + std::to_string(temp->h) + ", "
        //"F: " + std::to_string(temp->rhs) 
        ;
        
        std::cout << textoDevolver  << std::endl;
    }
    else
    {
        std::cout << "POSICION INVALIDA" << std::endl;
    }
}

// Verificar si la lista esta vacia
bool ListaGridNodosDL::esVacia()
{
    return (cant == 0);
}

// Agregar GridNodeDL al Inicio de la lista
void ListaGridNodosDL::agregarInicio(GridNodeDL* otro)
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
GridNodeDL* ListaGridNodosDL::sacarNodo(int pos)
{
    if (pos < cant)
    {
        GridNodeDL* aux = inicio;//0
        GridNodeDL* auxAnterior = nullptr;
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

// Eliminar un GridNodeDL en funcion a la posicion
/*void ListaGridNodosDL::eliminarPos(int pos)
{
    if (inicio == nullptr) {
        return;
    } else if (pos==0 && inicio->siguiente == nullptr)
    {
        cant--;
        delete inicio;
    }else if (pos == 0 && inicio->siguiente != nullptr) {
        GridNodeDL* temp = inicio;
        inicio = inicio->siguiente;
        cant--;
        delete temp;
    } else if (pos < cant) {
        GridNodeDL* temp = inicio;
        GridNodeDL* anterior = nullptr;

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
*/

// Encontrar un GridNodeDL en funcion a su elemento "x" e "y"
int ListaGridNodosDL::encontrarPos(int posX, int posY)
{
    GridNodeDL* temp = inicio;
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
void ListaGridNodosDL::agregarListAlFinal(ListaGridNodosDL* listaNueva)
{
    if (inicio == nullptr)
    {
        // Si la lista actual está vacía, se actualiza el inicio con la lista nueva
        inicio = listaNueva->inicio;
    }
    else
    {
        // Si la lista actual no está vacía, se busca el último nodo y se le asigna el inicio de la lista nueva
        GridNodeDL* temp = inicio;
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

void ListaGridNodosDL::agregarPadre(int pos, GridNodeDL* nodo)
{
    GridNodeDL* aux = inicio;
    for (int i = 0; i < pos; i++)
    {
        aux = aux->siguiente;
    }
    aux->padre = nodo;
}

// Agregar un GridNodeDL en funcion a la posicion
void ListaGridNodosDL::InsertarXkey(GridNodeDL *otro)
{
    if (this->cant == 0)
    {
        this->inicio = otro;
        cant++;
    }
    else
    {
        GridNodeDL *anterior = nullptr;
        GridNodeDL *actual = inicio;
        while (actual != nullptr && (otro->k1 > actual->k1)) // mientras nuevo sea mayor al actual
        {
            //std::cout<<"Entra al while de busqueda"<<std::endl;
            anterior = actual;
            actual = actual->siguiente;
        }
        //std::cout<<"Termina busqueda"<<std::endl;
        if (anterior == nullptr)
        {
            otro->siguiente = inicio;
            inicio = otro; // Asignar como inicio
            cant++;
        }
        else
        {
            otro->siguiente = actual;
            anterior->siguiente = otro;
            cant++;
        }
    }
}


// Agregar GridNode al Final de la lista
void ListaGridNodosDL::agregarFinal(GridNodeDL* otro)
{
    if (inicio != nullptr) {
        GridNodeDL* temp = inicio;
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

void ListaGridNodosDL::Imprimir(){
    GridNodeDL* aux = this->inicio;
    std::cout<<"OpenList -> ";
    while (aux != nullptr)
    {
        std::cout<<"["<< aux->x<< ";"<<aux->y<<"] ";
        aux = aux->siguiente;
    }
    std::cout<<std::endl;
}

void ListaGridNodosDL::ImprimirPath(){
    GridNodeDL* aux = this->inicio;
    std::cout<<"Path -> ";
    while (aux != nullptr)
    {
        std::cout<<"["<< aux->x<< ";"<<aux->y<<"] ";
        aux = aux->siguiente;
    }
    std::cout<<std::endl;
}


