Funkcja timedif służy do oblicznaia czasu. Dimmension to wymiar macierzy.
Mnożymy wymiary żeby uzyskać liczbe elementow. Dzielimy dla każdego procesu
 równą ilość el. później losujemy liczby dla wektora i macierzy. Scatter
dzieli macierz na kawalki, każdemu procesowi dajac tyle samo. Następnie 
Bcast rozsyła vector do wszystkich i Reduce dodaje wszyskie cześci vectora 
a Gather dodaje czesci macierzy.

