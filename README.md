# Image Processing Program

Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA

Programul isi propune sa lucreze cu imagini in format NetPBM (PPM - format color
sau PGM - format alb-negru), care pot fi stocate in fisiere de tip text sau 
binar. Fisierele contin pe primele 3 linii caracteristicile imaginii (formatul; 
dimensiunile (latime, lungime); intensitatea maxima suportata de pixeli) in 
format text, urmate de pixelii stocati in imagine.

Pentru a putea executa comenzi asupra imaginii, am echivalat pixelii cu 
elementele unei matrici asupra carora am efectual diferite operatii. Astfel, 
sunt trimise comenzi { <TIP COMANDA> <PARAMETRII COMENZII> } si programul 
afiseaza de fiecare data efectul acestora.

## Functionalitatile programului sunt:

1. **LOAD**: Incarca in memorie o imagine noua (daca exita deja una, o 
   inlocuieste). Sunt preluate proprietatile imaginii si pastrate in memorie, 
   alaturi de matricea de pixeli intr-o variabila de tip structura. Imaginea 
   de tip alb-negru are, pentru fiecare coordonata, un singur canal (gray), in 
   timp ce pentru imaginea color, exista 3 canale (r, g, b). In cazul in care 
   fisierul nu exista, afiseaza un mesaj in acest sens si este pastrata 
   imaginea initiala in memorie.

2. **SELECT**: Selecteaza coordonatele partii asupra caruia urmeaza sa fie 
   facute modificarile. Valorile trebuie sa se incadreze in intervalul 
   dimensiunilor, altfel comanda nu poate fi efectuata. Functia trateaza si 
   cazul in care valorile punctelor selectate sunt egale, comanda devenind 
   inexecutabila. Este verificat si cazul in care valorile primului punct sunt 
   mai mari decat celui de-al doilea, interschimbandu-le valorile. In cadrul 
   selectiei vor fi luate in considerare liniile si coloanele pana la ultimul 
   punct (excluzand linia si coloana aferenta).

3. **SELECT ALL**: Reprezinta un caz particular pentru functia antecedenta. Se 
   face automat atunci cand o noua imagine este incarcata sau prin transmiterea 
   comenzii specifice.

4. **HISTOGRAM**: Afiseaza histograma imaginii, calculata in functie de 
   numarul maxim de stelute si bin-uri. Am folosit un vector de frecventa, 
   care sa stocheze numarul de aparitii ale unui pixel (in functie de 
   intensitate, de la 0 la 255). Am facut o medie pentru fiecare interval dat 
   de bin-uri, iar histograma se raporteaza la intervalul cu cele mai multe 
   aparitii (va fi reprezentat de numarul maxim de stelute) pentru a afisa 
   numarul de stelute corespunzator.

5. **EQUALIZE**: Aplica un filtru imaginii (alb-negru) pentru a mari contrastul,
   cu ajutorul unei formule aplicate pentru fiecare pixel. La baza se afla tot 
   vectorul de frecventa, care este utilizat de formula.

6. **ROTATE**: Roteste partea din imagine luata prin selectie. Functia se 
   aplica doar daca este selectata imaginea in totalitate, sau selectia este 
   patratica. Se executa pentru unghiuri drepte astfel: pentru unghiurile 
   pozitive, rotirea se face la dreapta; pentru cele negative, la stanga. Am 
   folosit algoritmul pentru transpunerea matricelor, pe care l-am modificat 
   pentru ca rotirea "standard" sa se faca la un unghi de 90 de grade, spre 
   dreapta. Pentru fiecare unghi am ales sa se faca un numar de rotatii care 
   sa aduca selectia in forma dorita.

7. **CROP**: Modifica imaginea, inlocuind-o cu selectia. Am folosit o noua 
   matrice care sa pastreze valorile, am redimensionat imaginea originala, iar 
   apoi am transferat valorile. Am schimbat si proprietatile imaginii (latimea, 
   lungimea).

8. **APPLY**: Poate aplica 4 filtre imaginii color (EDGE, SHARPEN, BLUR, 
   GAUSSIAN_BLUR). Pentru fiecare filtru exista un nucleu (matrice de dimensiune
   3x3) si se aplica astfel: se considera (pentru fiecare punct) o matrice 
   (centrata in punct, de tip 3x3). Noua valoare a pixelului va reprezenta suma 
   produselor dintre elementele cu aceleasi coordonate ale matricelor. Operatia 
   se va efectua pentru fiecare canal. Daca valorile obtinute sunt in afara 
   intervalului de intensitate, pixelul va lua valoarea minima, respectiv maxima.

9. **SAVE**: Salveaza imaginea obtinuta dupa modificarile aplicate intr-un 
   fisier de tip text/binar, in functie de comanda data. Nu va tine cont de 
   tipul fisierului din care a fost incarcata imaginea.

10. **EXIT**: Elibereaza din memorie resursele si incheie executia programului.
    Daca nu a fost incarcata nicio imagine in memorie, se va afisa un mesaj.
