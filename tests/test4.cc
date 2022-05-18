#include "siga.h"

// Salva em um arquivo "test4.csv" uma lista ordenada por nome de estudantes, através do método selectionsort.
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <output_file>" << endl;
        return 1;
    }
    Siga siga("dataset.bin");
    siga.SalvarListaOrdendaEstudantesPorNome(argv[1], SELECTIONSORT);
    return 0;
}