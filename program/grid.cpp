#include "gridcell.h"
#include "ListaGridNodos.h"
#include "GridNode.h"
#include "ListaGridNodosDL.h"
#include "GridNodeDL.h"
#include <ctime>

void ponerBloqueoODesbloqueo(GridCell **grid, float cellSizeX, float cellSizeY, bool *pOrigen, bool *pDestino, bool *pEjecuto)
{
    Vector2 mousePosition = GetMousePosition();

    // Verifica clic izquierdo / Para bloquear
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        // Calcula la posición de la casilla correspondiente
        int cellX = mousePosition.x / cellSizeX;
        int cellY = mousePosition.y / cellSizeY;

        // Marca la casilla como bloqueada y cambia su color a rojo
        if (!grid[cellY][cellX].bloqueado)
        {
            grid[cellY][cellX].bloqueado = true;
            grid[cellY][cellX].color = RED;
            *pEjecuto = false;
        }
        if (grid[cellY][cellX].origen == true)
        {
            grid[cellY][cellX].origen = false;
            grid[cellY][cellX].volverOri = false;
            grid[cellY][cellX].bloqueado = true;
            grid[cellY][cellX].color = RED;
            *pOrigen = false;
        }
        else if (grid[cellY][cellX].destino == true)
        {
            grid[cellY][cellX].destino = false;
            grid[cellY][cellX].bloqueado = true;
            grid[cellY][cellX].color = RED;
            *pDestino = false;
        }
    }

    // Verifica clic derecho
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        // Calcula la posición de la casilla correspondiente
        int cellX = mousePosition.x / cellSizeX;
        int cellY = mousePosition.y / cellSizeY;

        // Desbloquea la casilla y cambia su color a celeste claro
        if (grid[cellY][cellX].bloqueado) // grid[cellY][cellX].bloqueado == true
        {
            grid[cellY][cellX].bloqueado = false;
            grid[cellY][cellX].color = CLITERAL(Color){184, 237, 255, 255};
            *pEjecuto = false;
        }
    }
}

void ponerOrigenODestino(GridCell **grid, float cellSizeX, float cellSizeY, int gridSize, bool *pOrigen, bool *pDestino, bool *pEjecuto)
{
    Vector2 mousePosition = GetMousePosition();

    // Calcula la posición de la casilla correspondiente
    int cellX = mousePosition.x / cellSizeX;
    int cellY = mousePosition.y / cellSizeY;

    // Verifica si es la primera selección (casilla origen)
    if (!*pOrigen && !grid[cellY][cellX].destino)
    {
        grid[cellY][cellX].origen = true;
        grid[cellY][cellX].volverOri = true;
        // Pinta la casilla origen de color verde
        grid[cellY][cellX].color = GREEN;
        *pEjecuto = false;
        *pOrigen = true;
    }
    // Verifica si es la segunda selección (casilla destino)
    else if (!*pDestino)
    {
        grid[cellY][cellX].destino = true;
        // Pinta la casilla destino de color amarillo
        grid[cellY][cellX].color = YELLOW;
        *pEjecuto = false;
        *pDestino = true;
    }
}

void reiniciarSeleccion(GridCell **grid, int gridSize)
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            grid[j][i].bloqueado = false;                           // Desbloquea la casilla
            grid[j][i].color = CLITERAL(Color){184, 237, 255, 255}; // Color celeste claro
            grid[j][i].origen = false;
            grid[j][i].volverOri = false;
            grid[j][i].destino = false;
            grid[j][i].camino = false;
        }
    }
}

void reiniciarCamino(GridCell **grid, int gridSize)
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (!grid[j][i].origen && !grid[j][i].destino && !grid[j][i].bloqueado) // grid[j][i].camino == true
            {
                grid[j][i].color = CLITERAL(Color){184, 237, 255, 255}; // Color celeste claro
                grid[j][i].camino = false;
            }
        }
    }
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[j][i].volverOri && !grid[j][i].origen)
            {
                for (int k = 0; k < gridSize; k++)
                {
                    for (int h = 0; h < gridSize; h++)
                    {
                        if (!grid[h][k].destino && !grid[h][k].bloqueado)
                        {
                            grid[h][k].color = CLITERAL(Color){184, 237, 255, 255};
                            grid[h][k].camino = false;
                            grid[h][k].origen = false;
                        }
                    }
                }
                grid[j][i].origen = true;
                grid[j][i].color = GREEN;
            }
        }
    }
}

void ejecutarAstar(GridCell **grid, int gridSize)
{

    int origenX, origenY, destX, destY;
    /// X,Y GOAL Y DEL START
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[j][i].origen)
            {
                origenX = i;
                origenY = j;
            }
            if (grid[j][i].destino)
            {
                destX = i;
                destY = j;
            }
        }
    }

    GridNode *origen = new GridNode(origenX, origenY);
    GridNode *destino = new GridNode(destX, destY);

    std::cout << "origen: " << origen->x << ", " << origen->y << std::endl;
    std::cout << "destino: " << destino->x << ", " << destino->y << std::endl;

    ListaGridNodos *camino = aStarPathfinding(grid, gridSize, origen, destino);

    for (int i = 0; i < camino->cant; i++)
    {
        grid[camino->getYporPos(i)][camino->getXporPos(i)].camino = true;
        grid[camino->getYporPos(i)][camino->getXporPos(i)].color = BLUE;
    }

    std::cout << "Salto de linea: JAAAAA" << std::endl;
    for (int i = 0; i < camino->cant; i++)
    {
        std::cout << "posicion del camino " << i + 1 << ": PosX-> " << camino->getXporPos(i) << " , PosY-> " << camino->getYporPos(i) << std::endl;
    }
}

void ejecutarDstarLite(GridCell **grid, int gridSize)
{
    int origenX, origenY, destX, destY;
    /// X,Y GOAL Y DEL START
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[j][i].origen)
            {
                origenX = i;
                origenY = j;
            }
            if (grid[j][i].destino)
            {
                destX = i;
                destY = j;
            }
        }
    }

    ListaGridNodosDL *camino = dStarLitePathfinding(grid, gridSize, origenX, origenY, destX, destY);
    std::cout << "retorna camino" << std::endl;
    camino->ImprimirPath();
    camino->sacarNodo(camino->cant - 1);
    camino->ImprimirPath();
    GridNodeDL *aux = camino->inicio;
    while (aux != nullptr)
    {
        grid[aux->y][aux->x].camino = true;
        grid[aux->y][aux->x].color = GRAY;
        aux = aux->siguiente;
    }
}

void pasoapaso(GridCell **grid, int gridSize)
{

    // Quita el camino de Gris. todo camino= true, pasa a camino = false.
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[j][i].camino && !grid[j][i].bloqueado) // grid[j][i].camino == true y lo esta bloqueado
            {
                grid[j][i].color = CLITERAL(Color){184, 237, 255, 255}; // pinta celeste
            }
            if (grid[j][i].camino) // grid[j][i].camino == true
            {
                grid[j][i].camino = false; // borra camino.
                std::cout << "Borra camino" << std::endl;
            }
            if (grid[j][i].caminoCerrado)
            {
                grid[j][i].color = CLITERAL(Color){184, 237, 255, 255}; // Color celeste claro
                grid[j][i].caminoCerrado = false;
            }
        }
    }

    /// Toma origen y destino
    int origenX, origenY, destX, destY;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[j][i].origen)
            {
                origenX = i;
                origenY = j;
            }
            if (grid[j][i].destino)
            {
                destX = i;
                destY = j;
            }
        }
    }

    // calculo el camino mas corto
    ListaGridNodosDL *camino = dStarLitePathfinding(grid, gridSize, origenX, origenY, destX, destY);
    std::cout << "-------------Paso a Paso---------------" << std::endl;
    camino->ImprimirPath();
    camino->sacarNodo(camino->cant - 1);
    camino->ImprimirPath();

    if (camino->inicio != nullptr)
    {
        // Pintar solo el primero
        GridNodeDL *aux = camino->sacarNodo(0);
        if (aux != nullptr)
        {
            std::cout << "Pina uno" << std::endl;
            grid[aux->y][aux->x].color = BLUE;
            // NO CAMBIA CAMINO A TRUE.
        }
        // ya se pintó solo el primero

        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                grid[j][i].origen = false;
                grid[j][i].camino = false;
                grid[j][i].caminoCerrado = false;
            }
        }

        // poner nuevo origen
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                if (aux->y == j && aux->x == i)
                {
                    grid[j][i].origen = true;
                    std::cout << "Pone nuevo el origen" << std::endl;
                }
            }
        }

        // volver a pintar el nuevo path de gris.
        GridNodeDL *nuevoaux = camino->inicio;
        while (nuevoaux != nullptr)
        {
            grid[nuevoaux->y][nuevoaux->x].camino = true;
            grid[nuevoaux->y][nuevoaux->x].color = GRAY;
            nuevoaux = nuevoaux->siguiente;
        }
    }
}