#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    printf("\nSolved Sudoku:\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%2d ", grid[row][col]);
        printf("\n");
    }
}

// Check if it's safe to place a number
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Main solver using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool emptyFound = false;

    // Find an empty cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                emptyFound = true;
                break;
            }
        }
        if (emptyFound)
            break;
    }

    // If no empty cell, puzzle is solved
    if (!emptyFound)
        return true;

    // Try digits 1-9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursive call
            if (solveSudoku(grid))
                return true;

            // Undo move
            grid[row][col] = 0;
        }
    }

    return false; // Trigger backtracking
}

// Main function
int main() {
    // 0 indicates empty cells
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid))
        printGrid(grid);
    else
        printf("No solution exists.\n");

    return 0;
}