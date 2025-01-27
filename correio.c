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
    char id[50]; // começando com V? e depois um C para carro? etc...
    char tipo[50]; // carro, moto, caminhao, van, bike
    int carga;
    bool status; // on e off
};

struct entrega{
    char  id[50]; // começando com #
    struct endereco origem;
    struct endereco destino;
    int dias; // criar funcao que calcula os dias
};

struct funcionario{
    char id[50]; // começando com F
    char nome[50];
};

struct cliente{
    char id[50]; // começando com C
    char nome[50];
    struct endereco ender;
    int servico; // vai ser int ou char? para padrao, economico e premium.
};

struct cliente Cliente1;

int main(){
    setlocale(LC_ALL,"portuguese");
    printf("---------------------------------------------------------\n");
    printf("Olá, seja bem-vindo ao sistema da LMC Correios!\n O que você gostaria de fazer?\n");
    printf("Digite:\n1 para Adicionar Informações;\n2 para Remover Informações;\n3 para Visualizar Informações;\n4 para Deletar Informações: ");

    int EscolhaFuncao;
    scanf("%d", &EscolhaFuncao);
    int EscolhaSecao;

    switch(EscolhaFuncao){
    case 1:
        printf("Adicionar Informações: onde deseja adicionar? Digite:\n1 para Seção Clientes;\n2 para Seção Funcionários;\n3 para Seção Veículos;\n4 para Seção Entrega: ");
        scanf("%d", &EscolhaSecao);
        switch(EscolhaSecao){
        case 1:
            printf("Digite o id do cliente começado com C: ");

            printf("\nDigite o nome completo do cliente: ");

            printf("\nDigite o endereço (sem o número) do cliente: ");

            printf("\nAgora digite o número do endereço: ");
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
        printf("Remover Informações: onde deseja remover? Digite:\n1 para Seção Clientes;\n2 para Seção Funcionários;\n3 para Seção Veículos;\n4 para Seção Entrega: ");
        scanf("%d", &EscolhaSecao);
        break;
    case 3:
        printf("Visualizar Informações: onde deseja visualizar? Digite:\n1 para Seção Clientes;\n2 para Seção Funcionários;\n3 para Seção Veículos;\n4 para Seção Entrega: ");
        scanf("%d", &EscolhaSecao);
        break;
    case 4:
        printf("Deletar Informações: onde deseja deletar? Digite:\n1 para Seção Clientes;\n2 para Seção Funcionários;\n3 para Seção Veículos;\n4 para Seção Entrega:");
        scanf("%d", &EscolhaSecao);
        break;
    }
    printf("---------------------------------------------------------\n");
    return 0;
}
