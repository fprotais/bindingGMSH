#include <gmsh.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>


int main(int argc, char** argv) {
    if (argc != 4){
        std::cout << "Usage: " << argv[0] << " infile.step scale outfile.ext" << std::endl;
        std::cout << "Example: " << argv[0] << " input.step 1 output.mesh" << std::endl;
        return 1;
    } 
    std::string infile = argv[1]; 
    double scale = std::stod(argv[2]);
    std::string outfile = argv[3]; 

    gmsh::initialize();
    gmsh::merge(infile);
    gmsh::option::setNumber("Mesh.MeshSizeFactor", scale);
    gmsh::option::setNumber("Mesh.Algorithm",11);
    gmsh::model::mesh::generate(2);
    gmsh::write(outfile);
    gmsh::finalize();

    return 0;
}


