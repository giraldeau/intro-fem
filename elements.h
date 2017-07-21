/*
 * elements.h
 *
 *  Created on: Jul 18, 2017
 *      Author: francisg
 */

#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include <Eigen/Dense>

#include <vector>

using Eigen::MatrixXd;
using Eigen::Vector2d;
using namespace std;

class Elem {
public:
	Elem() : mat(4, 4) {}
	int nodes[4];
	MatrixXd mat;
};

struct Mesh {
public:
	vector<Vector2d> pos;
	vector<double> heat;
	vector<Elem> elems;

	double interpolate1(Vector2d& loc, Elem& elem) {
		Vector2d& p0 = pos[elem.nodes[0]];
		Vector2d& p1 = pos[elem.nodes[1]];
		Vector2d& p2 = pos[elem.nodes[2]];
		Vector2d& p3 = pos[elem.nodes[3]];
		return ((p1.x() - loc.x())*(p3.y() - loc.y()))/((p1.x() - p0.x())*(p3.y() - p0.y()));
	}

};

#endif /* ELEMENTS_H_ */
