// Branch.h

#ifndef BRANCH_H
#define BRANCH_H

#include "Plot.h"

class Branch
{

	private:
		int max_tier, tier, order;
		int treeindex, tierindex;
		int strahler, progeny;
		double rbranch, rleaves;
		double rwidth, mleaves;
		int leaves;
		double x0, y0, z0;
		double x,  y,  z;
		double r,  th, ph;
		bool hidden;
		Plot* plot;
		Branch* parent;

	public:
		Branch(	int max_tier, int order, double x0, double y0, double z0, double r0, double th0, double ph0, double rbranch, double rleaves );
		Branch( Branch* parent,	int max_tier, int order, int index, double th, double ph, double rbranch, double rleaves );
		void init();

		void show( bool refresh );
		void hide( bool refresh );

		int get_tier();
		int get_index();
		bool get_hidden();

		void inc_progeny();
		void dec_progeny();

		void set_progeny( int progeny );
		int get_progeny();

		void set_strahler( int strahler );
		int get_strahler();

		Branch* get_parent();
		int get_leaves();
		bool equals( Branch* branch );
		bool get_parent_hidden();
		double get_x(),  get_y(),  get_z();
		double get_x0(), get_y0(), get_z0();
		double get_r(),  get_th(), get_ph();

};

#endif
