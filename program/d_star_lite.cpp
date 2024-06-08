/*
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
            std::cout<<"Entra al primer if de UpdateVertex"<<std::endl;
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
                            std::cout << "[" << x_vecino << "," << y_vecino << "] Posible_rhs: " << posible_rhs << " i: " << i << " j:" << j << "Bloqueado -> "<<vecino->bloqueado<< std::endl;
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
            std::cout<<"Calcula key: "<<u->k1<<std::endl;
            OpenList->InsertarXkey(u); 
            std::cout<<"Add to Open list ["<<u->x <<";"<<u->y<< "]  g: "<<u->g<< " rhs: "<<u->rhs <<" padre: ["<<u->padre->x <<";"<<u->padre->y<< "]" << std::endl;
        }
    }

    // Calcular el camino más corto desde el nodo objetivo hasta el nodo inicial
    void ComputeShortestPath() {//NOS QUEDAMOS ACA-------------------------------------------------------
        GridNodeDL* topKey = OpenList->inicio;
        start->CalcKey(start);
        // Continuar mientras la lista OpenList no esté vacía y se cumpla la condición de parada
        while (!OpenList->esVacia() && (topKey->k1 < this->start->k1 || start->rhs != start->g)) {
            std::cout<<"---------ENTRA AL WHILE DE COMPUTE SHORTESTPATH------------"<<std::endl;
            topKey = OpenList->sacarNodo(0);
            // Si el valor g es mayor que rhs, actualizar g y calcular los vecinos
            if (topKey->g > topKey->rhs) { //Overconsistent
                topKey->g = topKey->rhs;
                GridNodeDL* vecino;
                for (int i = -1; i <= 1; i ++) {
                    for (int j = -1; j <= 1; j ++) {
                        int x_neighbor = topKey->x + i;
                        int y_neighbor = topKey->y + j;
                        std::cout<<"vecino: "<< x_neighbor << ","<<y_neighbor<<std::endl;
                        vecino = getGridNodeDL(x_neighbor, y_neighbor);
                        if (enLimites(x_neighbor, y_neighbor) && !vecino->bloqueado) {
                            if (i == 0 && j == 0)
                            {}else{
                                std::cout<<"OpenList Antes de UpdateVertex"<<std::endl;
                                OpenList->Imprimir();                                
                                UpdateVertex(vecino);
                                std::cout<<"OpenList Desp de UpdateVertex"<<std::endl;
                                OpenList->Imprimir();
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
                            std::cout<<"OpenList Antes de UpdateVertex"<<std::endl;
                            OpenList->Imprimir();
                            UpdateVertex(vecino);
                            std::cout<<"OpenList Desp de UpdateVertex"<<std::endl;
                            OpenList->Imprimir();
                        }
                    }
                }
            }
        }//TERMINA EL WHILE
        std::cout<<"---------RESUMEN DE LA PRIMERA ITERACION------------"<<std::endl;
        OpenList->Imprimir();
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"----------------------------------------------------"<<std::endl;
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
    std::cout<<std::endl;
    std::cout<<"Bloqueados -> ";
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            GridNodeDL* aux = &grid.matriz[j][i];
            if (aux->bloqueado)
            {
                //std::cout<< "["<< i << ";"<< j <<"] ";
                std::cout<< "["<< aux->x << ";"<< aux->y <<"] ";
            }
        }
    }
    std::cout<<std::endl;
    std::cout<<"-------------------------------"<<std::endl;
    grid.ComputeShortestPath();
    std::cout << "ComputeShortesPath Terminado. Inicia marcha atras." << std::endl;
    ListaGridNodosDL *path = new ListaGridNodosDL(); // Crear una instancia de ListaGridNodosDL
    std::cout << "Path creado " << std::endl;
    path->ImprimirPath();
    std::cout << "Path: " << std::endl;
    while (start->padre != nullptr)//start != goal
    {
        //path->agregarInicio(start);                      // Agregar al inicio del Nodo
        
        /* if (start->g == std::numeric_limits<int>::max()) {
             path->~ListaGridNodosDL(); // No hay un camino conocido, se limpia la lista de nodos
             return path;
        }*/
/*
        GridNodeDL *newStart = nullptr;
        double minCost = std::numeric_limits<double>::max();
        GridNodeDL *neighbor;

        //GUIANDONOS DE LOS PADRES
        newStart = start->padre;

        //GUIANDONOS DE LOS MIN RHS
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int x_neighbor = start->x + i;
                int y_neighbor = start->y + j;
                neighbor = grid.getGridNodeDL(x_neighbor, y_neighbor);
                if (grid.enLimites(x_neighbor, y_neighbor) && !neighbor->bloqueado)
                {
                    std::cout<<"MinCost: "<<minCost<<" vecino RHS: "<< neighbor->rhs<<std::endl;
                    if (neighbor->rhs < minCost)
                    {
                        minCost = neighbor->rhs;
                        newStart = neighbor;
                    }
                }
            }
        }
        

        start = newStart;
        path->agregarFinal(start);
        std::cout << "[" << start->x << ";" << start->y << "]" << std::endl;

    }
    std::cout<<"termina el while retorna lista camino: "<<path->cant<<std::endl;
    path->ImprimirPath();
    return path;
}

*/