# Doom-Nukem
Final Project in the graphics branch of Hive Helsinki code school. Creating a very low level raycaster and a game with it.

## Usage
- In Windows environment, you have to install MingW gcc compiler for Windows.
Download the installer from https://sourceforge.net/projects/mingw/files/Installer/
This project assumes that it is installed to C:\MinGW
- In Linux environment you will need `gcc` compiler to be installed.

	sudo apt-get update
	sudo apt-get install build-essential

- Run `make` in the root to compile the program.
- Run maps by piping them to program. ie.
	`./doom-nukem map_files/test.DN2`

## Additional Project bonuses
- Menu.
- Secret rooms.
- Destroyable objects (enemies, and player)
- Gravitational variances between sectors.
- Story affects to the characters outlook.
- Hashing to verify mapfile integrity.

## Design Reasonings
- We decided to pursue a track of creating Duke Nukem-like engine.
- Player field of vision was first calculated as radians, and are then translated to pixels using how much they use screen space.
- Eventually we switched from Build engine to complete 3D engine using matrices and meshes, but the whole engine is running reverse, which causes objects have no depth.

## Biggest blocks throughout project
- Making linked list to cycle list due to traversing walls in a sector.
- Precision of a float.
- Calculating correct pixel offset (integers) with angles (float).
- Segfault in renderer when the recursive function returns back to the same portal it came from.
- Wall distorted because only angle is used. Solved using perpentual distance to the wall, and scaling it to the view.
- Getting correct offset for wall textures.
- Correcting walls by perspective-correct interpolation from affine texture coordinates.
- Correcting floors by perspective-correct interpolation.
- Trying to get all the functions to work with Windows as well as they do in Linux environment.
- Moving away from Build Engine type of structure to full 3D engine.
- Typecasting to from (float) to (int) when drawing scanlines.
- Implementing polygon clipping.
- Floating point issues with arccos functions.
- Getting collisions work when more complexity is added to the engine day by day.

## Learned through project
- Makefile and Makefile rules
- Batch scripting
- How to deploy code to a seperate repository
- Git Actions (Norminette and build script)
- Platform specific design problems (__write vs. write)
- Raycasting technique.
- Build engine internals.
- Convex space and polygons.
- Vector mathematics.
- Sector based map design.
- Affine texture mapping.
- Perspective correct texture mapping.
- Matrix calculations.
- Triangulation algorithms.
- Sutherland-Hodgeman Polygon Clipping.
- From flat shading to Gouraud shading.
- Averaging unit vectors and adjacent triangles.
- Using lighting models Phong-Blinn vs. Lambertian reflectance.
- Subdivision of scanlines to smaller batches to improve calculation speed ie. Quake and demos used these in end of 1990s
- Manipulation of direction and velocity of entities based on time.
- Manipulation of direction of the sprites to create animations and perspective to an object.
- Where void pointers and pointers to functions should be used.
- Möller–Trumbore ray-triangle intersection algorithm
- Game design.
- Level design.

## Links
- Fabien's Sanglard's tutorial for Building Duke Nukem Graphics Engine [Link](https://fabiensanglard.net/duke3d/build_engine_internals.php)
- Perspective Texture Mapping and scanline division by Mikael Kalms [Link](https://www.lysator.liu.se/~mikaelk/doc/perspectivetexture/)
- Perspective Texture Mapping article series by Chris Hecker [Link] http://www.chrishecker.com/Miscellaneous_Technical_Articles
- CS184 Lecture 30 summary [Link](https://people.eecs.berkeley.edu/~jfc/cs184f98/lec30/lec30.html)

## Credits
Crewmember sprite credits go to [NMN](https://opengameart.org/users/nmn)
