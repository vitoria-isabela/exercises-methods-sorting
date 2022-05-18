#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#include "siga.h"
#include "sort.h"


Siga::Siga(string arquivo_dados_estudante)
{
    this->arquivo_nome = arquivo_dados_estudante;
    this->file_stream.open(this->arquivo_nome, ios::in | ios::out | ios::binary ); // Binary: garante que os dados sejam lidos ou gravados sem traduzir novos caracteres de linha para \r e \n.

    if(this->file_stream.is_open())
    {
        cout << "SIGA: Inicializado com sucesso" << endl;
    }
    else
    {
        cout << "SIGA: Erro ao abrir arquivo" << endl;
        return; 
    }

    cout << this->ObterNumeroEstudantesArmazenados() << " registros de estudantes" << endl;
}


int  Siga::PesquisaPorMatricula(int matricula)
{
    //Posicionando o cursor no inicio do arquivo
    this->file_stream.seekg(0, this->file_stream.beg);

    //Declarando Estudante
    Estudante est = Estudante();

    for ( int i = 0; i < this->n_estudantes; i++)
    {
        //Ler do arquivo binário
        est.LerDoArquivoBinario(this->file_stream);
        //Verifica se a matricula é a mesma
        if ( est.ObterMatricula() == matricula )
            return i;
    }

    //Retornando o cursor pro fim de leitura
    this->file_stream.seekg(0, this->file_stream.end);

    //Caso não encontrar a matrícula retorna -1
    return -1;
}
        
void Siga::CadastraEstudante(Estudante est)
{
    //Verifica se est já está cadastrado
    if( PesquisaPorMatricula(est.ObterMatricula() ) != -1 )
        return;

    //Colocando o Cursor no Fim do arquivo binario
    this->file_stream.seekp(0, this->file_stream.end);

    //Adicionando o aluno
    est.EscreverNoArquivoBinario(this->file_stream);

    //Incrementando o número de estudantes
    this->n_estudantes = this->n_estudantes + 1;
}
        
void Siga::ImprimeEstudantePorMatricula(int matricula)
{
    int index = PesquisaPorMatricula(matricula);
    if( index == -1)
        cout << "Estudante não cadastrado" << endl;
    else 
    {
        this->file_stream.seekg((index * ESTUDANTE_SIZE), this->file_stream.beg ); // posição em que o launo se encontra no arquivo binario
        Estudante est = Estudante();

        est.LerDoArquivoBinario(this->file_stream);

        est.Imprimir();
    }
}
        
void Siga::SalvaListaEstudanteEmTexto(string arquivo_txt)
{
    //Cursor no inicio do arquivo binário
    this->file_stream.seekg(0, this->file_stream.beg);

    //Verifica se o arquivo está vazio
    if(this->n_estudantes == 0)
        return;

    fstream arq;
    //Abre o arquivo
    arq.open(arquivo_txt, ios::in | ios::out | ios::trunc); // trunc: (abreviação de truncate ) significa que quando o arquivo é aberto, o conteúdo antigo é removido imediatamente.
    if(!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }

    //Cria um vetor de alunos
    Estudante estudante;
        
    //Salva a primeira linha
    arq << "Matricula;Nome;Ano de Ingresso;Curso;IRA" << endl;

    //Le o vetor de Estudantes
    for( int i = 0; i < this->n_estudantes; i++)
    {
        estudante.LerDoArquivoBinario(this->file_stream);
        arq << estudante.ObterMatricula() << ";";
        arq << estudante.ObterNome() << ";";
        arq << estudante.ObterAnoIngresso() << ";";
        arq << estudante.ObterCurso() << ";";
        arq << estudante.ObterIRA() << endl;

    }

    //Fechando o arquivo
    arq.close();
}
        
        
void Siga::AlteraCadastroEstudante(Estudante est)
{
    //Pesquisa o aluno
    int index = PesquisaPorMatricula( est.ObterMatricula() );

    //Caso nao encontrado imprime e retorna
    if ( index == -1 )
    {
        cout << "Estudante não cadastrado" << endl;
        return;
    }

    //Coloca o cursor no estudante que será reescrito
    this->file_stream.seekp(index * ESTUDANTE_SIZE, this->file_stream.beg);

    //Reescreve os dados dele
    est.EscreverNoArquivoBinario(this->file_stream);

    cout << "Dados Alterados" << endl;
}
        
Siga::~Siga()
{
    this->file_stream.close();
}

int Siga::ObterNumeroEstudantesArmazenados()
{
    if ( this->file_stream.is_open() )
    {
        //Cursor no fim do arquivo binário
        this->file_stream.seekg(0, this->file_stream.end);

        // tellg() Retorna a posição do caractere atual no fluxo de entrada,
        // e como o cursor está no fim do arquivo binário, retorna o tamanho do arquivo binário.
        int length = this->file_stream.tellg();

         //Cursor no inicio do arquivo binário
        this->file_stream.seekg(0, this->file_stream.beg);

        this->n_estudantes = length / ESTUDANTE_SIZE;

        return this->n_estudantes;
    } else 
    {
        return 0;
    }
}


void Siga::ImportCSVData(string file)
{
    // TODO: 

    cout << "Importando dados do arquivo " << file << endl;
    int n_importados = this->n_estudantes;

    ifstream arq;
    // Abra um arquivo .csv com a seguinte formatação:
    // Matricula;Nome;Ano de Ingresso;Curso;IRA
    arq.open(file, ios::in);
    if(!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }

    string line;
    getline(arq, line); // Extrai caracteres de arq e os armazena em line até que o caractere de nova linha, '\n', seja encontrado
    while(getline(arq, line)) // pega cada linha do arquivo
    { 
        stringstream ss(line);  // Convertendo a linha para objeto stringstream (ss vai armazenar o registro de um estudante)

        string token;
        vector<string> tokens; // cria um vetor de tokens

        while(getline(ss, token, ';')) // lê a linha do objeto stringstream, armazenando-a na variável token, até que chegue em um ";"
            tokens.push_back(token); // Tokens podem ser adicionados no vetor de tokens c/ o método com push_back

        if(tokens.size() == 5)
        {
            // Para cada linha do arquivo, criar um objeto Estudante e escrever no arquivo binário.
            Estudante est; // Cria um estudante

            est.TrocarMatricula(stoi(tokens[0])); // posição 0 do vetor é a matricula ( o metodo stoi() analisa str interpretando seu conteúdo como um número inteiro da base especificada 
            //, que é retornada como um valor int.)
            est.TrocarNome(tokens[1].c_str()); // posição 1 do vetor é o nome (O metodo c_str() Retorna um ponteiro para um array que contém uma sequência de caracteres terminada em nulo (ou seja, uma string);
            est.TrocarAnoIngresso(stoi(tokens[2])); // posição 2 do vetor é o ano de ingresso
            est.TrocarCurso(stoi(tokens[3])); // posição 3 do vetor é o código do curso
            est.TrocarIRA(stof(tokens[4])); // posição 4 do vetor é o IRA ( Ometodo stof() Analisa o IRA interpretando seu conteúdo como um número de ponto flutuante, que é retornado como um valor do tipo float.)
            this->CadastraEstudante(est);
        }
    }

    // Atualize o numero de registros no binário.
    n_importados = this->n_estudantes - n_importados;
    
    // Imprima o numero de estudantes importados:
    cout << "Importacao concluida: " << n_importados << " novos alunos cadastrados" << endl;
}

bool compare_estudante_nome(Estudante &a, Estudante &b)
{
    return strcmp(a.ObterNome(), b.ObterNome()) < 0; // indica que o Nome do estudante A é "menor"/ vem antes em ordem crescente que o Nome do estudante B
}

bool compare_estudante_ira(Estudante &a, Estudante &b)
{
    return a.ObterIRA() >  b.ObterIRA(); // indica que o IRA do estudante A é maior que o IRA do estudante B
}

bool compare_estudante_curso(Estudante &a, Estudante &b)
{
    return a.ObterCurso() <  b.ObterCurso(); //Indica que o código do Curso do aluno A é menor que o do aluno B
}

Estudante* Siga::build_vector_from_file()
{
    Estudante *estudantes = new Estudante[this->n_estudantes]; // Cria um vetor de estudantes
    this->file_stream.seekg(0, this->file_stream.beg); // coloca cursor no inicio do arquivo
    for(int i = 0; i < this->n_estudantes; i++)
        estudantes[i].LerDoArquivoBinario(this->file_stream);
    
    return estudantes;

    //perguntar sobre o delete [] estudantes!
}

void Siga::SalvarListaOrdendaEstudantesPorNome(string arquivo_txt, sorting_method method)
{
    // Iremos aplicar a ordenação na memoria, para isso faca:

    // 1. Ler todos os dados do arquivo binário colocandos em um vetor
    Estudante * list_estudantes = build_vector_from_file();

    switch(method)
    {
        // 2. Ordenar o vetor usando o metodo de ordenação escolhido:
        //    - Ordenar por nome
        case BUBBLESORT:
            bubble_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);
            break;
        case INSERTIONSORT:
            insert_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);
            break;
        case SELECTIONSORT:
            selection_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);
            break;
        default:
           cout << "metodo de ordenação não encontrado" << endl;
            break;
    }

    ofstream arq;
    arq.open(arquivo_txt, ios::out);

    if(!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }

    for(int i = 0; i < this->n_estudantes; i++)
        // 3. Escrever o vetor ordenado no arquivo csv:
        //   matricula;nome;ano de ingresso;curso;IRA 
        arq << list_estudantes[i].ObterMatricula() << ";" << list_estudantes[i].ObterNome() << ";" << list_estudantes[i].ObterAnoIngresso() << ";" << list_estudantes[i].ObterCurso() << ";" << list_estudantes[i].ObterIRA() << endl;
    
    arq.close();

    delete [] list_estudantes;
}

void Siga::SalvarListaOrdenadaEstudantes(std::string arquivo_txt)
{
    // Iremos aplicar a ordenação na memoria, para isso faca: 

    // 1. Ler todos os dados do arquivo binário colocandos em um vetor
    Estudante * list_estudantes = build_vector_from_file();
    
    // 2. Ordenar o vetor usando a seguinte sequencia:
    //    - Ordene  por nome (crescente)
    bubble_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);

    //    - Ordenar por Curso 
    bubble_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_curso);

    ofstream arq;
    arq.open(arquivo_txt, ios::out);

    if(!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }

    for(int i = 0; i < this->n_estudantes; i++)
        // 3. Escrever o vetor ordenado no arquivo ASCII 
        arq << list_estudantes[i].ObterMatricula() << ";" << list_estudantes[i].ObterNome() << ";" << list_estudantes[i].ObterAnoIngresso() << ";" << list_estudantes[i].ObterCurso() << ";" << list_estudantes[i].ObterIRA() << endl;
    
    arq.close();

    delete [] list_estudantes;
}