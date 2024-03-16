#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    int rno,sub1,sub2;
    char name[30];
    float per;
} stud;

void insert(){
    FILE *fp = fopen("stud", "a");
    printf("Enter RNO, name, sub1, sub2: ");
    scanf("%d %s %d %d", &stud.rno, stud.name, &stud.sub1, &stud.sub2);
    stud.per = (float)(stud.sub1+stud.sub2)/2;
    fwrite(&stud,sizeof(stud),1,fp);
    fclose(fp);
}

void display(){
    FILE *fp= fopen("stud", "r");
    while (fread(&stud, sizeof(stud),1,fp));
    {
        printf("%d %s %d %d %.2f", stud.rno, stud.name, stud.sub1, stud.sub2, stud.per);
    }
    fclose(fp);
}

int main(){
    for(int i = 0; i < 5; i++){
        insert();
    }
    display();
    return 0;
}