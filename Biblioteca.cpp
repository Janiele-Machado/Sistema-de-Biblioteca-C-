#include <iostream>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

FILE *dados_biblioteca, *dados_biblioteca_aux; 

struct emprestimo
{
    char dt_emprestimo[11];
    char dt_devolucao[11];
    char usuario_empres[100];
};

struct livros
{
    int cod_catalogacao;
    char area[100];
    char titulo[100];
    char autores[100];
    char editora[100];
    float n_paginas;
    char livro_disp;

    struct emprestimo emprest;
};

struct livros liv;

int main()
{

    int opc, pos, cod_consulta;
    char opc_cadastro;

    do
    {
        cout << endl;
        cout << "------------MENU------------" << endl;
        cout << "|1-Cadastro                |" << endl;
        cout << "|2-Alteracao               |" << endl;
        cout << "|3-Exclusao                |" << endl;
        cout << "|4-Emprestimo              |" << endl;
        cout << "|5-Devolucao               |" << endl;
        cout << "|6-Consulta de Livros      |" << endl;
        cout << "|7-Livros Disponiveis      |" << endl;
        cout << "|8-Listagem Geral de Livros|" << endl;
        cout << "|9-Sair                    |" << endl;
        cout << "|--------------------------|" << endl;
        cin >> opc;

        if (opc == 1)
        {

            cout << "-----Cadastro de Livros:-----"<< endl;
            cout << "Deseja cadastrar um novo livro (S)im ou (N)ao :";
            cin >> opc_cadastro;

            while (opc_cadastro == 'S')
            {

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite os dados do livro para o cadastro:" << endl;
                cout << "Titulo do livro:" << endl;
                cin.get(liv.titulo, 99);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Codigo de catalogacao:" << endl;
                cin >> liv.cod_catalogacao;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Area(Ciencias exatas,ciencias humanas ou ciencias da saude):" << endl;
                cin.get(liv.area, 99);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Autor(es): " << endl;
                cin.get(liv.autores, 99);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Editora: " << endl;
                cin.get(liv.editora, 99);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Numero de paginas: " << endl;
                cin >> liv.n_paginas;
                liv.livro_disp = 'S';

                dados_biblioteca = fopen("dados_biblioteca.dat", "ab+");
                if (dados_biblioteca == NULL)
                {
                    dados_biblioteca = fopen("dados_biblioteca.dat", "wb");
                }

                if (fwrite(&liv, sizeof(struct livros), 1, dados_biblioteca) == 1)
                {
                    cout << "Cadastro realizado com sucesso!" << endl;
                }
                else
                {
                    cout << "Erro no cadastro" << endl;
                    cin.get();
                }
                fclose(dados_biblioteca);

                cout << "Gostaria de cadastrar outro livro?(S)im ou (N)ao:";
                cin >> opc_cadastro;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else if (opc == 2)
        {
            cout << "------Alteracao-------" << endl;
            cout << "Digite por favor o codigo do livro que voce quer alterar:" << endl;
            cin >> cod_consulta;
            dados_biblioteca = fopen("dados_biblioteca.dat", "rb+"); // rb+ é para leitura mas tbm para alteração
            pos = -1;
            if (dados_biblioteca == NULL)
            {
                cout << "erro em abrir o arquivo";
                cin.ignore();
                cin.get();
            }
            else
            {

                while (!feof(dados_biblioteca))
                {
                    fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                    pos++;
                    if (liv.cod_catalogacao == cod_consulta)
                    {
                        fseek(dados_biblioteca, sizeof(struct livros) * pos, SEEK_SET);
                        cout << "Livro encontrado!" << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Digite o novo Titulo do livro:" << endl;
                        cin.get(liv.titulo, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Digite o novo Codigo de catalogacao:" << endl;
                        cin >> liv.cod_catalogacao;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Digite a nova Area(Ciencias exatas,ciencias humanas ou ciencias da saude):" << endl;
                        cin.get(liv.area, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Digite o(s) novo(s) Autor(es): " << endl;
                        cin.get(liv.autores, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Digite a nova Editora: " << endl;
                        cin.get(liv.editora, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Digite o Numero de paginas: " << endl;
                        cin >> liv.n_paginas;
                        liv.livro_disp = 'S';
                        fwrite(&liv, sizeof(struct livros), 1, dados_biblioteca);
                        break;
                    }
                }
                fclose(dados_biblioteca);
            }
        }
        else if (opc == 3)
        {
            cout << "-----Excluindo Livro-----" << endl;
            cout << "Digite o codigo do livro que voce deseja excluir:" << endl;
            cin >> cod_consulta;
            dados_biblioteca_aux = fopen("dados_biblioteca_aux.dat", "wb");
            dados_biblioteca = fopen("dados_biblioteca.dat", "rb");
            if (dados_biblioteca == NULL)
            {
                cout << "Erro em abrir arquivo!";
                cin.ignore();
                cin.get();
            }
            else
            {
                fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                while (!feof(dados_biblioteca))
                {
                    if (liv.cod_catalogacao != cod_consulta)
                    {
                        fwrite(&liv, sizeof(struct livros), 1, dados_biblioteca_aux);
                    }
                    fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                }
                fclose(dados_biblioteca);
                fclose(dados_biblioteca_aux);
                remove("dados_biblioteca.dat");
                rename("dados_biblioteca_aux.dat", "dados_biblioteca.dat");
                cout << "Livro Excluido com sucesso!" << endl;
                cin.ignore();
                cin.get();
            }
        }
        else if (opc == 4)
        {
            cout << "-----Emprestimo-----" << endl;
            cout << "Digite por favor o codigo do livro que voce quer emprestado:";
            cin >> cod_consulta;

            dados_biblioteca = fopen("dados_biblioteca.dat", "rb+");
            pos = -1;
            if (dados_biblioteca == NULL)
            {
                cout << "Erro ao abrir arquivo" << endl;
                cin.ignore();
                cin.get();
            }
            else
            {
                while (!feof(dados_biblioteca))
                {
                    fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                    pos++;

                    if (cod_consulta == liv.cod_catalogacao)
                    {
                        if (liv.livro_disp == 'N')
                        {
                            cout << "O livro em questao nao esta disponivel para o emprestimo" << endl;
                            cin.ignore();
                            cin.get();
                        }
                        else
                        {

                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Digite a data do emprestimo:";
                            cin.get(liv.emprest.dt_emprestimo, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Digite seu nome: ";
                            cin.get(liv.emprest.usuario_empres, 99);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Digite a data de devolucao: ";
                            cin.get(liv.emprest.dt_devolucao, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            liv.livro_disp = 'N';
                            cout << "Emprestimo realizado com sussesso" << endl;
                            cout << "A data de devolucao sera no dia " << liv.emprest.dt_devolucao << endl;
                            cin.ignore();
                            cin.get();
                            fseek(dados_biblioteca, sizeof(struct livros) * pos, SEEK_SET);
                            fwrite(&liv, sizeof(struct livros), 1, dados_biblioteca);
                            break;
                        }
                    }
                }
                fclose(dados_biblioteca);
            }
        }
        else if (opc == 5)
        {
            cout << "---Devolucao--- " << endl;
            cout << "Digite o codigo para devolucao: " << endl;
            cin >> cod_consulta;

            dados_biblioteca = fopen("dados_biblioteca.dat", "rb+");
            pos = -1;
            if (dados_biblioteca == NULL)
            {
                cout << "Erro ao abrir o arquivo" << endl;
                cin.ignore();
                cin.get();
            }
            else
            {
                while (!feof(dados_biblioteca))
                {
                    fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                    pos++;
                    if (cod_consulta == liv.cod_catalogacao)
                    {
                        if (liv.livro_disp == 'N')
                        {
                            liv.livro_disp = 'S';
                            strcpy(liv.emprest.dt_emprestimo, "");
                            strcpy(liv.emprest.dt_devolucao, "");
                            strcpy(liv.emprest.usuario_empres, "");
                            fseek(dados_biblioteca, sizeof(struct livros) * pos, SEEK_SET);
                            fwrite(&liv, sizeof(struct livros), 1, dados_biblioteca);
                            cout << "Seu livro foi devolvido com sucesso" << endl;
                            cin.ignore();
                            cin.get();
                            break;
                        }
                        else if (liv.livro_disp == 'S')
                        {
                            cout << "Esse livro nao foi emprestado " << endl;
                            cin.ignore();
                            cin.get();
                        }
                    }
                }
                fclose(dados_biblioteca);
            }
        }
        else if (opc == 6)
        {

            cout << "-----Consulta de Livros:-----" << endl;
            cout << "Digite o codigo do livro: ";
            cin >> cod_consulta;
            dados_biblioteca = fopen("dados_biblioteca.dat", "rb");
            while (!feof(dados_biblioteca))
            {
                fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                if (cod_consulta == liv.cod_catalogacao)
                {
                    cout << "Aqui esta os dados desse livro:" << endl;
                    cout << "Titulo do livro: " << liv.titulo << endl;
                    cout << "Codigo de catalogacao:" << liv.cod_catalogacao << endl;
                    cout << "Area(Ciencias exatas,ciencias humanas ou ciencias da saude):" << liv.area << endl;
                    cout << "Autor(es):" << liv.autores << endl;
                    cout << "Editora: " << liv.editora << endl;
                    cout << "Numero de paginas:" << liv.n_paginas << endl;
                    if (liv.livro_disp == 'S')
                    {
                        cout << "Situacao do livro: Livre para o emprestimo " << endl;
                    }
                    else
                    {
                        cout << "Situacao do livro: Emprestado " << endl;
                    }
                    cout << "---------------------------------" << endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
            }
            fclose(dados_biblioteca);
        }
        else if (opc == 7)
        {
            dados_biblioteca = fopen("dados_biblioteca.dat", "rb");
            if (dados_biblioteca == NULL)
            {
                cout << "falha em ler o arquivo...";
            }
            else
            {
                cout << "-----Livros Disponiveis:----- " << endl;
                fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                while (!feof(dados_biblioteca))
                {

                    if (liv.livro_disp == 'S')
                    {
                        cout << "Titulo da obra: " << liv.titulo << endl;
                        cout << "Codigo do livro: " << liv.cod_catalogacao << endl;
                        cout << "-----------------------------------------" << endl;
                    }
                    fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                }

                fclose(dados_biblioteca);
                cin.ignore();
                cin.get();
            }
        }
        else if (opc == 8)
        {
            dados_biblioteca = fopen("dados_biblioteca.dat", "rb");
            if (dados_biblioteca == NULL)
            {
                cout << "falha em ler o arquivo...";
            }
            else
            {
                cout << "Listagem Geral de Livros " << endl;
                fread(&liv, sizeof(struct livros), 1, dados_biblioteca);

                while (!feof(dados_biblioteca))
                {
                    cout << "Titulo do livro: " << liv.titulo << endl;
                    cout << "Codigo de catalogacao:" << liv.cod_catalogacao << endl;
                    cout << "Area(Ciencias exatas,ciencias humanas ou ciencias da saude):" << liv.area << endl;
                    cout << "Autor(es):" << liv.autores << endl;
                    cout << "Editora: " << liv.editora << endl;
                    cout << "Numero de paginas:" << liv.n_paginas << endl;
                    if (liv.livro_disp == 'S')
                    {
                        cout << "Situacao do livro: Livre para o emprestimo " << endl;
                    }
                    else
                    {
                        cout << "Situacao do livro: Emprestado " << endl;
                    }
                    cout << "------------------------------------------" << endl;
                    fread(&liv, sizeof(struct livros), 1, dados_biblioteca);
                }

                fclose(dados_biblioteca);
                cin.ignore();
                cin.get();
            }
        }
        else if (opc == 9)
        {
            cout << "Obrigado por usar o codigo" << endl;
        }
        else
        {
            cout << "Opcao invalida,tente novamente";
            cin.ignore();
            cin.get();
        }

    } while (opc != 9);
}