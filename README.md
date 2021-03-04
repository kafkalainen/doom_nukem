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

# TO-DO
## Riku
- Refactor PNG parser.
- Reading map data from level editor.

## Joonas
- Write draw_floor function.

## Tomppa
- Map editor

## Elias
- Cleans and Normes code.
- Moves on to work on the map editor. 

# Done
- Tested to change int values in the tex_ft_draw_wall perspective_fix function, to no avail.
- We need to change angle, before it is normalized.

# Thoughts
- Half of the wall length needs to be added to the calculation in perspective fix.
-

# Wolf3d features that you must include:
- :white_check_mark: You can move through the universe in real time via the keyboard arrows, just like in the two original games. 360-degree rotation, forward and back move.
- :white_check_mark: Pressing the ESC key must close the window and exit the program properly.
- :white_check_mark: Clicking the red cross on the window border must clsoe the window and exit the program properly.
- :white_check_mark: There are textures on the walls.

# New features
- :white_check_mark: You can look up and down.
- :white_check_mark: The areas you go through don’t have a fixed shape, for exemple the rooms can have any number of walls in all possible directions.
- :black_square_button: The floor and ceiling have adjustable heights, which means different areas will not be at the same height - and you’ll have to manage that smoothly.
- :black_square_button: The floor and ceiling may not be horizontal but inclined planes.
- :black_square_button: The floors and ceilings have textures.
- :black_square_button: There can be a sky instead of a ceiling.
- :white_check_mark: Walls can be partially transparent, unveiling the room behind.
- :black_square_button: Decorative elements can be placed on the walls over the main texture (paintings, posters... ).
- :black_square_button: Objects or characters can be placed in the world as sprites that always face the player.
- :black_square_button: Objects or characters can be placed in the world as multiple sprites displayed according to the orientation between the object and the player (you’ll see the object or character from behind and from the side as you walk around it).
- :black_square_button: Each room or area has a light control tool, affecting both the walls and the objects
within.
- :black_square_button: Text messages can be displayed during the game over the rest of the graphics.
- :black_square_button: There must be a HUD (life, currency, ammunition, carried artifacts...) By that we mean several elements arranged on the player’s view and not a simple one-block banner.

# About the gameplay:
- :white_check_mark: The view follows the mouse smoothly, making it possible to spin around (a whole 360) and to look up and down.
- :white_check_mark: Strafing is possible.
- :black_square_button: Interactions with walls and steps of a reasonable height should be managed properly.
- :black_square_button: The player can run, jump, fall, bend down and get up.
- :black_square_button: The player can fly or swim (same difference...).
- :black_square_button: The objects present may or may not block the passage, in proportion to their visual representation.
- :black_square_button: The items around can be picked up - or not, and supply an inventory.
- :black_square_button: The player can interact with the elements of the rooms (walls, objects...), whether by simple proximity (walking on a dangerous area) or because of a voluntary action (pressing a button).
- :black_square_button: Actions or series of actions can result from interactions, from objects being picked-up, or even in a totally independent way. They can possibly be timed.
- :black_square_button: Actions can alter all the elements of the game, all the shapes, all the properties (the shape of a room, the height of a ceiling, the texture of a wall or an object, the location of the specific texture on a door that indicates its "handle", etc).
- :black_square_button: The 2 previous points obviously mean that your game must contain animations, various devices like door opening systems, keys and ways to use them, elevators and secret passages.
- :black_square_button: Specific characters and / or objects can have their own actions, reactions and interactions in the universe.
- :black_square_button: To mimic the Doom and Duke Nukem universes, projectiles can be fired and interact with the background, the objects, the characters, even the player itself.
- :black_square_button: There is a story with a mission, a goal to reach, a target (save the earth, get rich,... even something very simple, check out Doom).
- :black_square_button: There is a beginning and an end for each level.
- :white_check_mark: There are sound effects.
- :black_square_button: There’s music.

# Other considerations:
- :black_square_button: A level editor is mandatory. It can be integrated with the main executable and activated by a command line option, or it can be a separate binary. It can be used to completely define a level: the areas and the differences in height between them, the textures, the actions and interactions, etc.
- :black_square_button: Just like in the original games, you must pack in a single file all the elements you’re going to need for the game: the level’s design, textures and gameplay elements. One file per level is accepted, but it must be self-sufficient. The doom-nukem binary and the chosen level file must be self-sufficient.

# Expected bonuses
- :black_square_button: A menu to choose the level or some difficulty options.
- :black_square_button: A genuine aesthetic research, an atmosphere, neat and detailed sceneries.
- :black_square_button: A complex and researched story and scenario.
- :black_square_button: Many useless interactions and animations that contribute to the immersion into the world (phone booth, vending machines, public toilets, projectile stains on the walls, etc).
- :black_square_button: You can play in network with other players with a lobby, team/solo modes, capture
the flag mode, etc.
- :black_square_button: Multithreaded rendering using pthread.
- :black_square_button: Plenty of other things we haven’t even imagined yet!

# Links
- Fabien's Sanglard's tutorial for Building Duke Nukem Graphics Engine [Link](https://fabiensanglard.net/duke3d/build_engine_internals.php)
