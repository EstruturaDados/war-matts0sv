#include <stdio.h>
#include <string.h>
#include <locale.h>

//#include <windows.h> Para Windows, VScode (comentar o #include <locale.h>)

#define MAX_TERRITORIOS 5

struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

// funcao para limpa o buffer de entrada após scanf
void lbe()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    // controlar entrada e saida do console para aceitar caracteres especiais com UTF8 (<windows.h>)
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8); 

    setlocale(LC_ALL, "Portuguese"); // controlar entrada e saida do console para aceitar caracteres especiais

    struct Territorio lista[MAX_TERRITORIOS];

    // cadastro de 5 territorios
    for (int i = 0; i < MAX_TERRITORIOS; i++)
    {
        printf("\n=== Território %d ===\n", i + 1);

        printf("Nome: ");
        fgets(lista[i].nome, 30, stdin);
        lista[i].nome[strcspn(lista[i].nome, "\n")] = 0;

        printf("Cor do exército: ");
        fgets(lista[i].cor, 10, stdin);
        lista[i].cor[strcspn(lista[i].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &lista[i].tropas);
        lbe(); // limpa o \n (enter) que scanf deixa no buffer
    }

    // exibição de todos os territórios
    printf("\n=== TERRITÓRIOS CADASTRADOS ===\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++)
    {
        printf("Território %d: %s | Cor: %s | Tropas: %d\n",
               i + 1, lista[i].nome, lista[i].cor, lista[i].tropas);
    }

    return 0;
}