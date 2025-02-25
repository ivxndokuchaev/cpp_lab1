#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double a;
    double b;
    double c;
} QuadraticEquation;

QuadraticEquation readCoefficients(const char* filename) {
    FILE* inputFile = fopen(filename, "r");
    QuadraticEquation eq;

    if (inputFile == NULL) {
        fprintf(stderr, "Не удалось открыть файл.\n");
        exit(1);
    }

    if (fscanf(inputFile, "%lf %lf %lf", &eq.a, &eq.b, &eq.c) != 3) {
        fprintf(stderr, "Ошибка чтения файла.\n");
        fclose(inputFile);
        exit(1);
    }
    fclose(inputFile);
    return eq;
}

int solveQuadraticEquation(const QuadraticEquation eq, double* x1, double* x2) {
    // return 0; - нет вещественных корней
    // return 1; - два совпадающих вещественных корня
    // return 2; - два различных вещественных корня

    double discriminant = eq.b * eq.b - 4 * eq.a * eq.c;

    if (discriminant >= 0) {
        *x1 = (-eq.b + sqrt(discriminant)) / (2 * eq.a);
        *x2 = (-eq.b - sqrt(discriminant)) / (2 * eq.a);
        
        if (*x1 == *x2) {
            return 1;
        }

        return 2;
    } else {
        return 0;
    }
}

void writeRoots(const char* filename, double x1, double x2, int numRoots) {
    FILE* outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Не удалось открыть файл для записи.\n");
        exit(1);
    }

    if (numRoots == 0) {
        fprintf(outputFile, "Нет вещественных корней\n");
    } else if (numRoots == 1) {
        fprintf(outputFile, "x1 = x2 = %lf\n", x1);
    } else {
        fprintf(outputFile, "x1 = %lf\tx2 = %lf\n", x1, x2);
    }

    fclose(outputFile);
}


int main() {
    QuadraticEquation equation;
    double root1, root2;
    int numRoots;

    equation = readCoefficients("data.txt");
    numRoots = solveQuadraticEquation(equation, &root1, &root2);
    writeRoots("out.txt", root1, root2, numRoots);

    printf("Решение записано в файл out.txt\n");

    return 0;
}