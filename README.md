# Proiect Wordle ASC

<img align="right" width="200" height="200" src="https://i.imgur.com/AWDURXn.jpeg">

---

- Numele echipei : Hello Wordle
- Grupa : 152
- Membrii : Lida Rani-Leon, Neculae Andrei-Fabian, Popa Bianca-Daniela, Visan-Draghicescu Emanuel-Sebastian
- Medie : 4.33229

---

## Entropia
- La fiecare guess, botul alege cuvantul ce imparte cat mai egal baza de date in functie de pattern-uri, adica alege cuvantul cu cea mai mare entropie.
- Apoi, Wordle primeste cuvantul gasit ca input, generandu-i pattern-ul.
- La noul apel, botul pastreaza din baza de date doar cuvintele care au acelasi pattern cu cel dat de Wordle fata de cuvantul curent.
- Acesti pasi se repeta pana cand, in final, botul va ghici cuvantul dat, care se va afla mereu in noua baza de date.

---

## Link procese
- Cele doua procese comunica intre ele prin fisiere txt, iar cel principal (Wordle) apeleaza botul la fiecare guess prin functia system() din windows.h
- Comunicarea este lenta, astfel ca aflarea guess-urilor pentru fiecare cuvant dureaza 4-5 secunde.
- Fisierele text neimportante sunt generate in folderul Temp de catre Wordle, si apoi sterse la finalul executiei.


---

## Extra
### Interfata grafica
- Interfata grafica este facuta in terminal cu ajutorul header-ului Color.h
- Aceasta se reseteaza dupa fiecare cuvant gasit, avand o pauza scurta intre cuvinte generata de functia Sleep pentru lizibilitate
