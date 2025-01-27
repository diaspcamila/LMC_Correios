#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

struct endereco{
    char rua[50];
    int numero;
};

struct veiculo{
    char id[50]; // come�ando com V? e depois um C para carro? etc...
    char tipo[50]; // carro, moto, caminhao, van, bike
    int carga;
    bool status; // on e off
};

struct entrega{
    char  id[50]; // come�ando com #
    struct endereco origem;
    struct endereco destino;
    int dias; // criar funcao que calcula os dias
};

struct funcionario{
    char id[50]; // come�ando com F
    char nome[50];
};

struct cliente{
    char id[50]; // come�ando com C
    char nome[50];
    struct endereco ender;
    int servico; // vai ser int ou char? para padrao, economico e premium.
};

struct cliente Cliente1;

int main(){
    setlocale(LC_ALL,"portuguese");
    printf("---------------------------------------------------------\n");
    printf("Ol�, seja bem-vindo ao sistema da LMC Correios!\n O que voc� gostaria de fazer?\n");
    printf("Digite:\n1 para Adicionar Informa��es;\n2 para Remover Informa��es;\n3 para Visualizar Informa��es;\n4 para Deletar Informa��es: ");

    int EscolhaFuncao;
    scanf("%d", &EscolhaFuncao);
    int EscolhaSecao;

    switch(EscolhaFuncao){
    case 1:
        printf("Adicionar Informa��es: onde deseja adicionar? Digite:\n1 para Se��o Clientes;\n2 para Se��o Funcion�rios;\n3 para Se��o Ve�culos;\n4 para Se��o Entrega: ");
        scanf("%d", &EscolhaSecao);
        switch(EscolhaSecao){
        case 1:
            printf("Digite o id do cliente come�ado com C: ");

            printf("\nDigite o nome completo do cliente: ");

            printf("\nDigite o endere�o (sem o n�mero) do cliente: ");

            printf("\nAgora digite o n�mero do endere�o: ");
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        }
        break;
    case 2:
        printf("Remover Informa��es: onde deseja remover? Digite:\n1 para Se��o Clientes;\n2 para Se��o Funcion�rios;\n3 para Se��o Ve�culos;\n4 para Se��o Entrega: ");
        scanf("%d", &EscolhaSecao);
        break;
    case 3:
        printf("Visualizar Informa��es: onde deseja visualizar? Digite:\n1 para Se��o Clientes;\n2 para Se��o Funcion�rios;\n3 para Se��o Ve�culos;\n4 para Se��o Entrega: ");
        scanf("%d", &EscolhaSecao);
        break;
    case 4:
        printf("Deletar Informa��es: onde deseja deletar? Digite:\n1 para Se��o Clientes;\n2 para Se��o Funcion�rios;\n3 para Se��o Ve�culos;\n4 para Se��o Entrega:");
        scanf("%d", &EscolhaSecao);
        break;
    }
    printf("---------------------------------------------------------\n");
    return 0;
}
