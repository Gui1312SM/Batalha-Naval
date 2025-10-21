#include <stdio.h>

int main(){

    // Declaração e inicialização do tabuleiro 10x10 com zeros (água)
    int tabuleiro[10][10] = {0};
    
    // Vetores unidimensionais que representam as partes dos navios
    // Cada navio tem 3 posições com valor 3
    int partes_navio1[3] = {3, 3, 3};
    int partes_navio2[3] = {3, 3, 3};
    int partes_navio3[3] = {3, 3, 3};
    int partes_navio4[3] = {3, 3, 3};
    
    // ========== CONFIGURAÇÃO DOS NAVIOS ==========
    
    // Navio 1 - Horizontal
    int navio1_linha = 1;
    int navio1_coluna = 2;
    int navio1_tipo = 0;
    
    // Navio 2 - Vertical
    int navio2_linha = 5;
    int navio2_coluna = 8;
    int navio2_tipo = 1;
    
    // Navio 3 - Diagonal Descendente
    int navio3_linha = 3;
    int navio3_coluna = 3;
    int navio3_tipo = 2;
    
    // Navio 4 - Diagonal Ascendente
    int navio4_linha = 6;
    int navio4_coluna = 5;
    int navio4_tipo = 3;
    
    // Variáveis para loops e controle
    int i, j;
    
    // ========== POSICIONAMENTO DOS NAVIOS ==========
    
    // Navio 1 - Horizontal
    for (i = 0; i < 3; i++) {
        tabuleiro[navio1_linha][navio1_coluna + i] = partes_navio1[i];
    }
    
    // Navio 2 - Vertical
    for (i = 0; i < 3; i++) {
        tabuleiro[navio2_linha + i][navio2_coluna] = partes_navio2[i];
    }
    
    // Navio 3 - Diagonal Descendente
    for (i = 0; i < 3; i++) {
        tabuleiro[navio3_linha + i][navio3_coluna + i] = partes_navio3[i];
    }
    
    // Navio 4 - Diagonal Ascendente
    for (i = 0; i < 3; i++) {
        tabuleiro[navio4_linha + i][navio4_coluna - i] = partes_navio4[i];
    }
    
    // ========== CRIAÇÃO DAS MATRIZES DE HABILIDADES ==========
    
    // Tamanho das matrizes de habilidades (7x7)
    int tamanho_habilidade = 7;
    
    // Matriz para habilidade CONE (7x7)
    int habilidade_cone[7][7];
    
    // Matriz para habilidade CRUZ (7x7)
    int habilidade_cruz[7][7];
    
    // Matriz para habilidade OCTAEDRO (7x7)
    int habilidade_octaedro[7][7];
    
    // Centro da matriz de habilidade (ponto de origem)
    int centro = 3; // Para matriz 7x7, o centro está na posição [3][3]
    
    // ========== CONSTRUÇÃO DA HABILIDADE CONE ==========
    // Cone: Começa estreito no topo e expande para baixo
    // Formato: linha 0 = 1 posição, linha 1 = 3 posições, linha 2 = 5 posições, etc.
    
    printf("=== CONSTRUINDO HABILIDADE CONE ===\n");
    
    for (i = 0; i < tamanho_habilidade; i++) {
        for (j = 0; j < tamanho_habilidade; j++) {
            // Calcula a distância da coluna em relação ao centro
            int distancia_coluna = j - centro;
            
            // Se a distância for menor ou igual à linha, está dentro do cone
            if (distancia_coluna >= -i && distancia_coluna <= i) {
                habilidade_cone[i][j] = 1;
            } else {
                habilidade_cone[i][j] = 0;
            }
        }
    }
    
    // ========== CONSTRUÇÃO DA HABILIDADE CRUZ ==========
    // Cruz: Linha central horizontal e coluna central vertical
    
    printf("=== CONSTRUINDO HABILIDADE CRUZ ===\n");
    
    for (i = 0; i < tamanho_habilidade; i++) {
        for (j = 0; j < tamanho_habilidade; j++) {
            // Se está na linha central OU na coluna central, faz parte da cruz
            if (i == centro || j == centro) {
                habilidade_cruz[i][j] = 1;
            } else {
                habilidade_cruz[i][j] = 0;
            }
        }
    }
    
    // ========== CONSTRUÇÃO DA HABILIDADE OCTAEDRO (LOSANGO) ==========
    // Octaedro visto de frente: formato de losango
    // Expande do centro para cima/baixo e esquerda/direita
    
    printf("=== CONSTRUINDO HABILIDADE OCTAEDRO (LOSANGO) ===\n");
    
    for (i = 0; i < tamanho_habilidade; i++) {
        for (j = 0; j < tamanho_habilidade; j++) {
            // Calcula a distância Manhattan do centro
            int distancia_linha = i - centro;
            int distancia_coluna = j - centro;
            
            // Se a distância for negativa, inverte o sinal
            if (distancia_linha < 0) {
                distancia_linha = -distancia_linha;
            }
            if (distancia_coluna < 0) {
                distancia_coluna = -distancia_coluna;
            }
            
            // Se a soma das distâncias for <= ao raio, está dentro do losango
            if (distancia_linha + distancia_coluna <= centro) {
                habilidade_octaedro[i][j] = 1;
            } else {
                habilidade_octaedro[i][j] = 0;
            }
        }
    }
    
    // ========== DEFINIÇÃO DOS PONTOS DE ORIGEM DAS HABILIDADES ==========
    
    // Ponto de origem da habilidade CONE no tabuleiro
    int cone_origem_linha = 2;
    int cone_origem_coluna = 5;
    
    // Ponto de origem da habilidade CRUZ no tabuleiro
    int cruz_origem_linha = 6;
    int cruz_origem_coluna = 2;
    
    // Ponto de origem da habilidade OCTAEDRO no tabuleiro
    int octaedro_origem_linha = 7;
    int octaedro_origem_coluna = 7;
    
    // Variável para escolher qual habilidade exibir (1=Cone, 2=Cruz, 3=Octaedro, 0=Nenhuma)
    int habilidade_ativa = 1; // Altere este valor para visualizar diferentes habilidades
    
    // ========== SOBREPOSIÇÃO DA HABILIDADE NO TABULEIRO ==========
    
    // Cria uma cópia do tabuleiro para aplicar a habilidade
    int tabuleiro_com_habilidade[10][10];
    
    // Copia o tabuleiro original
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro_com_habilidade[i][j] = tabuleiro[i][j];
        }
    }
    
    // Aplica a habilidade escolhida
    if (habilidade_ativa == 1) {
        // Aplica CONE
        printf("\n=== APLICANDO HABILIDADE CONE ===\n");
        printf("Origem: [%d, %d]\n\n", cone_origem_linha, cone_origem_coluna);
        
        for (i = 0; i < tamanho_habilidade; i++) {
            for (j = 0; j < tamanho_habilidade; j++) {
                // Calcula a posição no tabuleiro
                int pos_linha = cone_origem_linha - centro + i;
                int pos_coluna = cone_origem_coluna - centro + j;
                
                // Verifica se está dentro dos limites do tabuleiro
                if (pos_linha >= 0 && pos_linha < 10 && pos_coluna >= 0 && pos_coluna < 10) {
                    // Se a habilidade afeta essa posição (valor 1)
                    if (habilidade_cone[i][j] == 1) {
                        // Marca com 5 se for água, mantém o valor se for navio
                        if (tabuleiro_com_habilidade[pos_linha][pos_coluna] == 0) {
                            tabuleiro_com_habilidade[pos_linha][pos_coluna] = 5;
                        }
                    }
                }
            }
        }
    } else if (habilidade_ativa == 2) {
        // Aplica CRUZ
        printf("\n=== APLICANDO HABILIDADE CRUZ ===\n");
        printf("Origem: [%d, %d]\n\n", cruz_origem_linha, cruz_origem_coluna);
        
        for (i = 0; i < tamanho_habilidade; i++) {
            for (j = 0; j < tamanho_habilidade; j++) {
                int pos_linha = cruz_origem_linha - centro + i;
                int pos_coluna = cruz_origem_coluna - centro + j;
                
                if (pos_linha >= 0 && pos_linha < 10 && pos_coluna >= 0 && pos_coluna < 10) {
                    if (habilidade_cruz[i][j] == 1) {
                        if (tabuleiro_com_habilidade[pos_linha][pos_coluna] == 0) {
                            tabuleiro_com_habilidade[pos_linha][pos_coluna] = 5;
                        }
                    }
                }
            }
        }
    } else if (habilidade_ativa == 3) {
        // Aplica OCTAEDRO
        printf("\n=== APLICANDO HABILIDADE OCTAEDRO (LOSANGO) ===\n");
        printf("Origem: [%d, %d]\n\n", octaedro_origem_linha, octaedro_origem_coluna);
        
        for (i = 0; i < tamanho_habilidade; i++) {
            for (j = 0; j < tamanho_habilidade; j++) {
                int pos_linha = octaedro_origem_linha - centro + i;
                int pos_coluna = octaedro_origem_coluna - centro + j;
                
                if (pos_linha >= 0 && pos_linha < 10 && pos_coluna >= 0 && pos_coluna < 10) {
                    if (habilidade_octaedro[i][j] == 1) {
                        if (tabuleiro_com_habilidade[pos_linha][pos_coluna] == 0) {
                            tabuleiro_com_habilidade[pos_linha][pos_coluna] = 5;
                        }
                    }
                }
            }
        }
    }
    
    // ========== EXIBIÇÃO DO TABULEIRO ORIGINAL ==========
    
    printf("\n");
    printf("=============================================\n");
    printf("     TABULEIRO ORIGINAL - 4 NAVIOS     \n");
    printf("=============================================\n\n");
    
    printf("   ");
    for (i = 0; i < 10; i++) {
        printf(" %d ", i);
    }
    printf("\n");
    
    printf("   ");
    for (i = 0; i < 10; i++) {
        printf("---");
    }
    printf("\n");
    
    for (i = 0; i < 10; i++) {
        printf("%2d|", i);
        for (j = 0; j < 10; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    // ========== EXIBIÇÃO DO TABULEIRO COM HABILIDADE ==========
    
    if (habilidade_ativa > 0) {
        printf("\n");
        printf("=============================================\n");
        printf("   TABULEIRO COM ÁREA DE EFEITO DA HABILIDADE\n");
        printf("=============================================\n\n");
        
        printf("   ");
        for (i = 0; i < 10; i++) {
            printf(" %d ", i);
        }
        printf("\n");
        
        printf("   ");
        for (i = 0; i < 10; i++) {
            printf("---");
        }
        printf("\n");
        
        for (i = 0; i < 10; i++) {
            printf("%2d|", i);
            for (j = 0; j < 10; j++) {
                printf(" %d ", tabuleiro_com_habilidade[i][j]);
            }
            printf("\n");
        }
    }
    
    // ========== EXIBIÇÃO DAS MATRIZES DE HABILIDADES ==========
    
    printf("\n");
    printf("=============================================\n");
    printf("      VISUALIZAÇÃO DAS HABILIDADES (7x7)    \n");
    printf("=============================================\n");
    
    // Exibe Habilidade CONE
    printf("\nHABILIDADE CONE:\n");
    for (i = 0; i < tamanho_habilidade; i++) {
        printf("  ");
        for (j = 0; j < tamanho_habilidade; j++) {
            if (habilidade_cone[i][j] == 1) {
                printf(" 3 ");
            } else {
                printf(" 0 ");
            }
        }
        printf("\n");
    }
    
    // Exibe Habilidade CRUZ
    printf("\nHABILIDADE CRUZ:\n");
    for (i = 0; i < tamanho_habilidade; i++) {
        printf("  ");
        for (j = 0; j < tamanho_habilidade; j++) {
            if (habilidade_cruz[i][j] == 1) {
                printf(" 3 ");
            } else {
                printf(" 0 ");
            }
        }
        printf("\n");
    }
    
    // Exibe Habilidade OCTAEDRO (LOSANGO)
    printf("\nHABILIDADE OCTAEDRO (LOSANGO):\n");
    for (i = 0; i < tamanho_habilidade; i++) {
        printf("  ");
        for (j = 0; j < tamanho_habilidade; j++) {
            if (habilidade_octaedro[i][j] == 1) {
                printf(" 3 ");
            } else {
                printf(" 0 ");
            }
        }
        printf("\n");
    }
    
    // ========== LEGENDA FINAL ==========
    
    printf("\n=============================================\n");
    printf("LEGENDA:\n");
    printf("  0 = Água\n");
    printf("  3 = Navio\n");
    printf("  5 = Área afetada pela habilidade\n");
    printf("\nPara alterar a habilidade exibida,\n");
    printf("modifique a variável 'habilidade_ativa':\n");
    printf("  1 = Cone\n");
    printf("  2 = Cruz\n");
    printf("  3 = Octaedro (Losango)\n");
    printf("  0 = Nenhuma habilidade\n");
    printf("=============================================\n");

    return 0;
}
