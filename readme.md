## Cub3D
C<p align="center">
  <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" alt="project-logo">
</p>
<p align="center">
<h1 align="center"></h1>
</p>
<p align="center">
<em>Cub3D is a simple raycasting engine inspired by Wolfenstein 3D. The goal is to create a FPS view of a labryinth.</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/last-commit/Jauppp/minishell?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/Jauppp/minishell?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/Jauppp/minishell?style=default&color=0080ff" alt="repo-language-count">
<p>
<p align="center">
	<!-- default option, no dependency badges. -->
</p>

<br><!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary><br>

- [ Features](#-features)
- [ Repository Structure](#-repository-structure)
- [ Modules](#-modules)
- [ Getting Started](#-getting-started)
  - [ Installation](#-installation)
- [ Authors](#-authors)
- [ Appendix](#-appendix)
- [ Acknowledgments](#-acknowledgments)
</details>
<hr>

##  Features

|   | Feature   | Description  |
|----|------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| ⚙️  | Architecture| The project was built on a modular monolithic architecture model.|
| 🧩 | Modularity| Major functionnalities are separated in modules (Parsing, Ray Casting, Rendering) to improve readibily and code organisation.||
| 📦 | Dependencies | MinilibX, math.h, X11.|

---

##  Repository Structure

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
---

##  Getting Started

**System Requirements:**

This project was built on Ubuntu 22, it is untested on other distributions and operating systems. 

The MLX is included in this repositery, but you might need to install its dependencies:

```sh
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

The project also requires make for compilation : 
``sh
sudo apt-get make
``

###  Installation

## Authors

- [@csweetin](https://github.com/cha202)
- [@cdomet-d](https://github.com/Jauppp)

## Appendix

##  Acknowledgments


[**Return**](#-overview)

---