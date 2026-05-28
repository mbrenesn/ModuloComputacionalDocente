#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Solves the 2D diffusion equation for a temperature field as a function of time
// Procedural paradigm
// Parallel version with shared memory paradigm

double seconds()
{
  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
  
  return sec;
}

int main() {
  // Lattice size
  const int Nx = 200;
  const int Ny = 200;

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
  double time_1 = seconds();
  #pragma omp parallel
  {
    for(int n = 0; n < steps; ++n){
      // Lattice update
 
      #pragma omp for
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
      // Very careful here! What's going on?
      #pragma omp single
      std::swap(T, T_new);

      // Output eliminated to evaluate performance
      // Careful! Outputs typically add serial time unless clever tricks are implemented
    }
  }
  double time_2 = seconds();

  std::cout << "Time to solution: " << time_2 - time_1 << std::endl;

  return 0;
}
