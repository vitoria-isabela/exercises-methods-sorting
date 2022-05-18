#ifndef SIGA_H__
#define SIGA_H__

#include <iostream>
#include <fstream>
#include <string>

#include "config.h"
#include "estudante.h"

using namespace std;

typedef enum {BUBBLESORT, INSERTIONSORT, SELECTIONSORT } sorting_method;

class Siga
{
    public:
        Siga(string arquivo_estudante);
        void CadastraEstudante(Estudante est);
        int  PesquisaPorMatricula(int matricula);
        void ImprimeEstudantePorMatricula(int matricula);
        void AlteraCadastroEstudante(Estudante est);
        void SalvaListaEstudanteEmTexto(string arquivo_txt);
        int  ObterNumeroEstudantesArmazenados();

        // TODO: Ordenação de Dados
        void ImportCSVData(string arquivo_csv);
        void SalvarListaOrdendaEstudantesPorNome(string arquivo_txt, sorting_method method);
        void SalvarListaOrdenadaEstudantes(string arquivo_txt);
        ~Siga();

    private:
        Estudante* build_vector_from_file();
        // atributos
        string   arquivo_nome;
        fstream  file_stream;
        int      n_estudantes;
};

#endif /* SIGA_H__ */