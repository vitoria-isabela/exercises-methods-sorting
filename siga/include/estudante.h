#ifndef ESTUDANTE_H__
#define ESTUDANTE_H__

#include <fstream>

using namespace std;

#define STR_MAX_SIZE 64
#define ESTUDANTE_SIZE (sizeof(char)*STR_MAX_SIZE + 3*sizeof(int) + sizeof(float))

class Estudante
{
    public:
        Estudante();
        Estudante(const char* nome, int matricula, int ano_ingresso, int curso, float ira);

        int         ObterMatricula();
        int         ObterAnoIngresso();
        int         ObterCurso();
        const char* ObterNome();
        float       ObterIRA();

        void TrocarMatricula(int matricula);
        void TrocarNome(const char* nome);
        void TrocarIRA(int ira);
        void TrocarAnoIngresso(int ano_ingresso);
        void TrocarCurso(int curso);

        void Imprimir();

        void LerDoArquivoBinario(fstream &file);
        void EscreverNoArquivoBinario(fstream &file);

    private:
        char   _nome[STR_MAX_SIZE];
        int    _matricula;
        int    _ano_ingresso;
        int    _codigo_curso;
        float  _ira;
};

#endif /* ESTUDANTE_H__ */