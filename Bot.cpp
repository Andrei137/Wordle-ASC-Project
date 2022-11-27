#include <cmath>
#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include "Utilities.h"

#define UPPER_LIMIT 244

std::ifstream read;
std::ofstream write;

int sum, poz;
char color[5], currColor[5];
double p, max;

Alphabet alph, secondGuess;
str givenWord, currWord, dummy, matrix[UPPER_LIMIT], matrixSecondGuess[UPPER_LIMIT], secondWords[UPPER_LIMIT];

class I_O
{
    public :
        void output(std::ofstream &write, str file)
        {
            write.open(file);
            if (file == "Temp/currWord.txt")
                write << currWord;
            elif (file == "Temp/auxAlphabet.txt")
                write << alph;
            elif (file == "Temp/secondGuessArray.txt")
                for (int i = 0; i < UPPER_LIMIT; ++i)
                    write << secondWords[i] << ' ';
            write.close();
        }
        void input(std::ifstream &read, str file)
        {
            read.open(file);
            if (file == "Temp/auxAlphabet.txt")
                read >> alph;
            elif (file == "Temp/firstTwoGuesses.txt")
                read >> currWord >> dummy;
            elif (file == "Temp/wordColor.txt")
            {
                read >> currWord;
                for (int i = 0; i < 5; ++i)
                    read >> color[i];
            }
            elif (file == "Temp/secondGuessArray.txt")
                for (int i = 0; i < UPPER_LIMIT; ++i)
                    read >> secondWords[i];
            read.close();
        }
};

int convert3To10(int number)
{
    int convertedNumber = 0, power = 1;
    do
    {
        convertedNumber += number % 10 * power;
        power *= 3;
    }
    while (number /= 10);
    return convertedNumber;
}

int turnCharIntoInt()
{
    int number = 0;
    for (int i = 0; i < 5; ++i)
        number = number * 10 + color[i] - '0';
    return number;
}

void createMatrix(str currWord, Alphabet alph, str matrix[])
{
    for (int i = 0; i < alph.len; ++i)
    {
        getColor(alph.word[i], currWord, color);
        matrix[convert3To10(turnCharIntoInt())].append(alph.word[i]);
    }
}


bool isEqual(char currColor[])
{
    for (int i = 0; i < 5; ++i)
        if (color[i] != currColor[i])
            return false;
    return true;
}

bool onlyOneLetterLeft()
{
    bool found = false;
    for (int i = 0; i < 5; ++i)
        if (color[i] != '2')
        {
            if (!found)
                found = true;
            else
                return false;
        }
    return true;
}

Alphabet createNewAlphabet()
{
    Alphabet newInput;
    newInput.len = 0;
    char currColor[5];
    for (int i = 0; i < alph.len; ++i)
    {
        getColor(alph.word[i], currWord, currColor);
        if (isEqual(currColor))
            newInput.word[newInput.len++] = alph.word[i];
    }
    return newInput;
}

str findBestEntropy(Alphabet alph, str matrix[])
{
    max = 0;
    double E[alph.len] = {0};
    for (int i = 0; i < alph.len; ++i)
    {      
        for (int j = 0; j < UPPER_LIMIT; ++j)
            matrix[j].clear();
        createMatrix(alph.word[i], alph, matrix);
        for (int j = 0; j < UPPER_LIMIT; ++j)
        {
            p = 1.0 * (matrix[j].length() / 5) / alph.len;
            if (p == 0)
                continue;
            elif (E[i] == 0)
                E[i] = -(p * log2(p));
            else
                E[i] -= p * log2(p);
        }
        if (E[i] > max)
        {
            max = E[i];
            poz = i;
        }
        elif (E[i] == max)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            int n = mt() % alph.len;
            if (n % 2 == 1)
                poz = i;
        }
    }
    return alph.word[poz];
}

int main()
{
    I_O().input(read, "Temp/firstTwoGuesses.txt");
    I_O().input(read, "Temp/auxAlphabet.txt");

    if (currWord == "-")
    {
        currWord = findBestEntropy(alph, matrix);

        for (int j = 0; j < UPPER_LIMIT; ++j)
            matrix[j].clear();

        createMatrix(currWord, alph, matrix);

        for (int i = 0; i < UPPER_LIMIT; ++i)
        {
            for (int j = 0; j < matrix[i].length(); j += 5)
            {
                secondGuess.word[j / 5] = "";
                for (int k = 0; k < 5; ++k)
                    secondGuess.word[j / 5] += matrix[i][j + k];
            }
            secondGuess.len = matrix[i].length() / 5;
            if (secondGuess.len)
                secondWords[i] = findBestEntropy(secondGuess, matrixSecondGuess);
            else
                secondWords[i] = "-";
        }

        I_O().output(write, "Temp/currWord.txt");
        I_O().output(write, "Temp/secondGuessArray.txt");

    }
    else
    {
        I_O().input(read, "Temp/wordColor.txt");

        alph = createNewAlphabet();

        I_O().output(write, "Temp/auxAlphabet.txt");

        if (dummy == "-")
        {    
            I_O().input(read, "Temp/secondGuessArray.txt");

            currWord = secondWords[convert3To10(turnCharIntoInt())];
        }
        else
            currWord = findBestEntropy(alph, matrix);

        I_O().output(write, "Temp/currWord.txt");
    }
    return 0;
}