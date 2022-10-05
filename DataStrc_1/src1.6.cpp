#include "time.h"
#include <stdio.h>
#include <stdlib.h>

#define AROWS 3
#define BROWS 4
#define ACOLS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5

class Matrix {
private:
  int rows, cols;
  int *data;

public:
  Matrix(int r, int c);
  int get_data();
  int show_data();
  Matrix addMatrix(Matrix const &);
 
};

Matrix::Matrix(int r, int c) : rows(r), cols(c) { data = new int[r * c]; }

int Matrix::get_data() {

  for (int i = 0; i < rows * cols; i++)
    data[i] = rand() % (rows * cols);

  
  return 1;
}

int Matrix::show_data() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", data[i * rows + j]);
    }
    printf("\n");
  }
  return 1;
}



Matrix Matrix::addMatrix(Matrix const &m) {
  Matrix tm(rows, cols);
  for (int i = 0; i < rows * cols; i++) {
    tm.data[i] = this->data[i] + m.data[i];
  }

  return tm; 
}



int main() {

  Matrix matrixA(AROWS, ACOLS);
  Matrix matrixA1(AROWS, ACOLS);
  Matrix matrixB(BROWS, BCOLS);
  Matrix matrixC(CROWS, CCOLS);
  Matrix matrixD(AROWS, ACOLS);

  srand(time(NULL));

  matrixA.get_data();
  matrixA.show_data();
  matrixA1.get_data();
  matrixA1.show_data();
  // matrixA.sort_data();
  matrixD = matrixA.addMatrix(matrixA1);
  printf("show D data\n");
  matrixD.show_data();

  return 0;
}