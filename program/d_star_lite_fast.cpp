#include "GridNodeDL.h"
#include "ListaGridNodosDL.h"
#include <cmath>
#include <string>

class Grid {
public:
    GridNodeDL* start;
    GridNodeDL* goal;
    ListaGridNodosDL* OpenList;
    GridNodeDL** matriz;
    int filas, columnas;
    //GridCell** grid;

    // Constructor de la clase Grid
    Grid(int x, int y, int sx, int sy, int gx, int gy) {
        this->columnas = x;
        this->filas = y;

        // Crear una matriz de nodos de tamaño (columnas x filas)
        matriz = new GridNodeDL*[columnas];
        for (int i = 0; i < columnas; i++) {
            matriz[i] = new GridNodeDL[filas];
        }

        this->start = &matriz[sx][sy];
        this->goal = &matriz[gx][gy];
        OpenList = new ListaGridNodosDL();
    }

    // Destructor de la clase Grid
    ~Grid() {
        // Liberar la memoria de la matriz
        for (int i = 0; i < filas; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }

    // Obtener un puntero al nodo en las coordenadas (x, y)
    GridNodeDL* getGridNodeDL(int x, int y) {
        return &(matriz[x][y]);
    }

    // Inicializar la matriz de nodos y configurar los valores iniciales
    void initialize(GridCell** grid) {
        for (int i = 0; i < this->filas; i++) {
            for (int j = 0; j < this->columnas; j++) {
                this->matriz[j][i].x = j;
                this->matriz[j][i].y = i;
                this->matriz[j][i].g = std::numeric_limits<int>::max();
                this->matriz[j][i].rhs = std::numeric_limits<int>::max();
                this->matriz[j][i].bloqueado = grid[i][j].bloqueado;            
            }
        }
        std::cout<<"Matriz size: "<<columnas <<";"<< filas<<std::endl;

        
        // Configurar los valores iniciales para el nodo objetivo
        goal->CalcKey(start);
        goal->rhs = 0;
        OpenList->agregarInicio(goal);
    }

    // Actualizar el valor rhs (right-hand-side) de un nodo dado
    void UpdateVertex(GridNodeDL *u)
    {
        if (u != goal)
        { // Calcular rhs
            double min = std::numeric_limits<double>::max();
            int x_vecino, y_vecino;
            GridNodeDL *vecino;
            double posible_rhs;

            // Calcular el valor mínimo rhs de los vecinos del nodo u
            int cont = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                { 
                    x_vecino = u->x + i;
                    y_vecino = u->y + j;
                    vecino = getGridNodeDL(x_vecino, y_vecino);
                    if (enLimites(x_vecino, y_vecino) && !vecino->bloqueado)
                    {
                        if (i == 0 && j == 0)
                        {}
                        else
                        {
                            posible_rhs = std::abs(u->manhattanDistancia(vecino) + vecino->g);
                            if (posible_rhs < min)
                            {
                                min = posible_rhs;
                                u->padre = vecino;
                            }
                        }
                    }
                    cont++;
                }
            }
            u->rhs = min;
        }
        int pos = OpenList->encontrarPos(u->x, u->y);
        if (pos != -1)
        {
            OpenList->sacarNodo(pos);
        }
        // Si el valor g (costo acumulado) es diferente a rhs, se actualiza y se agrega a la lista OpenList
        if (u->g != u->rhs){
            u->CalcKey(start);
            OpenList->InsertarXkey(u);
        }
    }

    // Calcular el camino más corto desde el nodo objetivo hasta el nodo inicial
    void ComputeShortestPath() {//NOS QUEDAMOS ACA-------------------------------------------------------
        GridNodeDL* topKey = OpenList->inicio;
        start->CalcKey(start);
        // Continuar mientras la lista OpenList no esté vacía y se cumpla la condición de parada
        while (!OpenList->esVacia() && (topKey->k1 < this->start->k1 || start->rhs != start->g)) {
            topKey = OpenList->sacarNodo(0);
            // Si el valor g es mayor que rhs, actualizar g y calcular los vecinos
            if (topKey->g > topKey->rhs) { //Overconsistent
                topKey->g = topKey->rhs;
                GridNodeDL* vecino;
                for (int i = -1; i <= 1; i ++) {
                    for (int j = -1; j <= 1; j ++) {
                        int x_neighbor = topKey->x + i;
                        int y_neighbor = topKey->y + j;
                        vecino = getGridNodeDL(x_neighbor, y_neighbor);
                        if (enLimites(x_neighbor, y_neighbor) && !vecino->bloqueado) {
                            if (i == 0 && j == 0)
                            {}else{
                                UpdateVertex(vecino); // agrega nodo a la open list
                            }   
                        }
                    }
                }
            }
            else
            {
                // Si el valor g es menor o igual que rhs, actualizar g y calcular los vecinos (UNDER CONSISTENT)
                topKey->g = std::numeric_limits<int>::max();
                GridNodeDL *vecino;
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        int x_neighbor = topKey->x + i;
                        int y_neighbor = topKey->y + j;

                        vecino = getGridNodeDL(x_neighbor, y_neighbor);
                        if (enLimites(x_neighbor, y_neighbor) && !vecino->bloqueado)
                        {
                            UpdateVertex(vecino); // no se agrega al openlist
                        }
                    }
                }
            }
        }//TERMINA EL WHILE
    }

    // Verificar si las coordenadas (x, y) están dentro de los límites de la matriz
    bool enLimites(int x, int y) {
        return ((x >= 0) && (x < this->columnas)) && ((y >= 0) && (y < this->filas));
    }
};

ListaGridNodosDL *dStarLitePathfinding(GridCell **gridcell, int gridSize, int StartX, int StartY, int GoalX, int GoalY)
{

    Grid grid(gridSize, gridSize, StartX, StartY, GoalX, GoalY);
    grid.initialize(gridcell); // Recibe la grilla grafica
    std::cout << "Initialize" << std::endl;
    GridNodeDL *start = grid.start;
    GridNodeDL *goal = grid.goal;
    std::cout << "Start -> ( x: " << start->x << ", y: " << start->y << ")"
              << "g: " << start->g << " rhs: " << start->rhs << std::endl;
    std::cout << "Goal -> ( x: " << goal->x << ", y: " << goal->y << ")"
              << "g: " << goal->g << " rhs: " << goal->rhs << std::endl;

    std::cout<<"------------MATRIZ-------------"<<std::endl;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            GridNodeDL* aux = &grid.matriz[j][i];
            std::cout<< "["<< aux->x << ";"<< aux->y <<"] ";
            //std::cout<< grid.getGridNodeDL(i,j)->bloqueado<< "  ";
        }
        std::cout<<std::endl;
    }
    grid.ComputeShortestPath();
    
    ListaGridNodosDL *path = new ListaGridNodosDL(); // Crear una instancia de ListaGridNodosDL
    path->ImprimirPath(); //Path Creado
    while (start->padre != nullptr)//start != goal
    {
        GridNodeDL *newStart = nullptr;
        double minCost = std::numeric_limits<double>::max();
        GridNodeDL *neighbor;

        //GUIANDONOS DE LOS PADRES
        newStart = start->padre;

        start = newStart;
        path->agregarFinal(start);
    }
    return path;
}
