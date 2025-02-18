#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int escolhaInfo, escolhaOperacao, escolhaEntregas;
    printf("Pressione qualquer tecla númerica para inicializar o sistema!\n");
    do {
        do {
            char input[10];
            fgets(input, sizeof(input), stdin);
            while (contemLetras(input) == 1) {
                printf("A escolha da operação é feita com números! Digite novamente.\n");
                fgets(input, sizeof(input), stdin);
            }
            escolhaInfo = atoi(input);
            escolhaInfo = menuPrincipal();
            switch (escolhaInfo) {
                case 0:
                    separarMenus();
                    criar_arquivos_iniciais();
                    break;

                case 1: // Clientes
                    do {
                        fgets(input, sizeof(input), stdin);
                        fflush(stdin);
                        while (contemLetras(input) == 1) {
                            printf("A escolha da operação é feita com números! Digite novamente.\n");
                            fgets(input, sizeof(input), stdin);
                        }
                        escolhaOperacao = atoi(input);
                        escolhaOperacao = menuUniversal();

                        switch (escolhaOperacao) {
                            case 1:
                                separarMenus();
                                criar_cliente();
                                break;
                            case 2:
                                separarMenus();
                                editCliente();
                                break;
                            case 3:
                                separarMenus();
                                delCliente();
                                break;
                            case 4:
                                separarMenus();
                                view_clientes();
                                break;
                            case 5:
                                printf("Voltando...\n");
                                separarMenus();
                                break; //
                            default:
                                printf("Opção inválida! Tente novamente.\n");
                                break;
                        }
                    } while (escolhaOperacao != 5);
                    break;
                case 2: //veiculos
                    do {
                        fgets(input, sizeof(input), stdin);
                        fflush(stdin);
                        while (contemLetras(input) == 1) {
                            printf("A escolha da operação é feita com números! Digite novamente.\n");
                            fgets(input, sizeof(input), stdin);
                        }
                        escolhaOperacao = atoi(input);
                        escolhaOperacao = menuUniversal();

                        switch (escolhaOperacao) {
                            case 1:
                                separarMenus();
                                criar_veiculo();
                                break;
                            case 2:
                                separarMenus();
                                editVeiculo();
                                break;
                            case 3:
                                separarMenus();
                                delVeiculo();
                                break;
                            case 4:
                                separarMenus();
                                view_veiculos();
                                break;
                            case 5:
                                separarMenus();
                                printf("Voltando...\n");
                                break; //
                            default:
                                printf("Opção inválida! Tente novamente.\n");
                                break;
                        }
                    }while(escolhaOperacao != 5);
                    break;
                case 3: //funcionarios
                    do {
                        fgets(input, sizeof(input), stdin);
                        fflush(stdin);
                        while (contemLetras(input) == 1) {
                            printf("A escolha da operação é feita com números! Digite novamente.\n");
                            fgets(input, sizeof(input), stdin);
                        }
                        escolhaOperacao = atoi(input);
                        escolhaOperacao = menuUniversal();
                        switch (escolhaOperacao) {
                            case 1:
                                separarMenus();
                                criar_funcionario();
                                break;
                            case 2:
                                separarMenus();
                                editFuncionario();
                                break;
                            case 3:
                                separarMenus();
                                delFuncionario();
                                break;
                            case 4:
                                separarMenus();
                                view_funcionarios();
                                break;
                            case 5:
                                separarMenus();
                                printf("Voltando...\n");
                                break;
                            default:
                                printf("Opção inválida! Tente novamente.\n");
                                break;
                        }
                    }while(escolhaOperacao != 5);
                case 4:
                    do {
                        escolhaEntregas = menuEntregas();
                        switch (escolhaEntregas) {
                            case 1: // Entregas Planejadas
                                do {
                                    escolhaOperacao = menuUniversal();
                                    switch (escolhaOperacao) {
                                        case 1:
                                            separarMenus();
                                            planejar_entrega();
                                            break;
                                        case 2:
                                            separarMenus();
                                            editEntregasPlanejadas();
                                            break;
                                        case 3: {
                                            int idD;
                                            separarMenus();
                                            printf("Digite o ID da entrega que deseja deletar.\n");
                                            scanf("%d", &idD);
                                            fflush(stdin);
                                            delEntregasPlanejada(idD);
                                            break;
                                        }
                                        case 4: {
                                            int idP;
                                            separarMenus();
                                            printf("Digite o ID da entrega que deseja visualizar.\n");
                                            scanf("%d", &idP);
                                            fflush(stdin);
                                            encontrar_entrega_planejada(idP);
                                            break;
                                        }
                                        case 5:
                                            separarMenus();
                                            printf("Voltando...\n");
                                            break;
                                        default:
                                            printf("Opção inválida! Tente novamente.\n");
                                    }
                                } while (escolhaOperacao != 5);
                                break;

                            case 2: // Entregas Realizadas
                                do {
                                    escolhaOperacao = menuUniversal();
                                    switch (escolhaOperacao) {
                                        case 1:
                                            separarMenus();
                                            planejar_entrega();
                                            break;
                                        case 2:
                                            separarMenus();
                                            editEntregasRealizadas();
                                            break;
                                        case 3: {
                                            int idD;
                                            separarMenus();
                                            printf("Digite o ID da entrega que deseja deletar.\n");
                                            scanf("%d", &idD);
                                            fflush(stdin);
                                            delEntregasRealizada(idD);
                                            break;
                                        }
                                        case 4: {
                                            int idP;
                                            separarMenus();
                                            printf("Digite o ID da entrega que deseja visualizar.\n");
                                            scanf("%d", &idP);
                                            fflush(stdin);
                                            encontrar_entrega_realizada(idP);
                                            break;
                                        }
                                        case 5:
                                            separarMenus();
                                            printf("Voltando...\n");
                                            break;
                                        default:
                                            printf("Opção inválida! Tente novamente.\n");
                                    }
                                } while (escolhaOperacao != 5);
                                break;

                            case 3:
                                printf("Voltando ao menu principal...\n");
                                break;

                            default:
                                printf("Opção inválida! Tente novamente.\n");
                        }
                    } while (escolhaEntregas != 3);
                    break;

                case 5:
                    printf("Saindo...\n");
                    break;

                default:
                    printf("Opção inválida! Tente novamente.\n");
                }while(escolhaInfo != 5);
            } while (escolhaInfo != 5);
        }while (escolhaInfo != 5);
    return 0;
}
