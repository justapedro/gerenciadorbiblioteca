//
// Projeto de Programação Estruturada
// Sistema de Gerenciamento de Biblioteca
//
// Integrantes:
// Guilherme Paupitz - RA 202314314
// Pedro Marcondes Silva - RA 202327824
// Valber de Jesus Batista - RA 202331049
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct livrobase {
    char titulo[100];
    char autor[50];
    char editora[30];
    char isbn[15];
    char categoria[30];
    int status;
    int edicao;
    float custo;
    float valoralug;
} livro;

int escreverarquivo(livro dados[], int tamanho) {
    FILE *arquivo = fopen("database.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return 1;
    }

    fprintf(arquivo, "titulo,autor,editora,isbn,categoria,status,edicao,custo,valoralug\n");
    int i;
    for (i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%s,%s,%s,%s,%s,%d,%d,%.2f,%.2f\n",
                dados[i].titulo, dados[i].autor, dados[i].editora, dados[i].isbn, dados[i].categoria,
                dados[i].status, dados[i].edicao, dados[i].custo, dados[i].valoralug);
    }

    fclose(arquivo);

    printf("Dados armazenados no arquivo %s com sucesso!\n", "database.csv");

    return 0;
}

livro *lerarquivo(int *tamanho) {
    FILE *arquivo = fopen("database.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return NULL;
    }

    char cabecalho[200];
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    livro *dados = malloc(100 * sizeof(livro));
    if (dados == NULL) {
        printf("Erro ao alocar memória!\n");
        fclose(arquivo);
        return NULL;
    }

    int i = 0;
    while (fscanf(arquivo, "%99[^,],%49[^,],%29[^,],%14[^,],%29[^,],%d,%d,%f,%f\n",
                  dados[i].titulo, dados[i].autor, dados[i].editora, dados[i].isbn, dados[i].categoria,
                  &dados[i].status, &dados[i].edicao, &dados[i].custo, &dados[i].valoralug) != EOF) {
        i++;
    }

    fclose(arquivo);

    *tamanho = i;
    return dados;
}

void adicionarRegistros(livro **dados, int *tamanho) {
	printf("------------- ADICIONAR REGISTROS --------------\n\nLendo arquivo...");
    int tamanholido,capacidade=1,i;
    if (lerarquivo(&tamanholido)==NULL) {
    	printf("Arquivo não encontrado, criando!");
    	escreverarquivo(NULL,0);
	}
    livro *dadoslidos = lerarquivo(&tamanholido);
    capacidade = tamanholido+1;
    *dados = malloc(capacidade * sizeof(livro));
    
    if(dadoslidos != NULL) {
    	for(i=0;i<tamanholido;i++) {
    		(*dados)[i] = dadoslidos[i];
		}
	}
	
    if (*dados == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    int continuar = 1;
    while (continuar == 1) {
        if (i >= capacidade) {
            capacidade += 1;
            livro *novos_dados = realloc(*dados, capacidade * sizeof(livro));
            if (novos_dados == NULL) {
                printf("Erro ao realocar memória!\n");
                free(*dados);
                return;
            }
            *dados = novos_dados;
        }
        system("CLS");
        setbuf(stdin,NULL);
      	printf("-------- ADICIONANDO REGISTRO - NUM. %i ---------\n", i + 1);
      	
		printf("\nDigite o título: ");
        scanf(" %99[^\n]", (*dados)[i].titulo);
        printf("\nDigite o autor: ");
        scanf(" %49[^\n]", (*dados)[i].autor);
        printf("\nDigite a editora: ");
        scanf(" %29[^\n]", (*dados)[i].editora);
        printf("\nDigite o ISBN: ");
        scanf(" %14[^\n]", (*dados)[i].isbn);
        printf("\nDigite a categoria: ");
        scanf(" %29[^\n]", (*dados)[i].categoria);
        printf("\nDigite o status ('1'' para Disponível)('2' para Indisponível): ");
        scanf("%d", &(*dados)[i].status);
        printf("\nDigite a edição (em número): ");
        scanf("%d", &(*dados)[i].edicao);
        printf("\nDigite o custo: ");
        scanf("%f", &(*dados)[i].custo);
        printf("\nDigite o valor de aluguel: ");
        scanf("%f", &(*dados)[i].valoralug);

        i++;

        printf("\n\nVocê gostaria de adicionar mais um registro? 1. Sim 2. Nao\n");
        scanf("%d", &continuar);
    }

    *tamanho = i;
}

void alterarRegistro() {
	printf("--------------- ALTERAR REGISTROS ---------------\n\nLendo arquivo... ");
    int tamanholido,id,i,encontrado=0;
    char escolha;
    livro *dadoslidos = lerarquivo(&tamanholido);
    if (dadoslidos == NULL) {
        printf("Nenhum dado encontrado.\n");
        return;
    }
    setbuf(stdin, NULL);
    printf("Registros encontrados: %i\n\nDigite o ID do livro que deseja alterar: ",tamanholido);
    scanf("%i",&id);
    for (i = 0; i < tamanholido; i++) {
        if (id == i+1) {
        	encontrado = 1;
        	printf("\n-- ID %i ------------\nNome: %s\nAutor: %s\nEditora: %s\nISBN: %s\nCategoria: %s\nStatus: %s\nEdição: %da Edição\nValor do Livro: RS%.2f\nValor do Aluguel: RS%.2f\n\nDigite E para editar ou qualquer tecla para cancelar: ",i+1,
                           dadoslidos[i].titulo, dadoslidos[i].autor, dadoslidos[i].editora, dadoslidos[i].isbn, dadoslidos[i].categoria,
                           dadoslidos[i].status == 1 ? "Disponível" : "Indisponível", dadoslidos[i].edicao, dadoslidos[i].custo, dadoslidos[i].valoralug);
            setbuf(stdin, NULL);
        	scanf("%c",&escolha);
        	if (escolha == 'e' || escolha == 'E') {
        	setbuf(stdin,NULL);
        	printf("\n----- EDITANDO -----\n\nDigite o novo título: ");
            scanf(" %99[^\n]", dadoslidos[i].titulo);
            printf("\nDigite o novo autor: ");
            scanf(" %49[^\n]", dadoslidos[i].autor);
            printf("\nDigite a nova editora: ");
            scanf(" %29[^\n]", dadoslidos[i].editora);
            printf("\nDigite o novo ISBN: ");
            scanf(" %14[^\n]", dadoslidos[i].isbn);
            printf("\nDigite a nova categoria: ");
            scanf(" %29[^\n]", dadoslidos[i].categoria);
            printf("\nDigite o novo status: ");
            scanf("%d", &dadoslidos[i].status);
            printf("\nDigite a nova edição: ");
            scanf("%d", &dadoslidos[i].edicao);
            printf("\nDigite o novo custo: ");
            scanf("%f", &dadoslidos[i].custo);
            printf("\nDigite o novo valor de aluguel: ");
            scanf("%f", &dadoslidos[i].valoralug);
            escreverarquivo(dadoslidos, tamanholido);
        	printf("Registro alterado com sucesso.\n");
			}
			else {
				printf("Edição do registro cancelada.\n");
			}
            break;
        }
    }
    if (!encontrado) {
        printf("Registro não encontrado.\n");
    }

    free(dadoslidos);
}

void removerRegistro() {
	printf("---------------- REMOVER REGISTRO ---------------\n\nLendo arquivo... ");
    int tamanholido,i,j=0,id;
    char escolha;
    livro *dadoslidos = lerarquivo(&tamanholido);
    livro *dados = malloc(tamanholido * sizeof(livro));
    printf("Registros encontrados: %i\n\nDigite o ID do livro que deseja remover: ",tamanholido);
    scanf("%i",&id);
    
    if(dadoslidos != NULL) {
    	for(i=0;i<tamanholido;i++) {
    		if (id == i+1) {
				printf("\n-- ID %i ------------\nNome: %s\nAutor: %s\nEditora: %s\nISBN: %s\nCategoria: %s\nStatus: %s\nEdição: %da Edição\nValor do Livro: RS%.2f\nValor do Aluguel: RS%.2f\n\nDigite R para remover ou qualquer tecla para cancelar: ",i+1,
                           dadoslidos[i].titulo, dadoslidos[i].autor, dadoslidos[i].editora, dadoslidos[i].isbn, dadoslidos[i].categoria,
                           dadoslidos[i].status == 1 ? "Disponível" : "Indisponível", dadoslidos[i].edicao, dadoslidos[i].custo, dadoslidos[i].valoralug);
	            setbuf(stdin, NULL);
	        	scanf("%c",&escolha);
	        	if (escolha == 'r' || escolha == 'R') {
		        	system("CLS");
		        	setbuf(stdin,NULL);
		        	printf("Registro removido com sucesso.\n");
				}
				else {
					printf("Remoção do registro cancelada.\n");
					dados[j] = dadoslidos[i];
					j++;
				}
    		}
    		else {
    			dados[j] = dadoslidos[i];
    			j++;
			}
		}
	}
    if (dados == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }
	escreverarquivo(dados, j);
    free(dadoslidos);
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    char selecmenu = 'N';
    while (selecmenu != 's') {
        system("CLS");
        int opcao;
        printf("----- SISTEMA DE GERENCIAMENTO DE BIBLIOTECA ----\n\n");
        printf("Digite o que deseja fazer:\n\n1. Visualizar registros\n2. Inserir Registros\n3. Alterar Registro\n4. Remover Registro\n5. Sair\n\nDigite a sua opção: ");
        scanf("%i", &opcao);
        system("CLS");
        
        if (opcao == 1) {
        	// Visualizar Registro
        	printf("-------------- VISUALIZAR REGISTROS -------------\n");
            printf("Lendo arquivo... ");
            int tamanholido;
            livro *dadoslidos = lerarquivo(&tamanholido);
            if (dadoslidos != NULL) {
            	printf("Registros encontrados: %i", tamanholido);
                int i;
                for (i = 0; i < tamanholido; i++) {
                    printf("\n\n-- ID %i ------------\nNome: %s\nAutor: %s\nEditora: %s\nISBN: %s\nCategoria: %s\nStatus: %s\nEdição: %da Edição\nValor do Livro: RS%.2f\nValor do Aluguel: RS%.2f",i+1,
                           dadoslidos[i].titulo, dadoslidos[i].autor, dadoslidos[i].editora, dadoslidos[i].isbn, dadoslidos[i].categoria,
                           dadoslidos[i].status == 1 ? "Disponível" : "Indisponível", dadoslidos[i].edicao, dadoslidos[i].custo, dadoslidos[i].valoralug);
                }
                printf("\n\nFim dos registros.");
                free(dadoslidos);
            } else {
                printf("Nenhum dado encontrado.\n");
            }
        } else if (opcao == 2) {
        	//Adicionar Registro
            livro *dados = NULL;
            int tamanho = 0;
            adicionarRegistros(&dados, &tamanho);
            if (tamanho > 0) {
                escreverarquivo(dados, tamanho);
                free(dados);
            }
        } else if (opcao == 3) {
        	//Alterar Registro
            alterarRegistro();
        } else if (opcao == 4) {
        	//Remover Registro
        	removerRegistro();
		}
		else if (opcao == 5) {
			selecmenu = 's';
		}
		else{
            printf("Opção inválida.\n");
        }
        if (selecmenu != 's') {
	        printf("\n-------------------------------------------------\nDigite qualquer tecla para voltar ou S para sair: ");
	        setbuf(stdin, NULL);
	        scanf(" %c", &selecmenu);
        }
        if(selecmenu == 'S') {
        	selecmenu = 's';
		}
    }

    return 0;
}
