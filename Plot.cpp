// Plot.cpp

#include "Plot.h"
#include <stdio.h>

Plot* Plot::pInstance = NULL;

Plot* Plot::CreateInstance()
{

	if (!pInstance) pInstance = new Plot();
	return pInstance;

}

Plot::Plot()
{

	gnuplot = popen("gnuplot -geometry 600x600 - > /dev/null 2>&1","w");
	//write("set term postscript eps color");
	//write("set xlabel \"x\" offset first 3,0,0");
	write("set xrange[-3:3]");
	//write("set ylabel \"y\" offset first 0,3,0");
	write("set yrange[-3:3]");
	//write("set zlabel \"z\" offset first 0,0,3");
	write("set zrange[0:6]");
	write("set view 90,0");
	write("set view equal_axes xyz");
	write("unset key");
	write("set border 15");
	write("set ticslevel 0");
	write("set zeroaxis lw 2 lt 1 lc rgb \"#000000\"");
	write("set xtics 1 axis nomirror");
	write("set ytics 1 axis nomirror");
	write("set ztics 1 axis nomirror");
//	write("unset xtics");
//	write("unset ytics");
//	write("unset ztics");
	write("f(x,y) = 0");
	write("splot f(x,y)");

}

Plot::~Plot()
{

	write("set terminal x11 close 0");
	write("exit");
	pclose(gnuplot);

}

void Plot::write( const char* command )
{

	fprintf(gnuplot, "%s\n", command);
	fflush(gnuplot);

}

void Plot::refresh()
{

	write("replot");

}
