#ifndef ficheiroClientes_h
#define ficheiroClientes_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executavel.c"

int NIF_mudar_saldo, NIF_mudar_saldo1; // variaveis globais
float alterar_saldo, alterar_saldo1;

typedef struct registoC
{
  char username[20]; 
  char password[20];
  int NIF;
  float saldo;
  struct registoC* seguinte;
  char localizacaoC[20];

} Cliente;


Cliente* inserirCliente(Cliente* inicio, char username[], char password[], int NIF, float saldo, char localizacaoC[]); // Inser��o de um novo registo
void listarCliente(Cliente* inicio); // listar na consola o conte�do da lista ligada
int existeCliente(Cliente* inicio, int NIF); // Determinar exist�ncia do 'codigo' na lista ligada 'inicio'
Cliente* removerCliente(Cliente* inicio, int NIF); // Remover um meio a partir do seu c�digo
int guardarCliente(Cliente* inicio);
Cliente* lerCliente();

void Consultar_Dados_Clientes() // Consulta de dados dos clientes de modo a facilitar a leitura de clientes por parte do gestor
{
	Cliente* clienteC = NULL;
	int voltar;
	clienteC = lerCliente(clienteC);
	listarCliente(clienteC);
	printf("\n\nPrima qualquer tecla para voltar\n");
	printf("Opcao:");
	scanf("%d", &voltar);
	switch (voltar)
	{
		default:
			return Menu_Opcoes_Gestor();
	}
}
////////////////////////////////////////////// Modificar Saldo de Clientes ///////////////////////////////////////////////

void adicionarSaldoG(Cliente* inicio, int NIF_mudar_saldo, float alterar_saldo) // Funcao para o gestor adicionar saldo a um cliente
{
  Cliente* current = inicio;
  while (current != NULL) {
      if(current->NIF == NIF_mudar_saldo) {
          current->saldo += alterar_saldo;
          guardarCliente(inicio); // saves the data in the file after updating the balance
          return;
      }
      current = current->seguinte;
  }
  printf("Cliente nao encontrado.\n");
}

void removerSaldoG(Cliente* inicio, int NIF_mudar_saldo1, float alterar_saldo1) //Funcao para o gestor remover saldo a um cliente 
{
    Cliente* current = inicio;
    while (current != NULL) {
        if(current->NIF == NIF_mudar_saldo1) {
            current->saldo -= alterar_saldo1;
            guardarCliente(inicio); // saves the data in the file after updating the balance
            return;
        }
        current = current->seguinte;
    }
    printf("Cliente nao encontrado.\n");
}


////////////////////////////////////////////////// Principais //////////////////////////////////////////////////

Cliente* inserirCliente(Cliente* inicio, char username[], char password[], int NIF, float saldo, char localizacaoC[]) // inserir novo cliente
{
  
  if (!existeCliente(inicio, NIF))
  {
  Cliente * novo = malloc(sizeof(struct registoC));
  if (novo != NULL)
  {
    strcpy(novo->username,username);
    strcpy(novo->password,password);
    strcpy(novo->localizacaoC,localizacaoC);
    novo->NIF = NIF;
    novo->saldo = saldo;
    novo->seguinte = inicio;
    return(novo);
  }
  } else return(inicio);
}

int existeCliente(Cliente* inicio, int NIF) //verificar se ja existia cliente ( utilizada no registo)
{
  while(inicio!=NULL)
  {
    if (inicio->NIF == NIF) return(1);
    inicio = inicio->seguinte;
  }
 return(0);
}

Cliente* removerCliente(Cliente* inicio, int NIF) // remover um cliente atraves do seu NIF
{
  Cliente *anterior=inicio, *atual=inicio, *aux;

  if (atual==NULL) return(NULL);
  else if (atual->NIF == NIF) // remo��o do 1� registo
  {
    aux = atual->seguinte;
    free(atual);
    return(aux);
  }
  else
  {
    while ((atual!=NULL)&&(atual->NIF!=NIF)) 
    {
      anterior = atual;
      atual = atual->seguinte;
    }
    if (atual==NULL) 
    {
      return(inicio);
    }
    else
    {
      anterior->seguinte = atual->seguinte;
      free(atual);
      return(inicio);
    }
  }
}

int guardarCliente(Cliente* inicio) // Guardar cliente em txt
{
  FILE* fp;
  fp = fopen("DadosCliente.txt","w");
  if (fp!=NULL)
  {
    Cliente* aux= inicio;
    while (aux != NULL)
    {
      fprintf(fp, "%s;%s;%d;%.2f;%s;\n", aux->username, aux->password, aux->NIF, aux->saldo, aux->localizacaoC);
      aux = aux->seguinte;
    }
    fclose(fp);
    return(1);
 }
 else return(0);
}

void listarCliente(Cliente * inicio) // Listar os clientes para o utilziador
{
  while (inicio != NULL)
  {
    printf("Username: %s ; Password: %s ; NIF: %d ; Saldo: %.2f ; Localizacao: %s ;\n",inicio->username,inicio->password, inicio->NIF, inicio->saldo, inicio->localizacaoC);
    inicio = inicio->seguinte;
  }
}


Cliente* lerCliente() //realizar a leitura de clientes ( de forma de manter a lista atualizada)
{
  FILE* fp;
  char user[20];
  char pass[20];
  char localizacaoC[20];
  int NIF;
  float saldo;
  Cliente* aux=NULL;
  fp = fopen("DadosCliente.txt","r");
  if (fp!=NULL)
  {
      while (fscanf(fp, "%[^;];%[^;];%d;%f;%[^;];\n", user, pass, &NIF, &saldo, localizacaoC) ==5)
      { 
        aux = inserirCliente(aux, user, pass, NIF, saldo, localizacaoC);
      }
    fclose(fp);
  }
  return aux;
}

int opregistarClienteG() // Menu para facilitar o gestor, na modificacao de dados dos clientes
{
  int op1;
  printf("\n\nAlterar Dados Clientes\n");
  printf("1. Inserir Cliente\n");
  printf("2. Listar Clientes\n");
  printf("3. Remover Cliente\n");
  printf("4. Adicionar Saldo a Cliente\n");
  printf("5. Remover Saldo a Cliente\n");
  printf("0. Sair\n");
  printf("9. Voltar\n\n");
  printf("Opcao:");
  scanf("%d",&op1);
  printf("\n\n");
  return(op1);
}

int Menu_Modificar_ClientesG() // Menu orientativo
{
  Cliente* clienteC = NULL; 
  clienteC = lerCliente(); // Lista ligada vazia 
  int op1;
  char username[20];
  char password[20];
  char localizacaoC[20];
  int NIF, localizacao1;
  float saldo;
  do
  {
    op1 = opregistarClienteG();
    switch(op1)
    {
      case 1: 
        printf("Username:\n");
        scanf("%s",username);
        scanf("%*c"); 
        printf("Password:\n");
        scanf("%s", password);
        scanf("%*c");
        printf("NIF:\n");
        scanf("%d",&NIF);
        printf("saldo:\n");
        scanf("%f",&saldo);
        
        do { 
            printf("Introduza a localizacao do cliente (1-6): ");
            scanf("%s", localizacaoC);
            localizacao1 = atoi(localizacaoC);
        } while (localizacao1 < 1 || localizacao1 > 6);
        clienteC = inserirCliente(clienteC, username, password, NIF, saldo, localizacaoC);
        guardarCliente(clienteC);
        printf("\nCliente inserido com sucesso!\n\n");
        Menu_Opcoes_Gestor();
        break;
      case 2: 
        listarCliente(clienteC); 
        break;
      case 3: 
        printf("NIF do meio do cliente a remover?\n");
        scanf("%d",&NIF);
        clienteC = removerCliente(clienteC, NIF);
        guardarCliente(clienteC);
        printf("\nCliente removido com sucesso!\n\n");
        Menu_Opcoes_Gestor();
      case 4:
        printf("NIF do Cliente: ");
        scanf("%d", &NIF_mudar_saldo);
        printf("Valor a adicionar: ");
        scanf("%f", &alterar_saldo);
        adicionarSaldoG(clienteC, NIF_mudar_saldo, alterar_saldo);
        clienteC = guardarCliente(clienteC);
        printf("\nSaldo adicionado com sucesso!\n\n");
        Menu_Opcoes_Gestor();
        //break;
      case 5:
        printf("NIF do Cliente: ");
        scanf("%d", &NIF_mudar_saldo1);
        printf("Valor a remover: ");
        scanf("%f", &alterar_saldo1);
        removerSaldoG(clienteC, NIF_mudar_saldo1, alterar_saldo1);
        clienteC = guardarCliente(clienteC);
        Menu_Opcoes_Gestor();
        //break;
      case 0:
        exit(1);
        break;
      case 9:
        Menu_Opcoes_Gestor();
    }
  } while (op1!=0);
  return 0;
}


#endif