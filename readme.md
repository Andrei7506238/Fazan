# FazanGameRO
Implementarea unui cheat pentru jocul [FAZAN](https://ro.wikipedia.org/wiki/Fazan_(joc)).
Programul va juca agresiv, incercand sa minimizeze numarul minim de cuvinte pe care urmatorul adversar le poate propune.

## Obiective ale programului in forma finala :
- Posibilitatea de a incarca lista de cuvinte in functie de regulile alese pentru joc (fara/cu forme flexionare, cu/fara diacritice), precum si o lista custom de cuvinte.
- Posibilitatea de a seta regulile jocului dupa preferinte (se accepta / nu se accepta acelasi cuvant de mai multe ori - caz in care va fi posibila memorarea cuvintelor spuse de ceilalti jucatori)


## Extra :
- Care este durata maxima a unui joc de fazan in care niciun jucator nu este inchis ? (nu sunt acceptate cuvinte duplicate)
- Lista de cuvinte care poate fi folosita pentru inchideri, sortata dupa prefix. Lista de prefixe pentru care nu exista cuvinte pentru inchideri.


## Informatii privind lista de cuvinte :
Listele actuale sunt versiuni modificate ale Listei Oficială de Cuvinte admise la Scrabble (LOC) disponibila pe [dexonline](https://dexonline.ro/scrabble) :
- Diacriticile romanesti sunt inlocuite in felul urmator : ("ă" - "~") ("î" - "^") ("â" - "#") ("ș" - ".") ("ț" - ",")
- Orice alte diacritice provenite din alte limbi trebuie inlocuite cu forma corespunzatoare din alfabetul englez (cuvinte precum Führer)


PROIECT WORK IN PROGRESS
