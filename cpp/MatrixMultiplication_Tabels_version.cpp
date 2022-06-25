#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int result[9];

void matrxMultipling3x3(int [], int []);
void writeValue(int [], int, int);
int *matrxMultipling(int [], int [], int, int, int, int);

int main( ){
  int A[9], B[9], *C, k = 1;    //Matrixes 3x3


  for(int i = 0; i < 3; i++ ){    //Fill matrixes
    for(int j = 0; j < 3; j ++ ){
      A[i * 3 + j] = k;
      B[i * 3 + j] = k;
      k++;
    }
  }

  //matrxMultipling3x3(A, B);
  C = matrxMultipling(A, B , 3, 3, 3, 3);
  writeValue(A, 3, 3);
  writeValue(B, 3, 3);
  //writeValue(result, 3, 3);
  writeValue(C, 3, 3);


  return 0;
}

void matrxMultipling3x3(int MA[], int MB[]){     //Multipling function for 3 X 3 Matrixes
  int temp;

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      temp = 0;
      for(int p = 0; p < 3; p++){
        temp += MA[i * 3 + p] * MB[p * 3 + j];
        result[i * 3 + j] = temp;
      }
    }
  }
}

void writeValue(int matrix[], int rows, int columns) {     //Write matrix
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      cout << setw(6) << matrix[i * rows + j];
    }
    cout << endl;
  }
}

int *matrxMultipling(int MA[], int MB[], int rowsA, int columnsA, int rowsB, int columnsB){     //Multipling function for every demension
  int temp, *result;

  if(columnsA == rowsB){
    result = new int [columnsA * rowsB];

    for(int i = 0; i < rowsA; i++){
      for(int j = 0; j < columnsB; j++){
        temp = 0;
        for(int p = 0; p < columnsA; p++){
          temp += MA[i * rowsA + p] * MB[p * rowsB + j];
          result[i * rowsA + j] = temp;
        }
      }
    }
  } else {
    cout << "Matrixes have not correct demensions, so we can't make it" << endl;
    exit(0);
  }
  return result;
}
