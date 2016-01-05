#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#define MAXITEMS 1000000

struct player
{
    char *name;
    float pts, ast, stl, rbs;
    long int id;
};

int ppgcmp(const void *player1, const void *player2){
struct player * const *one = player1;
struct player * const *two = player2;
if((*one)->pts < (*two)->pts) return 1;
else if((*one)->pts > (*two)->pts) return -1;
else return 0;
}

int apgcmp(const void *player1, const void *player2){
struct player * const *one = player1;
struct player * const *two = player2;
if((*one)->ast < (*two)->ast) return 1;
else if((*one)->ast > (*two)->ast) return -1;
else return 0;
}

int rpgcmp(const void *player1, const void *player2){
struct player * const *one = player1;
struct player * const *two = player2;
if((*one)->rbs < (*two)->rbs) return 1;
else if((*one)->rbs > (*two)->rbs) return -1;
else return 0;
}

int spgcmp(const void *player1, const void *player2){
struct player * const *one = player1;
struct player * const *two = player2;
if((*one)->stl < (*two)->stl) return 1;
else if((*one)->stl > (*two)->stl) return -1;
else return 0;
}

void sortPlayers(FILE* input, char *stat){

struct player *arr[MAXITEMS] = {NULL};
int z;
for(z = 0; z<MAXITEMS; z++){arr[z] = malloc(sizeof(struct player));}
z = 0;

    char nm[50], buffer[50];
    float points, assists, steals, minutes, rebounds;
    long int i = 0, ide, vote1, vote2, vote3;
    int j = 0;
    while(fscanf(input, "%ld %s %f %f %f %f %f %ld %ld %ld", &ide, nm, &points, &assists, &rebounds, &steals, &minutes, &vote1, &vote2, &vote3 )!= EOF){
struct player *B = malloc(sizeof(struct player));
	
B->name = (char *)subs(0, strlen(nm), nm);
B->id = ide;
if(strcmp(stat, "PPG")==0){
B->pts = points;
}
else if(strcmp(stat, "APG")==0){
B->ast = assists;}
else if(strcmp(stat, "RPG")==0){
B->rbs = rebounds;}
else if(strcmp(stat, "SPG")==0){
B->stl = steals;}
arr[z] = B;
z++;
arr[z]++;
}

if(strcmp(stat, "PPG")==0){
qsort(arr, z, sizeof(*arr), ppgcmp);
for(j = 0; j<z; j++){
printf("%ld %s %.1f\n", arr[j]->id, arr[j]->name, arr[j]->pts);}
}

else if(strcmp(stat, "APG")==0){
qsort(arr, z, sizeof(struct player *), apgcmp);
for(j = 0; j<z; j++){
printf("%ld %s %.1f\n", arr[j]->id, arr[j]->name, arr[j]->ast);}
}

else if(strcmp(stat, "RPG")==0){
qsort(arr, z, sizeof(struct player *), rpgcmp);
for(j = 0; j<z; j++){
printf("%ld %s %.1f\n", arr[j]->id, arr[j]->name, arr[j]->rbs);}
}

else if(strcmp(stat, "SPG")==0){
qsort(arr, z, sizeof(struct player *), spgcmp);
for(j = 0; j<z; j++){
printf("%ld %s %.1f\n", arr[j]->id, arr[j]->name, arr[j]->stl);}
}

}

