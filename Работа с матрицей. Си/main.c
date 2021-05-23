#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
    int** array2D;
    int width;
    int height;
};

typedef struct Matrix Matrix;
Matrix* initializeMatrix(int W, int H);
void freeMatrix(Matrix *matrix);
void readMatrix(FILE *file, Matrix *matrix);
void printMatrix(Matrix *matrix);

int main()
{
    FILE *file;
    const char* src_file = "C:\\text.txt"; // В пути к файлу экранируем символ '\' бэкслешем
    int W_MATRIX, H_MATRIX; // Ширина Высота
    file = fopen(src_file, "r");
    if (file != NULL)
    {
        fscanf(file, "%d", &H_MATRIX); // Считываем высоту матрицы
        fscanf(file, "%d", &W_MATRIX); // Считываем ширину матрицы
        Matrix *matrix = initializeMatrix(W_MATRIX, H_MATRIX);
        readMatrix(file, matrix);
        printMatrix(matrix);
        fclose(file);
        freeMatrix(matrix);
    }
    else
    {
        printf("%s", "Error opening file");
    }
    return 0;
}

Matrix* initializeMatrix(int W, int H)
{
    Matrix *matrix = (Matrix*)malloc(sizeof (Matrix));
    matrix->array2D = (int**)malloc(sizeof (int*) * H);
    for (int i = 0; i < H; ++i)
    {
        matrix->array2D[i] = (int*)malloc(sizeof (int) * W);
    }
    matrix->width = W;
    matrix->height = H;
    return matrix;
}

void freeMatrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->height; ++i)
    {
        free(matrix->array2D[i]);
    }
    free(matrix->array2D);
    free(matrix);
}

void readMatrix(FILE *file, Matrix *matrix)
{
    for (int i = 0; i < matrix->height; ++i)
    {
        for (int j = 0; j < matrix->width; ++j)
        {
            fscanf(file, "%d", matrix->array2D[i] + j);
        }
    }
}

void printMatrix(Matrix *matrix)
{
    printf("HEIGHT = %d\n", matrix->height);
    printf("WIDTH = %d\n", matrix->width);
    for (int i = 0; i < matrix->height; ++i)
    {
        for (int j = 0; j < matrix->width; ++j)
        {
            printf("%d\t", matrix->array2D[i][j]);
        }
        printf("\n");
    }
}
