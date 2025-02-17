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

int contemNumeros(const char *str);
int contemLetras(const char *str);

void separarMenus();
int menuPrincipal();
int menuUniversal();

void criar_arquivos_iniciais();
void atualizar_id(char caminho[]);

void criar_veiculo();
struct Veiculo encontrar_veiculo(int id);
void view_veiculos();
void armazenar_veiculos();
void delVeiculo();
void editVeiculo();

void criar_funcionario();
struct Funcionario encontrar_funcionario(int id);
void view_funcionarios();
void armazenar_funcionarios();
void delFuncionario();
void editFuncionario();

void criar_cliente();
struct Cliente encontrar_cliente(int id);
void view_clientes();
void armazenar_clientes();
void delCliente();
void editCliente();

void planejar_entrega();
struct Entrega_e1 encontrar_entrega_planejada(int id_entrega);
void armazenar_entregasPlanejadas();
void editEntregasPlanejadas();
void delEntregasPlanejada(int idProcurado);

void realizar_entrega(int id_entrega_planejada);
struct Entrega_e2 encontrar_entrega_realizada(int id_entrega_realizada);
void armazenar_entregasRealizadas();
void delEntregasRealizada(int id_DelEntrega_realizada);
void editEntregasRealizadas();

void gerar_relatorio(int id_entrega_realizada);