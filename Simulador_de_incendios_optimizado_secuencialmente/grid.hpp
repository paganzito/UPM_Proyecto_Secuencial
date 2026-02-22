#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>

class Grid
{
    public:
        Grid(int width, int height, int cellSize)
        : rows(height/cellSize), columns(width/cellSize), cellSize(cellSize), cells(rows * columns, 0) {};
        void Draw();
        void SetValue(int row, int column, int value);
        uint8_t GetValue(int row, int column);
        uint8_t GetValueUnsafe(int row, int column) const {
            return cells[row * columns + column];
        }
        bool IsWithinBounds(int row, int column);
        int GetRows() {return rows;}
        int GetColumns() {return columns;} 
        void FillRandom();
        void Clear();
        void ToggleCell(int row, int column);
        void ToggleCellFire (int row, int column);
        void Swap(Grid& other) {
            std::swap(cells, other.cells);
        }
    private:
        int rows;
        int columns;
        int cellSize;
        std::vector<uint8_t> cells;
};