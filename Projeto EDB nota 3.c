#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

typedef struct {
    int codigo;
    char descricao[50];
    float preco;
    int qnt;
} Produto;

typedef struct {
    int cpf;
    char nome[20];
    int celular;
} Cliente;

typedef struct no {
   int h; //ALTURA
   Cliente info;
   struct no *dir;
   struct no *esq;
}NoAVL;

typedef struct n{
    Produto info;
    struct n *dir, *esq;
}ArvoreProduto;

typedef struct {
	int entrada;
	int saida;
}Operacao;

typedef struct l{
	char data;
	Produto info;
	Operacao op;
	struct l *prox;
}Estoque;


NoAVL* inicializa() {
   return NULL;
}



/*############ Altura do n� #############*/

int alt(NoAVL *raiz) {
  if (raiz == NULL) return -1;
  return raiz->h;
}



/*############ Maior n�mero #############*/

int maior(int x, int y) {
   if (x > y) return x;
   else       return y;
}



/*############ Rota��o � direita #############*/

NoAVL* Direita(NoAVL *raiz) {
   NoAVL *aux;
   aux = raiz->esq;
   raiz->esq = aux->dir;
   aux->dir = raiz;

   raiz->h = maior(alt(raiz->dir), alt(raiz->esq)) + 1;
   aux->h = maior(alt(aux->esq), raiz->h) + 1;

   return aux;
}



/*############ Rota��o � esquerda #############*/

NoAVL* Esquerda(NoAVL *raiz) {
   NoAVL *aux;
   aux = raiz->dir;
   raiz->dir = aux->esq;
   aux->esq = raiz;

   raiz->h = maior(alt(raiz->dir), alt(raiz->esq)) + 1;
   aux->h = maior(alt(aux->dir), raiz->h) + 1;

   return aux;
}



/*############ Rotal��o dupla #############*/

NoAVL* EsquerdaD(NoAVL *raiz) {
   raiz->esq = Esquerda(raiz->esq);
   return Direita(raiz);
}



/*############ Rota��o dupla #############*/

NoAVL* DireitaE(NoAVL *raiz) {
   raiz->dir = Direita(raiz->dir);
   return Esquerda(raiz);
}



/*##########################################
############## BALANCEAMENTO ###############
##########################################*/

NoAVL *balancear(NoAVL *raiz){

    //Fator de balanceamento da raiz
    if (alt(raiz->esq) - alt(raiz->dir) < -1){

        //Fator de balanceamento do no a esquerda da raiz
        if(alt(raiz->esq->esq) - alt(raiz->esq->dir) > 0) raiz->esq = Esquerda(raiz->esq);

        raiz = Direita(raiz);
    }

    //Fator de balanceamento da raiz
    else if (alt(raiz->esq) - alt(raiz->dir) > 1){

        //Fator de balanceamento do no a direita da raiz
        if (alt(raiz->dir->esq) - alt(raiz->dir->dir) < 0) raiz->dir = Direita(raiz->dir);

        raiz = Esquerda(raiz);

    }

    return raiz;
}



/*##########################################
############# INSERIR CLIENTE ##############
##########################################*/

NoAVL* InserirCliente(NoAVL *raiz, Cliente c) {
   if (raiz == NULL) {
    raiz = (NoAVL*)malloc(sizeof(NoAVL));
    raiz->info = c;
    raiz->h = 0;
    raiz->esq = NULL;
    raiz->dir = NULL;
    printf("\nCliente cadastrado!");
    return raiz;
   }
   else {
        if(c.cpf < raiz->info.cpf) {
            raiz->esq = InserirCliente(raiz->esq, c);
            if((alt(raiz->esq) - alt(raiz->dir)) == 2)
               if(c.cpf < raiz->esq->info.cpf)
                  raiz = Direita(raiz);
               else
                  raiz = EsquerdaD(raiz);
        } else {
         if (c.cpf >= raiz->info.cpf) {
              raiz->dir = InserirCliente(raiz->dir, c);
              if((alt(raiz->dir) - alt(raiz->esq)) == 2)
                 if(c.cpf >= raiz->dir->info.cpf)
                    raiz = Esquerda(raiz);
                 else
                    raiz = DireitaE(raiz);
            }
        }

        raiz = balancear(raiz);

        raiz->h = maior(alt(raiz->esq), alt(raiz->dir)) + 1;

        return raiz;
   }
}



/*##########################################
############# BUSCAR CLIENTE ###############
##########################################*/

NoAVL *buscarCliente(NoAVL *raiz, int codigo){

    if (raiz == NULL){

        return raiz;

    }else{

        NoAVL *aux = raiz;

        while(aux != NULL){

            if(codigo < aux->info.cpf) aux = aux->esq;

            if(codigo > aux->info.cpf) aux = aux->dir;

            else return aux;

        }

    }

}


/*##########################################
############# ALTERAR CLIENTE ##############
##########################################*/

NoAVL* AlterarCliente(NoAVL *raiz, int id){

    if(raiz != NULL){
        if (id == raiz->info.cpf) {

            int celular, i;
            char nome[20];

            printf("Digite o novo nome do cliente : ");
            scanf("%s", &nome);
            for (i = 0; i < 20; i++) raiz->info.nome[i] = nome[i];
            printf("Digite o novo numero de celular do cliente : ");
            scanf("%d", &celular);
            raiz->info.celular = celular;

            raiz = balancear(raiz);

            printf("\n Cliente Alterado com sucesso!");

            return raiz;

        } else if (id < raiz->info.cpf) AlterarCliente(raiz->esq, id);
          else                          AlterarCliente(raiz->dir, id);
    }
}

NoAVL* procuraMenor(NoAVL *atual){
    NoAVL *no1 = atual;
    NoAVL *no2 = atual->esq;
    while(no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}


/*##########################################
################ MENOR CPF #################
##########################################*/

NoAVL *menorNoC(NoAVL *raiz){

    if (raiz == NULL) return raiz;

    else{

        if (raiz->esq == NULL) return raiz;
        else return menorNoC(raiz->esq);

    }

}



/*##########################################
############# REMOVER CLIENTE ##############
##########################################*/

NoAVL* removerCliente(NoAVL *raiz, int valor){
    NoAVL *aux;

    if (raiz != NULL){
        //SE O VALOR A SER REMOVIDO FOR MENOR QUE O DO N� ATUAL
        if (valor < raiz->info.cpf) raiz = removerCliente(raiz->esq, valor);
        else{
            //SE O VALOR A SER REMOVIDO FOR MAIOR QUE O DO N� ATUAL
            if (valor > raiz->info.cpf) raiz = removerCliente(raiz->dir, valor);
            //N� ENCONTRADO
            else{

                if (raiz->esq != NULL && raiz->dir != NULL){

                    //VERIFICAR SE OS FILHOS N�O S�O NULL
                    //SE N�O FOREM, BUSCAR O MENOR N� A PARTIR DO FILHO DA DIREITA
                    aux = menorNoC(raiz->esq);
                    raiz->info = aux->info;
                    raiz = removerCliente(raiz->dir, valor);

                }else{

                    //SE AMBOS OS FILHOS FOREM NULL, OU SE SOMENTE O DA DIREITA FOR NULL
                    //APENAS REMOVER O N� ATUAL E AJUSTAR OS PONTEIROS
                    aux = raiz;
                    if(raiz->esq == NULL){

                        raiz = raiz->dir;

                    }else{

                        //SE O N� DA ESQUERDA N�O FOR NULL, O N� PAI
                        //APONTAR� PARA O FILHO DA ESQUERDA DO N� ATUAL
                        raiz = raiz->esq;

                    }

                free(aux);

                }

            }

        }

    }

    return raiz;

}



/*##########################################
############# EXIBIR CLIENTE ###############
##########################################*/

NoAVL* ExibirCliente(NoAVL *raiz, int id){

    if(raiz != NULL){
        if (id == raiz->info.cpf)     return raiz;
        else if (id < raiz->info.cpf) ExibirCliente(raiz->esq, id);
        else                          ExibirCliente(raiz->dir, id);
    }

}


/*########################################################
############## INSERIR PRODUTO ###########################
########### INSERE OS DADOS DO NOVO NO ATUAL #############
########################################################*/

ArvoreProduto *inserirProduto(ArvoreProduto *atual, Produto novo){
    ArvoreProduto *aux = atual;

    //�rvore vazia
    if (aux == NULL){
    	aux = (ArvoreProduto*)malloc(sizeof(ArvoreProduto));
        aux->info = novo;
        aux->dir = NULL;
        aux->esq = NULL;

    //Inserir � esquerda
    }else if (novo.preco < aux->info.preco){
        aux = inserirProduto(aux->esq, novo);

    //Inserir � direita
    }else if (novo.preco >= aux->info.preco){
        aux = inserirProduto(aux->dir, novo);
    }

    printf("Produto adicionado com sucesso!");

    Sleep(1200);

    return aux;
}



/*##########################################
############# BUSCAR PRODUTO ###############
##########################################*/

ArvoreProduto *buscarProduto(ArvoreProduto *raiz, int codigo){
    ArvoreProduto *aux = raiz;

    //SE A �RVORE ESTIVER VAZIA
    if(aux == NULL){

        printf("N�o h� nenhum produto com este c�digo.");
        Sleep(1200);
        return NULL;

    }

    //SE A �RVORE N�O ESTIVER VAZIA, O LA�O VAI SE REPETIR AT� QUE SE ENCONTRE O N�
    //OU AT� QUE SE CHEGUE AO FIM DA �RVORE SEM ENCONTRAR O N�
    while (aux != NULL){

        if (codigo < aux->info.codigo) aux = aux->esq;

        else if (codigo > aux->info.codigo) aux = aux->dir;

        else{

            printf("\n\nC�digo: %d", aux->info.codigo);
            printf("\nDescri��o: %s", aux->info.descricao);
            printf("\nPre�o: %f", aux->info.preco);
            printf("\nQuantia em estoque: %s", aux->info.qnt);

            //getch();

            return aux;

        }

    }

    //CHEGOU AO FIM DA �RVORE SEM ENCONTRAR O N�
    printf("N�o h� nenhum produto com este c�digo.");

    //getch();

    return aux;
}



/*##########################################
############ EXIBIR PRODUTOS ###############
##########################################*/

void exibirProdutos(ArvoreProduto *raiz){

    //EXIBI��O POR ORDEM CRESCENTE DE PRE�OS

    if (raiz->esq != NULL) exibirProdutos(raiz->esq);

    printf("==================================================");
    printf("\nC�digo: %d", raiz->info.codigo);
    printf("\nDescri��o: %s", raiz->info.descricao);
    printf("\nPre�o: %.2f", raiz->info.preco);
    //printf("\nQuantia em estoque: %s", raiz->info.qnt);

    if (raiz->dir != NULL) exibirProdutos(raiz->dir);

}




/*##########################################
#### EXIBIR ESTOQUE DE UM �NICO PRODUTO ####
##########################################*/

void exibirEstoque(ArvoreProduto *raiz, int codigo){

    ArvoreProduto *aux = raiz;

    if(aux == NULL){

        printf("N�o h� nenhum produto com este c�digo.");
        Sleep(1200);
        return;

    }

    while(aux != NULL){

        if (codigo < aux->info.codigo) aux = aux->esq;
        else if (codigo > aux->info.codigo) aux = aux->dir;
        else{

            printf("Quantia em estoque de '%s': %d", aux->info.descricao, aux->info.qnt);

        }

    }

    printf("N�o h� nenhum produto com este c�digo.");
    Sleep(1200);
    return;

}



/*##########################################
############### MENOR PRE�O ################
##########################################*/

ArvoreProduto *menorNoP(ArvoreProduto *raiz){

    if (raiz == NULL) return raiz;

    else{

        if (raiz->esq == NULL) return raiz;
        else return menorNoP(raiz->esq);

    }

}




/*##########################################
############ REMOVER PRODUTOS ##############
##########################################*/

ArvoreProduto *removerProduto (ArvoreProduto *raiz, int codigo){

    ArvoreProduto *aux;

    if(raiz != NULL){
        //SE O VALOR A SER REMOVIDO FOR MENOR QUE O DO N� ATUAL
        if(codigo < raiz->info.codigo) raiz = removerProduto(raiz->esq, codigo);
        else{
            //SE O VELOR A SER REMOVIDO FOR MAIOR QUE O N� ATUAL
            if(codigo > raiz->info.codigo) raiz = removerProduto(raiz->dir, codigo);
            //N� ENCONTRADO
            else{

                if(raiz->esq != NULL && raiz->dir != NULL){

                    //VERIFICAR SE OS FILHOS N�O S�O NULL
                    //SE N�O FOREM, BUSCAR O MENOR N� A PARTIR DO FILHO DA DIREITA
                    aux = menorNoP(raiz->esq);
                    raiz->info = aux->info;
                    raiz = removerProduto(raiz->dir, raiz->info.codigo);

                }else{

                    //SE AMBOS OS FILHOS FOREM NULL, OU SE SOMENTE O DA DIREITA FOR NULL
                    //APENAS REMOVER O N� ATUAL E AJUSTAR OS PONTEIROS
                    aux = raiz;
                    if(raiz->esq == NULL){

                        raiz = raiz->dir;

                    }else{

                        //SE O N� DA ESQUERDA N�O FOR NULL, O N� PAI APONTAR� PARA O FILHO DA ESQUERDA
                        //DO N� ATUAL
                        raiz = raiz->esq;

                    }

                free(aux);

                }

            }

        }

    }

    return raiz;

}


Estoque* EntSai(Estoque *e,int dec){
	if(dec == 1){
		
	}
	if(dec == 2){
		
	}
}
/*##########################################
################ COMPRAR ###################
##########################################*/

ArvoreProduto *comprar(ArvoreProduto *raiz, int codigo){

    //O PRODUTO EXISTE NA �RVORE
    if (buscarProduto(raiz, codigo) != NULL){

        int q;

        printf("==========COMPRAR==========");
        printf("\n Quantas unidades? ");
        scanf("%d", &q);

        raiz->info.qnt += q;

    }else printf("O produto n�o existe no estoque. Adicione-o antes.");

    getch();

}




/*##########################################
################# VENDER ###################
##########################################*/

NoAVL *vender();




/*##########################################
############################################
############# FUN��O PRINCIPAL #############
############################################
##########################################*/

void menu () {

    setlocale(LC_ALL, "portuguese");

    system("color 0b");

    int op;
    int codigo;//VARI�VEL USADA NA BUSCA
    int x = 1;

    Cliente c;
    Estoque *e;
    e = NULL;

    ArvoreProduto *p = NULL;

    Produto novo;//VARI�VEL AUXILIAR USADA NAS OPERA��ES
    novo.codigo = 0;

    NoAVL *raiz = inicializa();

      while(x == 1) {
        limpatela:system("cls");

        printf("\n############################################# Thalyson Luan Menezes Pereira ############################################\n");
        printf("############################################# Joao Victor Pinto Goncalves ##############################################\n\n");

        printf("(1)  - Inserir produto\n");//OK
        printf("(2)  - Buscar produto\n");//OK
        printf("(3)  - Alterar produto\n");//OK
        printf("(4)  - Excluir produto\n");//OK
        printf("(5)  - Exibir produto\n");//OK
        printf("(6)  - Cadastrar Cliente\n");//OK
        printf("(7)  - Alterar Cliente\n");//OK
        printf("(8)  - Excluir Cliente\n");
        printf("(9)  - Exibir Cliente\n");//OK
        printf("(10) - Realizar entrada ou saida de estoque de produto\n");//????
        printf("(11) - Exibir estoque atual de um produto\n");//OK
        printf("(12) - Sair\n");//OK
        printf("\nDigite a opcao: ");
        scanf("%d", &op);

        switch(op) {

    /*###################################
    ####### INSER��O DE PRODUTOS#########
    ###################################*/
            case 1:
                system("cls");

                printf("Pre�o: ");
                scanf("%f", &novo.preco);

                printf("Quantidade: ");
                scanf("%d", &novo.qnt);
                
                printf("Descricao: ");
                fflush(stdin);
                gets(novo.descricao);

                novo.codigo++;
                printf("Seu codigo : %d\n", novo.codigo);

                p = inserirProduto(p, novo);
				getch();
                break;

    /*###################################
    ######## BUSCA DE PRODUTOS###########
    ###################################*/
            case 2:
                system("cls");

                printf("Digite o c�digo do produto: ");
                scanf("%d", &codigo);

                buscarProduto(p, codigo);

                getch();

                break;

    /*###################################
    ######### ALTERAR PRODUTOS###########
    ###################################*/
            case 3:
                system("cls");

                exibirProdutos(p);

                printf("\nDigite o c�digo do produto que deseja alterar: ");
                scanf("%d", &codigo);

                system("cls");

                if(buscarProduto(p, codigo) != NULL){

                    printf("\nDigite a descri��o do produto: ");
                    gets(novo.descricao);

                    printf("\nDigite o novo pre�o: ");
                    scanf("%f", novo.preco);

                    printf("\nDigite a quantidade:");
                    scanf("%d", &novo.qnt);

                    p = removerProduto(p, codigo);
                    p = inserirProduto(p, novo);

                printf("Produto alterado.");
                getch();

                }

                break;

    /*###################################
    ####### EXCLUS�O DE PRODUTOS ########
    ###################################*/
            case 4:
                system("cls");

                printf("Digite o c�digo do produto: ");
                scanf("%d", &codigo);

                if (buscarProduto(p, codigo) != NULL) p = removerProduto(p, codigo);
                else{

                    printf("N�o h� nenhum produto com este c�digo.");
                    Sleep(1200);

                }

                break;

    /*###################################
    ########### EXIBIR PRODUTOS##########
    ###################################*/
            case 5:
                system("cls");

                exibirProdutos(p);
                getch();

                break;

    /*###################################
    ######### CADASTRAR CLIENTE #########
    ###################################*/
            case 6:
                system("cls");

                printf("Digite o nome do cliente: "); // N�o aceita espa�o em branco no nome
                scanf("%s", &c.nome);

                printf("Digite a CPF do cliente: "); // Nao aceita espa�o em branco
                scanf("%d", &c.cpf);

                printf("Digite o numero de celular do cliente: "); // N�o aceita espa�o em branco
                scanf("%d", &c.celular);

                raiz = InserirCliente(raiz, c);
                getch();

                break;

    /*###################################
    ########## ALTERAR CLIENTE ##########
    ###################################*/
            case 7:
                system("cls");

                if (raiz == NULL) printf("A arvore esta vazia!");

                else {

                    int id;
                    printf("Digite o CPF do Cliente : ");
                    scanf("%d", &id);
                    NoAVL *aux = AlterarCliente(raiz, id);
                    if ( aux == NULL) printf("\n N�o encontrado");

                }

                getch();
                break;

     /*###################################
     ########## EXCLUIR CLIENTE ##########
     ###################################*/
            case 8:
                system("cls");

                printf("Digite o CPF do cliente: ");
                scanf("%d", &codigo);

                if(buscarCliente(raiz, codigo) != NULL){

                    raiz = removerCliente(raiz, codigo);
                    raiz = balancear(raiz);

                    printf("Cliente exclu�do.");

                }else printf("O cliente solicitado n�o existe.");

                getch();


                break;

     /*###################################
     ########## EXIBIR CLIENTE ###########
     ###################################*/
            case 9:
                system("cls");
                if (raiz == NULL) printf("A �rvore esta vazia!");
                else {
                    int id;
                    printf("Digite o CPF do Cliente : ");
                    scanf("%d", &id);
                    NoAVL *aux = ExibirCliente(raiz, id);
                    if (aux != NULL){
                        printf("\nnome do cliente: %s", aux->info.nome);
                        printf("\nn�mero de celular do cliente: %d", aux->info.celular);
                    }else printf("\n N�o encontrado");
                }
                getch();

                break;


            case 10:
                system("cls");
                printf("Que operacao deseja realizar: entrada[1] / saida[2]");
                int dec;
                scanf("%d", &dec);
                break;

     /*###################################
     ########## EXIBIR ESTOQUE ###########
     #########DE UM �NICO PRODUTO#########
     ###################################*/
            case 11:
                system("cls");

                printf("Digite c�digo do produto: ");
                scanf("%d", &codigo);

                exibirEstoque(p, codigo);

                break;

     /*###################################
     ############### SAIR ################
     ###################################*/
            case 12:
                system("cls");
                printf("\n\n\t\t SAIU\n\n");
                exit(0);
            //CASO A OP��O DIGITADA SEJA DIFERENTE DAS DISPON�VEIS
            default:
                printf("Op��o inv�lida");
                Sleep(1200);

                break;

    }  // Fim do switch case
  } // Fim do laco while
} // fim da fun��o menu

int main () {
  menu();

}
