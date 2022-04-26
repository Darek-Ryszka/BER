//  Dariusz Ryszka
//    Grupa D3    

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <time.h>
#include <stdlib.h>

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

int main(int argc, char** argv)
{
    if (argc != 3)
        {
            initLog(" Blad ! Zla liczba argumentow ! (" + to_string(argc - 1) + ") - required: 2.");

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

    file_A.close();
    file_B.close();

    initLog(" Zamkniecie obu plikow ");

    return 0;
}