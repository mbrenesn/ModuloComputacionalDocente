#!/bin/bash -l
#SBATCH --partition=parallel
#SBATCH --time=1:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=64
#SBATCH --job-name="Heat"

export OMP_NUM_THREADS=64

./heat.x > time_64.dat
