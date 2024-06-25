#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//------- ESTRUTURAS -------

typedef struct agenda{ //Typedef serve para definir um nome para simplificar, e o nome é definido no final, nesse está contato
    char nome[30]; 
    char numero[12]; //11 = 47 99999 9999 sem os espaços
}Contato;

typedef struct counter{
    int contadorNumero;
}Contador;

//------- VARIAVEIS GLOBAIS -------//
int contadorNumero = 0;

//-------PROTÓTIPO DAS FUNÇÕES -------//
void addContato(void);
void pesquisarContato(void); 
void excluirContato(void);   
void limparContato(void);

int main(void){
    //variaveis
    char opcao;

    do {
        printf("---------------------------------------\n");
        printf("       AGENDA DE CONTATOS - MENU   \n\n");
        printf("[a] Criar Contato \n");
        printf("[b] Pesquisar Contato \n");
        printf("[c] Excluir Contato \n");
        printf("[d] Apagar a Lista de Contatos \n");
        printf("[e] Fechar Agenda\n\n");
        printf("Digite a sua opcao: ");
        scanf("%c",&opcao);
        fflush(stdin);

        switch(opcao) {
            case 'a':
                addContato();
                break;
            case 'b':
                pesquisarContato();
                break;
            case 'c':
                excluirContato();
                break;
            case 'd':
                limparContato();
                break;
            case 'e':
                break;
        }
    } while (opcao != 'e');

    printf("\nSaindo...\n");

    return 0;
}


//------- FUNÇÕES -------//

void addContato(void){
    
    //Variaveis
    Contato contato; //Define estrutura "Nome" e "Numero", usado la no struct
    FILE *arquivo; //Declarar variavel "arquivo"
    arquivo = fopen("contatos.bin","ab"); //Atribui a variavel "Arquivo" ao arquivo | Por que é usado ab? a - append, e o B é por se tratar de binario
    
    //Teste para ver se abre
	if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
		return;
    }

    //Processo de pedir nome e número
    printf("Digite o nome do contato: ");
    fgets(contato.nome, sizeof(contato.nome), stdin); //variavel, tamanho maximo, tipo da entrada
    fflush(stdin);
    printf("Digite o numero do telefone: ");
    fgets(contato.numero, sizeof(contato.numero), stdin);
    fflush(stdin);
    fwrite(&contato, sizeof(Contato), 1, arquivo); //Não precisa do \n para dar um "enter" porque o gets pega o espaço do enter quando a gente escreve

    fclose(arquivo);
    printf("\nContato adicionado\n");

    /*FILE *arquivoContador;
    arquivoContador = fopen("contador.bin","wb")*/
}


void pesquisarContato(void) {
        
    //Variaveis

    Contato contato;
    FILE *arquivo;
    char name[31], opcao;

    arquivo = fopen("contatos.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("---------------------------------------\n");
    printf("       AGENDA DE CONTATOS - PESQUISA   \n\n");
    printf("[a] Pesquisa por Nome \n");
    printf("Digite a sua opcao: ");
    scanf(" %c",&opcao);
    fflush(stdin);

    if (opcao == 'a'){
        printf("Digite o nome: ");
        fgets(name, 30, stdin);

        while (fread(&contato, sizeof(Contato), 1, arquivo) == 1)
        {
            if (strcmp(contato.nome, name) == 0) { //strcmp = string comparate
                printf("\nNome:%sNumero:%s\n",contato.nome, contato.numero);
            }
        }
    }
}

void excluirContato(void) {

    char NomeExcluir[30];
    FILE *arquivo;
    int i, contador=0;
    Contato contatos[50];


    arquivo = fopen("contatos.bin", "r+b");     //Abrir arquivo original para leitura + escrita
    if (arquivo == NULL) {
        printf("Voce precisa criar contatos antes de excluir.\n");
        return;
    }


    printf("Digite o nome do contato para excluir: ");
    fgets(NomeExcluir, 30, stdin);
    fflush(stdin);

    while (fread(&contatos[contador], sizeof(Contato), 1, arquivo) == 1) //Le os contatos e atribui a variavel contatos
    {
        contador++;
    }

    for (i = 0; i < contador; i++)
    {
        if (strcmp(contatos[i].nome, NomeExcluir) == 0)// se o nome for o que queremos remover
        { 
            for (int j = i; j < contador - 1; j++)
            {
                contatos[j] = contatos[j + 1];
            }
            contador--; // Decrementa o contador para remover o último elemento da lista
            fseek(arquivo, 0, SEEK_SET);
            fwrite(contatos, sizeof(Contato), contador, arquivo); //escreve os contato de volta no arquivo
            printf("Contato excluido com sucesso.\n");
            break;
        } else {
            printf("Contato nao encontrado.\n");
        }
    }


    fclose(arquivo);
}

void limparContato(void){
    remove("contatos.bin");

    Contato contato; //Define estrutura "Nome" e "Numero", usado la no struct
    FILE *arquivo; //Declarar variavel "arquivo"
    arquivo = fopen("contatos.bin","wb"); //Atribui a variavel "Arquivo" ao arquivo | Por que é usado wb? W - write, e o B é por se tratar de binario

    char nomePlaceholder[31] = "Placeholder"; //Placeholder pq o programa de pesquisa não estava lendo o primeiro contato
    char numeroPlaceholder[12] = "11999999999";

	if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
		return;
    }

    strcpy(contato.nome, nomePlaceholder);
    strcpy(contato.numero, numeroPlaceholder);

    fwrite(&contato, sizeof(Contato), 1, arquivo); //Não precisa do \n para dar um "enter" porque o gets pega o espaço do enter quando a gente escreve
	printf("Lista limpa com sucesso!\n");
    fclose(arquivo);
    fflush(stdin);
}