#include "GridNode.h"

// Constructor del GridNode
GridNode::GridNode(int x, int y)
{
    this->x = x;
    this->y = y;
    g = 0;
    h = 0;
    f = 0;
    siguiente = nullptr;
    padre = nullptr;
}

// Destructor del GridNode
GridNode::~GridNode()
{
}


// FUNCIONES
// Imprimir un Nodo
void GridNode::imprimirNodo()
{
    std::string textoDevolver = "GridNode ["
    "X: " + std::to_string(x) + ", "
    "Y: " + std::to_string(y) + ", "
    "G: " + std::to_string(g) + ", "
    "H: " + std::to_string(h) + ", "
    "F: " + std::to_string(f) + "]";
    std::cout << textoDevolver  << std::endl;
}

// Función para calcular la distancia de Manhattan entre este nodo y otro nodo
int GridNode::manhattanDistancia(GridNode* otro)
{
    int diffX = std::abs(x - otro->x);
    int diffY = std::abs(y - otro->y);
    int diagonalMoves = std::min(diffX, diffY); // Número de movimientos en diagonal
    int lateralMoves = std::max(diffX, diffY) - diagonalMoves; // Número de movimientos laterales

    return diagonalMoves * 14 + lateralMoves * 10;
}

// Función para calcular la distancia de Manhattan del nodo
void GridNode::calcularDistancia(GridNode* nodoActual, GridNode* fin)
{
    g = nodoActual->g + manhattanDistancia(nodoActual);
    h = manhattanDistancia(fin);
    f = g + h;
}
