#include <string>
#include <iostream>
using namespace std;

#include "siga.h"

// Realiza o import de um aqruivo .csv para o arquivo dataset.bin e também salva uma lista de estudantes, através do método bubblesort, em um arquivo .csv.
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    Siga siga("dataset.bin");
    siga.ImportCSVData(argv[1]);
    siga.SalvarListaOrdenadaEstudantes(argv[2]);

    return 0;
}