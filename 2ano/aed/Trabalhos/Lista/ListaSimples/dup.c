#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "gfx.h"
#include <unistd.h>

typedef struct lista_Dupla{
	int info;
	struct lista_Dupla *prox;
	struct lista_Dupla *ant;
}ListDup;


/*-------------------------------------------------------------------------
DESENHAR A SETA PARA IDENTIFICAR UM NUMERO BUSCADO PELO USUARIO
PARAMETRO: A POSICAO QUE O ELEMENTO ESTA
----------------------------------------------------------------------------*/
void DesenhaSeta(int pos)
{
    int increase;
    increase = 64*pos;

    gfx_line(70+increase, 43, 70+increase,33);
    gfx_line(70+increase, 43, 70+increase+3, 43-3); 
    gfx_line(70+increase, 43, 70+increase-3, 43-3);
    gfx_paint();
    sleep(2);
}

/*--------------------------------------------------------------------------
OBJETIVO: DESENHAR OS NOS DA LISTA DUPLAMENTE ENCADEADA
PARAMETRO: A LISTA
---------------------------------------------------------------------------*/
void desenhaNo_Dup(ListDup *c)
{
    int increase=0;
    char convert[10];
	  
	gfx_set_color(255,0,0);
    gfx_rectangle(50+increase,50,95+increase,70);
    gfx_line(88+increase,50,88+increase,70);
    if(c->prox!=NULL){
    	/*DESENHA SETA INDO*/
        gfx_line(95+increase,54,(95+increase)+15,54);
        gfx_line((95+increase)+10,50,(95+increase)+15,54);
        gfx_line((95+increase)+10,58,(95+increase)+15,54);
    } 
    c=c->prox;
    if(c!=NULL)
    {
    	gfx_line((95+increase)+4,62,(95+increase)+19,62);/*O TAMANHO DA SETA SÃO 15 PIXELS COM O ESPACO QUE SOBRA DE 4 PIXELS, SÃO 19 NO TOTAL
            													ENTAO FACO O DESENHO DO PROXIMO NÓ PARA O ANTERIOR*/
       gfx_line((95+increase)+3,62,(95+increase)+8,59);
       gfx_line((95+increase)+3,62,(95+increase)+8,65);
       increase += 64;
    }
    while(c!=NULL){
       /*DESENHA O RETANGULO*/
       gfx_set_color(255,0,0);
       gfx_rectangle(50+increase,50,95+increase,70);
       gfx_line(88+increase,50,88+increase,70);
       if(c->prox!=NULL){
       		/*DESENHA SETA INDO*/
	        gfx_line(95+increase,54,(95+increase)+15,54);
	        gfx_line((95+increase)+10,50,(95+increase)+15,54);
	        gfx_line((95+increase)+10,58,(95+increase)+15,54);
	        /*DESENHA SETA VOLTANDO*/
	       gfx_line((95+increase)+4,62,(95+increase)+19,62);/*O TAMANHO DA SETA SÃO 15 PIXELS COM O ESPACO QUE SOBRA DE 4 PIXELS, SÃO 19 NO TOTAL
	            													ENTAO FACO O DESENHO DO PROXIMO NÓ PARA O ANTERIOR*/
	       gfx_line((95+increase)+3,62,(95+increase)+8,59);
	       gfx_line((95+increase)+3,62,(95+increase)+8,65);
       }
       sprintf(convert,"%d",c->info);
       gfx_text(53+increase,53,convert);
       increase += 64;  
       c = c->prox;
       /*sleep(1);*/
    }

}

/*--------------------------------------------------------------------------
OBJETIVO: CRIAR O NO CABEÇA
PARAMETRO: O PONTEIRO DA LISTA
RETORNO: O NO CABEÇA
-----------------------------------------------------------------------------*/
ListDup *cabeca(ListDup *ptl)
{
	if((ptl=malloc(sizeof(ListDup)))!=NULL)
	{
		ptl->prox = NULL;
		ptl->ant = NULL;
		return ptl;
	}
	else
	{
		printf("\n---------------SEM MEMORIA--------------");
		exit(404);
	}
	return NULL;
}

/*----------------------------------------------------------------------------
OBJETIVO: BUCAR UM ELEMENTO NA LISTA DUPLA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
		   O NUMERO QUE ESTA PROCURANDO - x
		   UM CONTADOR PARA PEGAR A SUA POSICAO - pos
RETORNO: O NÓ CORRESPONDENTE AO NUMERO
------------------------------------------------------------------------------*/
ListDup *Busca_Dup(ListDup *ptl, int x, int *pos)
{
	ListDup *pt=ptl->prox;
	*pos = 1;

	while(pt!=NULL)
	{
		if(pt->info == x)
			return pt;
		else
			pt = pt->prox;
			*pos=*pos+1;
	}

	return pt;
}

/*----------------------------------------------------------------------------
OBJETIVO: INSERIR UM ELEMENTO NA LISTA ENCADEADA, SEMPRE NO INÍCIO
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: A LISTA MODIFICADA
------------------------------------------------------------------------------*/
ListDup *Insere_Dup(ListDup *ptl)
{
	int x;/*o numero que vai inserir*/
	ListDup *novo;/*VAI SER O NOVO NÓ*/
	ListDup *proximo;/*OBTÉM O PROXIMO NÓ DA LISTA*/

	printf("\n-----------------INSERCAO---------------------\n");
	printf("\nQUAL NUMERO DESEJA INSERIR?");
	scanf("%d",&x);
	__fpurge(stdin);

	if((novo=malloc(sizeof(ListDup)))!=NULL)
	{
		novo->info = x;

		proximo = ptl->prox;

		if(proximo!=NULL)
		{
			novo->prox = ptl->prox;
			ptl->prox = novo;
			novo->ant = ptl;
			proximo->ant = novo;
		}
		else
		{
			novo->prox = ptl->prox;
			ptl->prox = novo;
			novo->ant = ptl;
		}
	}
	return ptl;

}

/*----------------------------------------------------------------------------
OBJETIVO: REMOVER UM ELEMENTO DA LISTA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: A LISTA MODIFICADA
------------------------------------------------------------------------------*/
ListDup *Remove_Dup(ListDup *ptl)
{
	int x;/*o numero que vai inserir*/
	int pos;/*OBTEM A POSICAO DO NO QUE VAI REMOVER, NAO UTILIZAMOS ELE NESSA FUNCAO
			POREM SERVE COMO PARÂMENTERO PARA A FUNCAO Busca_Dup*/
	ListDup *no;/*VAI RECEBER O NÓ DA BUSCA*/
	ListDup *anterior;/*RECEBE O NÓ ANTERIOR DO NÓ ENCONTRADO*/
	ListDup *proximo;/*RECEBE O PROXIMO NÓ DO NÓ ENCONTRADO*/

	if(ptl->prox != NULL){
		printf("\n-----------------REMOCAO---------------------\n");
		printf("\nQUAL NUMERO DESEJA REMOVER?");
		scanf("%d",&x);
		__fpurge(stdin);

		no = Busca_Dup(ptl,x,&pos);

		if(no!=NULL)
		{
			anterior = no->ant;
			proximo = no->prox;

			if(proximo != NULL){
				anterior->prox = proximo;
				proximo->ant = anterior;
			}
			else
			{
				anterior->prox = NULL;
			}
			free(no);
		}
		else
			printf("\n-------------ELEMENTO NAO ESTA NA LISTA------------\n");
	}
	else
		printf("\n---------------SEM ELEMENTOS NA LISTA----------------");
	return ptl;

}

/*----------------------------------------------------------------------------
OBJETIVO: BUSCAR UM ELEMENTO NA LISTA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void Buscando (ListDup *ptl)
{
	int x;/*O NUMERO A SER PROCURADO*/
	int pos;/*OBTEM A POSICAO DO NÓ PARA IMPRIMIR NA GFX*/
	ListDup *no;/*RECEBE O NÓ SE FOI ENCONTRADO*/

	if(ptl->prox!=NULL)
	{
		printf("\n-----------------BUSCAR---------------------\n");
		printf("\nQUAL NUMERO DESEJA BUSCAR?");
		scanf("%d",&x);
		__fpurge(stdin);

		no = Busca_Dup(ptl,x,&pos);

		if(no!=NULL)
		{
			DesenhaSeta(pos);
		}
		else
			printf("\n--------------NUMERO NAO ESTA PRESENTE NA LISTA---------------");
	}
	else
		printf("\n----------------SEM ELEMENTOS NA LISTA--------------\n");
}

/*----------------------------------------------------------------------------
OBJETIVO: DESALOCA OS ELEMENTOS DA LISTA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void Desaloca_Dup(ListDup *ptl)
{
	ListDup *desaloc; /*PONTEIRO PARA AUXILIAR QUANDO FOR DESALOCAR*/

	while(ptl!=NULL)
	{
		desaloc = ptl;
		ptl=ptl->prox;
		free(desaloc);
	}
}

int main ()
{
	ListDup *ptlista=NULL;/*O PONTEIRO PARA LISTA*/
	char op;/*OBTEM AS OPCOES DO MENU*/

	ptlista = cabeca(ptlista);
	do
	{
        gfx_init(800,200,"------------------LISTA DUPLAMENTE ENCADEADA------------------");
        gfx_clear();
		desenhaNo_Dup(ptlista);
		gfx_paint();
        printf("\n-----------------OPERACOES------------------\n");
		printf("\ta) BUSCA DE ELEMENTO;\n");
		printf("\tb) INSERCAO DE ELEMENTO;\n");
		printf("\tc) REMOCAO DE ELEMENTO;\n");
		printf("\td) SAIR;\n\t");
		scanf("%c",&op);
		__fpurge(stdin);
		switch(op)
		{
			case 'a':
				Buscando(ptlista);
			break;

			case 'b':
				ptlista = Insere_Dup(ptlista);
			break;

			case 'c':
				ptlista = Remove_Dup(ptlista);
			break;
		}
		
	}while(op!='d');

	Desaloca_Dup(ptlista);
	gfx_quit();
	return 0;
}
