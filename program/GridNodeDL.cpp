#include "GridNodeDL.h"/////////////falta h

// Constructor del GridNode
GridNodeDL::GridNodeDL()
{
    this->x = 0;
    this->y = 0;
    g = 0;
    h = 0;
    rhs = 0;
    k1 = 0;
    k2 = 0;
    siguiente = nullptr;
    padre = nullptr;
    bloqueado = false;
}

// Destructor del GridNode
GridNodeDL::~GridNodeDL()
{
}


// FUNCIONES
// Imprimir un Nodo
void GridNodeDL::imprimirNodo()
{
    std::string textoDevolver = "GridNode ["
    "X: " + std::to_string(x) + ", "
    "Y: " + std::to_string(y) + ", "
    "G: " + std::to_string(g) + ", "
    "H: " + std::to_string(h) + ", "
    "RHS: " + std::to_string(rhs) + "]";
    std::cout << textoDevolver  << std::endl;
}

// Función para calcular la distancia de Manhattan entre este nodo y otro nodo
int GridNodeDL::manhattanDistancia(GridNodeDL* otro)
{
    int diffX = std::abs(x - otro->x);
    int diffY = std::abs(y - otro->y);
    int diagonalMoves = std::min(diffX, diffY); // Número de movimientos en diagonal
    int lateralMoves = std::max(diffX, diffY) - diagonalMoves; // Número de movimientos laterales

    return diagonalMoves * 14 + lateralMoves * 10;
}

// Función para calcular la distancia de Manhattan del nodo
double GridNodeDL::calcularDistancia(GridNodeDL* nodoActual, GridNodeDL* inicio)
{
    g = nodoActual->g + manhattanDistancia(nodoActual);
    h = manhattanDistancia(inicio);
    return g + h;
}

void GridNodeDL::CalcKey(GridNodeDL* start){
    h = manhattanDistancia(start);
    k1 = std::min(g, rhs + h);//AFUERA O ADENTRO
    k2 = std::min(g, rhs);
}


