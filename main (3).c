#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double corrente_capacitor_0(double I0, double V0, double R) {
    return -I0 - (V0 / R);
}

double conv_corrente(double valor, int unidade) {
    switch (unidade) {
        case 1: return valor;
        case 2: return valor * 1e-3;
        case 3: return valor * 1e-6;
        case 4: return valor * 1e-9;
        default: return valor;
    }
}


double conv_capacitancia(double valor, int unidade) {
    switch (unidade) {
        case 1: return valor;
        case 2: return valor * 1e-3;
        case 3: return valor * 1e-6;
        case 4: return valor * 1e-9;
        case 5: return valor * 1e-12;
        default: return valor;
    }
}
double conv_resistencia(double valor, int unidade) {
    switch (unidade) {
        case 1: return valor;
        case 2: return valor * 1e3;
        default: return valor;
    }
}

double conv_indutancia(double valor, int unidade) {
    switch (unidade) {
        case 1: return valor;
        case 2: return valor * 1e-3;
        case 3: return valor * 1e-6;
        case 4: return valor * 1e-9;
        case 5: return valor * 1e-12;
        default: return valor;
    }
}

int main() {
    int continuar = 1;
     char nome_usuario[100];
    printf("Digite seu nome: ");
    scanf(" %[^\n]s", nome_usuario);
    while (continuar) {
        double R, L, C, V0, I0;
        int u_R, u_L, u_C, u_I0;
        printf("1 - Ohms\n");
        printf("2 - kOhms\n");
        printf("Escolha a unidade da resistencia (1-2): ");
        scanf("%d", &u_R);
        printf("Digite o valor da resistencia: ");
        scanf("%lf", &R);
        R = conv_resistencia(R, u_R);
        system("cls");

        printf("1 - Henrys\n");
        printf("2 - Millihenrys\n");
        printf("3 - Microhenrys\n");
        printf("4 - Nanohenrys\n");
        printf("5 - Picohenrys\n");
        printf("Escolha a unidade da indutancia (1-5): ");
        scanf("%d", &u_L);
        printf("Digite o valor da indutancia: ");
        scanf("%lf", &L);
        L = conv_indutancia(L, u_L);
        system("cls");

        printf("1 - Farads\n");
        printf("2 - Millifarads\n");
        printf("3 - Microfarads\n");
        printf("4 - Nanofarads\n");
        printf("5 - Picofarads\n");
        printf("Escolha a unidade da capacitancia (1-5): ");
        scanf("%d", &u_C);
        printf("Digite o valor da capacitancia: ");
        double valor_C;
        scanf("%lf", &valor_C);
        C = conv_capacitancia(valor_C, u_C);
        system("cls");

        printf("Digite a tensao inicial do capacitor (V): ");
        scanf("%lf", &V0);
        printf("1 - Amperes\n");
        printf("2 - Milliamperes\n");
        printf("3 - Microamperes\n");
        printf("4 - Nanoamperes\n");
        printf("Escolha a unidade da carga incial do indutor (1-4): ");
        scanf("%d", &u_I0);
        printf("Digite a carga inicial do indutor: ");
        scanf("%lf", &I0);
        I0 = conv_corrente(I0, u_I0);
        system("cls");
        double sigma = 1 / (2 * R * C);
        double omega0 = 1 / sqrt(L * C);
        double omega_d = sqrt(fabs(omega0 * omega0 - sigma * sigma));
        double pi = 3.141592654;
        printf("\n=========Resultados Calculados =========\n");
        printf("Autor(es): Thaynara Magno e Camila Nobrega\n");
        printf("usuario: %s\n", nome_usuario);
        printf("Sigma = %.2f s^-1\n", sigma);
        printf("omega_0 = %.2f rad/s\n", omega0);
        int tipo_amortecimento;
       double epsilon = 1e-6; // Precisao pra funcionar no vscode e codeblock
       if (fabs(sigma * sigma - omega0 * omega0) < epsilon) {
        tipo_amortecimento = 2;
       } else if (sigma * sigma < omega0 * omega0) {
       tipo_amortecimento = 1;
        } else {
        tipo_amortecimento = 3;
       }
        double I_C0 = corrente_capacitor_0(I0, V0, R);
        switch (tipo_amortecimento) {
            case 1:
                printf("Tipo de amortecimento: Subamortecido\n");
                printf("FrequEncia amortecida (W_d) = %.4f rad/s\n", omega_d);
                double B1 = V0;

                double B2 = (((I_C0 / C) - (-sigma * V0)) / omega_d);
                printf("B1 = %.2f \n", B1);
                printf("B2 = %.2f \n", B2);
                double tm = pi / omega_d;
                double V_tm = B1 * exp(-sigma * tm) * cos(omega_d * tm) + B2 * exp(-sigma * tm) * sin(omega_d * tm);

                printf("Tempo do pico maximo (tm) = %.6f s\n", tm);
                printf("Tensao no pico maximo (V(tm)) = %.4f V\n", V_tm);
                break;


            case 2:
                printf("Tipo de amortecimento: Criticamente Amortecido\n");
                double A2 = V0; // A1 é a tensão inicial
                double A1 = ((I_C0 / C) + (sigma * V0));
                  double tmcritico = (1 / sigma) - (A2 / A1); // Fórmula do pico máximo
                printf("A1 = %.2f\n", A1);
                printf("A2 = %.2f\n", A2);
                printf("Tempo do pico maximo (tm) = %.4f s\n", tmcritico);
                double V_tmcritico = (A1 * tmcritico + A2) * exp(-sigma * tmcritico);
                 printf("Tensao no pico maximo (V(tm)) = %.4f V\n", V_tmcritico);
                break;
            case 3:
                printf("Tipo de amortecimento: Superamortecido\n");
                double s1 = -sigma + omega_d;
                double s2 = -sigma - omega_d;
                printf("s1 = %.2f s^-1\n", s1);
                printf("s2 = %.2f s^-1\n", s2);
                double b1 = V0;
                double b2 = I_C0 / C;
                double A1_super = (b2 - s2 * b1) / (s1 - s2);
                double A2_super = b1 - A1_super;
                printf("A1 = %.2f \n", A1_super);
                printf("A2 = %.2f \n", A2_super);
                break;

            default:
                printf("Erro ao determinar o tipo de amortecimento.\n");
                return -1;
        }

        printf("\nDeseja reiniciar o programa? (1 - Sim, 0 - Nao): ");
        scanf("%d", &continuar);
        system("cls");
    }
    return 0;
}
