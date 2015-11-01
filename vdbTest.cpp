#include "mesh.h"
#include <openvdb/openvdb.h>
#include <openvdb/tools/MeshToVolume.h>
#include <iostream>

using namespace openvdb;
using namespace openvdb::tools;

typedef openvdb::math::Transform Transform;

int main()
{
	// Initialize the OpenVDB library.  This must be called at least
	// once per program and may safely be called multiple times.
	openvdb::initialize();

	cout << "loading mesh" << endl;
	ObjMesh mesh("C:/dev/apps/vdbTest/holes_coneFlower_growth_asymmetric_holes.obj");
	for (auto & v : mesh.vertices) {
		v *= 4.;
	}
	openvdb::FloatGrid::Ptr mgrid;
	Transform trans;
	trans.preScale(.25);

	cout << "making voxels" << endl;
	mgrid = meshToVolume<openvdb::FloatGrid>(mesh, trans,2,2);

	std::cout << "Exporting..." << std::endl;

	
	openvdb::io::File file("hyphae.vdb");
	// Add the grid pointer to a container.
	openvdb::GridPtrVec grids;
	grids.push_back(mgrid);
	// Write out the contents of the container.
	file.write(grids);
	file.close();
	
}