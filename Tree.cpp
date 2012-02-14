// Tree.cpp

#include "Tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const double pi = 3.141592653589793;

Tree::Tree( double x0, double y0, double z0, double r0, double th0, double ph0, int tiers, int order, double angle, double rbranch, double mbranch, double rleaves, double mleaves )
{

	this->hidden = true;
	this->tiers = tiers;
	this->order = order;
	this->angle = angle;
	this->rbranch = rbranch;
	this->mbranch = mbranch;
	this->rleaves = rleaves;
	this->mleaves = mleaves;

	plot = Plot::CreateInstance();
	plot->write("unset arrow");

	this->resize();
	branches[0][0] = new Branch(tiers,order,x0,y0,z0,r0,th0,ph0,rbranch,rleaves);
	for ( int i = 0; i < branches.size()-1; i++ )
	{
		this->index = 0;
		for ( int j = 0; j < branches[i].size(); j++ )
			NewBranch( branches[i][j] );
	}

	char command[128]; sprintf(command, "set title \"Tree (order %d, angle %0.3f, tier %d)\"", order, angle/pi, tiers);
	plot->write( command );

	this->show();
	this->strahler();

}

Tree::~Tree()
{

	for ( int i = 0; i < this->branches.size(); i++ )
		for ( int j = 0; j < branches[i].size(); j++ )
			delete branches[i][j];

}

void Tree::set_tiers( int tiers ) { this->tiers = tiers; }
void Tree::set_order( int order ) { this->order = order; }

void Tree::resize()
{

	branches.resize( this->tiers + 1 );
	for ( int i = 0; i < branches.size(); i++ )
		branches[i].resize( pow(this->order,i) );

}

void Tree::list()
{

	printf("| t | index | h | p | s | l |\n");
	for ( int i = 0; i < this->branches.size(); i++ )
		for ( int j = 0; j < this->branches[i].size(); j++ )
			printf("| %1d | %5d | %c | %1d | %1d | %2d |\n",
				branches[i][j]->get_tier(),
				branches[i][j]->get_index(),
				( branches[i][j]->get_hidden() ) ? 'y' : 'n',
				branches[i][j]->get_progeny(),
				branches[i][j]->get_strahler(),
				branches[i][j]->get_leaves()
			);

}

void Tree::show()
{

	for ( int i = 0; i < this->branches.size(); i++ )
		for ( int j = 0; j < branches[i].size(); j++ )
		   this->branches[i][j]->show( false );
	this->strahler();
	this->hidden = false;

}

void Tree::update()
{

	for ( int i = 0; i < this->branches.size(); i++ )
		for ( int j = 0; j < branches[i].size(); j++ )
			if ( this->branches[i][j]->get_hidden() == 0 )
				this->branches[i][j]->show( false );
			else this->branches[i][j]->hide( false );
	this->plot->refresh();

}

void Tree::hide()
{

	for ( int i = 0; i < this->branches.size(); i++ )
		for ( int j = 0; j < branches[i].size(); j++ )
			this->branches[i][j]->hide( false );
	this->plot->refresh();
	this->hidden = true;

}

bool Tree::toggle()
{

	if ( this->hidden ) { this->show(); return true; }
	else { this->hide(); return false; }

}

double Tree::get_height()
{

	double height = 0;
    for ( int i = 0; i < this->branches.size(); i++ )
        for ( int j = 0; j < this->branches[i].size(); j++ )
            if ( this->branches[i][j]->get_hidden() == 0 && this->branches[i][j]->get_z() > height )
				height = this->branches[i][j]->get_z();
    return height;

}

double Tree::get_width()
{

	double width = 0;
	double xmin = 0, xmax = 0;
	double ymin = 0, ymax = 0;
	for ( int i = 0; i < this->branches.size(); i++ )
        for ( int j = 0; j < this->branches[i].size(); j++ )
            if ( this->branches[i][j]->get_hidden() == 0 )
			{

				if ( this->branches[i][j]->get_x() > xmax ) xmax = this->branches[i][j]->get_x();
				if ( this->branches[i][j]->get_x() < xmin ) xmin = this->branches[i][j]->get_x();
				if ( this->branches[i][j]->get_y() > xmax ) ymax = this->branches[i][j]->get_y();
				if ( this->branches[i][j]->get_y() < xmin ) ymin = this->branches[i][j]->get_y();

			}
	xmax -= xmin; if ( xmax > width ) width = xmax;
	ymax -= ymin; if ( ymax > width ) width = ymax;

	return width;

}

int Tree::get_branches()
{

	int total = 0;
	for ( int i = 0; i < this->branches.size(); i++ )
	{
		int branches = 0;
		for ( int j = 0; j < this->branches[i].size(); j++ )
			if ( this->branches[i][j]->get_hidden() == 0 ) branches++;
		printf("Tier %2d has %4d branches.\n", i, branches);
		total += branches;
	}

	return total;

}

int Tree::get_tiers() { return this->tiers; }

int Tree::leaves()
{

	int total = 0;
	for ( int i = 0; i < this->branches.size(); i++ )
	{
		int leaves = 0;
		for ( int j = 0; j < this->branches[i].size(); j++ )
			if ( this->branches[i][j]->get_hidden() == 0 )
				leaves += branches[i][j]->get_leaves();
		printf("Tier %2d has %4d leaves.\n", i, leaves);
		total += leaves;
	}

	return total;

}

double Tree::volume()
{

	double total = 0;
	for ( int i = 0; i < this->branches.size(); i++ )
	{
		double volume = 0;
        for ( int j = 0; j < this->branches[i].size(); j++ )
			if ( this->branches[i][j]->get_hidden() == 0 )
			{
				const double pi = 3.141592653589793;
				double r = 0.5*this->mbranch*this->branches[i][j]->get_strahler();
				double h = branches[i][j]->get_r();
				volume += pi * r*r * h;
			}
		printf("Tier %2d has volume of %4.2f.\n",i,volume);
		total += volume;
	}
	return total;

}

void Tree::strahler()
{

	for ( int i = 0; i < this->branches.size(); i++ )
		for ( int j = 0; j < this->branches[i].size(); j++ )
			branches[i][j]->set_strahler( -1 );

	for ( int i = this->branches.size()-1; i >= 0; i-- )
		for ( int j = 0; j < this->branches[i].size(); j++ )
		{

			// if branch does not exist, Strahler number is not assigned
			if ( branches[i][j]->get_hidden() ) branches[i][j]->set_strahler( 0 );
			else
			{

				// If the node is a leaf (has no children), its Strahler number is one.
				if ( branches[i][j]->get_progeny() == 0 ) branches[i][j]->set_strahler( 1 );
				else
				{

					int strahler = 0;
					int count = 0;

					Branch* parent = branches[i][j];

					// Look for babies.
					for ( int k = 0; k < this->branches[i+1].size(); k++ )
					{

						Branch* child  = branches[i+1][k];

						// Find babies.
						if ( parent->equals( child->get_parent() ) )
						{

							if ( child->get_strahler() > strahler ) { strahler = child->get_strahler(); count = 0; }
							else if ( child->get_strahler() == strahler ) count++;

						}

					}

					parent->set_strahler( ( count ) ? strahler + 1: strahler );

				}

			// If the node has one child with Strahler number i, and all other children have Strahler numbers less than i, then the Strahler number of the node is i again.
			// If the node has two or more children with Strahler number i, and no children with greater number, then the Strahler number of the node is i + 1.

			}

		}

	this->update();

}

void Tree::progeny()
{

	for ( int i = 0; i < this->branches.size(); i++ )
		for ( int j = 0; j < this->branches[i].size(); j++ )
			printf("%d %d %d\n", branches[i][j]->get_tier(), branches[i][j]->get_index(), branches[i][j]->get_progeny());

}

void Tree::random( int min )
{

	this->show();
	this->strahler();
	this->update();

	for ( int i = min + 1; i < this->branches.size(); i++ )
		for ( int j = 0; j < this->branches[i].size(); j++ )
		{

			int randVal = rand() % ( this->tiers - branches[i][j]->get_tier() + 4 );
			if ( randVal == 0 )
			{
				this->branches[i][j]->hide( false );
				branches[i][j]->get_parent()->dec_progeny();
			}

		}

	for ( int k = min; k < this->branches.size(); k++ )
		for ( int i = this->branches.size()-1; i > 0; i-- )
			for ( int j = 0; j < this->branches[i].size(); j++ )
				if ( this->branches[i][j]->get_parent_hidden() )
				{
					this->branches[i][j]->hide( false );
					branches[i][j]->get_parent()->dec_progeny();
				}

	this->strahler();

}

void Tree::NewBranch( Branch* branch )
{

	const double pi = 3.141592653589793;

	for ( int i = 0; i < this->order; i++ )
	{

		int tier = branch->get_tier() + 1;
		branches[tier][this->index] = new Branch( branch, this->tiers, this->order, this->index,
			branch->get_th() - this->angle + 2.0/(this->order-1)*i*this->angle, 0, this->rbranch, this->rleaves );
		branch->inc_progeny();
		this->index++;

	}

}
