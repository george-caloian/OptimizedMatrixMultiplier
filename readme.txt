Caloian George
332CC

Tema 2 ASC - Inmultirea Eficienta a Matricelor in C/C++

Implementare:

- citirea matricilor A si B se face tratand separat cazurile
TT NN TN NT (transpus/netranspus) avand grija la cele 2 dimensiuni
nr linii respectiv coloane.

- metoda la care am ajuns sa ma incadrez in timp a fost cea de impartire
a matricelor in blocuri de dimensiune fixa ( exact cea prezentata in cadrul
laboratorului 5 )
- am incercat si metode mai primitive plecand de la cele mai simple obtinand
timpi imensi (20+ minute)
-sunt convins ca exista si abordari mai rapide / mult mai rapide dar 
de data asta m-am multumit cu incadrarea in cele 180 de secunde
-dupa inmultirea celor 2 matrici se fac si ultimele calcule de adunare
iar rezultatul se scrie in fisier

-am rulat pe cluster pe 2 cozi ( aveam o lista cu 5 6 dar la unele nu aveam acces
sper totusi a fie suficient chiar daca timpii sunt aproape de limita) 
hp-sl (~170s) campus-haswell (~150s)
-intuitiv tind sa cred ca intocmai a fost dat acest barem de 180s la care s-a ajuns
in urma unor teste facute de echipa responsabila de tema.

-am realizat si un grafic reprezantand durata individuala de rulare pe cate o operatie
de inmultire (am rescris fisierul cfg pentru a putea genera prin generatorul oferit
in schelet matrici de dimensiuni diferite de la 250 la 4000)
