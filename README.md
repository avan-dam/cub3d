# cub3d
This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way.

**Subject:**
Constraints are as follows:
- You must use the miniLibX
- The management of your window must remain smooth: changing to another window, minimizing, etc,
- Display different wall textures (the choise is yours) that vary depending on which side the wall is facing (North, South, East, West)
- Your program must be able to display an item (sprite) instead of a wall
- You program must be able to set the floor and ceiling colors to two different ones
- In case the Deepthought has eyes one day to evaluate your project, your program must save the first rendered image in bmp format when its second argument is "--save".
- If no second argument is supplied, the program displays the image in a window and respects the following rules:
  - The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
  - The W, A, S, D keys must allow you to move the point of view through the maze.
  - Pressing ESC must close the window and quit the program cleanly.
  - Clicking on the red cross on the window's frame must close the window and quit the program cleanly.
  - If the declared screen size in the map is greater than the display resolution, the window size will be set depending to the current display resolution
  - The use of images of the minilibX is strongly recommended

- Your program must take as a first argument a scene description file with the .cub extension.
  - The map must be composed of only 4 possible characters: **0** for an empty space, **1** for a wall, **2** for an item and **N, S, E, W** for the player's start position and spawning orientation.
  - The map must be closed/surrounded by walls, if not the program must return an error
  - Except for the map content, each type of element can be seperated by one or more empty line(s).
  - Except for the map, each type of information from an element can be seperated by one or more space(s).
  - The map must be parsed as it looks like in the file. Spaces are a valid part of the map, and is up to your to handle. You must be able to parse any kind of map, as long as it respects the maps rules.
  - Each element (except the map) firsts information is the type identifier (composed by one or two character(s)). followed by all specific information for each object in a strict order such as:
   - Resolution:
      e.g. R 1920 1080
      identifier: R
      x render size
      y render size
    - North texture:
      e.g. NO ./path_to_the_north_texture
      identifier: NO
      path to the north texture
    - South texture:
      e.g. SO ./path_to_the_south_texture
      identifier: SO
      path to the south texture
    - East texture:
      e.g. EA ./path_to_the_east_texture
      identifier: EA
      path to the east texture
    - West texture:
      e.g. NO ./path_to_the_west_texture
      identifier: WE
      path to the west texture
    - Sprite texture:
      e.g. S ./path_to_the_sprite_texture
      identifier: S
      path to the sprite texture
    - Floor color:
      e.g. F 220,100,0
      identifier: F
      R, G, B, colours in range [0.255]: 0, 255, 255
    - Ceiling color:
      e.g. C 225,30,0
      identifier: C
      R, G, B, colours in range [0.255]: 0, 255, 255
      
      
      
      
