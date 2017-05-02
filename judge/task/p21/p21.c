#include <stdio.h>
#include <stdlib.h>

void printError ( void )
{
  printf ( "ERROR\n" );
  exit ( EXIT_FAILURE );
}

int count ( double *array, int num, int rank )
{
  int count = 0, i;

  for ( i = 0; i < num; i++ )
    {
      if ( ( int ) ( array[ i ] + 0.5) == rank )
	{
	  count++;
	}
    }
  
  return count;
}

int main ( int argc, char *argv[] )
{
  int num, tmp, i, j;
  double *data;

  // データの個数を読み込む
  if ( scanf ( "%d", &num ) == EOF )
    {
      printError();
    }

  // データを読み込む
  tmp = 0;
  if ( ( data = ( double * ) malloc ( num * sizeof ( double ) ) ) == NULL )
    {
      printError();
    }
  while ( ( scanf ( "%lf", data + tmp ) != EOF ) || tmp < num )
    {
      tmp++;
    }

  // ヒストグラムをプロットする
  for ( i = 0; i < 21; i++ )
    {
      printf ( "%2d ", i );
      tmp = count ( data, num, i );
      for ( j = 0; j < tmp; j++ )
	{
	  printf ( "*" );
	}
      printf ( "\n" );
    }

  free ( data );
  
  return 0;
}
