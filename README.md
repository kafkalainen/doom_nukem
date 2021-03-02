# Doom-Nukem
Final Project in the graphics branch of Hive Helsinki code school. Creating a very low level raycaster and a game with it.

# Design Reasonings
- We decided to pursue a track of creating Duke Nukem engine.
- Calculate angles as radians, player field of vision is calculated as radians, and are then translated to pixels using how much they use screen space in ratio to the whole field of vision in radians (approx. 1.57)s

# Biggest blocks
- Linked list to Cycle list
- Precision of a float
- Pixel offset
- Is right point needed to properly render the space?
- Segfault in renderer when the function returns back to the same portal it came from.
- Wall distorted because only angle is used. Solved using perpentual distance to the wall.
Fabien's Sanglard's tutorial for Building Duke Nukem Graphics Engine [Link](https://fabiensanglard.net/duke3d/build_engine_internals.php)

# TO-DO
Riku
- Refactor PNG parser.
- Reading map data from level editor.

Joonas

# Done
- Tested to change int values in the tex_ft_draw_wall perspective_fix function, to no avail.
- We need to change angle, before it is normalized.
-

# Thoughts
- Half of the wall length needs to be added to the calculation in perspective fix.
-
