#include<stdio.h>

int main(){
    int max[5][3],alloc[5][3],need[5][3],available[3],work[3],state=0,value=0,instance[3],safe[5];
    char finish[5];
    int i,j,k,totalalloc=0;

    printf("Enter the Number of resrorces Allocated to each instance:\n");
    for(i=0;i<3;i++){
        scanf("%d",&instance[i]);
    }
    for(i=0;i<5;i++){
printf("Enter the Number of Maximum Allocated resource For Process %d",i);
for(j=0;j<3;j++){
    scanf("%d",&max[i][j]);
}
    }
    
    for(i=0;i<5;i++){
        printf("Enter the Number of Resorce Allocated For Process %d",i);
        for(j=0;j<3;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    for(i=0;i<5;i++){
        for(j=0;j<3;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    for(i=0;i<3;i++){
        totalalloc=0;
        for(j=0;j<5;j++){
            totalalloc+=alloc[j][i];
        }
         available[i]=instance[i]-totalalloc;
         work[i]=available[i];
    }

    for(i=0;i<5;i++){
        finish[i]='f';
    }

    printf("\n Allocated Resources \n");
for(i=0;i<5;i++)
{
for(j=0;j<3;j++)
{
printf("%d",alloc[i][j]);
}
printf("\n");
}
printf("\n Maximum Resources \n");
for(i=0;i<5;i++)
{
for(j=0;j<3;j++)
{
printf("%d",max[i][j]);
}
printf("\n");
}
printf("\n Needed Reources \n");
for(i=0;i<5;i++)
{
for(j=0;j<3;j++)
{
printf("%d",need[i][j]);
}
printf("\n");
}
printf("\n Available Reources");
for(i=0;i<3;i++)
{
printf("%d  ",available[i]);
}

printf("\n");
for(i=0;i<5;i++){
    for(j=0;j<3;j++){
    if(finish[i]=='f'&& need[i][j]<=work[j]){
        state=1;
    }else{
        state=0;
        break;
    }
    
    }

    if(state==1){
        finish[i]='t';
        for(j=0;j<3;j++){
            work[j]=work[j]+alloc[i][j];
        }
        safe[value]=i;
        ++value;
    }

    if(i==4){
        if(value==5){
            break;
        }else{
            i=-1;
        }
    }
    
}
    printf("Safe Sequeence:");
    for(i=0;i<5;i++){
        printf("%d--->",safe[i]);
    }
    return 0;
}