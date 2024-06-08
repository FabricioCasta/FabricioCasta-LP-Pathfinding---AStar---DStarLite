# Compilación y Ejecución del Proyecto

## Compilar archivos

Para compilar el archivo `grid.cpp` con la carpeta `include`, utiliza los siguientes comandos en orden:


g++ -c program/*.cpp -Iinclude; Move-Item -Path "*.o" -Destination compile -Force


g++ ./compile/*.o -Wall -I./include -L./lib main.cpp -o main -lraylib -lopengl32 -lgdi32 -lwinmm


.\main.exe


## Funcionamiento del grid

Al inicio, usando **LeftClic** en cualquier parte de la grilla, se hará el punto de partida (recuadro en verde), y el segundo **LeftClic** será el punto del final (recuadro en amarillo), luego con **Ctrl+LeftClic** podrás poner obstáculos que corten el camino a recorrer (recuadros en rojo), y cuando se termine de crear el laberinto, con la tecla **Enter**, correrá el algoritmo A_star y mostrará el camino más corto según dicho algoritmo en color azul; y si se apreta la tecla **Space**, correrá el algoritmo D_star_lite y mostrará el camino mas corto según dicho algoritmo en color gris, y si se apreta la tecla **Key_Right**, se verá como paso a paso el camino va avanzando y actualizandose en color azul hasta llegar al final, cumpliendo así el objetivo de los algoritmos del pathfinding.

Como adicional, para reiniciar el recorrido solo apretar la tecla **BackSpace**.
Para borrar los obstaculos, presionar **Ctrl+RightClic** sobre el camino rojo.
Para borrar los punto de partida o final, presionar sobre ellos **Ctrl+LeftClic** y luego **Ctrl+RightClic**, y con solo **LeftClic** podrás colocar o nuevo inicio o nuevo final.
Para reiniciar por completo la grilla, solo apretar el boton **Esc**.