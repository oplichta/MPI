Funkcja timedif służy do oblicznaia czasu. Dimmension to wymiar macierzy.
Mnożymy wymiary żeby uzyskać liczbe elementow. Dzielimy dla każdego procesu
 równą ilość el. później losujemy liczby dla wektora i macierzy. Scatter
dzieli macierz na kawalki, każdemu procesowi dajac tyle samo. Następnie 
Bcast rozsyła vector do wszystkich i Reduce dodaje wszyskie cześci vectora 
a Gather dodaje czesci macierzy.
Czas dla macierzy 10000 x 10000 sekwencyjnie 2.06268 sek
Czas dla macierzy 10000 x 10000 na 2 wątkach 3.08256 sek
Czas dla macierzy 10000 x 10000 na 4 wątkach 2.64310 sek
Czas dla macierzy 10000 x 10000 na 8 wątkach 2.7890 sek
Czas dla macierzy 10000 x 10000 na 16 wątkach 5.67925 sek
Czas dla macierzy 10000 x 10000 na 32 wątkach 7.28182 sek


