#include <stdio.h>
#include <stdbool.h>

#define N 9

void printGrid(int grid[N][N]) {
    printf("\nSolved Sudoku:\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%2d ", grid[row][col]);
        }
        printf("\n");
    }
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {

        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSudoku(int grid[N][N], int row, int col) {
    // If we reached the last cell
    if (row == N - 1 && col == N)
        return true;

    // Move to next row if at end of column
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip already filled cells
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid, row, col + 1))
                return true;
        }

        // Backtrack
        grid[row][col] = 0;
    }

    return false;
}

int main() {
    // 0 means empty cell
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

    if (solveSudoku(grid, 0, 0))
        printGrid(grid);
    else
        printf("No solution exists.\n");

    return 0;
}
