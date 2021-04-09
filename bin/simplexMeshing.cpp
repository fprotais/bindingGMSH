#include <gmsh.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>


int main(int argc, char** argv) {
    if (argc != 5){
        std::cout << "Usage: " << argv[0] << " infile.step dim scale outfile.ext" << std::endl;
        std::cout << "Example: " << argv[0] << " input.step 2 1 output.mesh" << std::endl;
        return 1;
    } 
    std::string infile = argv[1]; 
    int dim = std::stoi(argv[2]);
    double scale = std::stod(argv[3]);
    std::string outfile = argv[4]; 

    gmsh::initialize();
    gmsh::merge(infile);
    gmsh::option::setNumber("Mesh.MeshSizeFactor", scale);
    gmsh::model::mesh::generate(dim);
    gmsh::write(outfile);
    gmsh::finalize();

    return 0;
}

