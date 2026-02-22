#include <vector>
#include <utility>
#include "simulation.hpp"
#include <raylib.h>

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
    int liveNeighbors = 0;
    int rows = grid.GetRows();
    int cols = grid.GetColumns();

    
    int rowU = row - 1;
    if (rowU < 0) rowU = rows - 1;

    int rowD = row + 1;
    if (rowD == rows) rowD = 0;

    int colL = column - 1;
    if (colL < 0) colL = cols - 1;

    int colR = column + 1;
    if (colR == cols) colR = 0;

    
    liveNeighbors += grid.GetValueUnsafe(rowU, column); // N
    liveNeighbors += grid.GetValueUnsafe(rowD, column); // S
    liveNeighbors += grid.GetValueUnsafe(row, colL);    // W
    liveNeighbors += grid.GetValueUnsafe(row, colR);    // E
    liveNeighbors += grid.GetValueUnsafe(rowU, colL);   // NW
    liveNeighbors += grid.GetValueUnsafe(rowU, colR);   // NE
    liveNeighbors += grid.GetValueUnsafe(rowD, colL);   // SW
    liveNeighbors += grid.GetValueUnsafe(rowD, colR);   // SE

    return liveNeighbors;
}

void Simulation::Update()
{
    if(IsRunning())
    {
        for(int row = 0; row < grid.GetRows(); row++)
        {
            for(int column = 0; column < grid.GetColumns(); column++)
            {
                int liveNeighbors = CountLiveNeighbors(row, column);
                int cellValue = grid.GetValueUnsafe(row, column);
                
                
                if(cellValue == 1) {
                    if(GetRandomValue(1, 100) <= 2)
                    {
                        tempGrid.SetValue(row, column, 0);
                    }
                    else
                    {
                        tempGrid.SetValue(row, column, 1);
                    }
                }

                else if(cellValue == 2)
                {
                    if( GetRandomValue(1, 100) <= (100-humedad)*(liveNeighbors/8))
                    {
                        tempGrid.SetValue(row, column, 3);
                    }
                    else
                    {
                        if(GetRandomValue(1, 1000) <= 5)
                        {
                            tempGrid.SetValue(row, column, 3);
                        }
                        else
                        {
                            tempGrid.SetValue(row, column, 2);
                        }
                        
                    }
                }
                else if (cellValue == 3){
                    tempGrid.SetValue(row, column, 1);
                }
                else
                {
                    if(GetRandomValue(1, 100) <= 2)
                    {
                        tempGrid.SetValue(row, column, 2);
                    }
                    else
                    {
                        tempGrid.SetValue(row, column, 0);
                    }
                }
            }
        }
        grid.Swap(tempGrid);
    }
}

void Simulation::ClearGrid()
{
    if(!IsRunning())
    {
        grid.Clear();
    }
}

void Simulation::CreateRandomState()
{
    if(!IsRunning())
    {
        grid.FillRandom();
    }
}

void Simulation::ToggleCell(int row, int column)
{
    if(!IsRunning())
    {
        grid.ToggleCell(row, column);
    }
}
void Simulation::ToggleCellFire(int row, int column)
{
    if(!IsRunning())
    {
        grid.ToggleCellFire(row, column);
    }
}

