Program do obliczania liczby PI algorytmem Monte Carlo.
Funkcja timedif służy do obliczania czasu. Funkcja srand inicjalizuje
 losowanie liczb. Pierwsza pętla losuje punkty a druga sprawdza warunek
 x^2+y^2 <= 1. W wersji równoległej Bcast rozsyła do wszyskich x i y a Reduce 
sumuje wszyskie zliczone punkty do zmiennej all.
 
