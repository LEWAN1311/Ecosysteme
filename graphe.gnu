set terminal png size 1280,941 crop
set output 'testecosys.png'

set datafile separator " "

set xlabel "nombre de générations"
set ylabel "nombre d'individus"
set title "Projet-ecosys"

plot "Evol_Pop.txt" using 1:2 with lines title "proies","Evol_Pop.txt" using 1:3 with lines title "prédateurs" lt 2