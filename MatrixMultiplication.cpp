#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int **matrxMultipling3x3(int **, int **);
void writeValue(int **);
int **matrxMultipling(int **, int **, int, int, int, int);
void fillMatrix(int **, int, int, int *);

int main( ){
  int **A, **B, **C, k = 1;    //Two deminsilan matrixes

  A = new int * [3];    // 3 x3
  B = new int * [3];
  C = new int * [3];

  for(int i = 0; i < 3; i++ ){   //Creating referance to each element of row
    A [i] = new int [3];
    B [i] = new int [3];
    C [i] = new int [3];
  }

  for(int i = 0; i < 3; i++ ){    //Fill matrixes
    for(int j = 0; j < 3; j ++ ){
      A[i][j] = k;
      B[i][j] = k;
      k++;
    }
  }

  C = matrxMultipling3x3(A, B);
  //C = matrxMultipling(A, B , 3, 3, 3, 3);
  writeValue(C);


  for(int i = 0; i < 3; i++ ){      //Clearing memory
    delete [] A [i];
    delete [] C [i];
    delete [] B [i];
  }

  delete [] A;
  delete [] B;
  delete [] C;

  return 0;
}

int **matrxMultipling3x3(int **MA, int **MB){     //Multipling function
  int temp, **result;
  result = new int * [3];

  for(int i = 0; i < 3; i++){
    result[i] = new int [3];
  }

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      temp = 0;
      for(int p = 0; p < 3; p++){
        temp += MA[i][p] * MB[p][j];
        result[i][j] = temp;
      }
    }
  }
  return result;
}

void writeValue(int **matrix) {     //Write matrix
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      cout << setw(6) << matrix[i][j];
    }
    cout << endl;
  }
}

int **matrxMultipling(int **MA, int **MB, int rowsA, int columnsA, int rowsB, int columnsB){     //Multipling function for every demension
  int temp, **result;
  result = new int * [rowsA];

  if(columnsA == rowsB){
    for(int i = 0; i < rowsA; i++){
      result[i] = new int [columnsB];
    }

    for(int i = 0; i < rowsA; i++){
      for(int j = 0; j < columnsB; j++){
        temp = 0;
        for(int p = 0; p < columnsA; p++){
          temp += MA[i][p] * MB[p][j];
          result[i][j] = temp;
        }
      }
    }
  } else {
    cout << "Matrixes have not correct demensions, so we can't make it" << endl;
    exit(0);
  }
  return result;
}

void fillMatrix(int **matrix, int rows, int columns, int *values){  //Fill matrix with tabel of values
  int k = 0;
  for(int i = 0; i < rows; i++ ){    //Fill matrixes
    for(int j = 0; j < columns; j ++ ){
      matrix[i][j] = values[k];
      k++;
    }
  }
}
