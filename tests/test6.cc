#include "siga.h"

// Salva uma lista ordenada pelo nome num arquivo .csv através do método selectionsort.
int main(int argc, char *argv[])
{
    Siga siga("dataset.bin");
    siga.SalvarListaOrdendaEstudantesPorNome("test6.csv", SELECTIONSORT);
}