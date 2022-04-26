//  Dariusz Ryszka
//    Grupa D3    

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <bitset>

using namespace std;

void initLog(string message)
{
    fstream logFile;

    logFile.open("log.txt", ios::app);

    time_t t = time(0);
    string dt = ctime(&t);

    logFile << endl << dt.substr(0, dt.length() - 1) << " : " << message;

    logFile.close();
}
vector<vector<char>> convertToVector(fstream &file) 
{
    initLog(" Rozpoczeto konwersje pliku ");

    vector<vector<char>> sequenceVector;
    while (!file.eof()) 
        {
            string byte;
            vector<char> byteVector;
            int charCode = file.get();
            int i = 0;

            if (charCode != -1) 
                {
                    byte = bitset<8>(charCode).to_string();

                    for (int bit = 0; bit < 8; bit++) 
                        {
                            byteVector.push_back(byte[bit]);
                        }
                    sequenceVector.push_back(byteVector);
                    i++;
                }      
        }
    initLog(" Konwersja zakonczona ");
    return sequenceVector;
}
int comparison(vector<vector<char>> seqA, vector<vector<char>> seqB) 
{
    initLog(" Rozpoczeto obliczanie roznicy ");

    vector<vector<char>> tmp;
    int diffs = 0;
    int size_A = seqA.size();
    int size_B = seqB.size();

    if (size_A > size_B) 
        {
            tmp = seqA;
            seqA = seqB;
            seqB = tmp;
        }
    for (int i = 0; i < size_A; i++) 
        {
            for (int j = 0; j < 8; j++) 
            {
                if (seqA[i][j] != seqB[i][j]) diffs++;
            }
        }
    diffs += (size_B - size_A) * 8;
    initLog(" Obliczanie zakonczone ");

    return diffs;
}
int main(int argc, char** argv)
{
    initLog(" Start programu ");

    if (argc != 3)
        {
            initLog(" Blad ! Zla liczba argumentow ! (" + to_string(argc - 1) + ") - zalecane: 2.");

            return 0;
        }
    fstream file_A, file_B;

    file_A.open(argv[1]);
    file_B.open(argv[2]);

    if (!file_A.is_open() || !file_B.is_open())
        {
            initLog(" Nie mozna otworzyc jednego z plikow ! ");

            return 0;
        }
    else
        {
            initLog((string)" Udalo sie pomyslnie otworzyc pliki :) 1) " + argv[1] + " 2) " + argv[2]);
        }

    vector<vector<char>> byteSeqA = convertToVector(file_A);
    vector<vector<char>> byteSeqB = convertToVector(file_B);

    int diff = comparison(byteSeqA, byteSeqB);

    file_A.close();
    initLog((string)" Plik " + argv[1] + " zamkniety ");
    file_B.close();
    initLog((string)" Plik " + argv[2] + " zamkniety ");

    initLog(" Stop programu ");

    return 0;
}