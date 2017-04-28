#include <stdio.h>
#include <stdlib.h>

void printError ( void )
{
  printf ( "ERROR\n" );
  exit ( EXIT_FAILURE );
}

void swap ( int *array, int a, int b )
{
  int tmp;

  tmp = array[ a ];
  array[ a ] = array[ b ];
  array[ b ] = tmp;
}

void show ( int *array, int num )
{
  int i;
  for ( i = 0; i < num-1; i++ )
    {
      printf ( "%d ", array[ i ] );
    }
  printf ( "%d\n", array[ num-1 ] );
}

int selectionsort ( int *array, int num )
{
  int count = 0, tmp;
  int i, j;

  for ( i = 0; i < num - 1; i++ )
    {
      tmp = i;
      for ( j = i + 1; j < num; j++ )
	{
	  count++;
	  if ( array[ tmp ] > array[ j ] )
	    {
	      tmp = j;
	    }
	}

      if ( tmp != i )
	{
	  printf ( "SWAP(%d,%d)\n# ", i, tmp );
	  swap ( array, i, tmp );
	  show ( array, num );
	}
    }

  return count;
}

int main ( int argc, char *argv[] )
{
  int num, tmp, count;
  int *data;
  
  /* データの個数を読み込む */
  if ( scanf ( "%d", &num ) == EOF )
    {
      printError();
    }

  /* データを読み込む */
  if ( ( data = ( int * ) malloc ( num * sizeof ( int ) ) ) == NULL )
    {
      printError();
    }
  tmp = 0;
  while ( ( scanf ( "%d", data + tmp ) != EOF ) || tmp < num )
    {
      tmp++;
    }

  /* 表示する */
  // show ( data, num );

  /* 並べ替える */
  count = selectionsort ( data, num );

  /* 表示する */
  show ( data, num );
  printf ( "%d\n", count );

  free ( data );

  return 0;
}
