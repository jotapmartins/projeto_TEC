#include <stdio.h>
#include <string.h>

#define maxhorario 5

char horarios[maxhorario][20] = {"8:00", "10:00", "12:00", "14:00", "16:00"};
int disponivel[maxhorario] = {1, 1, 1, 1, 1};

//Salvar horário
void salvarhorario() {
    FILE *BD = fopen("horarios.txt", "w");
    if (BD != NULL) {
        for (int i = 0; i < maxhorario; i++) {
            fprintf(BD, "%d\n", disponivel[i]);
        }
        fclose(BD);
    }
}

//Cancelar agendamento
void cancelaragenda(char *cpf) {
    FILE *BD = fopen("usuario.txt", "r");
    if (BD == NULL) {
        printf("Erro ao abrir o arquivo de usuário.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(BD);
        return;
    }
    char linha[100];
    int encontrou = 0;

    printf("Agendamentos para o CPF %s:\n", cpf);
    while (fgets(linha, sizeof(linha), BD) != NULL) {
        if (strstr(linha, cpf) != NULL) {

            char *horario = strstr(linha, ", Horário: ");
            if(horario != NULL) {
                printf("%s", horario + 11);
                encontrou = 1;
            }
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    if (!encontrou) {
        printf("Nenhum agendamento encontrado para o CPF %s.\n", cpf);
    } else {
        printf("\nDigite o horário que deseja cancelar: (Ex: 8:00)");
        char horariocancel[20];
        scanf("%s", horariocancel);

        rewind(BD);
        while (fgets(linha, sizeof(linha), BD) != NULL) {
            if (strstr(linha, horariocancel) == NULL) {
                fprintf(temp, "%s", linha);
            } else {
                printf("Agendamento para %s cancelado com sucesso!\n", horariocancel);

                for (int i = 0; i < maxhorario; i++) {
                    if (strcmp(horarios[i], horariocancel) == 0) {
                        disponivel[i] = 1;
                        break;
                    }
                }
            }
        }
    }
    fclose(BD);
    fclose(temp);
    remove("usuario.txt");
    rename("temp.txt", "usuario.txt");
    salvarhorario();
}

//Consultar Agendamento
void consultaragenda(char *cpf) {
    FILE *BD = fopen("usuario.txt", "r");
    if (BD == NULL) {
        printf("Erro ao abrir o arquivo de usuários!\n");
        return;
    }

    char linha[100];
    int encontrou = 0;

    printf("Agendamentos para o CPF %s:\n", cpf);

    while (fgets(linha, sizeof(linha), BD) != NULL) {
        if (strstr(linha, cpf) != NULL) {
            // Exibe apenas o horário, sem mostrar CPF ou senha
            char *horario = strstr(linha, ", Horário: ");
            if (horario != NULL) {
                printf("%s", horario + 11);  // Pula o texto "CPF: " e exibe apenas o horário
                encontrou = 1;
            }
        }
    }

    if (!encontrou) {
        printf("Nenhum agendamento encontrado para o CPF %s.\n", cpf);
    }

    fclose(BD);
}

void carregarhorario() {
    FILE *BD = fopen("horarios.txt", "r");
    if (BD != NULL) {
        for (int i = 0; i < maxhorario; i++) {
            fscanf(BD, "%d", &disponivel[i]);
        }
        fclose(BD);
    }
}


void escolherhorario(char *cpf) {
    int opcao;

    printf("----------------------------------------------\n");
    printf("Horários disponíveis para agendamento: \n");
    for (int i = 0; i < maxhorario; i++) {
        if (disponivel[i]) {
            printf("%d. %s\n", i + 1, horarios[i]);
        }
    }

    printf("Escolha um horário: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > maxhorario || !disponivel[opcao - 1]) {
        printf("Opção inválida ou horário indisponível.\n");
        return;
    }

    disponivel[opcao - 1] = 0;
    salvarhorario();

    FILE *BD = fopen("usuario.txt", "a");
    if (BD != NULL) {
        fprintf(BD, "CPF: %s, Horário: %s\n", cpf, horarios[opcao - 1]);
        fclose(BD);
    }

    printf("Horário agendado com sucesso!Compareça na iTec Assistência Técnica no horário agendado, para realizar o serviço solicitado.\n");
}

void escolhermodelo(int *modeloValido) {
    int modelo;

    printf("-----------------------------------\n");
    printf("Qual modelo do seu iPhone? \n");
    printf("\n");
    printf("1. iPhone 11\n");
    printf("2. iPhone 12\n");
    printf("3. iPhone 13\n");
    printf("4. iPhone 14\n");
    printf("5. iPhone 15\n");
    printf("6. iPhone 16\n");

    printf("Escolha uma opção: ");
    scanf("%d", &modelo);
    printf("\n");

    switch (modelo) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            printf("Modelo do celular: iPhone %d\n", 10 + modelo);
            *modeloValido = 1;
            break;
        default:
            printf("Modelo inválido. Retornando ao menu principal.\n");
            *modeloValido = 0;
            return;
    }
}

int escolherProblema() {
    int opcao;
    printf("-----------------------------------\n");
    printf("Qual problema com seu iPhone?\n");
    printf("\n");
    printf("1. Vidro Frontal Quebrado.\n");
    printf("2. Vidro Traseiro Quebrado.\n");
    printf("3. Problema com a Bateria.\n");
    printf("4. Câmera Quebrada. \n");
    printf("5. Placa Queimada.\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 5) {
        printf("Opção inválida.\n");
        return 0;
    }

    switch (opcao) {
        case 1:
            printf("Problema com o vidro frontal.\n");
            break;
        case 2:
            printf("Problema com o vidro traseiro.\n");
            break;
        case 3:
            printf("Problema com a bateria.\n");
            break;
        case 4:
            printf("Problema com a câmera quebrada.\n");
            break;
        case 5:
            printf("Problema com a placa.\n");
            break;
    }

    return 1;
}

void menuPrincipal(char *cpf) {
    int opcao;
    int sair = 0;

    while (!sair) {
        printf("\n");
        printf("Bem-vindo ao Menu Principal.\n");
        printf("----------------------------------------\n");
        printf("1. Reportar problema no meu iPhone.\n");
        printf("2. Consultar meus Agendamentos.\n");
        printf("3. Cancelar Agendamentos.\n");
        printf("4. Sair.\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (!escolherProblema()) {
                    break;
                }

                int modeloValido = 0;
                escolhermodelo(&modeloValido);
                if (modeloValido) {
                    escolherhorario(cpf);
                }
                break;
            }
            case 2:
                consultaragenda(cpf);
                break;

            case 3:
                cancelaragenda(cpf);
                break;

            case 4:
            sair = 1;
            printf("Saindo do sistema...\n");
            break;

            default:
                printf("Opção inválida.\n");
        }
    }
}

void cadastrarUsuario() {
    char cpf[12];
    char senha[11];
    FILE *BD;

    BD = fopen("usuario.txt", "a");
    if (BD == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    printf("\n");
    printf("Digite o CPF para cadastro (somente números): ");
    scanf("%11s", cpf);
    printf("Digite a senha para cadastro: ");
    scanf("%10s", senha);

    fprintf(BD, "%s %s\n", cpf, senha);
    fclose(BD);
    printf("Cadastro realizado com sucesso!\n");
    printf("\n");
}

int efetuarLogin(char *cpf) {
    char senha[11];
    char cpfCadastrado[12];
    char senhaCadastrada[20];
    FILE *BD;

    BD = fopen("usuario.txt", "r");
    if (BD == NULL) {
        printf("Sem usuário!\n");
        return 0;
    }

    printf("\n");
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

    printf("CPF ou senha incorretos...\n");
    return 0;
}

int main(void) {
    int opcao;
    char cpf[12];
    int sair = 0;

    carregarhorario();

    while (!sair) {
        printf("Bem vindo(a) à iTEC Assistência Técnica!\n");
        printf("-----------------------------------------------\n");
        printf("1 - Cadastrar usuário\n");
        printf("2 - Fazer login\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                if (efetuarLogin(cpf)) {
                    menuPrincipal(cpf);
                }
                break;
            case 3:
                sair = 1;
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}