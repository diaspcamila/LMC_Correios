#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Veiculo {
    int id;
    char tipo[50];
    int carga;
    int disponivel; // 0 - Indisponivel, 1 - Disponivel
};

struct Funcionario{
    int id;
    char nome[50];
};

struct Cliente{
    int id;
    char nome[50];
    char endereco[80];
    int servico;
};

void criar_arquivos_iniciais(){
    int ID_incial = 1;

    FILE *arquivo_id_veic = fopen("mem_veic.dat", "wb");

    fwrite(&ID_incial, sizeof(int), 1, arquivo_id_veic);

    fclose(arquivo_id_veic);
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

// Função para armazenar os veiculos do banco de dados em um vetor de structs para entao fazer o necessário
struct Veiculo veiculos[1000];
int i = 0;
void retirar_veiculos() {
    FILE *banco_de_veiculos = fopen("veiculos.dat", "rb");
    if (banco_de_veiculos == NULL) {
        printf("Erro ao abrir o arquivo de veiculos\n");
        exit(1);
    }

    while(1){
        fseek(banco_de_veiculos, sizeof(struct Veiculo) * i, SEEK_SET);
        fread(&veiculos[i], sizeof(struct Veiculo), 1, banco_de_veiculos);

        if(feof(banco_de_veiculos)){
            fclose(banco_de_veiculos);
            break;
        }
        i++;
    }
    fclose(banco_de_veiculos);
}

void view_veiculos(){
    printf("Esses sao os veiculos cadastrados: \n");
    for(int k = 0; k < i; k++){
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

    for (int j = 0; j < i; j++) {
        fwrite(&veiculos[j], sizeof(struct Veiculo), 1, banco_de_veiculos);
    }
    fclose(banco_de_veiculos);
    printf("Mudança no banco de veiculos concluida!\n");
}

void delVeiculo() {
    retirar_veiculos();
    view_veiculos();
    printf("Digite o ID do veiculo que deseja deletar: \n");
    int idProcurado;
    scanf("%d", &idProcurado);
    for (int k = 0; k < i; k++) {
        if (idProcurado == veiculos[k].id) {
            for (int j = k; j < i-1; j++){
                veiculos[j] = veiculos[j + 1];
            }
            i--;
            printf("Veiculo deletado com sucesso!\n");
            break;
        }
    }
    view_veiculos();
    armazenar_veiculos();
}

int main(){
    int escoha;
    printf("escolha 1 para criar arquivos iniciais, 2 para criar veiculo, 3 para deletar veiculo");
    scanf("%d", &escoha);
    switch(escoha){
        case 1:
        criar_arquivos_iniciais();
        break;
        case 2:
        criar_veiculo();
        break;
        case 3:
        delVeiculo();
        break;
    }
}
