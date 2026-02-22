#include <raylib.h>
#include "grid.hpp"

void Grid::Draw()
{
    for(int row = 0; row < rows; row ++) 
    {
        for(int column = 0; column < columns; column++)
        {
            
            int value = cells[row * columns + column]; 
            Color color;
            
            // Lógica de colores
            if (value == 1) color = Color{55, 55, 55, 255}; //Gris (Estado 1)   
            else if (value == 2) color = Color{0, 255, 0, 255};  //Verde (Estado 2)   
            else if (value == 3) color = Color{255, 0, 0, 255};     //Rojo (Estado 3)
            else color = Color{139, 69, 19, 255};       //Marron (Estadp 0)
            
            
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

void Grid::SetValue(int row, int column, int value)
{
    if(IsWithinBounds(row, column))
    {
        cells[row * columns + column] = value;
    }
}

uint8_t Grid::GetValue(int row, int column)
{
    if(IsWithinBounds(row, column))
    {
        return cells[row * columns + column];
    }
    return 0;
}



bool Grid::IsWithinBounds(int row, int column)
{
    if(row >= 0 && row < rows && column >= 0 && column < columns)
    {
        return true;
    }
    return false;
}


void Grid::FillRandom()
{
    for(size_t i = 0; i < cells.size(); i++) {
        int azar = GetRandomValue(1, 100);
        if (azar <= 5) cells[i] = 0;
        else if (azar <= 15) cells[i] = 1;
        else if (azar <= 20) cells[i] = 3;
        else cells[i] = 2;
    }
}

void Grid::Clear()
{
    std::fill(cells.begin(), cells.end(), 0);
}

void Grid::ToggleCell(int row, int column)
{
    SetValue(row, column, 2);
}

void Grid::ToggleCellFire(int row, int column)
{
    SetValue(row, column, 3);
}
