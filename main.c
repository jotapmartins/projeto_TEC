#include <stdio.h>
#include <string.h>

void menuPrincipal() {
    printf("\n");
    printf("Qual o problema do seu celular? \n");
    printf("\n");
    printf("1. Vidro frontal quebrado.\n");
    printf("2. Vidro traseiro quebrado.\n");
    printf("3. Problema com a bateria.\n");
    printf("4. Câmera quebrada.\n");
    printf("5. Placa queimada.\n");
    printf("6. Outros...\n");
    printf("7. Sair\n");
}

void respostaOpcao(int opcao) {
    switch (opcao) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            printf("\nPor favor, informe qual o modelo do seu aparelho.\n");
            break;
        case 7:
            printf("\nSaindo do programa...\n");
            break;
        default:
            printf("\nOpção inválida! Por favor, escolha uma opção válida do menu.\n");
            break;
    }
}

void cadastrarUsuario() {
    char cpf[12];
    char senha[11];
    FILE *BD;

    BD = fopen("usuario.txt", "a");
    if (BD == NULL) {
        printf("Erro ao abrir o arquivo!!!\n");
        return;
    }

    printf("Digite o CPF para cadastro (somente números): ");
    scanf("%11s", cpf);
    printf("Digite a senha para cadastro: ");
    scanf("%10s", senha);

    fprintf(BD, "%s %s\n", cpf, senha);
    fclose(BD);
    printf("Cadastro realizado com sucesso!\n");
}

int efetuarLogin() {
    char cpf[12];
    char senha[11];
    char cpfCadastrado[12];
    char senhaCadastrada[20];
    FILE *BD;

    BD = fopen("usuario.txt", "r");
    if (BD == NULL) {
        printf("Sem usuários cadastrados!!!\n");
        return 0;
    }

    printf("Digite o CPF para login: ");
    scanf("%11s", cpf);
    printf("Digite a senha para login: ");
    scanf("%10s", senha);

    while (fscanf(BD, "%s %s", cpfCadastrado, senhaCadastrada) != EOF) {
        if (strcmp(cpf, cpfCadastrado) == 0 && strcmp(senha, senhaCadastrada) == 0) {
            printf("Login efetuado com sucesso!\n");
            fclose(BD);
            return 1;
        }
    }

    fclose(BD);
    printf("CPF ou senha incorretos!\n");
    return 0;
}

int executarPrograma() {
    int opcao;

    do {
        menuPrincipal();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        respostaOpcao(opcao);

        if (opcao == 7) {
            return 0;
        }

    } while (1);
}

int main(void) {
    int opcao;

    do {
        printf("\nBem-vindo à assistência técnica!\n");
        printf("1 - Cadastrar usuário\n");
        printf("2 - Fazer login\n");
        printf("Escolha uma opção para entrar: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrarUsuario();
        } else if (opcao == 2) {
            if (efetuarLogin()) {
                if (executarPrograma() == 0) {
                    break;
                }
            }
        } else {
            printf("Opção inválida.\n");
        }

    } while (1);

    return 0;
}
