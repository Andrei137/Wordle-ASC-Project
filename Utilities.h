#ifndef UTILITIES_H
#define UTILITIES_H


#include <fstream>
#include <string>

#define str std::string
#define elif else if


class Alphabet
{
    public :
        int len;
        str word[11500];

    private :
        friend std::ifstream & operator >> (std::ifstream &in, Alphabet &input)
        {
            input.len = 0;
            while (in >> input.word[input.len])
                ++input.len;
            return in;
        }

        friend std::ofstream & operator << (std::ofstream &out, Alphabet input)
        {
            for (int i = 0; i < input.len; ++i)
                out << input.word[i] << '\n';
            return out;
        }
};


void getColor(str givenWord, str currWord, char pattern[])
{
    for (int i = 0; i < 5; ++i)
        pattern[i] = '0';
    for (int i = 0; i < 5; ++i)
        if (currWord[i] == givenWord[i])
            pattern[i] = '2';
    for (int i = 0; i < 5; ++i)
    {
        int j = givenWord.find(currWord[i]);
        if (j != std::string::npos && j != i && pattern[i] == '0')
            pattern[i] = '1';
    }
}


#endif