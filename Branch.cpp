// Branch.cpp

#include "Branch.h"
#include <stdio.h>
#include <math.h>

Branch::Branch( int max_tier, int order, double x0, double y0, double z0, double r0, double th0, double ph0, double rbranch, double rleaves )
{

	this->parent = NULL;
	this->order = order;
	this->max_tier = max_tier;
	this->tier = 0;
	this->tierindex = 0;
	this->treeindex = 1;
	this->rbranch = rbranch;
	this->rleaves = rleaves;
	this->rwidth = rwidth;
	this->leaves = 0;

	this->origin[0] = x0;
	this->origin[1] = y0;
	this->origin[2] = z0;

	this->r  = r0;
	this->th = th0;
	this->ph = ph0;

	this->init();

}

Branch::Branch( Branch* parent, int max_tier, int order, int index, double th, double ph, double rbranch, double rleaves )
{

	this->parent = parent;
	this->order = order;
	this->max_tier = max_tier;
	this->tier = parent->get_tier() + 1;
	this->tierindex = index;
	this->treeindex = (int)(pow( this->order, this->tier ) / ( this->order - 1 )) + this->tierindex + this->order - 2;
	this->rbranch = rbranch;
	this->rleaves = rleaves;
	this->rwidth = rwidth;
	this->leaves = 0;

	this->origin[0] = parent->get_x();
	this->origin[1] = parent->get_y();
	this->origin[2] = parent->get_z();

	this->r  = parent->get_r() * rbranch;
	this->th = th;
	this->ph = ph;

	double c = 0; int d = 0;
	while ( c < this->r )
	{
		c += pow(this->rleaves, d) * this->r / this->max_tier;
		leaves++; d++;
	}

	this->init();

}

void Branch::init()
{

	this->hidden = true;
	this->progeny = 0;

	const double pi = 3.141592653589793;

	this->vector[0] = origin[0] + r*sin(th)*cos(ph);
	this->vector[1] = origin[1] + r*sin(th)*sin(ph);
	this->vector[2] = origin[2] + r*cos(th);

	plot = Plot::CreateInstance();

}

void Branch::show( bool refresh )
{

	char command[128];
	sprintf(command, "set arrow %d from %f,%f,%f to %f,%f,%f nohead lw %d lc rgb \"#%02X%02X%02X\"",this->treeindex,this->origin[0],this->origin[1],this->origin[2],this->vector[0],this->vector[1],this->vector[2],this->strahler-1,100,200*this->tier/this->max_tier,0);
	plot->write(command);
	if ( refresh ) plot->write("replot");
	this->hidden = false;

}	

void Branch::hide( bool refresh )
{

	char command[128];
	sprintf(command, "unset arrow %d",this->treeindex);
	plot->write(command);
	if ( refresh ) plot->write("replot");
	this->hidden = true;

}

bool Branch::equals( Branch* branch ) { return ( this->get_index() == branch->get_index() ); }

int Branch::get_tier()  { return this->tier; }
int Branch::get_index() { return this->treeindex; }

int Branch::get_strahler() { return this->strahler; }
void Branch::set_strahler( int strahler ) { this->strahler = strahler; }

int Branch::get_progeny() { return this->progeny; }
void Branch::set_progeny( int progeny ) { this->progeny = progeny; }

void Branch::inc_progeny() { this->set_progeny( this->get_progeny() + 1 ); }
void Branch::dec_progeny() { if ( this->get_progeny() ) this->set_progeny( this->get_progeny() - 1 ); }

bool Branch::get_hidden() { return this->hidden; }
Branch* Branch::get_parent() { return this->parent; }
int Branch::get_leaves() { return this->leaves; }
bool Branch::get_parent_hidden() { return this->parent->get_hidden(); }

double Branch::get_x0() { return this->origin[0]; }
double Branch::get_y0() { return this->origin[1]; }
double Branch::get_z0() { return this->origin[2]; }

double Branch::get_x()  { return this->vector[0];  }
double Branch::get_y()  { return this->vector[1];  }
double Branch::get_z()  { return this->vector[2];  }

double Branch::get_r()  { return this->r;  }
double Branch::get_th() { return this->th; }
double Branch::get_ph() { return this->ph; }
