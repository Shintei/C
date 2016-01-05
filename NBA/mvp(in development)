#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include <math.h>
#define MAXITEMS 1000000
#define CHAINED
#define START
#define SORTUP

int intlen(long int x){
if(x > 999999999) return 10;
if(x > 99999999) return 9;
if(x > 9999999) return 8;
if(x > 999999) return 7;
if(x > 99999) return 6;
if(x > 9999) return 5;
if(x > 999) return 4;
if(x > 99) return 3;
if(x > 9) return 2;
return 1;
}

struct player
{
    char *name;
    float pts, ast, rbs, stl, mins;
    long int id, v1, v2, v3, mvp;
};

char *subs(int i, int j, char *ch);

//ENTRY add(char *key, struct player *B2);

void calcMVP(FILE* input){


if(hcreate(MAXITEMS)==0){perror("Hashtable creation failed"); exit(0);}

    char *nm, buffer[50], buffer2[50], buffer3[50], finalm[50];
    nm = malloc(20*MAXITEMS*(sizeof(char)));
    long int id;
    char *theMVP;
    long int theMVPid = 0;
    long int currmvp = 0;
    struct player *vals = (struct player *)malloc(sizeof(struct player)*MAXITEMS);
    char *pname = nm;
    struct player B;
    //vals = B;
    ENTRY item, *founditem;
    char name_to_find[30];
    int j = 0, k = 0, l = 0;
    while(fscanf(input, "%ld %s %f %f %f %f %f %ld %ld %ld", &B.id, pname, &B.pts, &B.ast, &B.rbs, &B.stl, &B.mins, &B.v1, &B.v2, &B.v3 )!= EOF && j++ < MAXITEMS){
sprintf(buffer, "%ld", B.id);
char *tkey = buffer;
B.name = pname;
B.mvp = 0;
//printf("step %d %ld %s\n", j, B->v1, tkey);
//item.key = tkey;
//item.data = (void *)B;
//pname += 19;
vals[j] = B;
item.key = tkey;
item.data = (void *)&vals[j];
hsearch(item, ENTER);
}
//if (hsearch(it, FIND) != NULL){
//struct player *temp = (struct player *)it.data;
//printf("Found it");

rewind(input);
ENTRY *psearch, p;
while(fscanf(input, "%ld %s %f %f %f %f %f %ld %ld %ld", &B.id, pname, &B.pts, &B.ast, &B.rbs, &B.stl, &B.mins, &B.v1, &B.v2, &B.v3 )!= EOF && j++ < MAXITEMS){
sprintf(buffer, "%ld", B.v1);
sprintf(buffer2, "%ld", B.v2);
sprintf(buffer3, "%ld", B.v3);
char *tkey = buffer;
char *tkey2 = buffer2;
char *tkey3 = buffer3;
p.key = tkey;
if(B.v1 != B.id){
psearch = hsearch(p, FIND);
((struct player*)(psearch->data))->mvp+=3;
if(((struct player*)(psearch->data))->mvp > currmvp){
theMVP = ((struct player*)(psearch->data))->name;
theMVPid = ((struct player*)(psearch->data))->id;
currmvp = ((struct player*)(psearch->data))->mvp;
}
}
if((B.v2 != B.id) && (B.v2 != B.v1)){
psearch = hsearch(p, FIND);
((struct player*)(psearch->data))->mvp+=2;
if(((struct player*)(psearch->data))->mvp > currmvp){
theMVP = ((struct player*)(psearch->data))->name;
theMVPid = ((struct player*)(psearch->data))->id;
currmvp = ((struct player*)(psearch->data))->mvp;
}
}
if((B.v3 != B.id) && (B.v3 != B.v1) && B.v3 != B.v2){
psearch = hsearch(p, FIND);
((struct player*)(psearch->data))->mvp++;
if(((struct player*)(psearch->data))->mvp > currmvp){
theMVP = ((struct player*)(psearch->data))->name;
theMVPid = ((struct player*)(psearch->data))->id;
currmvp = ((struct player*)(psearch->data))->mvp;
}
}
sprintf(finalm, "%ld", theMVPid);
char *finaln = finalm;
ENTRY thisun;
thisun.key = finaln;
psearch = hsearch(thisun, FIND);
printf("The MVP is %ld %s, with %ld point(s).\n", theMVPid, theMVP, currmvp);
}
hdestroy();
}

