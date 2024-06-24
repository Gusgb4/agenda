#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct agenda{ //Typedef serve para definir um nome para simplificar, e o nome é definido no final, nesse está contato
    char nome[30]; 
    char numero[12]; //11 = 47 99999 9999 sem os espaços
}Contato;



//Prototipos das funções
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


//------- FUNÇÕES --------

void addContato(void){
    
    //Variaveis

    Contato contato; //Define estrutura "Nome" e "Numero", usado la no struct
    FILE *arquivo; //Declarar variavel "arquivo"
    arquivo = fopen("contatos.bin","wb"); //Atribui a variavel "Arquivo" ao arquivo | Por que é usado wb? W - write, e o B é por se tratar de binario


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
    fflush(stdin);
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
    printf("[b] Pesquisa por Numero \n\n");
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
    FILE *excluirContato, *Auxiliar;
    Contato c;

    excluirContato = fopen("contatos.bin", "rb");     //Abrir arquivo original para leitura

    if (excluirContato == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
	
    Auxiliar = fopen("temp.bin", "wb");    //Abrir arquivo temporario

    if (Auxiliar == NULL) {
        printf("Erro ao abrir arquivo temporario.\n");
        fclose(excluirContato);
        return;
    }

    printf("Digite o nome do contato a ser excluido: ");
    scanf("%29s", NomeExcluir);

   
    while (fscanf(excluirContato, "%s %s\n", c.nome, c.numero) == 2) {  //Verifica os contatos já salvos e salva no arquivo temporario, exceto o que será excluído.
        if (strcmp(c.nome, NomeExcluir) != 0) { //strcmp = string comparate
            fprintf(Auxiliar, "%s\t%s\n", c.nome, c.numero);
        }
    }

    fclose(excluirContato);
    fclose(Auxiliar);
    
	remove("contatos.bin");  // Remover o arquivo original e renomear o arquivo temporário para o original
    rename("temp.bin", "contatos.bin");
    printf("Contato excluido com sucesso.\n");
    fflush(stdin);
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
	
    fclose(arquivo);
    fflush(stdin);
}