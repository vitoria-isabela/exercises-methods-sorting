#include "siga.h"

// Salva no arquivo binário dataset.bin uma lista de estudantes ordenados por Nome e Código de curso, isso através do método de ordenação bubblesort.
int main(int argc, char *argv[])
{
    Siga siga("dataset.bin");
    siga.SalvarListaOrdenadaEstudantes(argv[1]);
}