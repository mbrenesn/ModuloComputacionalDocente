set terminal gif animate delay 5
set output "heat.gif"

set pm3d map
set size square
set palette viridis

set xrange [0:99]
set yrange [0:99]

set cbrange [0:1]

do for [i=0:99] {

    splot "heat.dat" index i using 1:2:3 notitle

}
