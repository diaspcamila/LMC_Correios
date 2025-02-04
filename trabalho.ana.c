//trabalho ana luiza
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void separarMenus(){
    //só pra ficar mais organizado, não tem função nenhuma apenas estética
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("---------------------------------------------------------\n");
}

// Espaço das funções de gerenciamento de clientes

typedef struct {
    char id[10];
    char nome[50];
    char rua[50];
    int numeroRua;
    char servico[10];
}Cliente;

void delCliente(Cliente itens[], int numClientes, char idProcurado[]){
    separarMenus();
    printf("Bem vindo ao menu de remoção de clientes! \n");
    printf("Por favor, insira o ID do cliente que deseja remover: ");
    scanf("%s", idProcurado);
    for (int i = 0; i < numClientes; i++){
        if (strcmp(itens[i].id, idProcurado) == 0){
            strcpy(itens[i].id, "");
            strcpy(itens[i].nome, "");
            strcpy(itens[i].rua, "");
            itens[i].numeroRua = 0;
            strcpy(itens[i].servico, "");
            printf("Removendo cliente...");
            printf("Cliente removido com sucesso!");
            return;
        }
        else {
            printf("Cliente não encontrado. Por favor, digite novamente.");
        }
    }
}

void visuCliente(Cliente itens[], int numClientes){
    separarMenus();
    printf("Um arquivo .txt será gerado com os dados dos clientes.");
    FILE *arquivo;
    arquivo = fopen("clientes.txt", "w");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
    }
    for (int i = 0; i < numClientes; i++){
        fprintf(arquivo, "ID: %s\n", itens[i].id);
        fprintf(arquivo, "Nome completo: %s\n", itens[i].nome);
        fprintf(arquivo, "Endereço: %s, %d\n", itens[i].rua, itens[i].numeroRua);
        fprintf(arquivo, "Serviço: %s\n", itens[i].servico);
    }
    printf("Arquivo gerado com sucesso!");
    fclose(arquivo);
}

void editCliente(Cliente itens[], int numClientes, char idProcurado[]){
    separarMenus();
    printf("Bem vindo ao menu de edição de clientes!");
    printf("Por favor, insira o ID do cliente que deseja editar: ");
    scanf("%d", idProcurado);
    for (int i = 0; i < numClientes; i++){
        if (strcmp(itens[i].id, idProcurado) == 0){
            printf("Digite o novo nome do cliente: ");
            scanf("%s", itens[i].nome);
            printf("Digite o novo endereço do cliente: ");
            scanf("%s", itens[i].rua);
            printf("Digite o novo número do endereço do cliente: ");
            scanf("%d", &itens[i].numeroRua);
            printf("Digite o novo serviço do cliente: ");
            scanf("%s", itens[i].servico);
            printf("Editando cliente...");
            printf("Cliente editado com sucesso!");
            return;
        }
        else {
            printf("Cliente não encontrado. Por favor, digite novamente.");
        }
    }
}

void gerenciarClientes(){
    int escolha;
    separarMenus();
    while (escolha != 3)
    {
        printf("Informe o que deseja fazer.");
        printf("[1] Adicionar cliente \n");
        printf("[2] Deletar cliente \n");
        printf("[3] Visualizar cliente \n");
    }
    switch (escolha){
        case 1:
        //addCliente();
        break;
        case 2:
       // delCliente();
        break;
        case 3:
        //visuCliente();
        break;
    }
}


void mainMenu(){
    int escolha;
    setlocale(LC_ALL,"portuguese");
    printf("---------------------------------------------------------\n");
    printf("Olá, seja bem-vindo ao sistema da LMC Correios!\n O que vocé gostaria de fazer?\n");
    while (escolha !=5){
        printf("[1] Gerenciar cliente \n");
        printf("[2] Gerenciar veículos \n");
        printf("[3] Gerenciar entregas \n");
        printf("[4] Gerenciar funcionários \n");
        printf("[5] Sair do sistema");
    }

    switch (escolha){
        case 1:
        gerenciarClientes();
        break;
        case 2:
       // gerenciarVeiculos();
        break;
        case 3:
        //gerenciarEntregas();
        break;
        case 4:
        //gerenciarFuncionarios();
        break;
        case 5:
        printf("Saindo do sistema...");
        default:
        printf("Input inválido. Por favor, tente novamente.");
    }
}

int main (){
    Cliente clientes[3] = {
        {"1", "Ana Luiza", "Rua 1", 1, "Economica"},
        {"2", "João", "Rua 2", 2, "Premium"},
        {"3", "Maria", "Rua 3", 3, "Padrão"}
    };
    //teste deletando cliente 2
    delCliente(clientes, 3, "2");
    //teste visualizando clientes
    visuCliente(clientes, 3);
    //teste editando cliente 3
    editCliente(clientes, 3, "3");


    return 0;
}
