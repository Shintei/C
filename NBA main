#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char* argv[] )
{
	
int num;

FILE *fp = fopen( argv[1], "r" );
FILE *fp2 = fopen( argv[1], "r" );

	if ( fp == 0 )
	{
		printf("Please select a valid file\n");
		return -1;
	}
	else 
	{
		for( num = 2; num < argc; num++ )
		{
			if ( strcmp( argv[num], "A" ) == 0 )
			{
				getStats( fp, argv[num+1] );	
			}
			if ( strcmp( argv[num], "B" ) == 0 )
			{
				sortPlayers( fp, argv[num+1] );	
			}
			if ( strcmp( argv[num], "C" ) == 0 )
			{
				calcDef( fp );	
			}
			if ( strcmp( argv[num], "D" ) == 0 )
			{
				calcMVP( fp );	
			}
else {}
		}
	}
fclose(fp);
return 0;
}
