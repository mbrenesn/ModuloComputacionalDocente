#include <iostream>
#include <vector>
#include <cmath>

// Solves the 2D diffusion equation for a temperature field as a function of time
// Procedural paradigm

int main() {
  // Lattice size
  const int Nx = 100;
  const int Ny = 100;

  // Physical parameters
  const double D = 1.0;
  const double h = 1.0;
  const double dt = 0.1;

  // Stability parameter
  const double alpha = D * dt / (h * h);

  // Number of timesteps
  const int steps = 3000;

  // Output every k steps
  const int output_every = 5;

  // Temperature fields
  std::vector<double> T(Nx * Ny, 0.0);
  std::vector<double> T_new(Nx * Ny, 0.0);

  // Initial state: localized hot spot
  double cx = Nx / 2.0;
  double cy = Ny / 2.0;
  double sigma = 10.0;
  for(int i = 0; i < Nx; ++i){
    for(int j = 0; j < Ny; ++j){
      double dx = i - cx;
      double dy = j - cy;
      
      T[i * Ny + j] = std::exp(-(dx * dx + dy * dy) / (2.0 * sigma * sigma));
    }
  }

  // Time evolution
  for(int n = 0; n < steps; ++n){
    // Lattice update
    for(int i = 1; i < Nx - 1; ++i){
      for(int j = 1; j < Ny - 1; ++j){

        T_new[i * Ny + j] = T[i * Ny + j] + alpha*(
                                       T[(i + 1) * Ny + j]
                                       + T[(i - 1) * Ny + j]
                                       + T[i * Ny + j + 1]
                                       + T[i * Ny + j - 1]
                                       - 4.0 * T[i * Ny + j]);
      }
    }

    // Swap arrays
    std::swap(T, T_new);

    // Output snapshots
    if(n % output_every == 0){
      for(int i = 0; i < Nx; ++i){
        for(int j = 0; j < Ny; ++j){
          std::cout << i << " " << j << " " << T[i * Ny + j] << std::endl;
        }
        std::cout << std::endl;
      }
      std::cout << "\n\n";
    }
  }

  return 0;
}
