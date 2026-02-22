#include <raylib.h>
#include "grid.hpp"

void Grid::Draw()
{
    for(int row = 0; row < rows; row ++) 
    {
        for(int column = 0; column < columns; column++)
        {
            Color color;
            if (cells[row][column] == 1) {
                color = Color{55, 55, 55, 255};   // Gris  (Estado 1)
            } 
            else if (cells[row][column] == 2) {
                color = Color{0, 255, 0, 255};   // Verde (Estado 2)
            } 
            else if (cells[row][column] == 3) {
                color = Color{255, 0, 0, 255};   // Rojo (Estado 3)
            } 
            else {
                color = Color{139, 69, 19, 255}; // Marron (Tierra)
            }
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

void Grid::SetValue(int row, int column, int value)
{
    if(IsWithinBounds(row, column))
    {
        cells[row][column] = value;
    }
}

int Grid::GetValue(int row, int column)
{
    if(IsWithinBounds(row, column))
    {
        return cells[row][column];
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
    for(int row = 0; row < rows; row ++)
    {
        for(int column = 0; column < columns; column++)
        {
            int azar = GetRandomValue(1, 100);

           if (azar <= 5) {
                cells[row][column] = 0; // 5% Probabilidad: Estado 0
            } 
            else if (azar <= 15) {      // 10% Probabilidad (del 6 al 15): Estado 1
                 cells[row][column] = 1; 
            }
            else if (azar <= 20) {      // 20% Probabilidad (del 16 al 35): Estado 3 (Fuego)
                cells[row][column] = 3; 
            } 
            else {
                cells[row][column] = 2; // Resto (65%): Estado 2 (Bosque)
            }
        }
    }
}

void Grid::Clear()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            cells[row][column] = 1;
        }
    }
}

void Grid::ToggleCell(int row, int column)
{
    if(IsWithinBounds(row, column))
    {
        cells[row][column] = 2;
    }
}

void Grid::ToggleCellFire(int row, int column)
{
    if(IsWithinBounds(row, column))
    {
        cells[row][column] = 3;
    }
}
