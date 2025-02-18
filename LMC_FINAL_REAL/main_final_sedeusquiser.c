#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int input_1, input_2, input_3, input_4;

    while(1){
        menuPrincipal();
        scanf("%d", &input_1);

        switch(input_1){
            //CRIAR ARQUIVOS INICIAIS
            case 0:
                criar_arquivos_iniciais();
                break;

            //CLIENTES
            case 1:
                menuUniversal();
                scanf("%d", &input_2);

                switch(input_2){
                    case 1:
                        criar_cliente();
                        break;
                    case 2:
                        editCliente();
                        break;
                    case 3:
                        delCliente();
                        break;
                    case 4:
                        view_clientes();
                        printf("Qual é o ID do cliente que deseja visualizar com mais detalhes?: ");
                        scanf("%d", &input_3);

                        struct Cliente vis_cliente = encontrar_cliente(input_3);
                        printf("ID: %d - NOME COMPLETO: %s - ESTADO: %s - CIDADE: %s - BAIRRO: %s - RUA: %s - NUMERO: %d - SERVICO: %d\n", vis_cliente.id, vis_cliente.nome, vis_cliente.estado, vis_cliente.cidade, vis_cliente.bairro, vis_cliente.rua, vis_cliente.numero, vis_cliente.servico);
                        break;
                    case 5:
                        break;
                    default:
                        printf("Operação inválida.\n");
                }
                break;

                //VEICULOS
                case 2:
                    menuUniversal();
                    scanf("%d", &input_2);

                    switch(input_2){
                        case 1:
                            criar_veiculo();
                            break;
                        case 2:
                            editVeiculo();
                            break;
                        case 3:
                            delVeiculo();
                            break;
                        case 4:
                            view_veiculos();
                            printf("Qual é o ID do veiculo que deseja visualizar com mais detalhes?: ");
                            scanf("%d", &input_3);

                            struct Veiculo vis_veiculo = encontrar_veiculo(input_3);
                            printf("ID: %d - TIPO: %s - CARGA: %d - DISPONIBILIDADE: %d\n", vis_veiculo.id, vis_veiculo.tipo, vis_veiculo.carga, vis_veiculo.disponivel);
                            break;
                        case 5:
                            break;
                        default:
                            printf("Operação inválida.\n");
                }
                break;

                //FUNCIONARIOS
                case 3:
                    menuUniversal();
                    scanf("%d", &input_2);

                    switch(input_2){
                        case 1:
                            criar_funcionario();
                            break;
                        case 2:
                            editFuncionario();
                            break;
                        case 3:
                            delFuncionario();
                            break;
                        case 4:
                            view_funcionarios();
                            printf("Qual é o ID do funcionario que deseja visualizar com mais detalhes?: ");
                            scanf("%d", &input_3);

                            struct Funcionario vis_funcionario = encontrar_funcionario(input_3);
                            printf("ID: %d - NOME COMPLETO: %s\n", vis_funcionario.id, vis_funcionario.nome);
                            break;
                        case 5:
                            break;
                        default:
                            printf("Operação inválida.\n");
                }
                break;

                //ENTREGAS
                case 4:
                    menuEntregas();
                    scanf("%d", &input_2);

                    switch(input_2){
                        case 1:
                            //ENTREGAS PLANEJADAS
                            menuUniversal();
                            scanf("%d", &input_3);

                            switch(input_3){
                                case 1:
                                    limparBuffer();
                                    planejar_entrega();
                                    break;

                                case 2:

                                    editEntregasPlanejadas();
                                    break;

                                case 3:
                                    view_entregaPlanejada();
                                    printf("Digite o ID da entrega planejada que deseja excluir.\n");
                                    scanf("%d", &input_4);
                                    delEntregasPlanejadas(input_4);
                                    break;

                                case 4:
                                    view_entregaPlanejada();

                                    printf("Digite o ID da entrega planejada que deseja visualizar com mais detalhes.\n");
                                    scanf("%d", &input_4);

                                    struct Entrega_e1 vis_entregaPlanejada = encontrar_entrega_planejada(input_4);
                                    printf("ID: %d - CLIENTE: %s - ORIGEM: %s - DESTINO: %s - TEMPO ESTIMADO: %d\n", vis_entregaPlanejada.id, vis_entregaPlanejada.cliente.nome, vis_entregaPlanejada.origem, vis_entregaPlanejada.cliente.cidade, vis_entregaPlanejada.tempo_estimado);
                                    break;

                                case 5:
                                    break;

                                default:
                                    printf("Operação inválida\n");
                            }
                            break;

                        case 2:
                            //ENTREGAS REALIZADAS
                            menuUniversal();
                            scanf("%d", &input_3);

                            switch(input_3){
                                case 1:
                                    view_entregaPlanejada();
                                    printf("Digite o ID da entrega planejada que deseja realizar.\n");
                                    scanf("%d", &input_4);
                                    limparBuffer();
                                    realizar_entrega(input_4);
                                    break;

                                case 2:
                                    view_entregaRealizada();
                                    editEntregasRealizadas();
                                    break;

                                case 3:
                                    view_entregaRealizada();
                                    printf("Digite o ID da entrega realizada que deseja excluir.\n");
                                    scanf("%d", &input_4);
                                    delEntregasRealizadas(input_4);
                                    break;

                                case 4:
                                    view_entregaRealizada();
                                    printf("Digite o ID da entrega realizada que deseja visualizar com mais detalhes.\n");
                                    scanf("%d", &input_4);

                                    struct Entrega_e2 vis_entregaRealizada = encontrar_entrega_realizada(input_4);
                                    printf("ID: %d - CLIENTE: %s - FUNCIONARIO: %s - VEICULO TIPO: %s\n", vis_entregaRealizada.entrega_e1.id, vis_entregaRealizada.entrega_e1.cliente.nome, vis_entregaRealizada.funcionario.nome, vis_entregaRealizada.veiculo.tipo);
                                    break;

                                case 5:
                                    break;

                                default:
                                    printf("Operação inválida.\n");
                            }
                            break;

                        case 3:
                            view_entregaRealizada();
                            printf("Digite o ID da entrega realizada na qual deseja gerar um relatorio.\n");
                            scanf("%d", &input_4);

                            gerar_relatorio(input_4);
                            break;
                }
                break;

            default:
                printf("Operação invalida.\n");
        }
    }
    return 0;
}
