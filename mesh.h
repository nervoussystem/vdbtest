#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <openvdb/openvdb.h>

using namespace std;

typedef openvdb::Vec3d Point;

struct ObjMesh {
	vector<Point> vertices;
	vector<size_t> indices;
	size_t polygonCount() const {
		return indices.size()/3;
	}
	size_t pointCount() { 
		return vertices.size();
	}
	size_t vertexCount(size_t n) const { // Vertex count for polygon n
		return 3;
	}
	
	// Return position pos in local grid index space for polygon n and vertex v
	void getIndexSpacePoint(size_t n, size_t v, openvdb::Vec3d& pos) const {
		pos = vertices[indices[n*3+v]];
	}

	void load(string filename) {
		ifstream in;
		in.open(filename);
		string line;
		string token;
		vertices.clear();
		indices.clear();
		while (getline(in, line)) {
			stringstream ss(line);
			vector<string> tokens;
			while (getline(ss, token, ' ')) {
				tokens.push_back(token);
			}
			if (tokens.size() > 3) {
				if (tokens[0] == string("v")) {
					vertices.push_back(Point(stod(tokens[1]), stod(tokens[2]), stod(tokens[3])));
				}
				else if (tokens[0] == string("f")) {
					indices.push_back(stoi(tokens[1]) - 1);
					indices.push_back(stoi(tokens[2]) - 1);
					indices.push_back(stoi(tokens[3]) - 1);
				}
			}
		}
	}

	ObjMesh() {

	}

	ObjMesh(string filename) {
		load(filename);
	}
};