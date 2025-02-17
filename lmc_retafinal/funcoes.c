#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//fun��es p/ checar se tem numero ou letra onde n�o deve
int contemNumeros(const char *str){
    char numeros[] = "0123456789";
    for(int i = 0; str[i] != '\0'; i++){
        for(int j = 0; numeros[j] != '\0'; j++){
            if(str[i] == numeros[j]){
                return 1; //encontrou numero!
            }
        }
    }
    return 0;
}

int contemLetras(const char *str){
    char letras[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; str[i] != '\0'; i++){
        for(int j = 0; letras[j] != '\0'; j++){
            if(str[i] == letras[j]){
                return 1; //encontrou letra!
            }
        }
    }
    return 0;
}

//menus
void separarMenus(){
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
    printf("|               [0] - Criar arquivos iniciais            |\n");
    printf("|               [1] - Gerenciar clientes                 |\n");
    printf("|               [2] - Gerenciar ve�culos                 |\n");
    printf("|               [3] - Gerenciar funcion�rios             |\n");
    printf("|               [4] - Gerenciar entregas                 |\n");
    printf("|               [5] - Voltar                             |\n");
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

// arquivos iniciais
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

//Funcoes dos veiculos
void criar_veiculo(){
    char tipo[50];
    int carga, disponivel, id_veic;
    //recolhendo as informa��es do usu�rio

    printf("Digite o tipo e carga do veiculo (em KG) a ser registrado, respectivamente:\n");
    scanf("%s %d", &tipo, &carga);

    getchar();
    printf("O ve�culo est� dispon�vel? Digite '0' para SIM e '1' para N�O?\n");
    scanf("%d", &disponivel);

    //montagem da vari�vel tipo veiculo
    //tipo e carga
    struct Veiculo veiculo;
    strcpy(veiculo.tipo, tipo);
    veiculo.carga = carga;
    veiculo.disponivel = disponivel;

    //associando ID ao veiculo criado e atualizando arquivo de mem�ria para usos futuros
    FILE *arquivo_id = fopen("mem_veic.dat","rb");
    fread(&id_veic, sizeof(int), 1, arquivo_id);
    veiculo.id = id_veic;

    atualizar_id("mem_veic.dat");

    //armazenando a vari�vel
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


// Fun��o para armazenar os veiculos do banco de dados em um vetor de structs para entao fazer o necess�rio
struct Veiculo veiculos[1000];
int tamanhoV = 0;
void retirar_veiculos() {
    FILE *banco_de_veiculos = fopen("veiculos.dat", "rb");
    if (banco_de_veiculos == NULL) {
        printf("Erro ao abrir o arquivo de veiculos\n");
        exit(1);
    }

    while(1){
        fseek(banco_de_veiculos, sizeof(struct Veiculo) * tamanhoV, SEEK_SET);
        fread(&veiculos[tamanhoV], sizeof(struct Veiculo), 1, banco_de_veiculos);

        if(feof(banco_de_veiculos)){
            fclose(banco_de_veiculos);
            break;
        }
        tamanhoV++;
    }
    fclose(banco_de_veiculos);
}

void view_veiculos(){
    retirar_veiculos();
    printf("Esses sao os veiculos cadastrados: \n");
    for(int k = 0; k < tamanhoV; k++){
        printf("ID: %d - TIPO: %s - CARGA: %d - DISPONIBILIDADE: %d\n", veiculos[k].id, veiculos[k].tipo, veiculos[k].carga, veiculos[k].disponivel);
    }
}

//colocando os veiculos modificados de volta no banco de dados
void armazenar_veiculos() {
    FILE *banco_de_veiculos = fopen("veiculos.dat", "wb");
    if (banco_de_veiculos == NULL) {
        printf("Erro ao abrir o arquivo de veiculos\n");
        exit(1);
    }

    for (int j = 0; j < tamanhoV; j++) {
        fwrite(&veiculos[j], sizeof(struct Veiculo), 1, banco_de_veiculos);
    }
    fclose(banco_de_veiculos);
    printf("Mudan�a no banco de veiculos concluida!\n");
}

void delVeiculo() {
    view_veiculos();
    printf("Digite o ID do veiculo que deseja deletar: \n");
    int idProcurado;
    scanf("%d", &idProcurado);
    for (int k = 0; k < tamanhoV; k++) {
        if (idProcurado == veiculos[k].id) {
            for (int j = k; j < tamanhoV-1; j++){
                veiculos[j] = veiculos[j + 1];
            }
            tamanhoV--;
            break;
        }
    }
    printf("Veiculo deletado com sucesso!\n");
    armazenar_veiculos();
}

void editVeiculo(){
    view_veiculos();
    int idProcuradoV, encontrado = 0;
    printf("Digite o ID do veículo que deseja editar: \n");
    scanf("%d", &idProcuradoV);
    fflush(stdin);
    for(int k = 0; k < tamanhoV; k++){
        if(idProcuradoV == veiculos[k].id){
            encontrado = 1;
            do{
                printf("Digite o novo tipo do veículo: \n");
                fgets(veiculos[k].tipo, 50, stdin);
                fflush(stdin);
                while(contemNumeros(veiculos[k].tipo) == 1){
                    printf("O tipo do veículo não pode conter números! Digite novamente: \n");
                    fgets(veiculos[k].tipo, 50, stdin);
                }
            }while(veiculos[k].tipo[0] == '\0');

            do{
                printf("Digite a nova capacidade de carga do veículo: \n");
                char input[10];
                fgets(input, sizeof(input), stdin);
                fflush(stdin);
                input[strcspn(input, "\n")] = '\0';
                while(contemLetras(input) == 1){
                    printf("A capacidade de carga não pode conter letras! Digite novamente: \n");
                    fgets(input, sizeof(input), stdin);
                }
                veiculos[k].carga = atoi(input);
                if(veiculos[k].carga <= 0){
                    printf("A capacidade de carga não pode ser negativa ou zero! Digite novamente: \n");
                }
            }while(veiculos[k].carga <= 0 || veiculos[k].carga == '\0');

            do{
                printf("Digite a nova disponibilidade do veículo: \n");
                char input[10];
                fgets(input, sizeof(input), stdin);
                fflush(stdin);
                input[strcspn(input, "\n")] = '\0';
                while(contemLetras(input) == 1){
                    printf("A disponibilidade do veículo é classificada como número! Digite novamente: ");
                    fgets(input, sizeof(input), stdin);
                }
                veiculos[k].disponivel = atoi(input);
                if(veiculos[k].disponivel != 1 && veiculos[k].disponivel != 0){
                    printf("Escolha uma opção válida!\n");
                }
            }while(veiculos[k].disponivel != 1 && veiculos[k].disponivel != 0);
            armazenar_veiculos();
            }
        }
        if(!encontrado){
            printf("Veiculo não encontrado!");
        }
    }
//FUN��ES FUNCIONARIO
void criar_funcionario(){
    char nome[50];
    int id_func;

    printf("Digite o nome completo do Funcion�rio: \n");
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
        printf("Erro ao armazenar funcion�rio");
    } else {
        fwrite(&novo_funcionario, sizeof(novo_funcionario), 1, banco_de_funcionarios);
        printf("Funcionario de ID: %d\nNome: %s\nArmazenado com sucesso\n", novo_funcionario.id, novo_funcionario.nome);
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

struct Funcionario funcionarios[1000];
int tamanhoF = 0;
void retirar_funcionario() {
    FILE *banco_de_funcionarios = fopen("funcionarios.dat", "rb");
    if (banco_de_funcionarios == NULL) {
        printf("Erro ao abrir o arquivo de funcionarios\n");
        exit(1);
    }

    while(1){
        fseek(banco_de_funcionarios, sizeof(struct Funcionario) * tamanhoF, SEEK_SET);
        fread(&funcionarios[tamanhoF], sizeof(struct Funcionario), 1, banco_de_funcionarios);

        if(feof(banco_de_funcionarios)){
            fclose(banco_de_funcionarios);
            break;
        }
        tamanhoF++;
    }
    fclose(banco_de_funcionarios);
}

void view_funcionarios(){
    retirar_funcionario();
    printf("Esses sao os funcionarios cadastrados: \n");
    for(int k = 0; k < tamanhoF; k++){
        printf("ID: %d - NOME COMPLETO: %s\n", funcionarios[k].id, funcionarios[k].nome);
    }
}

//colocando os funcionarios modificados de volta no banco de dados
void armazenar_funcionarios() {
    FILE *banco_de_funcionarios = fopen("funcionarios.dat", "wb");
    if (banco_de_funcionarios == NULL) {
        printf("Erro ao abrir o arquivo de veiculos\n");
        exit(1);
    }

    for (int j = 0; j < tamanhoF; j++) {
        fwrite(&funcionarios[j], sizeof(struct Funcionario), 1, banco_de_funcionarios);
    }
    fclose(banco_de_funcionarios);
    printf("Mudan�a no banco de funcionarios concluida!\n");
}

void delFuncionario() {
    view_funcionarios();
    printf("Digite o ID do funcionario que deseja deletar: \n");
    int idProcurado;
    scanf("%d", &idProcurado);
    for (int k = 0; k < tamanhoF; k++) {
        if (idProcurado == funcionarios[k].id) {
            for (int j = k; j < tamanhoF-1; j++){
                funcionarios[j] = funcionarios[j + 1];
            }
            tamanhoF--;
            printf("Funcionario deletado com sucesso!\n");
            break;
        }
    }
    armazenar_funcionarios();
}

void editFuncionario(){
    view_funcionarios();
    int idProcuradoF, encontrado = 0;
    printf("Digite o ID do funcionário que deseja editar: ");
    scanf("%d", &idProcuradoF);
    fflush(stdin);
    for(int k = 0; k < tamanhoF; k++){
        if(idProcuradoF == funcionarios[k].id){
            encontrado = 1;
            do{
                printf("Digite o novo nome do funcionário: \n");
                fgets(funcionarios[k].nome, 50, stdin);
                fflush(stdin);
                while(contemNumeros(funcionarios[k].nome) == 1){
                    printf("O nome do funcionário não pode conter números! Digite novamente: \n");
                    fgets(funcionarios[k].nome, 50, stdin);
                }
            }while(funcionarios[k].nome[0] == '\0');
        }
    }
    armazenar_funcionarios();
    if(!encontrado){
        printf("Funcionario não encontrado!");
    }
}
//FUN��ES CLIENTES
void criar_cliente(){
    int id_cliente, servico, numero;
    char nome[50], estado[20], cidade[20], bairro[20], rua[20];

    printf("Digite o nome completo do cliente: \n");
    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);

    printf("Digite o ESTADO onde o cliente reside: \n");
    fflush(stdin);
    fgets(estado, sizeof(estado), stdin);

    printf("Digite a CIDADE onde o cliente reside: \n");
    fflush(stdin);
    fgets(cidade, sizeof(cidade), stdin);

    printf("Digite o BAIRRO onde o cliente reside: \n");
    fflush(stdin);
    fgets(bairro, sizeof(bairro), stdin);

    printf("Digite a RUA onde o cliente reside: \n");
    fflush(stdin);
    fgets(rua, sizeof(rua), stdin);

    printf("Digite o NUMERO da casa do cliente: \n");
    scanf("%d", &numero);

    printf("Qual � o tipo do servico do cliente? economico(0), padrao(1) ou premium(2)? \n");
    scanf("%d", &servico);

    FILE *arquivo = fopen("mem_cliente.dat", "rb");
    fread(&id_cliente, sizeof(int), 1, arquivo);
    atualizar_id("mem_cliente.dat");
    fclose(arquivo);


    struct Cliente novo_cliente;
    novo_cliente.id = id_cliente;
    novo_cliente.servico = servico;
    novo_cliente.numero = numero;
    strcpy(novo_cliente.nome, nome);
    strcpy(novo_cliente.estado, estado);
    strcpy(novo_cliente.cidade, cidade);
    strcpy(novo_cliente.bairro, bairro);
    strcpy(novo_cliente.rua, rua);

    FILE *banco_de_clientes = fopen("clientes.dat", "ab");
    if (banco_de_clientes == NULL){
        printf("Falha em armazenar o cliente.\n");
    } else {
        fwrite(&novo_cliente, sizeof(struct Cliente), 1, banco_de_clientes);
        printf("Cliente ID: %d\nNome: %s\nEndereco: %s, %s, %s, %s, %d\nServico: %d\nArmazenado com sucesso.\n", novo_cliente.id, novo_cliente.nome, novo_cliente.estado, novo_cliente.cidade, novo_cliente.bairro, novo_cliente.rua, novo_cliente.numero, novo_cliente.servico);
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
struct Cliente clientes[1000];
int tamanhoC = 0;
void retirar_clientes() {
    FILE *banco_de_clientes = fopen("clientes.dat", "rb");
    if (banco_de_clientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes\n");
        exit(1);
    }

    while(1){
        fseek(banco_de_clientes, sizeof(struct Cliente) * tamanhoC, SEEK_SET);
        fread(&clientes[tamanhoC], sizeof(struct Cliente), 1, banco_de_clientes);

        if(feof(banco_de_clientes)){
            fclose(banco_de_clientes);
            break;
        }
        tamanhoC++;
    }
    fclose(banco_de_clientes);
}

void view_clientes(){
    retirar_clientes();
    printf("Esses sao os clientes cadastrados: \n");
    for(int k = 0; k < tamanhoC; k++){
        printf("ID: %d - NOME COMPLETO: %s - ESTADO: %s - CIDADE: %s - BAIRRO: %s - RUA: %s - NUMERO: %d - SERVICO: %d\n", clientes[k].id, clientes[k].nome, clientes[k].estado, clientes[k].cidade, clientes[k].bairro, clientes[k].rua, clientes[k].numero, clientes[k].servico);
    }
}

//colocando os clientes modificados de volta no banco de dados
void armazenar_clientes() {
    FILE *banco_de_clientes = fopen("clientes.dat", "wb");
    if (banco_de_clientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes\n");
        exit(1);
    }

    for (int j = 0; j < tamanhoC; j++) {
        fwrite(&clientes[j], sizeof(struct Cliente), 1, banco_de_clientes);
    }
    fclose(banco_de_clientes);
    printf("Mudan�a no banco de clientes concluida!\n");
}

void delCliente() {
    view_clientes();
    printf("Digite o ID do cliente que deseja deletar: \n");
    int idProcurado;
    scanf("%d", &idProcurado);
    for (int k = 0; k < tamanhoC; k++) {
        if (idProcurado == clientes[k].id) {
            for (int j = k; j < tamanhoC-1; j++){
                clientes[j] = clientes[j + 1];
            }
            tamanhoC--;
            printf("Cliente deletado com sucesso!\n");
            break;
        }
    }
    armazenar_clientes();
}

void editCliente(){
    view_clientes();
    int idProcurado, encontrado = 0;
    printf("Digite o ID do cliente que deseja editar: ");
    fflush(stdin);
    scanf("%d", &idProcurado);
    for(int k = 0; k < tamanhoC; k++){
        if (idProcurado == clientes[k].id){
                encontrado = 1;
                do{
                    printf("Digite o novo nome do cliente: \n");
                    fflush(stdin);
                    fgets(clientes[k].nome, 50, stdin);
                    while(contemNumeros(clientes[k].nome) == 1){
                        printf("O nome do cliente não pode conter números! Digite novamente: \n");
                        fgets(clientes[k].nome, 50, stdin);
                    }
                }while(clientes[k].nome[0] == '\0');

                do{
                    printf("Digite o novo estado do cliente: \n");
                    fflush(stdin);
                    fgets(clientes[k].estado, 20, stdin);
                    while(contemNumeros(clientes[k].estado) == 1){
                        printf("O estado do cliente não pode conter números! Digite novamente: \n");
                        fgets(clientes[k].estado, 20, stdin);
                        }
                    }while ((clientes[k].estado[0] == '\0'));

                do{
                    printf("Digite a nova cidade do cliente: \n");
                    fflush(stdin);
                    fgets(clientes[k].cidade, 20, stdin);
                    while(contemNumeros(clientes[k].cidade) == 1){
                        printf("O nome da cidade não pode conter números! Digite novamente: \n");
                        fgets(clientes[k].cidade, 20, stdin);
                    }
                }while(clientes[k].cidade[0] == '\0' || clientes[k].cidade[0] == '\n');

                do{
                    printf("Digite o novo bairro do cliente: \n");
                    fflush(stdin);
                    fgets(clientes[k].bairro, 20, stdin);
                    while(contemNumeros(clientes[k].bairro) == 1){
                        printf("O nome do bairro não pode conter números! Digite novamente: \n");
                        fgets(clientes[k].bairro, 20, stdin);
                    }
                }while(clientes[k].bairro[0] == '\0' || clientes[k].bairro[0] == '\n');

                do{
                    printf("Digite a nova rua do cliente: \n");
                    fflush(stdin);
                    fgets(clientes[k].rua, 20, stdin);
                    while(clientes[k].rua[0] == '\n'){
                        printf("O nome da rua não pode ser vazio! Digite novamente: \n");
                        fgets(clientes[k].rua, 20, stdin);
                    }
                }while(clientes[k].rua[0] == '\0' || clientes[k].rua[0] == '\n');

                do{
                    printf("Digite o novo número da rua do cliente: \n");
                    fflush(stdin);
                    char input[10];
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = '\0';
                    while(contemLetras(input) == 1){
                        printf("O número da rua não pode conter letras! Digite novamente: \n");
                        fgets(input, sizeof(input), stdin);
                    }
                    clientes[k].numero = atoi(input);
                    if(clientes[k].numero <= 0){
                        printf("O número da rua não pode ser negativo ou zero! Digite novamente: \n");
                    }
                }while(clientes[k].numero <= 0 || clientes[k].numero == '\0');

                do{
                    printf("Digite o novo serviço do cliente: \n");
                    char input[10];
                    fflush(stdin);
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = '\0';
                    if (strlen(input) == 0) {
                        printf("Entrada vazia! Digite um número válido (0, 1 ou 2).\n");
                        fgets(input, sizeof(input), stdin);
                    }
                    while(contemLetras(input) == 1){
                        printf("O tipo de serviço é classificado como número! Digite novamente: \n");
                        fgets(input, sizeof(input), stdin);
                    }

                    clientes[k].servico = atoi(input);
                    if(clientes[k].servico != 2 && clientes[k].servico != 1 && clientes[k].servico != 0){
                        printf("Escolha uma opção válida!");
                    }
                }while(clientes[k].servico != 2 && clientes[k].servico != 1 && clientes[k].servico != 0);
                armazenar_clientes();
            }
        }
        if(!encontrado){
            printf("Cliente não encontrado");
        }

    }
//fun��es quanto a entregas:
void planejar_entrega() {
    int id_entrega, tempo_estimado, id_cliente;
    char origem[20];

    //recolhendo informa��es do usu�rio
    printf("Qual � o ID do cliente que vai receber a entrega?\n");
    scanf("%d", &id_cliente);

    printf("Qual � a CIDADE-SEDE respons�vel pela entrega?\n");
    fflush(stdin);
    fgets(origem, sizeof(origem), stdin);

    printf("Em HORAS, qual � o tempo de entrega estimado da entrega?\n");
    scanf("%d", &tempo_estimado);

    //definindo ID da entrega;
    FILE *memoria_id = fopen("mem_entreg.dat", "rb");
    fread(&id_entrega, sizeof(int), 1, memoria_id);
    atualizar_id("mem_entreg.dat");
    fclose(memoria_id);

    //criando variavel tipo entrega etapa 1 e alocando valores a seus atributos
    struct Entrega_e1 nova_entrega_planejada;

    //id
    nova_entrega_planejada. id = id_entrega;
    //cliente
    nova_entrega_planejada.cliente = encontrar_cliente(id_cliente);
    //tempo_estimado
    nova_entrega_planejada.tempo_estimado = tempo_estimado;
    //origem e destino
    strcpy(nova_entrega_planejada.origem, origem);
    strcpy(nova_entrega_planejada.destino, nova_entrega_planejada.cliente.cidade);

    //armazenando nova entrega planejada em arquivo
    FILE *arquivo = fopen("entregas_e1.dat", "ab");

    if (arquivo == NULL){
        printf("Erro ao armazenar dados da entrega.");
    } else {
        fwrite(&nova_entrega_planejada, sizeof(nova_entrega_planejada), 1, arquivo);
        printf("ID da entrega: %d\nTempo estimado: %dh\nOrigem: %s\nDestino: %s\nEntrega planejada armazenada com sucesso.\n", nova_entrega_planejada.id, nova_entrega_planejada.tempo_estimado, nova_entrega_planejada.origem, nova_entrega_planejada.destino);
    }
    fclose(arquivo);

}


struct Entrega_e1 encontrar_entrega_planejada(int id_entrega) {
    FILE *banco_de_entregas_planejadas = fopen("entregas_e1.dat", "rb");
    struct Entrega_e1 entrega_planejada;

    fread(&entrega_planejada, sizeof(struct Entrega_e1), 1, banco_de_entregas_planejadas);

    int i = 0;

    while (1) {
        if (id_entrega == entrega_planejada.id) {
            fclose(banco_de_entregas_planejadas);
            return entrega_planejada;
        }


        i++;
        fseek(banco_de_entregas_planejadas, sizeof(struct Entrega_e1) * i, SEEK_SET);
        fread(&entrega_planejada, sizeof(struct Entrega_e1), 1, banco_de_entregas_planejadas);

        if (feof(banco_de_entregas_planejadas)){
            fclose(banco_de_entregas_planejadas);
            break;
        }
    }
}

//funcao deletar a entrega planejada
struct Entrega_e1 vetor_entregas_planejadas[1000];
int tamanhoE = 0;
void retirar_entregasPlanejadas() {
    FILE *banco_de_entregas_planejadas = fopen("entregas_e1.dat", "rb");
    if (banco_de_entregas_planejadas == NULL) {
        printf("Erro ao abrir o arquivo de entregas planejadas\n");
        exit(1);
    }

    while(1){
        fseek(banco_de_entregas_planejadas, sizeof(struct Entrega_e1) * tamanhoE, SEEK_SET);
        fread(&vetor_entregas_planejadas[tamanhoE], sizeof(struct Entrega_e1), 1, banco_de_entregas_planejadas);

        if(feof(banco_de_entregas_planejadas)){
            fclose(banco_de_entregas_planejadas);
            break;
        }
        tamanhoE++;
    }
    fclose(banco_de_entregas_planejadas);
}

//colocando as entregas planejadas modificadas de volta no banco de dados
void armazenar_entregasPlanejadas() {
    FILE *banco_de_entregas_planejadas = fopen("entregas_e1.dat", "wb");
    if (banco_de_entregas_planejadas == NULL) {
        printf("Erro ao abrir o arquivo de entregas planejadas\n");
        exit(1);
    }

    for (int j = 0; j < tamanhoE; j++) {
        fwrite(&vetor_entregas_planejadas[j], sizeof(struct Entrega_e1), 1, banco_de_entregas_planejadas);
    }
    fclose(banco_de_entregas_planejadas);
}

void delEntregasPlanejada(int idProcurado) {
    //recebe o id da entrega realizada equivalente ao id planejado para retirar o planejado
    for (int k = 0; k < tamanhoE; k++) {
        if (idProcurado == vetor_entregas_planejadas[k].id) {
            for (int j = k; j < tamanhoE-1; j++){
                vetor_entregas_planejadas[j] = vetor_entregas_planejadas[j + 1];
            }
            tamanhoE--;
            break;
        }
    }
    armazenar_entregasPlanejadas();
}

//Funcao deletar a entrega ja realizada
struct Entrega_e2 vetor_entregas_realizadas[1000];
int tamanhoE2 = 0;
void retirar_entregasRealizadas() {
    FILE *banco_de_entregas_realizadas = fopen("entregas_realizadas.dat", "rb");
    if (banco_de_entregas_realizadas == NULL) {
        printf("Erro ao abrir o arquivo de entregas realizadas\n");
        exit(1);
    }

    while(1){
        fseek(banco_de_entregas_realizadas, sizeof(struct Entrega_e2) * tamanhoE2, SEEK_SET);
        fread(&vetor_entregas_realizadas[tamanhoE2], sizeof(struct Entrega_e2), 1, banco_de_entregas_realizadas);

        if(feof(banco_de_entregas_realizadas)){
            fclose(banco_de_entregas_realizadas);
            break;
        }
        tamanhoE2++;
    }
    fclose(banco_de_entregas_realizadas);
}

//colocando as entregas realizadas modificadas de volta no banco de dados
void armazenar_entregasRealizadas() {
    FILE *banco_de_entregas_realizadas = fopen("entregas_realizadas.dat", "wb");
    if (banco_de_entregas_realizadas == NULL) {
        printf("Erro ao abrir o arquivo de entregas realizadas\n");
        exit(1);
    }

    for (int j = 0; j < tamanhoE2; j++) {
        fwrite(&vetor_entregas_realizadas[j], sizeof(struct Entrega_e2), 1, banco_de_entregas_realizadas);
    }
    fclose(banco_de_entregas_realizadas);
    printf("Mudança no banco de entregas realizadas concluida!\n");
}

void delEntregasRealizada(int id_DelEntrega_realizada) {
    retirar_entregasRealizadas();
    for (int k = 0; k < tamanhoE2; k++) {
        if (id_DelEntrega_realizada == vetor_entregas_realizadas[k].entrega_e1.id) {
            for (int j = k; j < tamanhoE2-1; j++){
                vetor_entregas_realizadas[j] = vetor_entregas_realizadas[j + 1];
            }
            tamanhoE2--;
            printf("Entrega realizada deletada com sucesso!\n");
            break;
        }
    }
    armazenar_entregasRealizadas();
}

void editEntregasRealizadas(){
    retirar_entregasRealizadas();
    int idProcuradoE, encontrado = 0;
    printf("Digite o ID da entrega que deseja editar: ");
    fflush(stdin);
    scanf("%d", &idProcuradoE);
    for(int k = 0; k < tamanhoE2; k++){
        if(idProcuradoE == vetor_entregas_realizadas[k].entrega_e1.id){
            encontrado = 1;
            do{
                printf("Digite a nova origem da entrega: \n");
                fflush(stdin);
                fgets(vetor_entregas_realizadas[k].entrega_e1.origem, 20, stdin);
                while(contemNumeros(vetor_entregas_realizadas[k].entrega_e1.origem) == 1){
                    printf("A origem da entrega não pode conter números! Digite novamente: \n");
                    fgets(vetor_entregas_realizadas[k].entrega_e1.origem, 20, stdin);
                }
            }while(vetor_entregas_realizadas[k].entrega_e1.origem[0] == '\0');

            do{
                printf("Digite o novo destino da entrega: \n");
                fflush(stdin);
                fgets(vetor_entregas_realizadas[k].entrega_e1.destino, 20, stdin);
                while(contemNumeros(vetor_entregas_realizadas[k].entrega_e1.destino) == 1){
                printf("O destino da entrega não pode conter números! Digite novamente: \n");
                    fgets(vetor_entregas_realizadas[k].entrega_e1.destino, 20, stdin);
                }
            }while(vetor_entregas_realizadas[k].entrega_e1.destino[0] == '\0');

            do{
                printf("Digite o novo tempo estimado da entrega: \n");
                char input[10];
                fflush(stdin);
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                while(contemLetras(input) == 1){
                    printf("O tempo estimado da entrega não pode conter letras! Digite novamente: \n");
                    fgets(input, sizeof(input), stdin);
                }
                vetor_entregas_realizadas[k].entrega_e1.tempo_estimado = atoi(input);
                if(vetor_entregas_realizadas[k].entrega_e1.tempo_estimado <= 0){
                    printf("O tempo estimado da entrega não pode ser negativo ou zero! Digite novamente: \n");
                }while(vetor_entregas_realizadas[k].entrega_e1.tempo_estimado <= 0);
            }while(vetor_entregas_realizadas[k].entrega_e1.tempo_estimado <= 0);
            armazenar_entregasRealizadas();
        }
    }
    if(!encontrado){
        printf("Entrega não encontrada!");
    }
}

void editEntregasPlanejadas(){
    retirar_entregasPlanejadas();
    int idProcuradoE, encontrado = 0;
    printf("Digite o ID da entrega que deseja editar: ");
    fflush(stdin);
    scanf("%d", &idProcuradoE);
    for(int k = 0; k < tamanhoE; k++){
        if(idProcuradoE == vetor_entregas_planejadas[k].id){
            encontrado = 1;
            do{
                printf("Digite a nova origem da entrega: \n");
                fflush(stdin);
                fgets(vetor_entregas_planejadas[k].origem, 20, stdin);
                while(contemNumeros(vetor_entregas_planejadas[k].origem) == 1){
                    printf("A origem da entrega não pode conter números! Digite novamente: \n");
                    fgets(vetor_entregas_planejadas[k].origem, 20, stdin);
                }
            }while(vetor_entregas_planejadas[k].origem[0] == '\0');

            do{
                printf("Digite o novo destino da entrega: \n");
                fflush(stdin);
                fgets(vetor_entregas_planejadas[k].destino, 20, stdin);
                while(contemNumeros(vetor_entregas_planejadas[k].destino) == 1){
                    printf("O destino da entrega não pode conter números! Digite novamente: \n");
                    fgets(vetor_entregas_planejadas[k].destino, 20, stdin);
                }
            }while(vetor_entregas_planejadas[k].destino[0] == '\0');

            do{
                printf("Digite o novo tempo estimado da entrega: \n");
                char input[10];
                fflush(stdin);
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                while(contemLetras(input) == 1){
                    printf("O tempo estimado da entrega não pode conter letras! Digite novamente: \n");
                    fgets(input, sizeof(input), stdin);
                }
                vetor_entregas_planejadas[k].tempo_estimado = atoi(input);
                if(vetor_entregas_planejadas[k].tempo_estimado <= 0){
                    printf("O tempo estimado da entrega não pode ser negativo ou zero! Digite novamente: \n");
                }
            }while(vetor_entregas_planejadas[k].tempo_estimado <= 0 && vetor_entregas_planejadas[k].tempo_estimado == '\0');
            armazenar_entregasPlanejadas();
        }
    }
    if(!encontrado){
        printf("Entrega não encontrada!");
    }
}

void realizar_entrega(int id_entrega_planejada) {
    int id_veiculo = -1, id_funcionario;

    //recolhendo informa��es do usu�rio

    printf("Qual � o ID do funcionario que vai realizar a entrega?\n");
    scanf("%d", &id_funcionario);

    //recolhendo o primeiro ve�culo dispon�vel
    int num;

    FILE *arquivo = fopen("mem_veic.dat", "rb");
    fread(&num, sizeof(int), 1, arquivo);
    fclose(arquivo);

    for (int i = 1; i < num; i++) {
        struct Veiculo veiculo = encontrar_veiculo(i);

        if (veiculo.disponivel == 0) {
            id_veiculo = veiculo.id;
            //EDITAR: MUDAR O STATUS DO VEICULO PARA OCUPADO
            break;
        }
    }

    //definindo se a entrega pode ser realizada
    if (id_veiculo == -1) {
        printf("Sem veiculos disponiveis. Impossivel realizar entrega");
        return;
    }

    //criando variavel do tipo entrega etapa 2 e alocando valores a seus atributos
    struct Entrega_e2 nova_entrega_realizada;

    //todos os dados do planejamento da entrega
    nova_entrega_realizada.entrega_e1 = encontrar_entrega_planejada(id_entrega_planejada);
    //funcionario responsavel pela entrega
    nova_entrega_realizada.funcionario = encontrar_funcionario(id_funcionario);
    //veiculo utilizado para a entrega
    nova_entrega_realizada.veiculo = encontrar_veiculo(id_veiculo);

    //armazenandando entrega realizada em arquivo
    FILE *arquivo_ = fopen("entregas_realizadas.dat", "ab");

    if (arquivo_ == NULL){
        printf("Erro ao armazenar dados da entrega.");
    } else {
        fwrite(&nova_entrega_realizada, sizeof(nova_entrega_realizada), 1, arquivo_);
        printf("Entrega armazenada com sucesso.\nID da entrega: %d\n", nova_entrega_realizada.entrega_e1.id);
        delEntregasPlanejada(nova_entrega_realizada.entrega_e1.id);
    }
    fclose(arquivo_);
}


struct Entrega_e2 encontrar_entrega_realizada(int id_entrega_realizada) {
    FILE *banco_de_entregas_realizadas = fopen("entregas_realizadas.dat", "rb");
    struct Entrega_e2 entrega_realizada;

    fread(&entrega_realizada, sizeof(struct Entrega_e2), 1, banco_de_entregas_realizadas);

    int i = 0;

    while (1) {
        if (id_entrega_realizada == entrega_realizada.entrega_e1.id) {
            fclose(banco_de_entregas_realizadas);
            return entrega_realizada;
        }


        i++;
        fseek(banco_de_entregas_realizadas, sizeof(struct Entrega_e2) * i, SEEK_SET);
        fread(&entrega_realizada, sizeof(struct Entrega_e2), 1, banco_de_entregas_realizadas);

        if (feof(banco_de_entregas_realizadas)){
            fclose(banco_de_entregas_realizadas);
            break;
        }
    }
}


void gerar_relatorio(int id_entrega_realizada) {
    struct Entrega_e2 entrega_realizada = encontrar_entrega_realizada(id_entrega_realizada);
    printf("ID da entrega: %d\n", entrega_realizada.entrega_e1.id);
    printf("ID do funcionario responsavel pela entrega: %d\n", entrega_realizada.funcionario.id);
    printf("ID do veiculo utilizado na entrega: %d\n", entrega_realizada.veiculo.id);
    printf("ID do cliente: %d\n", entrega_realizada.entrega_e1.cliente.id);
    printf("Origem: %s\nDestino: %s\n", entrega_realizada.entrega_e1.origem, entrega_realizada.entrega_e1.cliente.cidade);
    printf("Tempo total de entrega: %d", entrega_realizada.entrega_e1.tempo_estimado);
}