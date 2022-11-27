#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include "Utilities.h"
#include "Color.h"

std::ifstream read;
std::ofstream write;
std::ofstream writeSolution("Solutions.txt");

Alphabet alph;
int sum, currIndex, step, i, count;
str givenWord , currWord = "-", dummy;
char color[5];

class I_O
{
    public :
        void output(std::ofstream &write, str file)
        {
            write.open(file);
            if (file == "Temp/firstTwoGuesses.txt")
                write << currWord << ' ' << dummy;
            elif (file == "Temp/wordColor.txt")
            {
                write << currWord << ' ';
                for (int i = 0; i < 5; ++i)
                    write << color[i] << ' ';
            }
            elif (file == "Temp/auxAlphabet.txt" || file == "Temp/Alphabet.txt")
                write << alph;
            elif (file == "Temp/currWord.txt")
                write << currWord;
            write.close();
        }

        void input(std::ifstream &read, str file)
        {
            read.open(file);
            if (file == "Alphabet.txt")
                read >> alph;
            elif (file == "Temp/currWord.txt")
                read >> currWord;
            read.close();
        }
};

class Wordle
{
    public :
        char ch[5], color[5];
        bool usedColor;

        void defaultValue()
        {
            for (int i = 0; i < 5; ++i)
            {
                ch[i] = ' ';
                color[i] = '0';
            }
            usedColor = false;
        }

        void output(int i)
        {
            if (color[i] == '2')
                std::cout << dye::on_green(ch[i]).invert();
            elif (color[i] == '1')
                std::cout << dye::on_yellow(ch[i]).invert();
            else
                std::cout << ch[i];
        }

} currLane[11500];

class Read
{
    private :
        char input[5];

        void read(int index, bool color)
        {
            if (!index)
                std::cout << "\nCurrently at word " << i + 1 << "\n\n _____ _____ _____ _____ _____ \n";
            std::cout << "|     |     |     |     |     |\n|  " ;
            for (int i = 0; i < 5; ++i)
            {
                if (color)
                    currLane[index].output(i);
                else
                    std::cout << currLane[index].ch[i];
                if (i != 4)
                    std::cout << "  |  ";
            }
            std::cout << "  |\n|_____|_____|_____|_____|_____|\n";
        }

    public :
        void clearScreen()
        {
            HANDLE hOut;
            COORD Position;
            hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            Position.X = 0;
            Position.Y = 0;
            SetConsoleCursorPosition(hOut, Position);
        }

        void noColor(int index)
        {
            read(index, 0);
        }

        void color(int index)
        {
            for (int i = 0; i < 5 && !currLane[index].usedColor; ++i)
                currLane[index].usedColor = (currLane[index].color[i] != '0');
            read(index, 1);
        }

} readInput;

class showTable
{   
    public :
        void noColor()
        {
            for (int i = 0; i <= currIndex; ++i)
                if (currLane[i].usedColor)
                    readInput.color(i);
                else
                    readInput.noColor(i);
        }

        void color()
        {
            for (int i = 0; i <= currIndex; ++i)
                readInput.color(i);
        }

} table;

bool found(char color[])
{
    for (int i = 0; i < 5; ++i)
        if (color[i] != '2')
            return false;
    return true;
}

void showCurrLane(bool finished)
{
    getColor(givenWord, currWord, currLane[currIndex].color);
    for (int j = 0; j < 5; ++j)
    {
        Sleep(10);
        readInput.clearScreen();
        currLane[currIndex].ch[j] = currWord[j];
        currLane[currIndex].color[j] = color[j];
        if (j != 4)
            table.noColor();
        else
        {
            if (!finished)
                currLane[++currIndex].defaultValue();
            Sleep(50);
            table.color();
        }
    }
}

int main()
{
    system("mkdir Temp");
    system("cls");

    currLane[0].defaultValue();

    table.noColor();

    I_O().input(read, "Alphabet.txt");
    I_O().output(write, "Temp/auxAlphabet.txt");
    I_O().output(write, "Temp/firstTwoGuesses.txt");

    system("g++ -std=gnu++2a Bot.cpp -o Bot.exe -O2");
    system("Bot");

    // for (i = 0; i < alph.len; ++i)
    for (i = 0; i < 10; ++i)
    {
        step = 1;
        currIndex = 0;
        dummy = "-";
        for (int j = 0; j < currIndex; ++j)
            currLane[j].defaultValue();

        I_O().output(write, "Temp/auxAlphabet.txt");
        I_O().input(read, "Temp/currWord.txt");

        givenWord = alph.word[i];

        getColor(givenWord, currWord, color);
        showCurrLane(found(color));

        if (givenWord != currWord)
            writeSolution << givenWord << " : " << currWord << " -> ";
        else
            writeSolution << givenWord << " : " << currWord;

        I_O().output(write, "Temp/firstTwoGuesses.txt");
        I_O().output(write, "Temp/wordColor.txt");

        system("g++ -std=gnu++2a Bot.cpp -o Bot.exe -O2");
        system("Bot");

        dummy = currWord;

        I_O().input(read, "Temp/currWord.txt");

        getColor(givenWord, currWord, color);
        showCurrLane(found(color));

        ++step;

        if (givenWord != currWord)
            writeSolution << currWord << " -> ";
        else
            writeSolution << currWord << '\n';

        I_O().output(write, "Temp/firstTwoGuesses.txt");

        while (!found(color))
        {
            I_O().output(write, "Temp/currWord.txt");
            I_O().output(write, "Temp/wordColor.txt");

            system("g++ -std=gnu++2a Bot.cpp -o Bot.exe -O2");
            system("Bot");

            I_O().input(read, "Temp/currWord.txt");

            getColor(givenWord, currWord, color);
            showCurrLane(found(color));

            ++step;

            if (!found(color))
                writeSolution << currWord << " -> ";
            else
                writeSolution << currWord << '\n';
        }
        sum += step;
        currWord = dummy;
        I_O().output(write, "Temp/currWord.txt");
        Sleep(250);
        system("cls");
    }
    writeSolution << (float)sum / alph.len;
    writeSolution.close();

    system("rmdir /q /s Temp");
    system("del Bot.exe");
    return 0;
}