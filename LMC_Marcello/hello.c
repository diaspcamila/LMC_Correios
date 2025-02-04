#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

void main(){
    //criar_arquivos_iniciais();
    int user_input;
    criar_cliente();
    printf("Digite o ID do cliente: \n");
    scanf("%d", &user_input);
    struct Cliente cliente = encontrar_cliente(user_input);
    printf("Nome do cliente de ID %d: %s", user_input, cliente.nome);
}