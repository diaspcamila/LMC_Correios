#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

FILE *ptrF;

struct funcionario{
    char id[50]; // começando com F
    char nome[50];
};

void criarFuncionario(){
    separarMenus();
    char id[50];
    char nome[50];
    printf("Escreva o nome completo e o ID do funcionario a ser adicionado: ");
    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);
    fflush(stdin);
    gets(id);
    ptrF = fopen("funcionarios.dat", "a+b");
    if (ptrF == NULL){
        printf("ERRO! O arquivo não foi aberto!\n");
        return 0;
    }
    fprintf(ptrF, "%s%s\n", nome, id);
    fclose(ptrF);
    printf("Funcionário criado com sucesso!\n");
    mainMenu();
};

//visualizar funcioanrio
void viewFuncionario(){
    separarMenus();
    char nome[50], id[50], linha[50];
    int result;
    printf("Insira o ID do funcionario que deseja visualizar: ");
    ptrF = fopen("funcionarios.dat", "r+b");
    if (ptrF == NULL){
        printf("ERRO! O arquivo não foi aberto!\n");
        return;
    }
    fgets(nome, sizeof(nome), stdin);
    fseek(ptrF, 0, SEEK_SET);
    while(fgets(linha,50,ptrF) !=  NULL){ // le do 0 do line ate o 100
        if(strstr(linha, nome) != NULL){ // procura em line se existe palavra, se nao for null, achou
            printf("As informações do funcionário pesquisado é: \n");
            fprintf(stdout, "%s ", nome);
            fprintf(stdout, "%s\n", id); // como vou botar o id aaaaaaaaaaaaaaaaaaaaaaaaaa
            result = 1;
            return;
        }
    }
    if(result != 1) printf("Funcionário não encontrado. Tente novamente!\n");

    mainMenu();
}

//deletar funcionario
void delFuncionario(){
    separarMenus();

    mainMenu();
}

//editar mal feito, aprenas procurei o nome nao terminei de substituir.
void editarFuncionario(){
    char *nomeM;
    char nome[50];
    nomeM = (char *) malloc(50 *sizeof(char));
    char palavra[50], linha[50];
    int result = 0;

    printf("Digite o nome que deseja editar: \n");
    fflush(stdin);
    fgets(palavra, sizeof(palavra), stdin);
    struct funcionario ef;

    ptrF = fopen("testef.dat", "r+b");
    if (ptrF == NULL){
        printf("ERRO! O arquivo não foi aberto!\n");
        strcpy(ef.nome, palavra);
        return ef;
    }

    fseek(ptrF, 0, SEEK_SET);
    while(fgets(linha,50,ptrF) !=  NULL){ // le do 0 do line ate o 100
        if(strstr(linha, palavra) != NULL){ // procura em line se existe palavra, se nao for null, achou
            printf("ACHOU (NOME) %s\n", palavra);
            result = 1;
            printf("Digite o novo nome:");
            fflush(stdin);
            fgets(nomeM, sizeof(nomeM), stdin);
            strcpy(ef.nome, nomeM);
            //removerFuncionario("testf.dat", palavra, nomeM);
            return ef;
        }
    }
    if(result != 1) printf("STRING NOT FOUND!\n");
};

void gerenciarFuncionarios(){
    int escolhaF;
    separarMenus();
    printf("Informe o que deseja fazer: \n");
    printf("[1] Adicionar funcionario \n");
    printf("[2] Deletar funcionario \n");
    printf("[3] Visualizar funcionario \n");
    printf("[4] Editar funcionario \n");
    scanf("%d", &escolhaF);
    switch (escolhaF){
        case 1:
        criarFuncionario();
        break;
        case 2:
        //delFuncionario();
        break;
        case 3:
        viewFuncionario();
        break;
        case 4:
        //editFuncionario();
        break;
        default:
        printf("Input inválido. Por favor, tente novamente.");
    }
}

void mainMenu(){
    int escolha;
    setlocale(LC_ALL,"portuguese");
    printf("---------------------------------------------------------\n");
    printf("Olá, seja bem-vindo ao sistema da LMC Correios!\n O que vocé gostaria de fazer?\n");
    printf("[1] Gerenciar cliente \n");
    printf("[2] Gerenciar veículos \n");
    printf("[3] Gerenciar entregas \n");
    printf("[4] Gerenciar funcionários \n");
    printf("[5] Sair do sistema");
    scanf("%d", &escolha);

    switch (escolha){
        case 1:
        //gerenciarClientes();
        break;
        case 2:
       // gerenciarVeiculos();
        break;
        case 3:
        //gerenciarEntregas();
        break;
        case 4:
        gerenciarFuncionarios();
        break;
        case 5:
        printf("Saindo do sistema...");
        default:
        printf("Input inválido. Por favor, tente novamente.");
    }
}

int main () {
    mainMenu();
    return 0;
}

