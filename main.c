#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Veiculo{
    int id;
    char tipo[50];
    int carga;
    int disponivel;
};

struct Funcionario{
    int id;
    char nome[50];
};

struct Cliente{
    int id;
    char nome[50];
    char estado[20];
    char cidade[20];
    char bairro[20];
    char rua[20];
    int numero;
    int servico;
};

struct Entrega_e1 {
    int id;
    struct Cliente cliente;
    char origem[20];
    char destino[20];
    int tempo_estimado;
};

struct Entrega_e2 {
    struct Entrega_e1 entrega_e1;
    struct Veiculo veiculo;
    struct Funcionario funcionario;
};


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

    printf("Qual é o tipo do servico do cliente? economico (0), padrao(1) ou premium(2)? \n");
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


//funções quanto a entregas:
void planejar_entrega() {
    int id_entrega, tempo_estimado, id_cliente;
    char origem[20];

    //recolhendo informações do usuário
    printf("Qual é o ID do cliente que vai receber a entrega?\n");
    scanf("%d", &id_cliente);

    printf("Qual é a CIDADE da cede responsável pela entrega?\n");
    scanf("%s", &origem);

    printf("Em HORAS, qual é o tempo de entrega estimado da entrega?\n");
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
        printf("Entrega planejada armazenada com sucesso.\nID da entrega: %d\nTempo estimado: %dh\nOrigem: %s\nDestino: %s\n", nova_entrega_planejada.id, nova_entrega_planejada.tempo_estimado, nova_entrega_planejada.origem, nova_entrega_planejada.destino);
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


void realizar_entrega(int id_entrega_planejada) {
    int id_veiculo = -1, id_funcionario;

    //recolhendo informações do usuário

    printf("Qual é o ID do funcionario que vai realizar a entrega?\n");
    scanf("%d", &id_funcionario);

    //recolhendo o primeiro veículo disponível
    int num;

    FILE *arquivo = fopen("mem_veic.dat", "rb");
    fread(&num, sizeof(int), 1, arquivo);
    fclose(arquivo);

    for (int i = 0; i < num; i++) {
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
        //APAGAR ENTREGA PLANEJADA DE ID EQUIVALENTE
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


int main() {

    return 0;
}