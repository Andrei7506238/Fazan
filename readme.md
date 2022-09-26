# FazanGameRO
Implementarea unui cheat pentru jocul [FAZAN](https://ro.wikipedia.org/wiki/Fazan_(joc)).
Programul va juca agresiv, greedy, incercand sa minimizeze numarul minim de cuvinte pe care urmatorul adversar le poate propune.

## Obiective principale:
- [x] Posibilitatea de a incarca lista de cuvinte in functie de regulile alese pentru joc (forma de baza (fara diacritice) / forma flexionara (cu diacritice)) precum si posibilitatea de a incarca o lista custom de cuvinte (nume fisier : custom.txt)
- [x] Posibilitatea de a seta regulile jocului dupa preferinte (se accepta / nu se accepta acelasi cuvant de mai multe ori - caz in care va fi posibila memorarea cuvintelor spuse de ceilalti jucatori, precum si cuvantului propriu din prima runda).
- [x] Programul va semnala cuvintele care nu exista in lista de cuvinte sau care au fost folosite deja (in functie de regulile jocului)


## Extra:
- [ ] Care este durata maxima a unui joc de fazan in care niciun jucator nu este inchis ? (nu sunt acceptate cuvinte duplicate) - NEIMPLEMENTAT INCA
- [x] Lista de cuvinte care poate fi folosita pentru inchideri, sortata dupa prefix [Forma Baza](rezultatCercetare/ListaCuvinteFolositeLaBlocareBaza.md) [Forma Flexionara](rezultatCercetare/ListaCuvinteFolositeLaBlocareFlex.md)

## Instructiuni meniu:
1. Se alege lista de cuvinte dorita introducand una din tastele 1,2 sau 3, urmat de enter. Pentru informatii privind lista custom de cuvinte mergi mai jos.
2. Se alege modul de joc (sau una din optiunile extra) introducand numarul corespunzator optiunii, apoi apasand enter.

### Instructiuni joc cu posibilitate de repetare cuvinte:
Se introduce cuvantul adversarului precedent urmat de enter. Programul va afisa o sugestie care sa blocheze sau sa puna in dificultate maxima jucatorul urmator, ori va afisa FAZAN daca nu exista cuvinte disponibile. Nu pot fi eliminate cuvinte din lista. Programul va atentiona atunci cand un cuvant introdus nu este valid. Jocul se opreste la introducerea caracterului '0'.

### Instructiuni joc fara repetare cuvinte:
Similar cu modul de joc anterior.
Cuvintele adversarilor (exceptand cel al adversarului precedent) trebuie introduse cu caracterul "-" in fata. Cuvantul adversarului imediat precedent trebuie introdus normal.
Programul nu va va ajuta in prima runda (in care inchiderile sunt interzise). Introduceti TOATE cuvintele din prima runda a jocului pentru a fi sterse din lista.

## Informatii privind lista de cuvinte:
Listele actuale sunt versiuni modificate ale Listei Oficială de Cuvinte admise la Scrabble (LOC) disponibila pe [dexonline](https://dexonline.ro/scrabble):
- Diacriticile romanesti din lista flexionara sunt inlocuite in felul urmator : ("ă" - "~") ("î" - "^") ("â" - "#") ("ș" - ".") ("ț" - ",")
- Orice alte diacritice provenite din alte limbi trebuie inlocuite cu forma corespunzatoare din alfabetul englez (cuvinte precum Führer) - lista flexionara
- Pentru a folosi o lista custom de cuvinte creati fisierul custom.txt in dosarul cu fisierul executabil; Un singur cuvant pe rand; Regulile privind diacriticele sunt cele de mai sus.

## PROIECT WORK IN PROGRESS
