#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
//已知bug:輸出範圍超過螢幕大小會很怪，超過10無法顯示
void charsegmentdisplay(char [],int);//輸出模擬七段顯示器的數字
void clearscreen();//清空螢幕
void show_tower(int *,int);//顯示當前移動狀況
void hanoi(int *,int,int,int,int,int,int []);//依序為，儲存河內塔資料的陣列，總層數，要移動的盤子編號(連帶該盤上面的所有盤子)，要移走盤子的柱子，中間柱(該回無作用)，盤子要移到的柱子，當前柱子的深度(共3個柱子，3個int的陣列)
char* mergeint(int,int,int);//三根柱子同一層的數字合併(方便印出)
#define delaysecond 1//每次移動後停留的時間
#define next_run_delaysecond 5//做完一輪後下一輪的間隔時間

int main(void) {
  int num,i=0;
  printf("input number of layer: ");
  scanf("%d", &num);
  int *hanoi_tower=malloc(num*3*sizeof(int));
  void* temp;
while (1) {
  int k[3]={0,num,num};
  for(i=0;i<=num;i++){
    *(hanoi_tower+i*3+0)=i;
    *(hanoi_tower+i*3+1)=0;
    *(hanoi_tower+i*3+2)=0;
  }
  clearscreen();
  printf("\n\nA\t\tB\t\tC\n\n");
  show_tower(hanoi_tower,num); 
  hanoi(hanoi_tower,num,num,0,1,2,k);
  printf("\t\tfinished!");
  fflush(stdout);//強制輸出finish
  sleep(next_run_delaysecond);
  //free(hanoi_tower);//清空記憶體
  clearscreen();
  printf("input number of layer: ");
  scanf("%d", &num);
  if(hanoi_tower){
    temp=realloc(hanoi_tower,num*3*sizeof(int));
    if(temp==NULL){
      printf("relloc error!");
    }
    else{
      hanoi_tower=temp;
    }
  }
  }
  return 0;
}

void clearscreen(){
    printf("\e[1;1H\e[2J");
}

void show_tower(int *hanoi_tower,int num){
  int i,j;
    for(i=1;i<=num;i++){      
      charsegmentdisplay(mergeint(*(hanoi_tower+i*3),*(hanoi_tower+i*3+1),*(hanoi_tower+i*3+2)),3);//超過10無法顯示
      printf("\n");
  }
  printf("\n\n\n\n");
    for(i=1;i<=num;i++){      
      for(j=0;j<3;j++){
        printf("%5d   ",*(hanoi_tower+i*3+j));
      }
      printf("\n");
  }
}

void hanoi(int *hanoi_tower,int num,int n, int A, int B, int C,int k[]) {
    if(n==1) {
      sleep(delaysecond);
      clearscreen();
      printf("Move sheet %d from %c to %c",*(hanoi_tower+(k[A]+1)*3+A),A+'A',C+'A');     
      *(hanoi_tower+k[C]*3+C)=*(hanoi_tower+(k[A]+1)*3+A);
      *(hanoi_tower+(k[A]+1)*3+A)=0;
      printf("\n\nA\t\tB\t\tC\n\n");
      show_tower(hanoi_tower,num);      
      k[A]++;
      k[C]--;
    }
    else {
      hanoi(hanoi_tower,num,n-1, A, C, B,k);
      hanoi(hanoi_tower,num,1, A, B, C,k);
      hanoi(hanoi_tower,num,n-1, B, A, C,k);
    }
}

void charsegmentdisplay(char a[],int q){
  int i=0,j,g,m;
  const bool segment[10][3][3]={
{{0,0,0},{0,0,0},{0,0,0}},//0，不顯示
{{1,0,1},{0,0,1},{0,0,1}},//1
{{1,1,1},{0,1,1},{1,1,0}},//2
{{1,1,1},{0,1,1},{0,1,1}},//3
{{1,0,1},{1,1,1},{0,0,1}},//4
{{1,1,1},{1,1,0},{0,1,1}},//5
{{1,1,1},{1,1,0},{1,1,1}},//6
{{1,1,1},{1,0,1},{0,0,1}},//7
{{1,1,1},{1,1,1},{1,1,1}},//8
{{1,1,1},{1,1,1},{0,1,1}} //9
};
const char display[3][3]={
  {' ','_',' '},
  {'|','_','|'},
  {'|','_','|'}};
    for(i=0;i<3;i++){
        for(g=0;g<q;g++){
          for(j=0;j<3;j++){
              printf("%c",segment[a[g]-'0'][i][j]?display[i][j]:' ');
          }
          printf("\t\t");
        }
        printf("\n");
    }
}

char* mergeint(int a,int b,int c){
  static char x[4];
  x[0]=a+'0';
  x[1]=b+'0';
  x[2]=c+'0';
  return x;
}