set xlabel "X" # Название оси X
set ylabel "Y" # Название оси Y
set zlabel "Z" # Название оси Z
set title "Аттрактор типа двойной завиток" # Заголовок графика

splot 'data3d.txt' using 1:2:3 with lines title "Chua's attractor"

pause -1