// Tree.h

#ifndef TREE_H
#define TREE_H

#include "Branch.h"
#include <vector>

using namespace std;

class Tree
{

	private:
		bool hidden;
		int tiers, order, index;
		double angle;
		double rbranch, mbranch;
		double rleaves, mleaves;
		vector< vector< Branch* > > branches;
		Plot* plot;

	public:
		Tree( double x0, double y0, double z0, double r0, double th0, double ph0,
			int tiers, int order, double angle, double rbranch, double mbranch, double rleaves, double mleaves );
		~Tree();
		void init();
		void list();
		void resize();
		int leaves();
		double volume();
		void set_tiers( int tiers );
		void set_order( int order );
		void strahler();
		void progeny();
		void random( int min );
		void show();
		void update();
		void hide();
		int get_branches();
		int get_tiers();
		double get_height();
		double get_width();
		bool toggle();
		void NewBranch( Branch* branch );

};

#endif
