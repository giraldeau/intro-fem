#include <iostream>

#include "elements.h"

using Eigen::PartialPivLU;

#include <functional>

using namespace std;

int IDX2(int i, int j, int dimx) {
	return j*dimx+i;
}

void testIdentity() {
	MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);

	MatrixXd inv = m.inverse();
	MatrixXd i = inv * m;

	std::cout << m << std::endl;
	std::cout << inv << std::endl;
	std::cout << i << std::endl;

}

void foreach_pos(int x, int y, function<void (int i, int j)> fn) {
	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			fn(i, j);
		}
	}
}

void fill_zone(int x0, int x1, int y0, int y1, function<void (int i, int j)> fn) {
	for (int j = y0; j < y1; j++) {
		for (int i = x0; i < x1; i++) {
			fn(i, j);
		}
	}
}

void dump_grid(int dimx, int dimy, vector<double>& data){
	for (int j = 0; j < dimy; j++) {
		for (int i = 0; i < dimx; i++) {
			cout << data[IDX2(i,j,dimx)] << " ";
		}
		cout << endl;
	}
}

void interpolate_elem(Mesh& mesh, Elem& elem){
	Vector2d& p0 = mesh.pos[elem.nodes[0]];
	Vector2d& p1 = mesh.pos[elem.nodes[1]];
	Vector2d& p2 = mesh.pos[elem.nodes[2]];
	Vector2d& p3 = mesh.pos[elem.nodes[3]];
}

int main() {

	Mesh mesh;

	int dimx = 10;
	int dimy = 10;
	int n = dimx * dimy;
	mesh.pos.resize(n);
	mesh.heat.resize(n);
	mesh.elems.resize((dimx - 1) * (dimy - 1));


	double domx = 1.;
	double domy = 2.;

	double stepx = domx / dimx;
	double stepy = domy / dimy;

	foreach_pos(dimx, dimy, [&](int i, int j){
		mesh.pos[IDX2(i, j, dimx)] = Vector2d(stepx * i, stepy * j);
	});

	foreach_pos(dimx-1, dimy-1, [&](int i, int j){
		Elem& e = mesh.elems[IDX2(i, j, dimx-1)];
		e.nodes[0] = IDX2(i, j, dimx);
		e.nodes[1] = IDX2(i+1, j, dimx);
		e.nodes[2] = IDX2(i+1, j+1, dimx);
		e.nodes[3] = IDX2(i, j+1, dimx);
	});

	fill(mesh.heat.begin(), mesh.heat.end(), 15.);

	fill_zone(0, dimx, 0, 1, [&](int i, int j){
		int idx = IDX2(i, j, dimx);
		mesh.heat[idx] = 100.;
	});

	dump_grid(dimx, dimy, mesh.heat);

	interpolate_elem(mesh, mesh.elems[0]);

	// Example for solving system
	// MatrixXd mat(4, 4);
	// PartialPivLU<MatrixXd> lu = mat.lu();

	cout << "done";

}
