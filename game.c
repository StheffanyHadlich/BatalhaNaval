#include <stdlib.h>
#include <stdio.h>
#include <conio.c>
#include <time.h>

void apresentaMatriz( int N,int mUsuario[][N],int color);
void displayBatalhaNaval();
void musicaFinal();
void displayBatalhaNaval();

int divs(float a, float b){
  int c = a/b;
  return c;
}

int main(){
  const int N = 7;
  int mSistema[N][N],mUsuario[N][N];
  int i,j,L,C,nomeLinhas,nomeColunas,linha,coluna,vitoria,n=0,nJogadores,jogador=0;
  
  char coordenadas[3],lin,col,saida;
  
  srand(time(NULL));

  apresentacao();
  
  system("cls");
  textcolor(15);
  displayBatalhaNaval();

  printf("\n\nDigite o numero de Jogadores: ");
  scanf("%d",&nJogadores);
  
  char nome[nJogadores][20],nomeaux[20];
  int pontos[nJogadores],aux;
  
  system("cls");

  do{
    displayBatalhaNaval();

    printf("\n\nDigite o nome do jogador %d:",jogador+1);
    scanf("%s",nome[jogador]);
    system("cls");

    for (i=0 ;i<N;i++){ //Esse for vai carregar A com valores "tiro vazio" onde depois serao as posições dos barcos
      for(j=0;j<N;j++){
        mSistema[i][j]=15;
      }
    }

    nomeColunas=65;//Variavel para carregar a coluna '1 - 7'
    for (i=1 ;i<N; i++){ //Esse for carrega a matriz apresentavel ao usuario
      mUsuario[0][0]=14;
      nomeLinhas=49;//Variavel para carregar a linha 'A - F'
      for(j=1;j<N;j++){
        mUsuario[i][j]=126;// Apresenta os '~' ao usuario
        mUsuario[0][j]=nomeLinhas;//Carrega a linha de '1 - 7'
        nomeLinhas++;
      }
      mUsuario[i][0]=nomeColunas;//Carrega a coluna de 'A a F'
      nomeColunas++;
    }

  /* -------------------------RANDOM DOS BARCOS---------------------------------*/
  //Randon dos 2 Cruzadores
  i=0;
  do {
    L = (rand()%6)+1; // L variavel para pegar um valor random para linha
    C = (rand()%5)+1; // C variavel para pegar um valor random para coluna
  
    if (mSistema[L][C]==15 && mSistema[L][C+1]==15){ // If para verificar se nao existe nenhum barco ja na posicao
      mSistema[L][C]=1;
      mSistema[L][C+1]=1;
      i++;
    }
  }while(i<2);//While para carregar 2 Cruzadores
  
  //Randon dos 2 Hidroaviões
  i=0;
  do {
    L = (rand()%5)+2;
    C = (rand()%4)+1;
   
   if (mSistema[L][C]==15 && mSistema[L][C+1]==15 && mSistema[L][C+2]==15 && mSistema[L-1][C+1]==15 && mSistema[L-1][C]==15 && mSistema[L-1][C+2]==15){ //If para verificar se nao existe nenhum barco na posicao
      mSistema[L][C]=2;
      mSistema[L][C+2]=2;
      mSistema[L-1][C+1]=2;
      i++;
    }
  }while(i<2);// Para carregar 2 Hidros
  /* ---------------------------------------------------------------------------*/

  vitoria=0;//Variavel que vai armazenar quantos acertos a pessoa teve, para terminar o jogo
  pontos[jogador]=0;//Variavel para guardar os pontos

  /* --------------------------INICIO DO JOGO-----------------------------------*/
  apresentaMatriz(N,mUsuario,1);
  while (vitoria<10){ //Loop até a vitória
    int coorL,coorC;
    scanf(" %[^\n]",coordenadas); //string para ler a coordenada
    
    coorL=0;
    coorC=0;
    coorL= toupper(coordenadas[0])-64;//Transforma 'A .. F' em um valor "Valido em decimal" para poder ser comparado
    coorC= toupper(coordenadas[1])-48;//Transforma '1 .. 6' em um valor "Valido em decimal" para poder ser comparado
    system("cls");

    while (coorL>N-1 || coorL<0 || coorC>N-1 || coorC<0){// Caso a coordenada for invalida ele ficara pedindo valores até ser valida
      printf("\n Voce pode acertar:\n\n Tiro na agua: (%c)   Cruzadores: (%c%c)\n\n Hidroavioes: (%c)\n             (%c %c)\n\n",15,1,1,2,2,2);
      for (i=0 ;i<N; i++){ //Esse for apresenta a matriz ao usuario
        textbackground(1);
        for(j=0;j<N;j++){
          printf(" %c ",mUsuario[i][j]);
        }
        printf("\n                     \n");
      }

      textcolor(15);
      textbackground(0);
      printf("\nCoordenada invalida!\nDigite a coordenada (Por Exemplo: C3):");
      
      scanf(" %[^\n]",coordenadas);
      coorL= toupper(coordenadas[0])-64;
      coorC= toupper(coordenadas[1])-48;
      system("cls");
    }

    //Caso a coordenada estiver válida contina aqui
    if(mUsuario[coorL][coorC]=='~'){ //Verificar se nao e uma coordenada repetida
      pontos[jogador]++; //Se nao for a variavel de pontos e incrementada
    }

    if(mSistema[coorL][coorC]!=15 && mUsuario[coorL][coorC]=='~'){  //Verificar se o usuario acertou e a variavel nao e repetida
      apresentaMatriz(N,mUsuario,10);
      textbackground(0);
      printf("\nVoce Acertou :D ");
      Sleep(100);
      vitoria++;
      system("cls");
    }
    else{
      apresentaMatriz(N,mUsuario,12);
      textbackground(0);
      printf("\nVoce Errou :(");
      printf("\a");
      Sleep(100);
      system("cls");
    }

    mUsuario[coorL][coorC]=mSistema[coorL][coorC];

    apresentaMatriz(N,mUsuario,1);
    textcolor(15);
    textbackground(0);
  }
  
  printf("\nParabens!! Voce fez %d jogadas.\n",pontos[jogador]);
  system("pause");
  system("cls");

  jogador++;
  system("cls");
  textcolor(15);

}while(jogador<nJogadores);

//Quando vitoria chegar a 10 (aparecer todos os barcos ao usuario) vem pra ca:
for(j=nJogadores-1;j>0;j--){
  for(i=0;i<j;i++){
    if(pontos[i]>pontos[i+1]){
      aux=pontos[i];
      pontos[i]=pontos[i+1];
      pontos[i+1]=aux;
      strcpy(nomeaux,nome[i]);
      strcpy(nome[i],nome[i+1]);
      strcpy(nome[i+1],nomeaux);
    }
  }
}

displayBatalhaNaval();
printf("\n\n--------------------------Ranking--------------------------\n");
printf("\n              Nome                        Numero de Jogadas\n");
for (i=0;i<nJogadores;i++){
  printf("\n %d%c %15s                              %d",i+1,167,nome[i],pontos[i]);
}
printf("\n\n-----------------------------------------------------------\n\n");
system("pause");
system("cls");


displayBatalhaNaval();
printf("\n\n%c Fear Of the Dark - Iron Maiden %c",10,14);
printf("\n\n\n\n\n\n\n\n\n                                 Desenvolvido por: Hadlich/Costa.");
musicaFinal();

return 0;
getch();
}


void apresentaMatriz( int N,int mUsuario[][N],int color){
  int i,j;
  printf("\n Voce pode acertar:\n\n Tiro na agua: (%c)   Cruzadores: (%c%c)\n\n Hidroavioes: (%c)\n             (%c %c)\n\n",15,1,1,2,2,2);
  for (i=0 ;i<N; i++){
    textbackground(color);
    for(j=0;j<N;j++){
      printf(" %c ",mUsuario[i][j]);
    }
    printf("\n                     \n");
  }
  textbackground(0);
  printf("\nDigite a coordenada (Por Exemplo: C3) e pressione enter : \n");
}

void musicaFinal(){
  while (1){
    int n1 = 1;
    while(n1 <= 2){
      Beep(293,250);
      Beep(293,250);
      Beep(220,250);
      Beep(220,250);
      Beep(293,250);
      Beep(293,250);
      Beep(330,250);
      Beep(330,250);
      Beep(349,250);
      Beep(349,250);
      Beep(330,250);
      Beep(330,250);
      Beep(293,250);
      Beep(293,250);
      Beep(330,250);
      Beep(293,250);
      Beep(262,250);
      Beep(262,250);
      Beep(196,250);
      Beep(196,250);
      Beep(262,250);
      Beep(262,250);
      Beep(293,250);
      Beep(293,250);
      Beep(330,250);
      Beep(330,250);
      Beep(293,250);
      Beep(293,250);
      Beep(262,250);
      Beep(262,250);
      Beep(330,250);
      Beep(262,250);
      n1++;
    }
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(220 , 1.33),250);
    Beep(divs(220 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(349 , 1.33),250);
    Beep(divs(349 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(262 , 1.33),250);
    Beep(divs(262 , 1.33),250);
    Beep(divs(196 , 1.33),250);
    Beep(divs(196 , 1.33),250);
    Beep(divs(262 , 1.33),250);
    Beep(divs(262 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(262 , 1.33),250);
    Beep(divs(262 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(262 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(220 , 1.33),250);
    Beep(divs(220 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(349 , 1.33),250);
    Beep(divs(349 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(divs(330 , 1.33),250);
    Beep(divs(293 , 1.33),250);
    Beep(175,250);
    Beep(175,250);
    Beep(131,250);
    Beep(131,250);
    Beep(175,250);
    Beep(175,250);
    Beep(196,250);
    Beep(196,250);
    Beep(220,250);
    Beep(220,250);
    Beep(196,250);
    Beep(196,250);
    Beep(175,250);
    Beep(175,250);
    Beep(220,500);
    Beep(175,500);
  }
}

void displayBatalhaNaval(){
  printf("\n\n    %c%c%c %c%c%c %c%c%c %c%c%c %c   %c %c %c%c%c\n    %c%c%c %c %c  %c  %c %c %c   %c %c %c %c\n    %c%c%c %c%c%c  %c  %c%c%c %c   %c%c%c %c%c%c\n    %c%c%c %c %c  %c  %c %c %c%c%c %c %c %c %c\n\n"
  ,201,205,187,201,205,187,205,203,205,201,205,187,186,186,186,201,205,187,186,205,188,186,186,186,186,186,186,186,186,186,186
  ,186,205,187,186,205,186,186,186,205,186,186,186,205,186,186,205,186,200,205,188,186,186,186,186,186,200,205,205,186,186,186,186);

  printf("        %c%c%c %c%c%c %c %c %c%c%c %c  \n        %c %c %c %c %c %c %c %c %c  \n        %c %c %c%c%c %c %c %c%c%c %c  \n        %c %c %c %c %c%c%c %c %c %c%c%c\n      "
  ,201,205,187,201,205,187,186,186,201,205,187,186,186,186,186,186,186,186,186,186,186
  ,186,186,186,205,186,186,186,186,205,186,186,186,186,186,186,200,205,188,186,186,200,205,205);
}

int apresentacao(){
  int i;
  for (i=1;i<16;i++){ // Apresentação Inicial
    textcolor(i);

    displayBatalhaNaval();

    textcolor(15);
    Beep(293,250);
    Beep(220,250);
    if(kbhit()){
      if(getch()){
        return 0;
      }
    }
    printf("\n\n\n Pressione qualquer tecla para iniciar...");
    Beep(242,250);
    Beep(262,250);
    if(kbhit()){
      if(getch()){
        return 0;
      }
    }
    Beep(330,250);
    Beep(330,250);
    if(kbhit()){
      if(getch()){
        return 0;
      }
    }
    Beep(262,250);
    Beep(330,250);
    if(kbhit()){
      if(getch()){
        return 0;
      }
    }
    system("cls");
    if(i==15){
      i=1;
    }
  }
}
