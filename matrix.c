#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define create_matrix_double(r, c) create_matrix(r, c, print_value_double, PrintMatrix, input_value_double, input_matrix, TranspositionDoubleMatrix, MultiplyTwoDoubleMatrix, SumTwoDoubleMatrix)

#define create_matrix_complex(r, c) create_matrix(r, c, print_value_complex, PrintMatrix, input_value_complex, input_matrix, TranspositionComplexMatrix, MultiplyTwoComplexMatrix, SumTwoComplexMatrix)

typedef struct Matrix
{
    int lines;
    int columns;
    void ***values;

    void *(*print_value)(void *, int, int);

    void *(*print)(void *);

    void *(*input_value)(void *, int, int);

    void *(*input)(void *);

    void *(*transpose)(void *);

    void *(*mul_matrix)(void *, void *);

    void *(*add_matrix)(void *, void *);
} Matrix;

void *create_matrix(int r, int c, void *print_value, void *print, void *input_value, void *input, void *transpose, void *mul_matrix, void *add_matrix);

void *print_value_double(void *m, int r, int c);

void *print_value_complex(void *m, int r, int c);

void *PrintMatrix(void *a);

void *input_value_double(void *a, int r, int c);

void *input_value_complex(void *a, int r, int c);

void *input_matrix(void *a);

void *TranspositionDoubleMatrix(void *a);

void *TranspositionComplexMatrix(void *a);

void *MultiplyTwoDoubleMatrix(void *a, void *b);

void *MultiplyTwoComplexMatrix(void *a, void *b);

void *SumTwoDoubleMatrix(void *a, void *b);

void *SumTwoComplexMatrix(void *a, void *b);

void *create_double()
{
    int r, c;
    printf("lines: ");
    scanf("%d", &r);
    while (r < 1)
    {
        printf("Enter a positive integer!\nlines: ");
        scanf("%d", &r);
    }
    printf("columns: ");
    scanf("%d", &c);
    while (c < 1)
    {
        printf("Enter a positive integer!\ncolumns: ");
        scanf("%d", &c);
    }
    Matrix *m = create_matrix_double(r, c);
    return (*m).input(m);
}
void *create_complex()
{
    int r, c;
    printf("lines: ");
    scanf("%d", &r);
    while (r < 1)
    {
        printf("Enter a positive integer!\nlines: ");
        scanf("%d", &r);
    }
    printf("columns: ");
    scanf("%d", &c);
    while (c < 1)
    {
        printf("Enter a positive integer!\ncolumns: ");
        scanf("%d", &c);
    }
    Matrix *m = create_matrix_complex(r, c);
    printf("Enter two numbers separated by a space!");
    return (*m).input(m);
}

void *create_matrix(int r, int c,
                    void *print_value,
                    void *print,
                    void *input_value,
                    void *input,
                    void *transpose,
                    void *mul_matrix,
                    void *add_matrix)
{
    Matrix *m = malloc(sizeof(Matrix));
    (*m).lines = *(int *)malloc(sizeof(int));
    (*m).columns = *(int *)malloc(sizeof(int));
    (*m).lines = r;
    (*m).columns = c;
    (*m).values = (void ***)malloc(sizeof(void **) * r);
    for (int i = 0; i < r; i++)
    {
        (*m).values[i] = (void **)malloc(sizeof(void *) * c);
        for (int j = 0; j < c; j++)
        {
            (*m).values[i][j] = (void *)malloc(sizeof(void *));
        }
    }
    (*m).print_value = print_value;
    (*m).print = print;
    (*m).input_value = input_value;
    (*m).input = input;
    (*m).transpose = transpose;
    (*m).mul_matrix = mul_matrix;
    (*m).add_matrix = add_matrix;
    return m;
}

int main()
{
    printf("Select the type of matrices:\n1 - double\n2 - complex\n");
    int s1 = 0;
    Matrix *m;
    while ((s1 < 1) || (s1 > 2))
    {
        scanf("%d", &s1);
        switch (s1)
        {
        case 1:
        {
            m = create_double();
            break;
        }
        case 2:
        {
            m = create_complex();
            break;
        }
        default:
        {
            printf("Enter a number from the list!\n");
            break;
        }
        }
    }
    int s2 = 0, r, c;
    Matrix *m1;
    while (s2 != 5)
    {
        printf("\nYour matrix:\n");
        (*m).print(m);
        printf("Select the action with matrix:\n1 - input new matrix\n2 - transpose\n3 - add matrix\n4 - multiply by matrix\n5 - exit\n");
        scanf("%d", &s2);
        switch (s2)
        {
        case 1:
        {
            if (s1 == 1)
                m = create_double();
            if (s1 == 2)
                m = create_complex();
            break;
        }
        case 2:
        {
            m = (*m).transpose(m);
            break;
        }
        case 3:
        {
            if (s1 == 1)
                m1 = create_double();
            if (s1 == 2)
                m1 = create_complex();
            printf("\nNew matrix:\n");
            (*m1).print(m1);
            m = (*m).add_matrix(m, m1);
            break;
        }
        case 4:
        {
            if (s1 == 1)
                m1 = create_double();
            if (s1 == 2)
                m1 = create_complex();
            printf("\nNew matrix:\n");
            (*m1).print(m1);
            m = (*m).mul_matrix(m, m1);
            break;
        }
        case 5:
        {
            break;
        }
        default:
        {
            printf("Enter a number from the list!\n");
            break;
        }
        }
    }
    return 0;
}

//Выводит элемент вещественной матрицы
void *print_value_double(void *a, int r, int c)
{
    Matrix *m = (Matrix *)a;
    printf("%.1lf", *(double *)(*m).values[r][c]);
}

//Выводит элемент комплексной матрицы
void *print_value_complex(void *a, int r, int c)
{
    Matrix *m = (Matrix *)a;
    double complex v = *(double complex *)(*m).values[r][c];
    if (cimag(v) < 0)
    {
        printf("%.1f - %.1f*I", creal(v), fabs(cimag(v)));
    }
    else
    {
        printf("%.1f + %.1f*I", creal(v), cimag(v));
    }
    return NULL;
}

//Вывод на экран матрицу
void *PrintMatrix(void *a)
{
    Matrix *m = (Matrix *)a;
    for (int i = 0; i < (*m).lines; i++)
    {
        printf("|");
        for (int j = 0; j < (*m).columns; j++)
        {
            (*m).print_value(m, i, j);
            if (j < (*m).columns - 1)
                printf("   ");
        }
        printf("|\n");
    }
    printf("\n");
    return NULL;
}

//Ввод с клавиатуры элемента вещественной
void *input_value_double(void *a, int r, int c)
{
    Matrix *m = (Matrix *)a;
    scanf("%lf", (double *)((*m).values[r][c]));
    return m;
}

//Ввод с клавиатуры элемента комплексной матрицы
void *input_value_complex(void *a, int r, int c)
{
    Matrix *m = (Matrix *)a;
    double d1, d2;
    scanf("%lf%lf", &d1, &d2);
    *(double complex *)((*m).values[r][c]) = d1 + d2 * I;
    return m;
}

//Ввод с клавиатуры матрицы
void *input_matrix(void *a)
{
    Matrix *m = (Matrix *)a;
    for (int i = 0; i < (*m).lines; i++)
    {
        for (int j = 0; j < (*m).columns; j++)
        {
            printf("matrix[%d][%d]: ", i + 1, j + 1);
            m = (*m).input_value(m, i, j);
        }
    }
    return m;
}

//Транспонирует вещественную матрицу
void *TranspositionDoubleMatrix(void *a)
{
    Matrix *m = (Matrix *)a;
    Matrix *t = create_matrix_double((*m).columns, (*m).lines);
    for (int i = 0; i < (*t).lines; i++)
    {
        for (int j = 0; j < (*t).columns; j++)
        {
            (*t).values[i][j] = (*m).values[j][i];
        }
    }
    return t;
}

//Транспонирует комплексную матрицу
void *TranspositionComplexMatrix(void *a)
{
    Matrix *m = (Matrix *)a;
    Matrix *t = create_matrix_complex((*m).columns, (*m).lines);
    for (int i = 0; i < (*t).lines; i++)
    {
        for (int j = 0; j < (*t).columns; j++)
        {
            (*t).values[i][j] = (*m).values[j][i];
        }
    }
    return t;
}

//Перемножает вещественные матрицы
void *MultiplyTwoDoubleMatrix(void *a, void *b)
{
    Matrix *m_a = (Matrix *)a;
    Matrix *m_b = (Matrix *)b;
    if ((*m_a).columns != (*m_b).lines)
    {
        printf("WRONG SIZES OF MATRIX\n");
        return m_a;
    }
    int r = (*m_a).lines, c = (*m_b).columns, n = (*m_a).columns;
    Matrix *m = create_matrix_double(r, c);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            *(double *)(*m).values[i][j] = (double)0;
            for (int k = 0; k < n; k++)
            {
                *(double *)(*m).values[i][j] += *(double *)(*m_a).values[i][k] * *(double *)(*m_b).values[k][j];
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Перемножает комплексные матрицы
void *MultiplyTwoComplexMatrix(void *a, void *b)
{
    Matrix *m_a = (Matrix *)a;
    Matrix *m_b = (Matrix *)b;
    if ((*m_a).columns != (*m_b).lines)
    {
        printf("WRONG SIZES OF MATRIX\n");
        return m_a;
    }
    int r = (*m_a).lines, c = (*m_b).columns, n = (*m_a).columns;
    Matrix *m = create_matrix_complex(r, c);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            *(double complex *)(*m).values[i][j] = (double complex)0;
            for (int k = 0; k < n; k++)
            {
                *(double complex *)(*m).values[i][j] +=
                    *(double complex *)(*m_a).values[i][k] * *(double complex *)(*m_b).values[k][j];
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Прибавляет вещественную матрицу
void *SumTwoDoubleMatrix(void *a, void *b)
{
    Matrix *m_a = (Matrix *)a;
    Matrix *m_b = (Matrix *)b;
    if (((*m_a).lines != (*m_b).lines) || ((*m_a).columns != (*m_b).columns))
    {
        printf("WRONG SIZES OF MATRIX\n");
        return m_a;
    }
    for (int i = 0; i < (*m_a).lines; i++)
    {
        for (int j = 0; j < (*m_a).columns; j++)
        {
            *(double *)(*m_a).values[i][j] += *(double *)(*m_b).values[i][j];
        }
    }
    printf("Operation completed successfully!\n");
    return m_a;
}

//Прибавляет комплексную матрицу
void *SumTwoComplexMatrix(void *a, void *b)
{
    Matrix *ma = (Matrix *)a;
    Matrix *mb = (Matrix *)b;
    if (((*ma).lines != (*mb).lines) || ((*ma).columns != (*mb).columns))
    {
        printf("WRONG SIZES OF MATRIX\n");
        return ma;
    }
    for (int i = 0; i < (*ma).lines; i++)
    {
        for (int j = 0; j < (*ma).columns; j++)
        {
            *(double complex *)(*ma).values[i][j] += *(double complex *)(*mb).values[i][j];
        }
    }
    printf("Operation completed successfully!\n");
    return ma;
}
