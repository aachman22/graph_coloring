#include<iostream>
#include<stdio.h>
#include<graphics.h>
using namespace std;

int v,i,j,e,d[10],temp=0,n1,n2,n,max1=0,max1_index,color[10],clr=0,flag=0,intensity[10],k=0,ind,neighbour[10],neighbourc[10];
int g[10][10],set[10][10];
char ch;

float pi = 22/7;
int xc = 320, yc = 240, rc = 200;

int bfill(int x, int y, int fcol, int bcol){
  int current = getpixel(x,y);
  if((current!=fcol) && (current!=bcol)){
    putpixel(x,y,fcol);
    bfill(x+1,y,fcol,bcol);
    bfill(x-1,y,fcol,bcol);
    bfill(x,y+1,fcol,bcol);
    bfill(x,y-1,fcol,bcol);

  }
}

int finalcolor(){
  for(i=0;i<v;i++){
    for(int j=0;j<v;j++){
      if(color[i]==color[j]){
        intensity[i]+=1;
      }
    }
  }
  for(i=0;i<v;i++){
    cout<<color[i]<<" : "<<intensity[i]<<endl;
  }
  for(i=0;i<v;i++){
    if(intensity[i]==1){
      ind=i;
    }
  }
  j=0;

  for(i=0;i<v;i++){
    if(g[ind][i]==1){
      neighbour[j]=i;
      neighbourc[j]=color[i];
      j++;
    }
  }

  /*for(i=0;i<j;i++){
    cout<<neighbour[i]<<endl;
  }*/
  int chx=0;

  for(i=0;i<v;i++){
    for(k=0;k<j;k++){
      if(neighbour[k]==i){
        chx+=1;
      }
      else if(g[i][ind]==0){
        if(color[i]!=neighbourc[k]){
          //cout<<neighbour[k];
          chx+=0;
        }
        else{
          chx+=1;
        }
      }
    }
    //cout<<chx;
    if(chx==0){
      color[ind]=color[i];
      break;
    }
    chx=0;
  }
}

int coloring(int index, int color[]){

  set[k][index]=2;

  for(i=index;i<v;i++){
    if(g[index][i]==0){
      set[k][i]=1;
    }
}

for(i=index;i<v;i++){
  if(set[k][i]==set[k][i+1]==1){
    set[k][i]=0;
    //color[i]=clr;
  }
}

  if(color[index]>clr){
    color[index]=clr;
  }

  for(i=0;i<v;i++){
    if((g[index][i]==1) && (color[index]==color[i]) && (set[k][i]==0)){
      color[i]=clr+1;
      flag=1;
    }
  }
  if(flag==1){
    clr++;
  }
  flag=0;
}

void resetintensity(){
  for(i=0;i<10;i++){
    intensity[i]=0;
  }
}

void initialize_color(){
  for(i=0;i<n;i++){
      color[i]=0;
  }
}

int main(){
  do{
    cout<<"\nEnter the number of vertices : ";
    cin>>v;
    cout<<"Enter the number of edges : ";
    cin>>e;

    int gd = DETECT, gm;
  	initgraph(&gd,&gm,NULL);

    float div1,fi;

    div1 = 360/v;
    cout<<"\nDivision = "<<div1;

    int x[15],y[15];

    for(fi = div1;fi<=360;fi=fi+div1){
  		x[i] = xc + rc*cos((pi*fi)/180);
  		y[i] = yc + rc*sin((pi*fi)/180);

  		circle(x[i],y[i],25);
  		i++;
  	}

    cout<<"Enter the edges : "<<endl<<endl;
    int cnt = 0;
    while(cnt<e){
      cout<<"Enter edge "<<cnt+1<<" :\n";
      cin>>n1>>n2;
      if(g[n1][n2]!=1){
        g[n1][n2] = g[n2][n1] = 1;
        cnt++;
        cout<<"\n";
        line(x[n1],y[n1],x[n2],y[n2]);
      }
      else{
        cout<<"\nAlready entered edge between "<<n1<<" and "<<n2<<endl<<endl;
      }
    }

    for(i=0;i<v;i++){
      temp=0;
      for(j=0;j<v;j++){
        temp+=g[i][j];
      }
      d[i] = temp;
    }

    initialize_color();

    for(j=0;j<v;j++){
        coloring(j, color);
        k++;
    }

    finalcolor();
    resetintensity();
    finalcolor();

    for(i=0;i<v;i++){
      bfill(x[i],y[i]-1,color[i]+1,WHITE);
      bfill(x[i],y[i]+1,color[i]+1,WHITE);
      bfill(x[i]+1,y[i],color[i]+1,WHITE);
      bfill(x[i]-1,y[i],color[i]+1,WHITE);
    }

    cout<<"Do you want to try again?";
    cin>>ch;
    cleardevice();
  }while(ch=='y');

}
