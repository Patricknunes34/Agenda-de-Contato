#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define ALERTA(msg) MessageBox(NULL, msg, "Aviso", MB_OK | MB_ICONWARNING)
#else
    #define ALERTA(msg) system("zenity --warning --text='" msg "'")
#endif

#ifdef DEBUG
    #define CLEAR_SCREEN() 
#else
    #ifdef _WIN32
        #define CLEAR_SCREEN() system("cls")
    #else
        #define CLEAR_SCREEN() system("clear")
    #endif
#endif

void Adicionar_contato() {
    CLEAR_SCREEN();

    char nome[50];
    char telefone_digitado[20]; // Para receber o telefone sem formatação
    char telefone_formatado[20];
    char linha[100];
    int existe = 0;

    FILE *Arquivo = fopen("Agenda_Contato.txt", "r");
    if (Arquivo == NULL) {
        perror("Erro ao abrir o arquivo para verificar contato");
        return;
    }

    printf("Digite o nome do contato: ");
    scanf(" %49[^\n]", nome);

    while (fgets(linha, sizeof(linha), Arquivo)) {
        char nomeExistente[50], telefoneExistente[20];
        sscanf(linha, "Nome: %49[^,], Telefone: %19[^\n]", nomeExistente, telefoneExistente);
        if (strcmp(nomeExistente, nome) == 0) {
            ALERTA("Erro: Contato já existente na agenda!");
            existe = 1;
            break;
        } else if (strstr(nomeExistente, nome) != NULL || strstr(nome, nomeExistente) != NULL) {
            ALERTA("Aviso: Nome semelhante já existe na agenda!");
        }
    }
    fclose(Arquivo);

    if (existe) return;

    printf("Digite o telefone do contato (formato xx xxxxx-xxxx): ");
    scanf(" %19[^\n]", telefone_digitado);

    // Formatar o número de telefone
    if (strlen(telefone_digitado) >= 10) {
        snprintf(telefone_formatado, sizeof(telefone_formatado), "(%c%c) %c%c%c%c%c-%c%c%c%c",
                 telefone_digitado[0], telefone_digitado[1],
                 telefone_digitado[2], telefone_digitado[3], telefone_digitado[4],
                 telefone_digitado[5], telefone_digitado[6],
                 telefone_digitado[7], telefone_digitado[8], telefone_digitado[9],
                 (strlen(telefone_digitado) > 10) ? telefone_digitado[10] : '\0');
    } else {
        strcpy(telefone_formatado, telefone_digitado); // Se o formato for inválido, salva como digitado
        ALERTA("Aviso: Formato de telefone digitado eh invalido!");
    }

    Arquivo = fopen("Agenda_Contato.txt", "r");
    if (Arquivo == NULL) {
        perror("Erro ao abrir o arquivo para verificar telefone");
        return;
    }

    while (fgets(linha, sizeof(linha), Arquivo)) {
        char nomeExistente[50], telefoneExistente[20];
        sscanf(linha, "Nome: %49[^,], Telefone: %19[^\n]", nomeExistente, telefoneExistente);
        if (strcmp(telefoneExistente, telefone_formatado) == 0) {
            char aviso[150];
            snprintf(aviso, sizeof(aviso), "Erro: Numero ja existe na agenda! Dono: %s", nomeExistente);
            ALERTA(aviso);
            fclose(Arquivo);
            return;
        } else if (strstr(telefoneExistente, telefone_formatado) != NULL || strstr(telefone_formatado, telefoneExistente) != NULL) {
            char aviso[150];
            snprintf(aviso, sizeof(aviso), "Aviso: Numero semelhante ja existe na agenda! Dono: %s", nomeExistente);
            ALERTA(aviso);
        }
    }
    fclose(Arquivo);

    Arquivo = fopen("Agenda_Contato.txt", "a");
    if (Arquivo == NULL) {
        perror("Erro ao abrir o arquivo para adicionar contato");
        return;
    }
    fprintf(Arquivo, "Nome: %s, Telefone: %s\n", nome, telefone_formatado);
    fclose(Arquivo);

    printf("Contato adicionado com sucesso!\n");
}

void Procurar_Contato() {
    CLEAR_SCREEN();

    char nome[50];
    char linha[100];
    int encontrado = 0;

    FILE *Arquivo = fopen("Agenda_Contato.txt", "r");
    if (Arquivo == NULL) {
        perror("Erro ao abrir o arquivo para procurar contato");
        return;
    }

    printf("Digite parte do nome do contato: ");
    scanf(" %49[^\n]", nome);

    while (fgets(linha, sizeof(linha), Arquivo)) {
        char nomeExistente[50];
        sscanf(linha, "Nome: %49[^,],", nomeExistente);
        if (strstr(nomeExistente, nome) != NULL) {
            printf("Contato encontrado: %s", linha);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato nao encontrado.\n");
    }

    fclose(Arquivo);
}

void Mostrar_Contatos() {
    CLEAR_SCREEN();

    char linha[100];

    FILE *Arquivo = fopen("Agenda_Contato.txt", "r");
    if (Arquivo == NULL) {
        perror("Erro ao abrir o arquivo para mostrar contatos");
        return;
    }

    printf("==== Lista de Contatos ====\n");
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), Arquivo)) {
        printf("%s", linha);
        encontrado = 1;
    }

    if (!encontrado) {
        printf("Nenhum contato encontrado na agenda.\n");
    }

    fclose(Arquivo);
}

void Editar_Contato() {
    CLEAR_SCREEN();

    char nome[50], novoTelefone[20];
    char linha[100];
    int encontrado = 0;

    FILE *Arquivo = fopen("Agenda_Contato.txt", "r");
    FILE *Temp = fopen("Temp.txt", "w");

    if (Arquivo == NULL || Temp == NULL) {
        perror("Erro ao abrir os arquivos para edição");
        return;
    }

    printf("Digite o nome do contato para editar: ");
    scanf(" %[^\n]", nome);

    while (fgets(linha, sizeof(linha), Arquivo)) {
        char nomeExistente[50], telefoneExistente[20];
        sscanf(linha, "Nome: %[^,], Telefone: %[^\n]", nomeExistente, telefoneExistente);
        
        if (strcmp(nomeExistente, nome) == 0) {
            printf("Digite o novo telefone para %s: ", nome);
            scanf(" %[^\n]", novoTelefone);
            fprintf(Temp, "Nome: %s, Telefone: %s\n", nome, novoTelefone);
            printf("Contato atualizado com sucesso!\n");
            encontrado = 1;
        } else {
            fputs(linha, Temp);
        }
    }

    fclose(Arquivo);
    fclose(Temp);

    remove("Agenda_Contato.txt");
    rename("Temp.txt", "Agenda_Contato.txt");

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

void Excluir_contato_existente() {
    CLEAR_SCREEN();

    char linha[100];
    int encontrado = 0;
    int i = 1;
    int escolha;
    FILE *Arquivo = fopen("Agenda_Contato.txt", "r");
    FILE *Temp = fopen("Temp.txt", "w");

    if (Arquivo == NULL || Temp == NULL) {
        perror("Erro ao abrir os arquivos para exclusão");
        return;
    }

    printf("==== Lista de Contatos ====\n");

    // Exibe todos os contatos e numerados
    while (fgets(linha, sizeof(linha), Arquivo)) {
        printf("%d - %s", i, linha);  // Exibe o contato numerado
        i++;
    }

    if (i == 1) {  // Verifica se há contatos na agenda
        printf("Nenhum contato encontrado.\n");
        fclose(Arquivo);
        fclose(Temp);
        return;
    }

    // Solicita que o usuário escolha um contato
    printf("Escolha o número do contato que deseja excluir: ");
    scanf("%d", &escolha);

    rewind(Arquivo);  // Volta para o início do arquivo para reprocessar os contatos

    i = 1;
    while (fgets(linha, sizeof(linha), Arquivo)) {
        if (i == escolha) {
            printf("Contato encontrado: %s", linha);
            printf("Tem certeza que deseja excluir este contato? (s/n): ");
            char confirmacao;
            scanf(" %c", &confirmacao);
            if (confirmacao == 's' || confirmacao == 'S') {
                printf("Excluindo contato: %s", linha);
                encontrado = 1;
            } else {
                printf("Exclusão cancelada.\n");
                fputs(linha, Temp);  // Reescreve o contato no arquivo temporário sem deletá-lo
            }
        } else {
            fputs(linha, Temp);  // Mantém os outros contatos no arquivo temporário
        }
        i++;
    }

    fclose(Arquivo);
    fclose(Temp);

    remove("Agenda_Contato.txt");
    rename("Temp.txt", "Agenda_Contato.txt");

    if (encontrado) {
        printf("Contato excluído com sucesso!\n");
    } else {
        printf("Contato não encontrado ou exclusão cancelada.\n");
    }
}


int main() {
    int opcao;

    do {
        printf("\nMENU AGENDA CONTATO\n");
        printf("\n");
        
		printf("1 - Adicionar Contato\n");
        printf("2 - Procurar Contato\n");
        printf("3 - Mostrar Contatos\n");
        printf("4 - Editar Contato\n");
        printf("5 - Excluir Contato\n");        
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                Adicionar_contato();
                break;
            case 2:
                Procurar_Contato();
                break;
            case 3:
                Mostrar_Contatos();
                break;
            case 4:
                Editar_Contato();
                break;
            case 5:
                Excluir_contato_existente();
                break;
            case 6:
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

