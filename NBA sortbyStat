#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000000

// Creates a player list and stores them in a Player array.
void getStats(FILE* input, char *pname)
{
//The Player Structure
struct playerA
{
    char *name;
    float pts, ast, stl, mins, rbs;
    long int id;
};

    struct playerA players[2000];
    char nm[50];
    float points, assists, steals, minutes, rebounds;
    long int i = 0, ide, vote1, vote2, vote3;
    int j = 0;
    while(fscanf(input, "%ld %s %f %f %f %f %f %ld %ld %ld", &ide, nm, &points, &assists, &rebounds, &steals, &minutes, &vote1, &vote2, &vote3 )!= EOF)
    {
        if(strcmp(pname, nm) == 0)
        {
            players[i].ast=assists, players[i].mins = minutes, players[i].name = nm;
            players[i].pts = points, players[i].rbs = rebounds, players[i].stl = steals; players[i].id = ide;i++;
        }
    }
printf("There are %ld player(s) with the name \"%s\".\n\n", i, pname);

for(j=0;j<i;j++){
printf("The statistics of %s (ID: %ld) are :\n%.1f point(s) per game;\n%.1f assist(s) per game;\n%.1f rebound(s) per game;\n%.1f steal(s) per game;\n%s plays %.1f minute(s) per game.\n\n",pname, players[j].id, players[j].pts, players[j].ast, players[j].rbs, players[j].stl, pname, players[j].mins );}


}
