#include <raylib.h>
#include <iostream>
#include "simulation.hpp"
#include <chrono>

int main(int argc, char* argv[])
{
    //Falta de argumento
    if (argc < 6) {
        std::cout << "Uso: " << argv[0] << " <Anchura> <Altura> <TamanoCelda> <NumeroIteraciones> <Humedad>" << std::endl;
        std::cout << "Ejemplo: " << argv[0] << " 800 600 10" << std::endl;
        return 1; 
    }

    Color GREY = {29, 29, 29, 255};
    const int WINDOW_WIDTH = std::stoi(argv[1]);
    const int WINDOW_HEIGHT = std::stoi(argv[2]);
    const int CELL_SIZE = std::stoi(argv[3]);
    const int LIMIT_ITERATIONS = std::stoi(argv[4]);
    const int HUMEDAD = std::stoi(argv[5]); //0-100
    
    //int FPS = 8;
    //SetTargetFPS(FPS);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life");
    
    Simulation simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE, HUMEDAD};


    
    bool runningBenchmark = false;
    int currentIteration = 0;

  
    auto inicio = std::chrono::steady_clock::now();

    //Simulation Loop
    while(WindowShouldClose() == false) 
    {   
        if (runningBenchmark)
        {
            currentIteration++;

            // (B) Verificar final
            if (currentIteration >= LIMIT_ITERATIONS)
            {
                auto fin = std::chrono::steady_clock::now();
                auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
                runningBenchmark = false;
                std::cout << "Tiempo transcurrido: " << duracion.count() << " ms" << std::endl;
                CloseWindow();
                return 0;
            }
        }
        // 1. Event Handling
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            simulation.ToggleCell(row, column);
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            simulation.ToggleCellFire(row, column);
        }
        if(IsKeyPressed(KEY_ENTER))
        {
            SetWindowTitle("Game of Life is running ...");
            runningBenchmark = true;
            
            simulation.Start();
            inicio = std::chrono::steady_clock::now();
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            simulation.Stop();
            SetWindowTitle("Game of Life has stopped.");
        }
        else if(IsKeyPressed(KEY_R))
        {
            simulation.CreateRandomState();
        }
        else if(IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
        }

        // 2. Updating State
        simulation.Update(); 

        // 3. Drawing
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
}