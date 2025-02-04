//Declaração das structs
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
    char endereco[80];
    int servico;
};

void criar_arquivos_iniciais();
void atualizar_id(char caminho[]);

void criar_veiculo();
struct Veiculo encontrar_veiculo(int id);

void criar_funcionario();
struct Funcionario encontrar_funcionario(int id);

void criar_cliente();
struct Cliente encontrar_cliente(int id);