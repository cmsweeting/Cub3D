<p align="center">
    <img src="https://raw.githubusercontent.com/cdomet-d/images/refs/heads/main/baloon.png" align="center" width="30%">
</p>
<p align="center"><h1 align="center">CUB3D</h1></p>
<p align="center">
Cub3D is a simple raycasting engine inspired by Wolfenstein 3D. The goal is to create a FPS view of a labryinth.</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/last-commit/cmsweeting/Cub3D?style=default&logo=git&logoColor=white&color=DB504A" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/cmsweeting/Cub3D?style=default&color=DB504A" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/cmsweeting/Cub3D?style=default&color=DB504A" alt="repo-language-count">
<br>

##  Table of Contents

- [ Getting Started](#-getting-started)
  - [ Prerequisites](#-prerequisites)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
- [ Features](#-features)
- [ Project Structure](#-project-structure)
  - [ Project Index](#-project-index)
- [ Acknowledgments](#-acknowledgments)

---

##  Getting Started

###  Prerequisites

This project was built on Ubuntu 22, it is untested on other distributions and operating systems. 

The MLX is included in this repositery, but you might need to install its dependencies:

```sh
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

The project also requires make for compilation : 
```sh
sudo apt-get install make
```
###  Installation

Install Cub3D using one of the following methods:

**Build from source:**

```sh
❯ git clone https://github.com/cmsweeting/Cub3D
❯ cd Cub3D
❯ make
```
###  Usage

Cub3D requires a configuration file to be provided in order to be able to run. You can find several valid config files under the maps/ directory. 

Once the executable is created, you can run it :
```sh
❯ ./cub3D maps/anymap
```
You can provide you own map, though note that if must contain:
- four textures identified by 'NO ', 'SO ', 'WE ', 'EA ' (with the quotes removed)
- two RGB colors identified by 'F ' and 'C '
- A closed map composed of '0', '1', and one of those four identifiers : N, S, W or E to determine the player's start position and orientation. 

You may also provide your own textures in .xpm format.

---
##  Features

|      | Feature         | Summary       |
| :--- | :---:           | :---          |
| ⚙️  | **Architecture**  | <ul><li>Cub3D uses a modular architecture with separate modules for parsing, rendering, and game logic.</li><li>The project is built using the C programming language.</li><li>It utilizes various libraries and dependencies to manage graphics, input/output operations, and other system resources.</ul> |
| 🔌 | **Integrations**  | <ul><li>Cub3D integrates various libraries and dependencies for graphics rendering, input/output operations, and system resources.</li><li>The project uses XPM (X PixMap) files for image rendering and CUB files for map parsing.</li>
| 🧩 | **Modularity**    | <ul><li>Cub3D has a modular architecture, which allows for easy maintenance, modification, and extension of individual modules.</li><li>The project's modularity enables the development of new features and game modes without affecting the overall structure.</li></ul> |
| 🧪 | **Testing**       | <ul><li> Running `bash scripts/test_parsing` will run a serie of unit test on the map's parsing to ensure that a range of case are handled.|

---

---

##  Project Structure

```sh
.
├── libs/
│   ├── mlx
│   └── libft
├── maps
├── scripts/
│   ├── exf
│   ├── extract_funct
│   ├── norm
│   ├── prep
│   ├── push
│   ├── readme
│   └── test_parsing
├── src/
│   ├── error_handling/
│   │   └── error_handling.c
│   ├── includes/
│   │   ├── cub3D.h
│   │   └── struct.h
│   ├── parsing/
│   │   ├── extract_file.c
│   │   ├── get_map_data.c
│   │   ├── handle_colors.c
│   │   ├── init_mlx.c
│   │   ├── init_textures.c
│   │   ├── is_map_valid.c
│   │   ├── iterative_floodfill.c
│   │   ├── memory_allocation
│   │   └── p_utils.c
│   ├── print_strcts.c
│   ├── raycasting/
│   │   ├── display.c
│   │   ├── draw.c
│   │   ├── events.c
│   │   ├── math_utils.c
│   │   ├── movements.c
│   │   ├── raycasting.c
│   │   └── raycasting_utils.c
│   ├── main.c
│   └── print_strcts.c
├── textures
└── Makefile
```
###  Project Index
<details open>
	<summary><b>src</b></summary>
	<blockquote>
		<table>
		<tr>
			<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/main.c'>main.c</a></b></td>
			<td>- Initialize and run a game by parsing a map file, validating its contents, and setting up the display<br>- The main function takes one command-line argument, which is the path to the map file<br>- It then populates a ray structure with the configuration files values, validates the map, initializes the display, and runs the game.</td>
		</tr>
		<tr>
			<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/print_strcts.c'>print_strcts.c</a></b></td>
			<td>- The `print_strcts.c` file provides a mechanism to print the structure of various game elements, including player positions, textures, and map information<br>This code helps developers visualize and debug their projects by providing a clear representation of the game's internal state.</td>
		</tr>
		</table>
		<details>
			<summary><b>includes</b></summary>
			<blockquote>
				<table>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/includes/struct.h'>struct.h</a></b></td>
					<td>- Defines the fundamental data structures and types used throughout the project's architectur.</td>
				</tr>
				</table>
			</blockquote>
		</details>
		<details>
			<summary><b>error_handling</b></summary>
			<blockquote>
				<table>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/error_handling/error_handling.c'>error_handling.c</a></b></td>
					<td>- Handles error messages by joining error codes and messages into a single string, then prints the resulting message to the standard error stream.</td>
				</tr>
				</table>
			</blockquote>
		</details>
		<details>
			<summary><b>parsing</b></summary>
			<blockquote>
				<table>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/init_mlx.c'>init_mlx.c</a></b></td>
					<td>- Initialize and load textures from XPM files into the game's rendering engine. This function creates images from XPM files representing the east, south, west, and north walls of a room in a Cub3D game.<br>- It uses the MLX library to load these textures and store them as pointers within the `t_ray` structure.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/extract_file.c'>extract_file.c</a></b></td>
					<td>- The `extract_file` function parses a file and extracts its contents into a character array, allowing the file's data to be processed further<br>- This code is part of a larger project that handles parsing and processing of files in a specific format<br>- The extracted file content is then used to populate a parser object with relevant values.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/is_map_valid.c'>is_map_valid.c</a></b></td>
					<td>- Validates the integrity of a map by ensuring the presence of a player start position and allocates memory for the square map<br>- This code ensures the map meets the necessary conditions to be considered valid.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/handle_colors.c'>handle_colors.c</a></b></td>
					<td>Handles colors by parsing RGB values from input files, validating their format and range, and storing them as integers in a data structure<br>- This functionality enables the creation of color-coded maps with distinct floor and ceiling colors.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/init_textures.c'>init_textures.c</a></b></td>
					<td>- Initialize textures by retrieving XPM data from the MLX library, assigning it to respective ray structures (ea, we, so, no), and verifying successful retrieval<br>- This code enables the parsing of texture information, a crucial step in rendering 3D graphics.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/p_utils.c'>p_utils.c</a></b></td>
					<td>This file provides utility functions for parsing and validating map elements in the Cub3D project<br>- It includes checks for invalid characters, element presence, and maximum line length<br>- The code ensures that all required elements are present and correctly formatted, reporting errors if any issues are found.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/get_map_data.c'>get_map_data.c</a></b></td>
					<td>- The `get_map_data.c` file is responsible for parsing map data from a .cub configuration file<br>- It extracts and processes information about the game's elements, such as textures, colors, and paths, to populate the parser's internal structures<br>- This code plays a crucial role in setting up the game environment and ensuring proper rendering of game objects.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/iterative_floodfill.c'>iterative_floodfill.c</a></b></td>
					<td>- The iterative_floodfill.c file implements the iwall function, which performs a flood fill algorithm on a given map to identify and mark walls in a 2D environment<br>- This function takes a parser object as input, iterates through the map, and marks non-zero cells as ' ' (space) characters, effectively creating a wall representation.</td>
				</tr>
				</table>
				<details>
					<summary><b>memory_allocation</b></summary>
					<blockquote>
						<table>
						<tr>
							<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/memory_allocation/destroy_structs.c'>destroy_structs.c</a></b></td>
							<td>- Destroying memory structures is the primary purpose of this code file<br>- It frees allocated memory blocks for parser and ray objects, ensuring proper deallocation and preventing memory leaks.</td>
						</tr>
						<tr>
							<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/parsing/memory_allocation/memalloc.c'>memalloc.c</a></b></td>
							<td>- The `memalloc.c` file optimizes memory allocation for the parsing module of a project by providing functions to dynamically reallocate and copy map data structures<br>- It ensures efficient handling of large maps, reallocating memory as needed while preserving original data integrity.</td>
						</tr>
						</table>
					</blockquote>
				</details>
			</blockquote>
		</details>
		<details>
			<summary><b>raycasting</b></summary>
			<blockquote>
				<table>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/raycasting/display.c'>display.c</a></b></td>
					<td>- The `display.c` file initializes and manages the graphical display of a raycasting game<br>- It sets up the rendering context, creates windows, and handles user input events to control the game's camera angles and movement<br>- The file also cleans up resources when the display is closed.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/raycasting/movements.c'>movements.c</a></b></td>
					<td>Updates the player's position and angle based on movement inputs, ensuring valid movements within the game map while maintaining a consistent orientation. Enables the player to move around the 3D environment and respond to user input.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/raycasting/draw.c'>draw.c</a></b></td>
					<td> Render raycasting results by drawing a column of pixels representing a wall's texture and color, taking into account distance, height, and ceiling/floor colors</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/raycasting/math_utils.c'>math_utils.c</a></b></td>
					<td>- Calculate distances between points and normalize angles within the raycasting system.Provides mathematical functions to support the overall architecture of the project<br>- It enables accurate calculations of distances between points and ensures that angles are properly normalized.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/raycasting/events.c'>events.c</a></b></td>
					<td>- Handles user input events in the raycasting game, enabling movement and rotation controls<br>- The file processes keyboard inputs to update the player's movements and camera orientation, allowing for seamless navigation through the game environment.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/raycasting/raycasting.c'>raycasting.c</a></b></td>
					<td>- The `raycasting.c` file implements the raycasting algorithm for rendering a 3D scene onto a 2D surface<br>- It calculates the intersection points of rays with walls, determines the closest hit point, and draws columns based on the distance from the camera<br>- The code handles vertical and horizontal intersections, normalizes angles, and adjusts the camera's view to remove the fish-eye effect.</td>
				</tr>
				<tr>
					<td><b><a href='https://github.com/cmsweeting/Cub3D/blob/master/src/raycasting/raycasting_utils.c'>raycasting_utils.c</a></b></td>
					<td>- The file provides utility functions to check collisions and find walls in a given environment<br>- It enables the detection of boundaries, such as walls or floors, allowing for more accurate rendering and navigation within the 3D space.</td>
				</tr>
				</table>
			</blockquote>
		</details>
</details>

---

##  Ressources

- [Ray-Casting Tutorial For Game Development And Other Purposes](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [Map generator](https://notimetoplay.itch.io/ascii-mapper)
- [Readme AI](https://github.com/eli64s/readme-ai)


---
