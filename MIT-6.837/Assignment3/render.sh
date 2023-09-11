g++ *.cpp *.C -o raytracer -lGL -lGLU -lglut
cd data
cp ../raytracer ./
./raytracer -input scene3_01_cube_orthographic.txt -size 200 200 -output output3_01.tga -gui
./raytracer -input scene3_02_cube_perspective.txt -size 200 200 -output output3_02.tga -gui
./raytracer -input scene3_03_bunny_mesh_200.txt -size 200 200 -output output3_03.tga -gui
./raytracer -input scene3_04_bunny_mesh_1k.txt -size 200 200 -output output3_04.tga -gui
./raytracer -input scene3_05_axes_cube.txt -size 200 200 -output output3_05.tga -gui
./raytracer -input scene3_06_crazy_transforms.txt -size 200 200 -output output3_06.tga -gui
./raytracer -input scene3_07_plane.txt -size 200 200 -output output3_07.tga -gui -tessellation 10 5
./raytracer -input scene3_08_sphere.txt -size 200 200 -output output3_08.tga -gui -tessellation 10 5
./raytracer -input scene3_08_sphere.txt -size 200 200 -output output3_08.tga -gui -tessellation 20 10
./raytracer -input scene3_08_sphere.txt -size 200 200 -output output3_08.tga -gui -tessellation 10 5 -gouraud
./raytracer -input scene3_08_sphere.txt -size 200 200 -output output3_08.tga -gui -tessellation 20 10 -gouraud
./raytracer -input scene3_09_exponent_variations.txt -size 300 300 -output output3_09.tga -gui -tessellation 100 50 -gouraud
./raytracer -input scene3_10_exponent_variations_back.txt -size 300 300 -output output3_10.tga -gui -tessellation 100 50 -gouraud 
./raytracer -input scene3_11_weird_lighting_diffuse.txt -size 200 200 -output output3_11.tga -gui -tessellation 100 50 -gouraud
./raytracer -input scene3_12_weird_lighting_specular.txt -size 200 200 -output output3_12.tga -gui -tessellation 100 50 -gouraud