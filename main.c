#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int dia, mes, ano;
} date;

typedef struct{
  char rua[50], cidade[50], estado[50];
  int numero;
} address;

typedef struct{
  char nome[50], cpf[11];
  int telefone;
  address end;
  date data;
} client;

typedef struct{
  char nome[50];
  int cod, quantidade, preco;
} pizza;

typedef struct{
  client cliente;
  pizza piz;
  int qntd, vlT;
} sell;

int func_menu(int *num);
int func_menu_secund(int *num, char menu[]);

int func_menu(int *num){
  int aux = 0;
  printf("MENU PRINCIPAL \n");
  printf("1- inclusao, alteracao, consulta, delecao do cliente\n");
  printf("2- inclusao, alteracao, consulta, delecao de Pizza\n");
  printf("3- inclusao, alteracao, consulta, delecao de venda\n");
  printf("4- abrir e fechar os arquivos\n");
  printf("5- listar clientes, pizzas ou vendas\n");
  printf("6- para sair do programa\n");
  printf("Opcao: ");
  scanf("%d", &aux);
  *num = aux;
  return *num;
}
int func_menu_secund(int *num, char menu[]){
  int aux = 0;
  printf("\n MENU %s\n", menu);
  printf("1- Inclusao de %s\n", menu);
  printf("2- Alteracao de %s\n", menu);
  printf("3- Consulta de %s\n", menu);
  printf("4- Delecao de %s\n", menu);
  printf("5- Voltar para o menu anterior\n");
  printf("Opcao: ");
  scanf("%d", &aux);
  *num = aux;
  return *num;
}
int listas_menu(int *num){
  int aux = 0;
  printf("MENU DE LISTAS \n");
  printf("1- listar Clientes\n");
  printf("2- listar Pizzas\n");
  printf("3- listar Vendas\n");
  printf("4- clientes que compraram acima de um valor\n");
  printf("5- quantidade de produtos com estoque abaixo de um certo valor\n");
  printf("6- para sair do programa\n ");
  printf("Opcao: ");
  scanf("%d", &aux);
  *num = aux;
  return *num;
}
void cadastro_piz(pizza *piz, int *qntPi){
  int conf = 0, tam;

  if (piz[0].cod == 0)
  {
    *qntPi = 0;
  }
  printf("Adicionando pizzas!");
  do
  {
    conf = 0;
    printf("\nDigite o codigo da pizza: ");
    scanf("%d", &tam);
    for (int j = 0; j <= *qntPi; j++)
    {
      printf("%d\n", piz[j].cod);
      if (tam == piz[j].cod)
      {
        conf = 1;
        printf("\n Nao e possivel adicionar um codigo existente\n");
      }
    }
  } while (conf != 0);
  piz[*qntPi].cod = tam;
  printf("Digite o nome da pizza: ");
  fflush(stdin);
  gets(piz[*qntPi].nome);
  printf("Digite a quantidade de estoque desta pizza: ");
  scanf("%d", &piz[*qntPi].quantidade);
  printf("Digite o preco desta pizza: ");
  scanf("%d", &piz[*qntPi].preco);
  (*qntPi)++;
}
void cadastroClt(client *cli, int *qntCl){
  char cpf[11];
  int resp = 0;
  do
  {
    resp = 0;
    fflush(stdin);
    printf(" Insira o cpf: ");
    gets(cpf);
    for (int j = 0; j < *qntCl; j++)
    {
      printf("%s\n", cpf);
      printf("%s\n", cli[j].cpf);
      if (strcmp(cpf, cli[j].cpf) == 0)
      {
        printf("Nao foi possivel adicionar, cpf ja existente\n");
        resp = 1;
      }
    }
  } while (resp != 0);
  strcpy(cli[*qntCl].cpf, cpf);
  printf("%s", cli[*qntCl].cpf);
  fflush(stdin);
  printf("Digite o nome do cliente: ");
  gets(cli[*qntCl].nome);
  printf("Digite o telefone do cliente: ");
  scanf("%d", &cli[*qntCl].telefone);
  printf("Digite a rua do cliente: ");
  fflush(stdin);
  gets(cli[*qntCl].end.rua);
  printf("Digite a cidade do cliente: ");
  gets(cli[*qntCl].end.cidade);
  printf("Digite o estado do cliente: ");
  gets(cli[*qntCl].end.estado);
  printf("Digite o numero da casa do cliente: ");
  scanf("%d", &cli[*qntCl].end.numero);
  printf("Digite a data de aniversario do cliente\nNeste formato: 11/12/2003\nOpcao: ");
  scanf("%d/%d/%d",&cli[*qntCl].data.dia,&cli[*qntCl].data.mes,&cli[*qntCl].data.ano);
  fflush(stdin);
  (*qntCl)++;
}
void incluirvenda(sell *ven, int *qntVen, pizza *piz, client *cli, int qntCl, int qntPi){
  int i = 0, j=0, cod, qntdPi=0;
  char cpf[11];

  fflush(stdin);
  printf(" Insira o cpf: ");
  gets(cpf);


  while (i < qntCl && strcmp(cli[i].cpf,cpf) != 0)
  {
    i++;
  }
  if (i == qntCl)
  {
    printf("Cpf nao existe\n");
  }
  else{
    strcpy(ven[i].cliente.cpf, cpf);
    printf("Digite o codigo da pizza: ");
    scanf("%d",&cod);
    while (j < qntPi && cod!=piz[j].cod){
      j++;
    }
    if(j==qntPi){
      printf("%d\n",qntPi);
    printf("Codigo nao existe\n");
    }
    else{
      ven[*qntVen].piz.cod = cod;
      printf("%d\n",piz[j].quantidade);
      printf("Digite a quantidade de pizza\n");
      scanf("%d",&qntdPi);
      while(piz[j].quantidade<=qntdPi){
      printf("Não existe essa quantidade de pizza!\n");
      scanf("%d",&qntPi);
        }
      piz[j].quantidade = piz[j].quantidade-qntdPi;
      ven[*qntVen].qntd = qntdPi;
      printf("Venda concluida com sucesso\n");
      (*qntVen)++;
    }
  }
}
void alteracaoClt(client *cli, int qntCl){
  int i=0, op=0;
  char cpf[11];
  printf("Digite o cpf do cliente que deseja alterar os dados: ");
  fflush(stdin);
  gets(cpf);
  while (i < qntCl && strcmp(cli[i].cpf,cpf) != 0)
  {
    i++;
  }
  if(i==qntCl){
    printf("Cpf nao existe\n");
  }
  else{

    printf("Qual informacao deseja alterar:\n1- Nome\n2- Telefone\n3- Rua\n4- Cidade\n5- Estado\n6- Numero de endereco\n");
    scanf("%d",&op);
    fflush(stdin);
    switch (op)
    {
    case 1:
      printf("Digite um novo nome: ");
      gets(cli[i].nome);
      break;
    case 2:
      printf("Digite um novo Telefone: ");
      scanf("%d",&cli[i].telefone);
      break;
    case 3:
      printf("Digite uma nova rua: ");
      gets(cli[i].end.rua);
      break;
    case 4:
      printf("Digite uma nova cidade: ");
      gets(cli[i].end.cidade);
      break;
    case 5:
      printf("Digite um novo estado: ");
      gets(cli[i].end.estado);
      break;
    case 6:
      printf("Digite um novo numero de endereco: ");
      scanf("%d",&cli[i].end.numero);
      fflush(stdin);
      break;
    case 7:
      printf("Digite nova data de aniversario\nExemplo (11/12/2003)\nOpcao:");
      scanf("%d/%d/%d",&cli[i].data.dia, &cli[i].data.mes, &cli[i].data.ano);
      fflush(stdin);
      break;

    default:
      printf("Opcao invalida\n");
      break;
    }
  }
}
void alteracaoPi(pizza *piz, int qntPi){
  int i=0, op=0;
  int cod=0;
  printf("Digite o codigo da pizza que deseja alterar os dados: ");
  scanf("%d",&cod);
  fflush(stdin);
  while (i < qntPi && cod!=piz[i].cod)
  {
    i++;
  }
  if(i==qntPi){
    printf("Codigo nao existe\n");
  }
  else{
    printf("Digite qual alteracao deseja fazer nas pizzas:\n1- Nome\n2- Codigo\n3- Quantidade\n4- Preco\nOpcao: ");
    scanf("%d",&op);
    switch (op)
    {
    case 1:
      printf("Digite um novo nome: ");
      gets(piz[i].nome);
      break;
    case 2:
      printf("Digite um novo Codigo: ");
      scanf("%d",&piz[i].cod);
      break;
    case 3:
      printf("Digite uma nova quantidade: ");
      scanf("%d",&piz[i].quantidade);
      break;
    case 4:
      printf("Digite um novo preco: ");
      scanf("%d",&piz[i].preco);
      break;
    default:
      printf("Opcao invalida\n");
      break;
    }
  }
}
void alteracaoVen(sell *ven, int qntVen, pizza *piz, int qntPi){
  int i = 0, j=0, k=0,l=0, cod, op=0, qnt=0;
  char cpf[11];
  printf("Digite o Cpf do cliente que realizou a venda: ");
  fflush(stdin);
  gets(cpf);
  while (i < qntVen && strcmp(ven[i].cliente.cpf,cpf) != 0)
  {
    i++;
  }
  if (i == qntVen)
  {
    printf("Cpf nao existe\n");
  }
  else{
    printf("Deseja alterar:\n1- Alteracao da Pizza\n2- Alteracao da quantidade\n");
    scanf("%d",&op);
    if(op==1){
    printf("Digite o codigo da nova pizza: ");
    scanf("%d",&cod);
    while (j < qntPi && cod!=piz[j].cod){
      j++;
    }
    if(j==qntPi){
    printf("Codigo nao existe\n");
    }
    else{
      while (k<qntPi && ven[i].piz.cod!=piz[k].cod)
      {
        k++;
      }

      if(ven[i].qntd>piz[j].quantidade){ // conferindo a venda que ja estava no cpf, com a quantidade da nova pizza
        printf("Não existe a quantidade de pizza necessaria para alteracao!\n");
        piz[k].quantidade=piz[k].quantidade-ven[i].qntd;
      }
      else{
        piz[k].quantidade=piz[k].quantidade+ven[i].qntd;
        ven[i].piz.cod = cod;
        piz[j].quantidade = piz[j].quantidade - ven[i].qntd;
        printf("Alteracao feita com sucesso\n");
    }
    }
    }
    else if(op==2){
      printf("Digite a nova quantidade na venda: ");
      scanf("%d",&qnt);
      while (l < qntPi && ven[i].piz.cod!=piz[l].cod){
      l++;
    }
    piz[l].quantidade = piz[l].quantidade+ven[i].qntd;
    if(qnt > piz[l].cod){
      printf("Nao pode realizar a alteracao da quantidade!\n");
      piz[l].quantidade = piz[l].quantidade-ven[i].qntd;
    }
    else{
      piz[l].quantidade = piz[l].quantidade - qnt;
      ven[i].qntd = qnt;
      printf("Quantidade alterada com sucesso!\n");
    }
    }
  }
}
void listClt(client *cli, int qntCl){
    int i;
    for (i=0;i<qntCl;i++) {
        printf("\nCliente %d", i+1);
        printf("\nNome: %s", cli[i].nome);
        printf("\nCPF: %s", cli[i].cpf);
        printf("\nTelefone: %d", cli[i].telefone);
        printf("\nEndereco\n");
        printf("Rua: %s", cli[i].end.rua);
        printf("\nNumero: %d", cli[i].end.numero);
        printf("\nCidade: %s", cli[i].end.cidade);
        printf("\nEstado: %s", cli[i].end.estado);
        printf("\nData de nascimento\n");
        printf("%d/%d/%d\n", cli[i].data.dia, cli[i].data.mes, cli[i].data.ano);
    }
}
void listPiz(pizza *piz, int qntPi){
    int i;
    for (i=0;i<qntPi;i++) {
        printf("\nPizza %d", i+1);
        printf("\nNome: %s", piz[i].nome);
        printf("\nCodigo: %d", piz[i].cod);
        printf("\nQuantidade: %d", piz[i].quantidade);
        printf("\nPreco: %d\n", piz[i].preco);
    }
}
void listVen(sell *venda, int qntVen){
    int i;
    for (i=0;i<qntPi;i++) {
        printf("\nVenda %d", i+1);
        printf("\nCpf cliente: %s", venda[i].cliente);
        printf("\nCodigo da Pizza: %d", venda[i].piz.cod);
        printf("\nNome da pizza: %s", venda[i].piz.nome);
        printf("\nQuantidade: %d", venda[i].qntd);
        printf("\nPreco total da Venda: %d\n", venda[i].vlT);
    }
}

int main()
{
  int qntCl = 0, i = 0, qntPi = 0, qntVen = 0, num;
  char menu[10];
  date data[10];
  address end[10];
  client cli[10];
  pizza piz[10];
  sell venda[10];
  printf("π PIzzaria EXPRESS! π - BEM VINDO(A)\n");
  do
  {
    fflush(stdin);
    num = func_menu(&num);
    fflush(stdin);
    switch (num)
    {
    case 1:
      do
      {
        fflush(stdin);
        char menu[10] = "CLIENTE";
        num = func_menu_secund(&num, menu);
        switch (num)
        {
        case 1:
          printf(" -- CADASTRO DO CLIENTE -- \n");
          cadastroClt(cli, &qntCl);

          break;
        case 2:
          printf(" -- Alterar dados de Clientes --\n");
          alteracaoClt(cli,qntCl);
          break;
        case 3:
          printf(" -- Consulta de Clientes --\n");

          break;
        case 4:
          printf(" -- Delecao de Clientes --\n");
          break;
        case 5:
          printf(" Saindo do menu...\n");
          break;
        default:
          printf(" Opcao invalida!\n");
          break;
        }
      } while (num != 5);
      num = 0;
      break;
    case 2:
      do
      {
        fflush(stdin);
        char menu[10] = "PIZZA";
        num = func_menu_secund(&num, menu);
        switch (num)
        {
        case 1:
          printf(" -- CADASTRO DA PIZZA -- \n");
          cadastro_piz(piz, &qntPi);
          break;
        case 2:
          printf(" -- Alterar dados de Pizzas -- \n");
          alteracaoPi(piz,qntPi);
          break;
        case 3:
          printf(" -- Consulta de Pizza --\n");
          break;
        case 4:
          printf(" -- Delecao de Pizza --\n");
          break;
        case 5:
          printf("Saindo do menu...\n");
          break;
        default:
          printf("Opcao invalida!\n");
          break;
        }

      } while (num != 5);
      num = 0;
      break;
    case 3:
      do
      {
        fflush(stdin);
        char menu[10] = "VENDA";

        num = func_menu_secund(&num, menu);
        switch (num)
        {
        case 1:
          printf(" -- CADASTRO DA VENDA -- \n");
          incluirvenda(venda, &qntVen, piz, cli, qntCl, qntPi);
          break;
        case 2:
          printf(" -- Alterar dados da Venda --\n");
          alteracaoVen(venda, qntVen, piz, qntPi);
          break;
        case 3:
          printf(" -- Consulta de Venda --\n");
          for(int j=0; j<qntVen; j++){
            printf("O cpf: %s\n",venda[j].cliente.cpf);
            printf("O codigo: %d\n",venda[j].piz.cod);
          }
          break;
        case 4:
          printf(" -- Delecao de Venda --\n");

          break;
        case 5:
          printf("Saindo do menu...\n");
          break;
        default:
          printf("Opcao invalida!\n");
          break;
        }
      } while (num != 5);
      num = 0;
      break;
    case 4:
      // abrir e fechar os arquivos;
      break;
    case 5:
        do{
        fflush(stdin);
        num = listas_menu(&num);
        fflush(stdin);
        switch (num){
        case 1:
            printf(" LISTAR os CLIENTES ");
            listClt(cli, qntCl);
          break;
        case 2:
            printf(" LISTAR as PIZZAS ");
            listPiz(piz, qntPi);
          break;
        case 3:
            printf(" LISTAR as VENDAS ");
            listVen(venda, qntVen);
          break;
        case 4:
           
        case 5:
          break;
        case 6:
            printf("Saindo do menu...\n");
          break;
        default:
          printf("Opcao invalida!\n");
          break;
        }
      } while (num != 6);
      num = 0;
        break;
    case 6:
      printf("\nSAINDO DO PROGRAMA :D\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }

  } while (num != 6);

  return 0;
}
