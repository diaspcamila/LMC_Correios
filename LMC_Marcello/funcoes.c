#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//Funções para IDs
void criar_arquivos_iniciais(){
    int ID_incial = 1;

    FILE *arquivo_id_veic = fopen("mem_veic.dat", "wb");
    FILE *arquivo_id_entreg = fopen("mem_entreg.dat", "wb");
    FILE *arquivo_id_func = fopen("mem_func.dat", "wb");
    FILE *arquivo_id_cliente = fopen("mem_cliente.dat", "wb");
    
    fwrite(&ID_incial, sizeof(int), 1, arquivo_id_veic);
    fwrite(&ID_incial, sizeof(int), 1, arquivo_id_entreg);
    fwrite(&ID_incial, sizeof(int), 1, arquivo_id_func);
    fwrite(&ID_incial, sizeof(int), 1, arquivo_id_cliente);

    fclose(arquivo_id_veic);
    fclose(arquivo_id_entreg);
    fclose(arquivo_id_func);
    fclose(arquivo_id_cliente);
}


void atualizar_id(char caminho[]){
    int num;
    FILE *arquivo = fopen(caminho, "rb");

    fread(&num, sizeof(int), 1, arquivo);
    num++;
    //num agora tem o valor do ID desatualizado + 1

    arquivo = fopen(caminho, "wb");
    fwrite(&num, sizeof(int), 1, arquivo);
    fclose(arquivo);
}


//FUNÇÕES VEÍCULOS
void criar_veiculo(){
    char tipo[50];
    int carga, disponivel, id_veic;
    //recolhendo as informações do usuário

    printf("Digite o tipo e carga do veiculo (em KG) a ser registrado, respectivamente:\n");
    scanf("%s %d", &tipo, &carga);
    
    getchar();
    printf("O veículo está disponível? Digite '0' para SIM e '1' para NÄO?\n");
    scanf("%d", &disponivel);

    //montagem da variável tipo veiculo
    //tipo e carga
    struct Veiculo veiculo;
    strcpy(veiculo.tipo, tipo);
    veiculo.carga = carga;
    veiculo.disponivel = disponivel;

    //associando ID ao veiculo criado e atualizando arquivo de memória para usos futuros
    FILE *arquivo_id = fopen("mem_veic.dat","rb");
    fread(&id_veic, sizeof(int), 1, arquivo_id);
    veiculo.id = id_veic;
    
    atualizar_id("mem_veic.dat");

    //armazenando a variável
    FILE *arquivo = fopen("veiculos.dat", "ab");

    if (arquivo == NULL){
        printf("Erro ao armazenar dados do veiculo.");
    } else {
        fwrite(&veiculo, sizeof(veiculo), 1, arquivo);
        printf("Veiculo ID: %d\nTipo: %s\nCarga: %d\nDisponibilidade: %d\nArmazenado com sucesso\n", veiculo.id, veiculo.tipo, veiculo.carga, veiculo.disponivel);
    }

    fclose(arquivo);
}


struct Veiculo encontrar_veiculo(int id){
    FILE *banco_de_veiculos = fopen("veiculos.dat", "rb");

    struct Veiculo veiculo;
    fread(& veiculo, sizeof(struct Veiculo), 1, banco_de_veiculos);

    int i = 0;

    while(1){
        if (id == veiculo.id) {
            fclose(banco_de_veiculos);
            return veiculo;
            break;
        }

        i++;
        fseek(banco_de_veiculos, sizeof(struct Veiculo) * i, SEEK_SET);
        fread(&veiculo, sizeof(struct Veiculo), 1, banco_de_veiculos);

        if(feof(banco_de_veiculos)){
            fclose(banco_de_veiculos);
            break;
        }
    }
}


//FUNÇÕES FUNCIONARIO
void criar_funcionario(){
    char nome[50];
    int id_func;

    printf("Digite o nome completo do Funcionário: ");
    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);

    FILE *arquivo = fopen("mem_func.dat", "rb");
    fread(&id_func, sizeof(int), 1, arquivo);
    atualizar_id("mem_func.dat");
    fclose(arquivo);

    struct Funcionario novo_funcionario;
    novo_funcionario.id = id_func;
    strcpy(novo_funcionario.nome, nome);

    FILE *banco_de_funcionarios = fopen("funcionarios.dat", "ab");
    if (banco_de_funcionarios == NULL){
        printf("Erro ao armazenar funcionário");
    } else {
        fwrite(&novo_funcionario, sizeof(novo_funcionario), 1, banco_de_funcionarios);
        printf("Funcionario de ID: %d\nNome: %s\n Armazenado com sucesso", novo_funcionario.id, novo_funcionario.nome);
    }
    fclose(banco_de_funcionarios);
}


struct Funcionario encontrar_funcionario(int id){
    FILE *banco_de_funcionarios = fopen("funcionarios.dat", "rb");
    struct Funcionario funcionario;

    fread(&funcionario, sizeof(struct Funcionario), 1, banco_de_funcionarios);

    int i = 0;

    while(1){  
        if (id == funcionario.id) {
            fclose(banco_de_funcionarios);
            return funcionario;
            break;
        }

        i++;
        fseek(banco_de_funcionarios, sizeof(struct Funcionario) * i, SEEK_SET);
        fread(&funcionario, sizeof(struct Funcionario), 1, banco_de_funcionarios);

        if(feof(banco_de_funcionarios)){
            fclose(banco_de_funcionarios);
            break;
        }
    }
}


//FUNÇÕES CLIENTES
void criar_cliente(){
    int id_cliente, servico;
    char nome[50], endereco[80];

    printf("Digite o nome completo do cliente: \n");
    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);

    printf("Digite o endereco do cliente no formato 'ESTADO, CIDADE, BAIRRO, RUA, NUMERO': \n");
    fflush(stdin);
    fgets(endereco, sizeof(endereco), stdin);

    printf("Qual é o tipo do servico do cliente? economico (0), padrao(1) ou premium(2)? \n");
    scanf("%d", &servico);

    FILE *arquivo = fopen("mem_cliente.dat", "rb");
    fread(&id_cliente, sizeof(int), 1, arquivo);
    atualizar_id("mem_cliente.dat");
    fclose(arquivo);


    struct Cliente novo_cliente;
    novo_cliente.id = id_cliente;
    novo_cliente.servico = servico;
    strcpy(novo_cliente.nome, nome);
    strcpy(novo_cliente.endereco, endereco);

    FILE *banco_de_clientes = fopen("clientes.dat", "ab");
    if (banco_de_clientes == NULL){
        printf("Falha em armazenar o cliente.\n");
    } else {
        fwrite(&novo_cliente, sizeof(struct Cliente), 1, banco_de_clientes);
        printf("Cliente ID: %d\nNome: %s\nEndereco: %s\nServico: %d\nArmazenado com sucesso.\n", novo_cliente.id, novo_cliente.nome, novo_cliente.endereco, novo_cliente.servico);
    }
    fclose(banco_de_clientes);
}

struct Cliente encontrar_cliente(int id){
    FILE *banco_de_clientes = fopen("clientes.dat", "rb");
    struct Cliente cliente;

    fread(&cliente, sizeof(struct Cliente), 1, banco_de_clientes);

    int i = 0;

    while (1) {
        if (id == cliente.id) {
            fclose(banco_de_clientes);
            return cliente;
            break;
        }

        i++;
        fseek(banco_de_clientes, sizeof(struct Cliente) * i, SEEK_SET);
        fread(&cliente, sizeof(struct Cliente), 1, banco_de_clientes);

        if (feof(banco_de_clientes)){
            fclose(banco_de_clientes);
            break;
        }
    } 
}