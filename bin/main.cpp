#include <gmsh.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

const std::string Mambo_dir = "../mambo/";
const std::vector<std::string> model_dir = {"Basic/", "Simple/", "Medium/"};

static void gmsh_simplexmesh_stepmodel(const std::string& inname, const std::string& outname, int dim = 3){
    gmsh::initialize();

    gmsh::merge(inname);
    gmsh::option::setNumber("Mesh.MeshSizeFactor", 0.3);
    gmsh::model::mesh::generate(dim);
    gmsh::write(outname);
    gmsh::finalize();
}

static void gmsh_quadmesh_stepmodel(const std::string& inname, const std::string& outname){

    gmsh::initialize();

    gmsh::merge(inname);
    gmsh::option::setNumber("Mesh.MeshSizeFactor", 0.1);
    gmsh::option::setNumber("General.AbortOnError", 1);
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::option::setNumber("General.ExpertMode", 1);
    gmsh::option::setNumber("Mesh.Algorithm",11);
    // gmsh::option::setNumber("Mesh.MeshSizeMin", 3);
    // gmsh::option::setNumber("Mesh.MeshSizeMax", 3);

    gmsh::model::mesh::generate(2);
    gmsh::write(outname);
    
    gmsh::finalize();
    return;
}

std::vector<std::pair<std::string, int>> scene_settings =  {
    {"General.BackgroundGradient", 0},
    {"General.Antialiasing", 1},
    {"General.Trackball",0},
    {"General.SmallAxes",0},
    {"Geometry.Points", 0},
    {"Geometry.Lines", 1},
    {"Geometry.LineWidth", 1.2},
    {"Geometry.LineType", 1},
    {"Geometry.NumSubEdges", 200},
    {"Mesh.ColorCarousel", 0},
    {"Mesh.LineWidth", 1.2},
    {"Mesh.SurfaceFaces",1},
    {"Geometry.Lines", 1},
    {"Geometry.Surfaces", 0},
    {"Geometry.SurfaceType", 2},
};
std::vector<std::pair<std::string, std::array<int, 3>>> scene_colors =  {
    {"Mesh.Quadrangles", {242,242,242}},
    {"Geometry.Lines", {0, 160, 220}},
};
static void test_gui_playing(const std::string& inname, const std::string& imagename){
    gmsh::initialize();

    gmsh::merge(inname);
    gmsh::finalize();

}

int main(int argc, char** argv) {
    int ct = 0;
    int mesh_nb = 0;
    if (argc == 2) mesh_nb = std::stoi(argv[1]); 
    for (const std::string& dir : model_dir){
        for (const auto& entry : fs::directory_iterator(Mambo_dir + dir)) {
            if (ct++ != mesh_nb) continue;
            std::cerr << "Processing: " << entry << std::endl;
            std::string ext = entry.path().extension().string();
            std::string filename = entry.path().stem().string();
            gmsh_quadmesh_stepmodel(entry.path().string(), filename + "_quad.mesh");
            // gmsh_simplexmesh_stepmodel(entry.path().string(), filename + ".mesh");
        }
    }

    return 0;
}

