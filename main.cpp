// main.cpp

#include "Plot.h"
#include "Tree.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

Plot* plot = Plot::CreateInstance();
const double pi = 3.141592653589793;

void reset();
void redraw();
void height();
void width();
void screenshot();
int total_leaf_mass();
int total_branch_mass();
int total_tree_mass();
void average_leaf_surface_area();
void write( const char* string );

double x0;
double y0;
double z0;
double r0;
double th0;
double ph0;

int tiers;
int order;
double angle;
double rleafsa;
double leafsa;
double rbranch;
double dbranch;
double mbranch;
double rleaves;
double mleaves;
int minRand;

Tree* tree;

int main()
{

	srand ( (unsigned)time(NULL) );

	reset();

	while ( true )
	{

		int select = -1;

		printf("Make a selection:\n");
		printf(" [ 0] Exit Simulation\n");
		printf(" [ 1] Toggle Tree Display\n");
		printf(" [ 2] Refresh Output\n");
		printf(" [ 3] Change Value: Branching Angle     [%0.3f]\n", angle/pi);
		printf(" [ 4] Change Value: Branch Scaling      [%0.2f]\n", rbranch);
		printf(" [ 5] Change Value: Tree Density        [%0.2f]\n", dbranch);
		printf(" [ 6] Change Value: Branch D Multiplier [%0.2f]\n", mbranch);
		printf(" [ 7] Change Value: Leafing Ratio       [%0.2f]\n", rleaves);
		printf(" [ 8] Change Value: Leaf SA Ratio       [%0.2f]\n", rleafsa);
		printf(" [ 9] Change Value: Average Leaf SA     [%0.2f]\n", leafsa);
		printf(" [10] Change Value: Average Leaf Mass   [%0.2f]\n", mleaves);
		printf(" [11] Change Value: Tiers               [%d]\n",    tiers);
		printf(" [12] Change Value: Order               [%d]\n",    order);
		printf(" [13] Random Removal\n");
		printf(" [14] Random Removal Loop\n");
		printf(" [15] List\n");
		printf(" [16] Leaves\n");
		printf(" [17] Total Leaf Mass\n");
		printf(" [18] Total Branch Mass\n");
		printf(" [19] Total Tree Mass\n");
		printf(" [20] Average Leaf Surface Area\n");
		printf(" [21] Strahler\n");
		printf(" [22] Height\n");
		printf(" [23] Width\n");
		printf(" [24] Reset\n");
		printf(" [99] Screenshot\n");

		printf(">> ");
		scanf("%d",&select);

		switch ( select )
		{

			case 0:
				delete plot;
				return 0;
			case 1:
				if (tree->toggle()) write("Displaying tree...");
				else write("Hiding tree...");
				break;
			case 2:
				plot->refresh();
				write("Refreshing display...");
				break;
			case 3:
			 	printf("Branching Angle: ");
				scanf("%lf",&angle); angle *= pi;
				redraw(); break;
			case 4:
				printf("Branch Tier Scaling: ");
				scanf("%lf",&rbranch);
				redraw(); break;
			case 5:
				printf("Tree Density: ");
				scanf("%lf",&dbranch);
				redraw(); break;
			case 6:
				printf("Branch D Multiplier: ");
				scanf("%lf",&mbranch);
				redraw(); break;
			case 7:
				printf("Leafing Ratio: ");
				scanf("%lf",&rleaves);
				redraw(); break;
			case 8:
				printf("Leaf Surface Area Ratio: ");
				scanf("%lf",&rleafsa);
				redraw(); break;
			case 9:
				printf("Average Leaf Surface Area: ");
				scanf("%lf",&leafsa);
				redraw(); break;
			case 10:
				printf("Average Leaf Mass: ");
				scanf("%lf",&mleaves);
				redraw(); break;
			case 11:
				printf("Tiers: ");
				scanf("%d", &tiers);
				redraw(); break;
			case 12:
				printf("Order: ");
				scanf("%d", &order);
				redraw(); break;
			case 13:
				printf("Minimum Tier: ");
				scanf("%d", &minRand); redraw();
				tree->random( minRand ); break;
			case 14:
				printf("Minimum Tier: ");
				scanf("%d", &minRand);
				while ( true ) { redraw(); tree->random( minRand ); for ( unsigned long i = 0; i < 100000000; i++ ); } break;
			case 15: tree->list(); break;
			case 16: tree->leaves(); break;
			case 17: total_leaf_mass(); break;
			case 18: total_branch_mass(); break;
			case 19: total_tree_mass(); break;
			case 20: average_leaf_surface_area(); break;
			case 21: tree->strahler(); break;
			case 22: height(); break;
			case 23: width(); break;
			case 24: reset(); break;
			case 99: screenshot(); break;

		}

	}

	return 0;

}

void height()
{

	char status[128];
	sprintf( status, "Height of tree is %0.2f.", tree->get_height()); write( status );

}

void width()
{

	char status[128];
	sprintf( status, "Width of tree is %0.2f.", tree->get_width()); write( status );

}

void average_leaf_surface_area()
{

	char status[128];
	int tiers = tree->get_tiers();
	for ( int i = 1; i <= tiers; i ++ )
	{

		double sa = 0.5 * leafsa * rleafsa * tiers / i;
		sprintf(status, "Average leaf surface area for tier = %d: %0.2f", i, sa); write( status );

	}

}

int total_leaf_mass()
{

	char status[128];
	int leaves = tree->leaves();
	double total = mleaves*leaves;
	sprintf(status, "\nTotal number of leaves: %d",    leaves); write( status );
	sprintf(status, "Mass of one leaf:       %0.2f", mleaves); write( status );
	sprintf(status, "Total mass of leaves:   %0.2f\n", total); write( status );
	return total;

}

int total_branch_mass()
{

	char status[128];
	int branches = tree->get_branches();
	double volume = tree->volume();
	double total = dbranch*volume;
	sprintf(status, "\nTotal number of branches: %d",    branches); write( status );
	sprintf(status, "Total volume of branches: %0.2f", volume); write( status );
	sprintf(status, "Total mass of branches:   %0.2f\n", total); write( status );
	return total;

}

int total_tree_mass()
{

	char status[128];
	double branches = total_branch_mass();
	double leaves   = total_leaf_mass();
	double total = branches + leaves;
	sprintf(status, "\nTotal mass of branches: %0.2f", branches); write( status );
	sprintf(status, "Total mass of leaves:   %0.2f", leaves); write( status );
	sprintf(status, "Total mass of tree:     %0.2f\n", total); write( status );
	return total;

}

void screenshot()
{

	//plot->write("set term postscript eps color");
	plot->write("set term png color small");
	char savefile[128]; sprintf(savefile, "./screenshots/tree-%Lu.png", (unsigned long long)time( NULL ));
	char command[128];  sprintf(command,  "set out \"%s\"",					savefile);
	char status[128];   sprintf(status,   "Screenshot saved to \"%s\".",	savefile);
	plot->write( command ); write( status );
	plot->refresh();
	plot->write( "set term x11" );

}

void reset()
{

	x0 = 0;
	y0 = 0;
	z0 = 0;
	r0 = 1;
	th0 = 0;
	ph0 = 0;

	tiers = 7;
	order = 2;
	angle = pi/8;
	rbranch = 0.80;
	mbranch = 2.00;
	dbranch = 2.00;
	rleaves = 2.00;
	mleaves = 1.00;
	rleafsa = 0.35;
	leafsa  = 0.48;
	minRand = 2;

	tree = new Tree( x0, y0, z0, r0, th0, ph0, tiers, order, angle, rbranch, mbranch, rleaves, mleaves );

}

void redraw()
{

	delete tree; tree = new Tree( x0, y0, z0, r0, th0, ph0, tiers, order, angle, rbranch, mbranch, rleaves, mleaves );

}

void write( const char* string )
{

	printf("%s\n", string);

}
