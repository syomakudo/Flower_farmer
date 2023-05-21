#include <stdio.h>
#include <stdlib.h>

void changeValue(int** array, int rows, int cols, int row, int col, int newValue) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        array[row][col] = newValue;
    } else {
        printf("Invalid row or column index.\n");
    }
}

int main() {
    int rows = 3;
    int cols = 3;

    // 2次元配列の動的確保
    int** array = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        array[i] = (int*)malloc(cols * sizeof(int));
    }

    // 初期値の設定
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = i * cols + j;
        }
    }

    // 配列の内容を表示
    printf("Before:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // (1, 1)の要素を変更
    int newRow = 1;
    int newCol = 1;
    int newValue = 99;
    changeValue(array, rows, cols, newRow, newCol, newValue);

    // 配列の内容を表示（変更後）
    printf("After:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 配列の解放
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}
