#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

//structs
typedef struct Cliente{
    char idCliente[9];
    char nome[50];
    char rua[50];
    int numeroRua;
    char servico[10];
};
typedef struct Veiculo{
    char idVeiculo[9];
    char tipo[20];
    int cargaMaxima;
    bool status;
};
typedef struct Funcionario{
    char idFuncionario[9];
    char nome[50];
};
typedef struct Entrega{
    char idEntrega[9];
    char nome[50];
    char rua[50];
    char nomeOrigem[50];
    char ruaOrigem[50];
    int tempo;
};

//menus
void separarMenus(){
    //só pra ficar mais organizado, não tem função nenhuma apenas estética
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("---------------------------------------------------------\n");
}

int menuPrincipal(){
    int escolhaInfo;
    printf("---------------------------------------------------------\n");
    printf("|                [1] - Gerenciar clientes                |\n");
    printf("|                [2] - Gerenciar veículos                |\n");
    printf("|                [3] - Gerenciar funcionários            |\n");
    printf("|                [4] - Gerenciar entregas                |\n");
    printf("|                [5] - Voltar                            |\n");
    printf("---------------------------------------------------------\n");
    scanf("%d", &escolhaInfo);
    return escolhaInfo;
}

int menuUniversal(){
    int escolhaOperacao;
    printf("---------------------------------------------------------\n");
    printf("|                    [1] - Cadastrar                     |\n");
    printf("|                    [2] - Editar                        |\n");
    printf("|                    [3] - Excluir                       |\n");
    printf("|                    [4] - Visualizar                    |\n");
    printf("|                    [5] - Voltar                        |\n");
    printf("---------------------------------------------------------\n");
    scanf("%d", &escolhaOperacao);
    return escolhaOperacao;
}

//funções edit
void editCliente(){
    FILE *arquivo;
    struct Cliente cliente;
    char idProcuradoC[9];
    arquivo = fopen("clientes.txt", "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    printf("Digite o ID do cliente que deseja editar: ");
    scanf("%s", idProcuradoC);
    while(fread(&cliente, sizeof(struct Cliente), 1, arquivo)){
        if(strcmp(cliente.idCliente, idProcuradoC) == 0){
            printf("Digite o novo nome do cliente: \n");
            scanf("%s", cliente.nome);
            printf("Digite a nova rua do cliente: \n");
            scanf("%s", cliente.rua);
            printf("Digite o novo número da rua do cliente: \n");
            scanf("%d", &cliente.numeroRua);
            printf("Digite o novo serviço do cliente: \n");
            scanf("%s", cliente.servico);
            fseek(arquivo, -sizeof(struct Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(struct Cliente), 1, arquivo);
            break;
        } else {
            printf("Cliente não encontrado!");
        }
    }
    fclose(arquivo);
}
void editVeiculo(){
    FILE *arquivo;
    struct Veiculo veiculo;
    char idProcuradoV[9];
    arquivo = fopen("veiculos.txt", "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    printf("Digite o ID do veículo que deseja editar: ");
    scanf("%s", idProcuradoV);
    while(fread(&veiculo, sizeof(struct Veiculo), 1, arquivo)){
        if(strcmp(veiculo.idVeiculo, idProcuradoV) == 0){
            printf("Digite o novo tipo do veículo: \n");
            scanf("%s", veiculo.tipo);
            printf("Digite a nova carga máxima do veículo: \n");
            scanf("%d", &veiculo.cargaMaxima);
            printf("Digite o novo status do veículo: \n");
            scanf("%d", &veiculo.status);
            fseek(arquivo, -sizeof(struct Veiculo), SEEK_CUR);
            fwrite(&veiculo, sizeof(struct Veiculo), 1, arquivo);
            break;
        } else {
            printf("Veículo não encontrado!");
        }
    }
    fclose(arquivo);
}

void editFuncionario(){
    FILE *arquivo;
    struct Funcionario funcionario;
    char idProcuradoF[9];
    arquivo = fopen("funcionarios.txt", "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    printf("Digite o ID do funcionário que deseja editar: ");
    scanf("%s", idProcuradoF);
    while(fread(&funcionario, sizeof(struct Funcionario), 1, arquivo)){
        if(strcmp(funcionario.idFuncionario, idProcuradoF) == 0){
            printf("Digite o nome do funcionário: \n");
            scanf("%s", funcionario.nome);
            fseek(arquivo, -sizeof(struct Funcionario), SEEK_CUR);
            fwrite(&funcionario, sizeof(struct Funcionario), 1, arquivo);
            break;
        } else {
            printf("Funcionário não encontrado!");
        }
    }
    fclose(arquivo);
}
void editEntrega(){
    FILE *arquivo;
    struct Entrega entrega;
    char idProcuradoE[9];
    arquivo = fopen("entregas.txt", "rb");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    printf("Digite o ID da entrega que deseja editar: ");
    scanf("%s", idProcuradoE);
    while (fread(&entrega, sizeof(struct Entrega), 1, arquivo)){
        if (strcmp(entrega.idEntrega, idProcuradoE) == 0){
            printf("Digite o novo nome do destinatário: \n");
            scanf("%s", entrega.nome); 
            printf("Digite a nova rua do destinatário: \n");
            scanf("%s", entrega.rua);
            printf("Digite o novo nome do remetente: \n");
            scanf("%s", entrega.nomeOrigem);
            printf("Digite a nova rua do remetente: \n");
            scanf("%s", entrega.ruaOrigem);
            printf("Digite o novo tempo de entrega: \n");
            scanf("%d", &entrega.tempo);
            fseek(arquivo, -sizeof(struct Entrega), SEEK_CUR);
            fwrite(&entrega, sizeof(struct Entrega), 1, arquivo);
            break;
        } else {
            printf("Entrega não encontrada!");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int escolhaInfo;
    int escolhaOperacao;
    switch (escolhaInfo = menuPrincipal()){
        case 1: //clientes
            switch (escolhaOperacao = menuUniversal()){
                case 1: 
                    //addCliente();
                    break;
                case 2: 
                    editCliente();
                    break;
                case 3: 
                    //delCliente();
                    break;
                case 4: 
                    //showCliente();
                    break;
                case 5: 
                    printf("Voltando ao menu principal...");
                    menuPrincipal();   
                    break;
                default:
                printf("Insira uma opção válida para gerenciamento de clientes!");
                    break;
            }
            break;
    
        case 2: //veículos
            switch (escolhaOperacao = menuUniversal()){
                case 1: 
                    //addVeiculo();
                    break;
                case 2: 
                    editVeiculo();
                    break;
                case 3: 
                    //delVeiculo();
                    break;
                case 4: 
                    //showVeiculo();
                    break;
                case 5: 
                    printf("Voltando ao menu principal...");
                    menuPrincipal();   
                    break;
                default:
                printf("Insira uma opção válida para gerenciamento de veículos!");
                    break;
            }
            break;
        case 3: //funcionários
            switch (escolhaOperacao = menuUniversal()){
                case 1: 
                    //addFuncionario();
                    break;
                case 2: 
                    editFuncionario();
                    break;
                case 3: 
                    //delFuncionario();
                    break;
                case 4: 
                    //showFuncionario();
                    break;
                case 5: 
                    printf("Voltando ao menu principal...");
                    menuPrincipal();   
                    break;
                default:
                printf("Insira uma opção válida para gerenciamento de funcionários!");
                    break;
            }
            break;
        case 4: //entregas
            switch (escolhaOperacao = menuUniversal()){
                case 1: 
                    //addEntrega();
                    break;
                case 2: 
                    editEntrega();
                    break;
                case 3: 
                    //delEntrega();
                    break;
                case 4: 
                    //showEntrega();
                    break;
                case 5: 
                    printf("Voltando ao menu principal...");
                    menuPrincipal();   
                    break;
                default:
                printf("Insira uma opção válida para gerenciamento de entregas!");
                    break;
            }
            break;

    default:
        printf("Insira uma opção válida para escolher a categoria!");
        break;
    }
    return 0;
}
