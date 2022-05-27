# RayTracer - Final Project for COMP354 Computer Graphics

## Supported Features

1) Local Illumination
2) Global Illumination
3) Primitive Shapes (Spheres, Rectangles)
4) Accelerated Structures
5) Anti-Aliasing
6) Soft and Hard Shadows
7) Area and Spot Light source

This code is used for three purposes:

1) Build the official course solution
2) Build the student solution 
3) Build a dummy application that showcases some of the codebase.

Each build is controlled by two defines:
COURSE_SOLUTION and STUDENT_SOLUTION.

If none of these variables are defined the dummy code is built. This is the default behaviour.
If COURSE_SOLUTION is defined, the code expects the course solution (this should never be defined)
IF STUDENT_SOLUTION is defined the code expects a student solution is implemented in the src folder. Have a look at the main.cpp file for the expected interface.

You can switch on and off these defines in the CMakeLists.txt file. 

# Usage

Building the solution:
1) Uncomment the #add_compile_options(-DSTUDENT_SOLUTION) line in the CMakeLists.txt 
```bash
mkdir build
mkdir src
cd build
cmake ../
make
./raytracer <filename.json>
```

Note that some test scenes are provided in the assets folder. You can do a soft link to the assets folder in the build folder for your convenience.
