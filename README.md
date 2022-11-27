# Proiect Wordle ASC

<img align="right" width="150" height="150" src="https://i.imgur.com/AWDURXn.jpeg">

---

- Numele echipei : Hello Wordle
- Grupa : 152
- Membrii : Lida Rani-Leon, Neculae Andrei-Fabian, Popa Bianca-Daniela, Visan-Draghicescu Emanuel-Sebastian
- Medie : Ponderata

---

## Entropia
- La fiecare guess, botul alege cuvantul ce imparte cat mai egal baza de date in functie de pattern-uri.
- Apoi, cuvantul gasit este dat ca guess in Wordle, generandu-se astfel pattern-ul lui.
- La noul apel, botul pastreaza din baza de date doar cuvintele care au acelasi pattern cu cel dat de Wordle fata de cuvantul curent.
- Acesti pasi se apeleaza recursiv, urmand ca in final botul sa ghiceasca cuvantul dat, care va afla mereu in noua baza de date.

---

## Link-ul dintre procese
- Cele doua procese comunica intre ele prin fisiere txt, iar cel principal (Wordle) apeleaza botul la fiecare guess prin functia system() din windows.h
- Comunicarea este lenta, astfel ca aflarea guess-urilor pentru fiecare cuvant dureaza 4-5 secunde.
- Fisierele text neimportante sunt generate in folderul Temp de catre Wordle, si apoi sterse la finalul executiei.


---

## Interfata grafica
- Interfata grafica este facuta in terminal cu ajutorul header-ului Color.h
- Aceasta se reseteaza dupa fiecare cuvant gasit, avand o pauza scurta intre cuvinte generata de functia Sleep pentru lizibilitate
