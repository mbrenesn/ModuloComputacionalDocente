#include <iostream>
#include <vector>

void print_mat(std::vector<double> &mat, int rows, int cols){

  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      std::cout << mat[i * cols + j] << " ";
    }
    std::cout << std::endl;
  }
}

int main(){

  int l = 500;
  int n = 500;
  int m = 500;

  std::vector<double> A(l * n, 0.0);
  std::vector<double> B(n * m, 0.0);
  std::vector<double> C(l * m, 0.0);

  // Inicialización de A
  for(int i = 0; i < l; ++i){
    for(int j = 0; j < n; ++j){
      A[i * n + j] = i;
    }
  }

  //print_mat(A, l, n);
  //std::cout << std::endl;

  // Inicialización de B
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      B[i * m + j] = j;
    }
  }
  
  //print_mat(B, n, m);
  //std::cout << std::endl;

  // Multiplicación de matrices
  for(int i = 0; i < l; ++i){
    for(int j = 0; j < m; ++j){
      for(int k = 0; k < n; ++k){
        C[i * m + j] += A[i * n + k] * B[k * m + j];
      }
    }
  }
  
  //print_mat(C, l, m);

  return 0;
}
