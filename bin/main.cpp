#include <gmsh.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

#if 0
namespace fs = std::filesystem;

const std::string Mambo_dir = "../mambo/";
const std::vector<std::string> model_dir = {"Basic/", "Simple/", "Medium/"};
void iterate_on_mambo() {
    for (const std::string& dir : model_dir){
        for (const auto& entry : fs::directory_iterator(Mambo_dir + dir)) {
            std::cerr << "Processing: " << entry << std::endl;
            std::string ext = entry.path().extension().string();
            std::string filename = entry.path().stem().string();
            std::string path2file = entry.path().string();
        }
    }
}
#endif

// in degree
static void set_rotation(int rotX, int rotY, int rotZ){
    gmsh::option::setNumber("General.RotationX", rotX);
    gmsh::option::setNumber("General.RotationY", rotY);
    gmsh::option::setNumber("General.RotationZ", rotZ);
}
static void set_scale(double scale){
    gmsh::option::setNumber("General.ScaleX", scale);
    gmsh::option::setNumber("General.ScaleY", scale);
    gmsh::option::setNumber("General.ScaleZ", scale);
}
typedef std::array<double, 3> vec3;

static void set_plan_clipping(vec3 d, double l){
    gmsh::option::setNumber("Mesh.Clip", 1);
    gmsh::option::setNumber("Geometry.Clip", 1);
    gmsh::option::setNumber("General.ClipWholeElements", 1);
    gmsh::option::setNumber("General.ClipOnlyVolume", 0);


    gmsh::option::setNumber("General.Clip0A", d[0]);
    gmsh::option::setNumber("General.Clip0B", d[1]);
    gmsh::option::setNumber("General.Clip0C", d[2]);
    gmsh::option::setNumber("General.Clip0D", l);


}
static void set_box_clipping(vec3 A, vec3 B){
    gmsh::option::setNumber("Mesh.Clip", 63);
    gmsh::option::setNumber("Geometry.Clip", 63);
    gmsh::option::setNumber("General.ClipWholeElements", 1);
    gmsh::option::setNumber("General.ClipOnlyVolume", 0);

    gmsh::option::setNumber("General.Clip0D", A[0]);
    gmsh::option::setNumber("General.Clip1D", A[1]);
    gmsh::option::setNumber("General.Clip2D", A[2]);
    gmsh::option::setNumber("General.Clip3D", B[0]);
    gmsh::option::setNumber("General.Clip4D", B[1]);
    gmsh::option::setNumber("General.Clip5D", B[2]);
}
static void turnoff_clipping(){
    gmsh::option::setNumber("Mesh.Clip", 0);
    gmsh::option::setNumber("Geometry.Clip", 0);
}


std::vector<std::pair<std::string, int>> scene_settings =  {
    {"General.BackgroundGradient", 0},
    {"General.Antialiasing", 1},
    {"General.Trackball",0},
    // {"General.SmallAxes",0},

    {"Geometry.Points", 1},
    {"Geometry.PointSize", 10},
    {"Geometry.PointType", 1},

    {"Geometry.Lines", 1},
    {"Geometry.LineWidth", 2},
    {"Geometry.LineType", 1},

    {"Geometry.NumSubEdges", 200},
    {"Mesh.ColorCarousel", 0},

    {"Mesh.LineWidth", 1.2},

    {"Geometry.Lines", 1},
    {"Geometry.Surfaces", 0},
    {"Geometry.SurfaceType", 2},

    {"Mesh.SurfaceFaces",0},
    {"Mesh.SurfaceEdges",0},

    {"Mesh.VolumeFaces",1},
    {"Mesh.VolumeEdges",1},

};
std::vector<std::pair<std::string, std::array<int, 3>>> scene_colors =  {
    {"Mesh.Quadrangles", {242,242,242}},
    {"Mesh.Tetrahedra", {242,242,242}},
    {"Geometry.Lines", {0, 160, 220}},
    {"Geometry.Points", {90, 90, 90}},
};
static void test_gui_playing(const std::string& stepmodel, const std::string& meshmodel){
    gmsh::initialize(0,nullptr, false);
    gmsh::fltk::update();
    gmsh::merge(stepmodel);
    gmsh::fltk::update();
    gmsh::merge(meshmodel);
    gmsh::fltk::update();
    for (auto p : scene_settings) gmsh::option::setNumber(p.first, p.second);
    for (auto p : scene_colors) gmsh::option::setColor(p.first, p.second[0],p.second[1],p.second[2]);
    set_rotation(0, 60, 30);
    set_scale(0.8);
    gmsh::fltk::update();

    int rot = 60;
    while (gmsh::fltk::isAvailable()) {
        std::cerr << cos(rot*2*M_PI/360) << " : " << sin(rot*2*M_PI/360) << std::endl;
        set_plan_clipping({cos(rot*2*M_PI/360),0,sin(rot*2*M_PI/360)}, 1);
        // set_rotation(0, rot, 30);
        rot = (rot+1) % 360;
        gmsh::fltk::update();
        gmsh::graphics::draw();
    }
    gmsh::finalize();

}



int main(int argc, char** argv) {
    if (argc != 3){
        std::cout << "Usage: " << argv[0] << " mesh.step  mesh.mesh (or msh supported format)" << std::endl;
        return 1;
    } 
    std::string stepmodel = argv[1]; 
    std::string meshmodel = argv[2]; 
    test_gui_playing(stepmodel, meshmodel);
    return 0;
}

