
#include <string>
#include <iostream>
using namespace std;

#include "siga.h"

//argc : Um inteiro que contém a contagem de argumentos que seguem em argv . O parâmetro argc é sempre maior ou igual a 1.

// argv : Uma matriz de strings terminadas em nulo representando argumentos de linha de comando inseridos pelo usuário do programa. 
//Por convenção, argv[0]é o comando com o qual o programa é invocado. argv[1]é o primeiro argumento de linha de comando. 
//O último argumento da linha de comando é argv[argc - 1]e argv[argc]é sempre NULL.

// Testa a importação de 1000 arquivos (siga1000.csv) para o arquivo dataset.bin.
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    Siga siga("dataset.bin");
    siga.ImportCSVData(argv[1]);
    return 0;

}