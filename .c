# #include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numero;
    char nome[100];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

Conta corrente[MAX_CONTAS];
int total_corrente = 0;

Conta poupanca[MAX_CONTAS];
int total_poupanca = 0;

int buscarConta(Conta contas[], int total, int numero) {
    if (total == 0) return -1;
    for (int i = 0; i < total; i++) {
        if (contas[i].numero == numero)
            return i;
    }
    return -2;
}

void cadastrarConta(Conta contas[], int *total, int numero) {
    if (*total >= MAX_CONTAS) {
        printf("Limite de contas atingido.\n");
        return;
    }

    int pos = buscarConta(contas, *total, numero);
    if (pos >= 0) {
        printf("Conta ja cadastrada.\n");
        return;
    }

    contas[*total].numero = numero;
    printf("Nome do cliente: ");
    getchar(); // limpar buffer
    fgets(contas[*total].nome, 100, stdin);
    contas[*total].nome[strcspn(contas[*total].nome, "\n")] = 0;

    printf("CPF: ");
    fgets(contas[*total].cpf, 15, stdin);
    contas[*total].cpf[strcspn(contas[*total].cpf, "\n")] = 0;

    printf("Telefone: ");
    fgets(contas[*total].telefone, 20, stdin);
    contas[*total].telefone[strcspn(contas[*total].telefone, "\n")] = 0;

    printf("Saldo inicial: ");
    scanf("%f", &contas[*total].saldo);

    (*total)++;
    printf("Conta cadastrada com sucesso!\n");
}

void consultarSaldo(Conta contas[], int total, int numero) {
    int pos = buscarConta(contas, total, numero);
    if (pos >= 0) {
        printf("Saldo da conta %d: R$ %.2f\n", numero, contas[pos].saldo);
    } else if (pos == -1) {
        printf("Cadastro esta vazio.\n");
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void depositar(Conta contas[], int total, int numero) {
    int pos = buscarConta(contas, total, numero);
    if (pos >= 0) {
        float valor;
        printf("Valor a depositar: ");
        scanf("%f", &valor);
        contas[pos].saldo += valor;
        printf("Deposito realizado. Novo saldo: R$ %.2f\n", contas[pos].saldo);
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void sacar(Conta contas[], int total, int numero) {
    int pos = buscarConta(contas, total, numero);
    if (pos >= 0) {
        float valor;
        printf("Valor a sacar: ");
        scanf("%f", &valor);
        if (contas[pos].saldo >= valor) {
            contas[pos].saldo -= valor;
            printf("Saque realizado. Novo saldo: R$ %.2f\n", contas[pos].saldo);
        } else {
            printf("Saldo insuficiente.\n");
        }
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void exibirContas(Conta contas[], int total) {
    if (total == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("Conta: %d - Nome: %s - Telefone: %s\n",
               contas[i].numero, contas[i].nome, contas[i].telefone);
    }
}

void menu() {
    int opcao, tipo, numero;
    do {
        printf("\n---- Banco Dinheiro Certo ----\n");
        printf("1 - Cadastrar nova conta\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Depositar\n");
        printf("4 - Sacar\n");
        printf("5 - Exibir contas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        printf("Tipo de conta (1-Corrente, 2-Poupanca): ");
        scanf("%d", &tipo);

        Conta *cadastro;
        int *total;

        if (tipo == 1) {
            cadastro = corrente;
            total = &total_corrente;
        } else if (tipo == 2) {
            cadastro = poupanca;
            total = &total_poupanca;
        } else {
            printf("Tipo de conta invalido.\n");
            continue;
        }

        if (opcao == 1) {
            printf("Numero da nova conta: ");
            scanf("%d", &numero);
            cadastrarConta(cadastro, total, numero);
        } else if (opcao == 2) {
            printf("Numero da conta: ");
            scanf("%d", &numero);
            consultarSaldo(cadastro, *total, numero);
        } else if (opcao == 3) {
            printf("Numero da conta: ");
            scanf("%d", &numero);
            depositar(cadastro, *total, numero);
        } else if (opcao == 4) {
            printf("Numero da conta: ");
            scanf("%d", &numero);
            sacar(cadastro, *total, numero);
        } else if (opcao == 5) {
            exibirContas(cadastro, *total);
        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
