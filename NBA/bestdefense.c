#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player
{
    char *name;
    float pts, ast, stl, rbs, min;
    long int id;
};

char *subs(int i, int j, char *ch){
int k =0;
char *ch1;
ch1 = malloc(j*sizeof(char));
while(k<j){
ch1[k] = ch[i]; i++; k++;
}
return ch1;
}

void calcDef(FILE* input){
struct player Co, Cd;

float calco = 0.0, calcd = 0.0, temp = 0.0;

    Co.name = NULL;
    Cd.name = NULL;
    char nm[50];
    float points, assists, steals, minutes, rebounds;
    long int i = 0, ide, vote1, vote2, vote3, idholdd, idholdo;
    int j = 0;
    while(fscanf(input, "%ld %s %f %f %f %f %f %ld %ld %ld", &ide, nm, &points, &assists, &rebounds, &steals, &minutes, &vote1, &vote2, &vote3 )!= EOF){
temp = ((rebounds*5)+(steals*3))/minutes;
if(temp > calcd){calcd = temp; idholdd = ide; Cd.name = subs(0, strlen(nm), nm);}
temp = (points+(assists*2)+(rebounds/2))/minutes;
if(temp > calco){calco = temp; idholdo = ide; Co.name = subs(0, strlen(nm), nm);}
}
printf("\nThe best defense player is %s (%ld), with the defense value %f.\n\nThe best offense player is %s (%ld), with the offense value %f.\n", Cd.name, idholdd, calcd, Co.name, idholdo, calco);
}
