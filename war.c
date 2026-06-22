#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// funcao para limpa o buffer de entrada após scanf
void lbe()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void cadastrarTerritorios(Territorio* mapa, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n=== Território %d ===\n", i + 1);

        printf("Nome: ");
        fgets((mapa + i)->nome, 30, stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = 0;

        printf("Cor do exército: ");
        fgets((mapa + i)->cor, 10, stdin);
        (mapa + i)->cor[strcspn((mapa + i)->cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &(mapa + i)->tropas);
        lbe();
    }
}

void exibirTerritorios(Territorio* mapa, int n)
{
    printf("\n=== TERRITÓRIOS ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i + 1,
               (mapa + i)->nome,
               (mapa + i)->cor,
               (mapa + i)->tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor)
{

    int dado_atq = rand() % 6 + 1;
    int dado_def = rand() % 6 + 1;

    printf("\n--- Resolução do Ataque ---\n");
    printf("  %s rola: %d\n", atacante->nome, dado_atq);
    printf("  %s rola: %d\n", defensor->nome, dado_def);

    if (dado_atq > dado_def)
    {

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        printf("  Resultado: %s CONQUISTOU %s!\n",
               atacante->nome, defensor->nome);
        printf("  %s agora tem %d tropas e pertence ao exército %s.\n",
               defensor->nome, defensor->tropas, defensor->cor);
    }
    else
    {

        if (atacante->tropas > 0)
            atacante->tropas--;

        printf("  Resultado: %s DEFENDEU com sucesso!\n", defensor->nome);
        printf("  %s perdeu 1 tropa (restam %d).\n",
               atacante->nome, atacante->tropas);
    }
}

void liberarMemoria(Territorio* mapa)
{
    free(mapa);
}

int main()
{

    // SetConsoleOutputCP(CP_UTF8); // controlar saida do concole para aceitar caracteres especias
    // SetConsoleCP(CP_UTF8);       // controlar entrada do concole para aceitar caracteres especias
    setlocale(LC_ALL, "Portuguese");

    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);
    lbe();

    if (n <= 0)
    {
        printf("Número inválido de territórios.\n");
        return 1;
    }

    Territorio* mapa = (Territorio *)calloc(n, sizeof(Territorio));

    if (mapa == NULL)
    {
        printf("Erro: falha ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    exibirTerritorios(mapa, n);

    char continuar;
    do
    {
        printf("\n=== FASE DE ATAQUE ===\n");
        exibirTerritorios(mapa, n);

        int idx_atq;
        printf("\nÍndice do território ATACANTE (1-%d): ", n);
        scanf("%d", &idx_atq);
        lbe();
        idx_atq--;

        if (idx_atq < 0 || idx_atq >= n)
        {
            printf("Índice inválido.\n");
            continue;
        }

        int idx_def;
        printf("Índice do território DEFENSOR (1-%d): ", n);
        scanf("%d", &idx_def);
        lbe();
        idx_def--;

        if (idx_def < 0 || idx_def >= n)
        {
            printf("Índice inválido.\n");
            continue;
        }

        if (idx_atq == idx_def)
        {
            printf("Um território não pode atacar a si mesmo.\n");
            continue;
        }

        if (strcmp((mapa + idx_atq)->cor, (mapa + idx_def)->cor) == 0)
        {
            printf("Você não pode atacar um território da sua própria cor (%s)!\n",
                   (mapa + idx_atq)->cor);
            continue;
        }
        atacar(mapa + idx_atq, mapa + idx_def);

        exibirTerritorios(mapa, n);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        lbe(); // limpa o \n (enter) que scanf deixa no buffer

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa);

    printf("\nPrograma encerrado. Memória liberada.\n");
    return 0;
}