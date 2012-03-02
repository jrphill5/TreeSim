#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>

using namespace std;

void plot( const char* command);
void printv( double* v );
void printm( double* m );
double dot( double* v1, double* v2 );
double length( double* v );
double* transform( double* m, double* v );
double* transpose( double* m );

const double pi = 3.141592653589793;

void sighandler(int sig);
FILE* gnuplot;

int main()
{

	gnuplot = popen("gnuplot - > /dev/null 2>&1","w");
	//plot("set term postscript eps color");
	plot("set xlabel \"y\"");
	plot("set xrange[-3:3]");
	plot("set ylabel \"x\"");
	plot("set yrange[-3:3]");
	plot("set zlabel \"z\"");
	plot("set zrange[0:3]");
	plot("set view equal_axes xyz");
	plot("set view 60,30");
	plot("unset key");
	plot("unset border");
	plot("set ticslevel 0");
	plot("set zeroaxis lw 2 lt 1 lc rgb \"#000000\"");
	plot("set xtics axis nomirror");
	plot("set ytics axis nomirror");
	plot("set ztics axis nomirror");
	plot("f(x,y) = -1");
	plot("splot f(x,y)");
	plot("replot");

	double r = 1.0;
	double a = pi / 6.0;
	double b = pi / 6.0;
	double c = pi / 6.0;

	double xhat[3] = { 1.0, 0.0, 0.0 };
	double yhat[3] = { 0.0, 1.0, 0.0 };
	double zhat[3] = { 0.0, 0.0, 1.0 };

	double* vector;
	vector = (double*) calloc(3, sizeof(double));

	char command[128];

	double rotA[]   = {  cos(a), -sin(a),  0.0,
	                     sin(a),  cos(a),  0.0,
                         0.0,     0.0,     1.0     };

	double rotB[]   = {  1.0,     0.0,     0.0,
	                     0.0,     cos(b),  sin(b),
	                     0.0,    -sin(b),  cos(b)  };

	double rotC[]   = {  cos(c),  sin(c),  0.0,
	                    -sin(c),  cos(c),  0.0,
	                     0.0,     0.0,     1.0     };

	double rotBA[]  = {  cos(a),        -sin(a),         0.0,
	                     sin(a)*cos(b),  cos(a)*cos(b),  sin(b),
	                    -sin(a)*sin(b), -cos(a)*sin(b),  cos(b)  };

	double rotCBA[] = {  cos(a)*cos(c) + sin(a)*cos(b)*sin(c),  cos(a)*cos(b)*sin(c) - sin(a)*cos(c),  sin(b)*sin(c),
	                     sin(a)*cos(b)*cos(c) - cos(a)*sin(c),  cos(a)*cos(b)*cos(c) + sin(a)*sin(c),  sin(b)*cos(c),
	                    -sin(a)*sin(b),                        -cos(a)*sin(b),                         cos(b)         };

	// unit vector
/*	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;*/

	vector = transform( rotA, xhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#FF0000\"", vector[0],vector[1],vector[2]); plot(command);

	vector = transform( rotA, yhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#FF0000\"", vector[0],vector[1],vector[2]); plot(command);

	vector = transform( rotA, zhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#FF0000\"", vector[0],vector[1],vector[2]); plot(command);

	plot("replot");

	vector = transform( rotBA, xhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#00FF00\"", vector[0],vector[1],vector[2]); plot(command);

	vector = transform( rotBA, yhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#00FF00\"", vector[0],vector[1],vector[2]); plot(command);

	vector = transform( rotBA, zhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#00FF00\"", vector[0],vector[1],vector[2]); plot(command);

	plot("replot");

	vector = transform( rotCBA, xhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#0000FF\"", vector[0],vector[1],vector[2]); plot(command);

	vector = transform( rotCBA, yhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#0000FF\"", vector[0],vector[1],vector[2]); plot(command);

	vector = transform( rotCBA, zhat ); printv( vector );
	sprintf(command,"set arrow from 0,0,0 to %f,%f,%f lc rgb \"#0000FF\"", vector[0],vector[1],vector[2]); plot(command);

	plot("replot");

	while (true)
	{

		signal(2, &sighandler);

	};

	return 0;

}

void sighandler(int sig)
{

	plot("exit");
	fclose(gnuplot);
	exit(1);

}

void plot( const char* command )
{

	fprintf(gnuplot, "%s\n", command);
	fflush(gnuplot);

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

double dot( double* v1, double* v2 )
{

	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];

}

double length( double* v )
{

	return pow( dot(v, v), 0.5 );

}

double* transform( double* m, double* v )
{

	static double vector[3] = {0.0};

/*	for ( int j = 0; j < 3; j++ )
		for ( int i = 0; i < 3; i++ )
			vector[j] += m[3*j+i]*v[i];*/

	vector[0] = m[0]*v[0] + m[1]*v[1] + m[2]*v[2];
	vector[1] = m[3]*v[0] + m[4]*v[1] + m[5]*v[2];
	vector[2] = m[6]*v[0] + m[7]*v[1] + m[8]*v[2];

	return vector;

}

double* transpose( double* m )
{

	static double matrix[9] = {0};

	for ( int j = 0; j < 3; j++ )
        for ( int i = 0; i < 3; i++ )
            matrix[j] += m[3*i+j];

	return matrix;

}
