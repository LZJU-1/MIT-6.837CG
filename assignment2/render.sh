cd data
cp ../a2 ./
./a2 -input scene2_01_diffuse.txt -size 200 200 -output ./out/output2_01.tga
./a2 -input scene2_02_ambient.txt -size 200 200 -output ./out/output2_02.tga
./a2 -input scene2_03_colored_lights.txt -size 200 200 -output ./out/output2_03.tga -normals ./out/normals2_03.tga
./a2 -input scene2_04_perspective.txt -size 200 200 -output ./out/output2_04.tga -normals ./out/normals2_04.tga
./a2 -input scene2_05_inside_sphere.txt -size 200 200 -output ./out/output2_05.tga -depth 9 11 ./out/depth2_05.tga -normals ./out/normals2_05.tga -shade_back
./a2 -input scene2_05_inside_sphere.txt -size 200 200 -output ./out/output2_05_no_back.tga
./a2 -input scene2_06_plane.txt -size 200 200 -output ./out/output2_06.tga -depth 8 20 ./out/depth2_06.tga -normals ./out/normals2_06.tga
./a2 -input scene2_07_sphere_triangles.txt -size 200 200 -output ./out/output2_07.tga -depth 9 11 ./out/depth2_07.tga -normals ./out/normals2_07.tga -shade_back
./a2 -input scene2_07_sphere_triangles.txt -size 200 200 -output ./out/output2_07_no_back.tga
./a2 -input scene2_08_cube.txt -size 200 200 -output ./out/output2_08.tga
./a2 -input scene2_09_bunny_200.txt -size 200 200 -output ./out/output2_09.tga
./a2 -input scene2_10_bunny_1k.txt -size 200 200 -output ./out/output2_10.tga
./a2 -input scene2_11_squashed_sphere.txt -size 200 200 -output ./out/output2_11.tga -normals ./out/normals2_11.tga
./a2 -input scene2_12_rotated_sphere.txt -size 200 200 -output ./out/output2_12.tga -normals ./out/normals2_12.tga
./a2 -input scene2_13_rotated_squashed_sphere.txt -size 200 200 -output ./out/output2_13.tga -normals ./out/normals2_13.tga
./a2 -input scene2_14_axes_cube.txt -size 200 200 -output ./out/output2_14.tga
./a2 -input scene2_15_crazy_transforms.txt -size 200 200 -output ./out/output2_15.tga
./a2 -input scene2_16_t_scale.txt -size 200 200 -output ./out/output2_16.tga -depth 2 7 ./out/depth2_16.tga