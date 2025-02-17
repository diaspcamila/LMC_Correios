#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int escolhaInfo;
    int escolhaOperacao;
    do {
        do {
            printf("Pressione qualquer tecla númerica para inicializar o sistema!\n");
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
                        printf("Escolha uma opção do menu de clientes: \n");
                        fgets(input, sizeof(input), stdin);
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
                                separarMenus();
                                break; //
                            default:
                                printf("Opção inválida! Tente novamente.\n");
                                break;
                        }
                    } while (escolhaOperacao != 5);

                    break;
                case 2:
                    do {
                        printf("Escolha uma opção do menu de veículos: \n");
                        fgets(input, sizeof(input), stdin);
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
                                break; //
                            default:
                                printf("Opção inválida! Tente novamente.\n");
                                break;
                        }
                    }while(escolhaOperacao != 5);

                case 5:
                    printf("Saindo...\n");
                    break;

                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (escolhaInfo != 5);
        }while (escolhaInfo != 5);
    return 0;
}
