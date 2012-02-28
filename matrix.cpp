#include <stdio.h>
#include <math.h>

using namespace std;

void printv( double* v );
void printm( double* m );
double* transform( double* m, double* v );

const double pi = 3.141592654;

int main()
{

	double r = 1.0;
	double th = pi / 4.0;
	double ph = pi / 4.0;

	double matrix[] = { 1, 2, 3,
						4, 5, 6,
						7, 8, 9  };

	double rotZ[]   = {  cos(th), -sin(th), 0.0,
						 sin(th),  cos(th), 0.0,
						 0.0,      0.0,     1.0  };

	double rotY[]   = {  cos(ph),  0.0,     sin(ph),
						 0.0,      1.0,     0.0,
						-sin(ph),  0.0,     cos(ph)  };

	double vector[] = { r*sin(th)*cos(ph), 
						r*sin(th)*sin(ph),
						r*cos(th)          };

	printm( rotZ );
	printm( rotY );
	printv( vector );

	vector = transform( rotZ, vector );
	vector = transform( rotY, vector );

	printv( vector );

	return 0;

}

void printv( double* v )
{

	printf("\n");
	for ( int i = 0; i < 3; i++ )
		printf("[ % 1f ]\n", v[i]);
	printf("\n");

}

void printm( double* m )
{

	printf("\n");
	for ( int j = 0; j < 3; j++ )
	{
		printf("[ ");
		for ( int i = 0; i < 3; i++ )
			printf("% 1f ", m[3*j+i]);
		printf("]\n");
	}
	printf("\n");

}

double* transform( double* m, double* v )
{

	static double vector[3] = {0};

	for ( int j = 0; j < 3; j++ )
		for ( int i = 0; i < 3; i++ )
			vector[j] += m[3*j+i]*v[i];

	return vector;

}
