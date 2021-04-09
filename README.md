# bindingGMSH
Small programs to call gmsh for meshing and displaying step file in C++. Occasionnaly binding with ultimaille. 

quadqs_models.zip are step models comming from [https://arxiv.org/pdf/2103.04652.pdf](https://arxiv.org/pdf/2103.04652.pdf) (Thanks Maxence Reberol)
# Depandancies
The code rely on GMSH to work. As gmsh is kinda troublesome to compile, you can download their Software Development Kit (SDK) at http://gmsh.info/ and set GMSH_INCLUDE_DIR and GMSH_LIB in cmake. Development version is alright.
Typically, you would have the following:
* linux:
```sh
cmake -DGMSH_INCLUDE_DIR=".../gmsh-git-Linux64-sdk/include/" -DGMSH_LIB=".../gmsh-git-Linux64-sdk/lib/libgmsh.so" ..
```
* MacOS:
```sh
cmake -DGMSH_INCLUDE_DIR=".../gmsh-git-MacOSX-sdk/include/" -DGMSH_LIB=".../gmsh-git-MacOSX-sdk/lib/libgmsh.dylib" ..
```
* Windows:
Not straight forward (compatibility issues between mingw and mvsc). I might look into it later
# Compile 
```sh
git clone -recurse-submodules https://github.com/fprotais/bindingGMSH
cd ultimaille 
mkdir build 
cd build 
cmake -DGMSH_INCLUDE_DIR="..." -DGMSH_LIB="..." .. 
make -j 
./simpleMeshing ../mambo/Basic/B35.step 3 0.1 tet.mesh
./simpleMeshing ../mambo/Basic/B35.step 2 0.1 tri.mesh
./quadMeshing ../mambo/Basic/B35.step 0.1 quad.mesh

```
