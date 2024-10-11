#include <stdio.h>
#include <string.h>

#define maxhorario 5

char horarios[maxhorario][20] = {"8:00", "10:00", "12:00", "14:00", "16:00"};
int disponivel[maxhorario] = {1, 1, 1, 1, 1}; //1 disponivel, 0 indisponivel

void consultaragenda( char *cpf) {
    FILE *BD = fopen("usuario.txt", "r");
    char linha[100];
    int encontrou = 0;

    if (BD == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos.\n");
        return;
    }

    printf("\nAgendamentos para o CPF %s:\n", cpf);

    while (fgets(linha, sizeof(linha), BD) != NULL) {
        if (strstr(linha, cpf) != NULL) {
            printf("%s", linha);
            encontrou = 1;
        }
    }
    fclose(BD);

    if(!encontrou) {
        printf("Nenhum agendamento encontrado.\n");
    }
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

void salvarhorario() {
    FILE *BD = fopen("horarios.txt", "w");
    if (BD != NULL) {
        for (int i = 0; i < maxhorario; i++) {
            fprintf(BD, "%d\n", disponivel[i]);
        }
        fclose(BD);
    }
}

void escolherhorario(char *cpf) {
    int opcao;

    printf("\nHorários disponíveis para agendamento: \n");
    for (int i = 0; i < maxhorario; i++) {
        if (disponivel[i]) {
            printf("%d. %s\n", i + 1, horarios[i]);
        }
    }

    printf("\nEscolha um horário: ");
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

    printf("Horário agendado com sucesso!\n", horarios[opcao - 1]);
}

void escolhermodelo() {
    int modelo;

    printf("\nQual modelo do seu iPhone? \n");
    printf("1. iPhone 11\n");
    printf("1. iPhone 12\n");
    printf("1. iPhone 13\n");
    printf("1. iPhone 14\n");
    printf("1. iPhone 15\n");
    printf("1. iPhone 16\n");

    printf("Escolha uma opção: ");
    scanf("%d", &modelo);

    switch(modelo) {
        case 1:
          printf("Modelo escolhido: iPhone 11\n");
          break;
        case 2:
          printf("Modelo escolhido: iPhone 12\n");
          break;
        case 3:
          printf("Modelo escolhido: iPhone 13\n");
          break;
        case 4:
          printf("Modelo escolhido: iPhone 14\n");
          break;
        case 5:
          printf("Modelo escolhido: iPhone 15\n");
          break;
        case 6:
          printf("Modelo escolhido: iPhone 16\n");
          break;
        default:
          printf("Modelo inválido.\n");
        
    }
}

void menuPrincipal(char *cpf) {
    int opcao;
    
    printf("\n");
    printf("Bem-vindo ao Menu Principal.\n");
    printf("1. Reportar problema no seu iPhone.\n");
    printf("2. Consultar meus Agendamentos.\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            printf("\nQual problema com seu iPhone?\n");
            printf("1. Vidro Frontal Quebrado.\n");
            printf("2. Vidro Traseiro Quebrado.\n");
            printf("3. Problema com a Bateria.\n");
            printf("4. Câmera Quebrada. \n");
            printf("5. Placa Queimada.\n");

            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch(opcao) {
                case 1:
                    printf("Problema selecionado: Vidro Frontal Quebrado.\n");
                    break;
                case 2:
                    printf("Problema selecionado: Vidro Traseiro Quebrado.\n");
                    break;
                case 3:
                    printf("Problema selecionado: Problema com a Bateria.\n");
                    break;
                case 4:
                    printf("Problema selecionado: Câmera Quebrada.\n");
                    break;
                case 5:
                    printf("Problema selecionado: Placa Queimada.\n");
                    break;
                default:
                    printf("Opção inválida.\n");
                    return;
            }
          
            escolhermodelo();
            escolherhorario(cpf);
            break;

        case 2:
            consultaragenda(cpf);
            break;
        default:
            printf("Opção inválida.\n");
    }  
}

void cadastrarUsuario() {
  char cpf[12];
  char senha[11];
  FILE *BD;

  BD = fopen("usuario.txt", "a");
  if (BD == NULL) {
    printf("Erro!\n");
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
    printf("Sem usuário!\n");
    return 0;
  }

  printf("Digite o CPF para login: ");
  scanf("%11s", cpf);
  printf("Digite a senha para login: ");
  scanf("%10s", senha);

  while (fscanf(BD, "%s %s", cpfCadastrado, senhaCadastrada) != EOF) {
    if (strcmp(cpf, cpfCadastrado) == 0 &&
        strcmp(senha, senhaCadastrada) == 0) {
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

  carregarhorario();

  printf("Bem vindo(a) à iTEC Assistência Técnica! \n");
  printf("1 - Cadastrar usuário \n");
  printf("2 - Fazer login\n");
  printf("Escolha uma opção para entrar: ");
  scanf("%d", &opcao);

  if (opcao == 1) {
    cadastrarUsuario();
  } else if (opcao == 2) {
      if (efetuarLogin(cpf)) {
          menuPrincipal(cpf);
      };
  } else {
    printf("Opção invalida.\n");
  }
    
  return 0;
}