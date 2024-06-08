#include "gridcell.h"
#include <chrono>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 900;  // Ancho de la pantalla
    int screenHeight = 600; // Alto de la pantalla

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitWindow(screenWidth, screenHeight, "Aplicación de Pathfinding");

    const int gridSize = 12; // Tamaño de la grilla (15x15 casillas)

    float cellSizeX = screenWidth / gridSize;  // Tamaño horizontal de cada casilla
    float cellSizeY = screenHeight / gridSize; // Tamaño vertical de cada casilla

    bool *pOrigen = new bool(false);
    bool *pDestino = new bool(false);
    bool *pEjecuto = new bool(false);

    // Matriz para almacenar el estado de cada casilla
    GridCell **gridMuestra = new GridCell *[gridSize];
    for (int i = 0; i < gridSize; i++)
    {
        gridMuestra[i] = new GridCell[gridSize];
    };

    /*
    // Cambiar el tamaño de la ventana a la resolución de la pantalla principal
    SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    // Ajustar la posición de la ventana a la esquina superior izquierda de la pantalla
    SetWindowPosition(0, 0);
    */

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // evitar que esc o cierre
        SetExitKey(WindowShouldClose());
        // Update
        //----------------------------------ks------------------------------------------------

        // Verifica esta presionado la tecla Ctrl Izq
        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
            ponerBloqueoODesbloqueo(gridMuestra, cellSizeX, cellSizeY, pOrigen, pDestino, pEjecuto);
        }

        // Verifica si se presiona clic izquierdo y no esta presionado el Ctrl Izq
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsKeyUp(KEY_LEFT_CONTROL))
        {
            ponerOrigenODestino(gridMuestra, cellSizeX, cellSizeY, gridSize, pOrigen, pDestino, pEjecuto);
        }

        // Verifica esta presionado la tecla ESC
        if (IsKeyPressed(KEY_ESCAPE))
        {
            reiniciarSeleccion(gridMuestra, gridSize);
            *pOrigen = false;
            *pDestino = false;
            *pEjecuto = false;
        }

        // Verifica esta presionado la tecla BACKSPACE, reiniciar camino
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            reiniciarCamino(gridMuestra, gridSize);
            *pEjecuto = false;
        }

        if (IsKeyPressed(KEY_ENTER) && *pOrigen && *pDestino && !*pEjecuto)
        {
            // Crea un objeto time_point para registrar el tiempo de inicio
            auto inicio = std::chrono::high_resolution_clock::now();

            ejecutarAstar(gridMuestra, gridSize);
            *pEjecuto = true;

            // Crea otro objeto time_point para registrar el tiempo de finalización
            auto fin = std::chrono::high_resolution_clock::now();
            // Calcula la duración de la ejecución
            std::chrono::duration<double> duracion = fin - inicio;
            // Imprime la duración en segundos
            std::cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << std::endl;
        }

        if (IsKeyPressed(KEY_SPACE) && *pOrigen && *pDestino && !*pEjecuto)
        {
            // Crea un objeto time_point para registrar el tiempo de inicio
            auto inicio = std::chrono::high_resolution_clock::now();

            ejecutarDstarLite(gridMuestra, gridSize);
            *pEjecuto = true;

            // Crea otro objeto time_point para registrar el tiempo de finalización
            auto fin = std::chrono::high_resolution_clock::now();
            // Calcula la duración de la ejecución
            std::chrono::duration<double> duracion = fin - inicio;
            // Imprime la duración en segundos
            std::cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << std::endl;
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            pasoapaso(gridMuestra, gridSize);
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DrawText("Congrats! You created your first window!", 19.0, 200, 20, LIGHTGRAY);

        // Dibujar la grilla
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                int cellX = i * cellSizeX; // Posición horizontal de la casilla
                int cellY = j * cellSizeY; // Posición vertical de la casilla

                // Dibuja la casilla con el color correspondiente
                DrawRectangle(cellX, cellY, cellSizeX, cellSizeY, gridMuestra[j][i].color);
                DrawRectangleLines(cellX, cellY, cellSizeX, cellSizeY, WHITE);
            }
        }

        if (IsWindowResized())
        {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            cellSizeX = screenWidth / gridSize;  // Tamaño horizontal de cada casilla
            cellSizeY = screenHeight / gridSize; // Tamaño vertical de cada casilla
            SetWindowSize(screenWidth, screenHeight);
            // Realizar cualquier otro ajuste necesario cuando se redimensione la ventana
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}