# FORT — Fallout Resource Tools

**A collection of tools for exploring, viewing, and converting resource formats used by classic Fallout games and FOnline.**

FORT (*FallOut Resource Tools*) is a work-in-progress toolkit focused on modding and working with legacy game assets from **Fallout 1, Fallout 2, Fallout Tactics, and FOnline**.

The project provides readers, viewers, and converters for various game-specific file formats, with the long-term goal of bringing these resources into more accessible and modern workflows.

> **Project status:** Work in progress. Some tools and formats are implemented, while others remain planned.

---

## Table of Contents

- [Features](#features)
- [Supported Games and Formats](#supported-games-and-formats)
  - [FOnline Tools](#1-fonline-tools)
  - [Fallout 1 and Fallout 2 Tools](#2-fallout-1-and-fallout-2-tools)
  - [Fallout Tactics Tools](#3-fallout-tactics-tools)
- [Configuration](#configuration)
- [Recent Updates](#recent-updates)
- [Planned Features](#planned-features)
- [Acknowledgements and References](#acknowledgements-and-references)

---

## Features

FORT brings together tools for working with several classic Fallout and FOnline resource formats.

Depending on the format, supported operations include:

- **Reading:** Inspect supported file structures and resource data.
- **Viewing:** Examine graphics and other supported resources.
- **Conversion:** Export resources into more accessible formats, including PNG and other target formats.
- **Modding support:** Help make legacy game assets easier to inspect and reuse in modding workflows.

The available operations vary by format. Features listed under [Planned Features](#planned-features) are not yet presented as implemented functionality.

## Supported Games and Formats

### 1. FOnline Tools

| Format | Available functionality |
|---|---|
| FOnline 2D graphics formats | Read newer revisions and convert graphics to `.png` |
| `.fotxtb` | Read newer revisions and convert text resources to `.msg` |

### 2. Fallout 1 and Fallout 2 Tools

| Format | Available functionality |
|---|---|
| `.map` | Read Fallout maps and convert them to FOnline `.fomap` |
| `.frm` | Read, view, and convert graphics to `.png` |
| `.pro` | Read and view prototype files |
| `.rix` | Read, view, and convert images to `.png` |
| `.msk` | Read, view, and convert images to `.png` |

**MAP conversion:** The legacy Fallout map reader and converter has received code corrections to improve compatibility with map files. Nested inventory objects are now parsed recursively, addressing a parsing failure encountered during conversion of the Junktown map, `JUNKCSNO.MAP`.

### 3. Fallout Tactics Tools

| Format | Available functionality |
|---|---|
| `.zar` | Read, view, and convert graphics to `.png` |
| `.til` | Read, view, and convert graphics to `.png` |

---

## Configuration

FORT's configuration depends on which games, assets, and engines you intend to work with.

### Fallout Master Archive Extraction

Configure the workspace path to extract the original Fallout `master.dat` archive into your chosen target directory.

Ensure that the extraction destination matches the directory structure expected by the tools.

### FOnline Root Mapping

Configure the FOnline engine and asset paths to point to your main project root directory.

Correct path configuration is important for resolving the assets, maps, and server configuration files required by the tools.

> **Note:** The exact configuration steps may depend on your local installation and project setup.

---

## Recent Updates

### 2026

Recent development work has focused on improving the existing C++ codebase and resolving issues in legacy resource conversion.

- **Fallout MAP conversion:** Corrected parsing of nested inventory objects to prevent the reader from becoming misaligned when processing map data.
- **Junktown map compatibility:** Successfully converted and loaded `JUNKCSNO.MAP` in FOClassic Mapper after the parsing correction.
- **Legacy format support:** Continued work on converting Fallout `.map` resources into FOnline `.fomap` format.
- **Development environment:** Continued source-code maintenance using Visual Studio and C++ tooling.

FORT remains a work in progress, and further testing across different maps and resource files is encouraged.

---

## Planned Features

The following features are planned for future development. Their inclusion here does not imply that they are already implemented.

### 1. FOnline Tools

- [ ] `.fomap` reader and additional map utilities, such as a map generator.
- [ ] `.fofrm` reader, viewer, and editor.
- [ ] `.fopro` reader, viewer, and editor.
- [ ] FOnline 3D model reader for newer revisions, with conversion to `.gltf`.

### 2. Fallout 1 and Fallout 2 Tools

- [ ] `.acm` reader and converter to `.ogg`.
- [ ] `.mve` reader, viewer, and converter to `.ogv`.
- [ ] `.dat` reader and viewer.
- [ ] `SAVE.DAT` reader, viewer, and editor.
- [ ] `.aaf` reader and viewer.
- [ ] `.fon` reader and viewer.

### 3. Fallout Tactics Tools

- [ ] `.spr` reader, viewer, and PNG conversion tools, including conversion from Fallout `.frm` and FOnline `.fofrm` formats.
- [ ] `.zar` conversion to and from Fallout `.frm`.
- [ ] `.til` conversion to and from Fallout `.frm` and FOnline `.fofrm`.

### 4. Additional Tools

- [ ] Additional utilities related to Fallout games and FOnline.
- [ ] Further improvements to existing readers, viewers, and converters.

---

## Acknowledgements and References

FORT builds on the work of developers and communities who have documented these games' resource formats and made useful code and technical references available.

Special thanks to:

- **JordanCpp** — For allowing the use of byte and memory reader implementations from [ArcanumWorld](https://github.com/JordanCpp/ArcanumWorld).
- **Cvet** — For the [FOnline Engine](https://github.com/cvet/fonline), used as a reference for understanding resource formats and their structures.
- **TeamX.ru** — For documentation describing Fallout file formats and their underlying data structures.

These projects and documentation resources have been valuable references for understanding legacy file formats and developing FORT's conversion tools.

---

## Contributing and Development

FORT is an ongoing project, and improvements to existing tools and support for additional formats are part of its development goals.

Testing against real game assets is particularly useful for identifying compatibility issues in legacy resource readers and converters.

When reporting a conversion issue, consider including:

- The game and resource format involved.
- The name of the file that fails to convert.
- The operation being performed.
- The error message or relevant output, if available.

These details can help make issues easier to reproduce and resolve.

---

## Disclaimer

FORT is a work-in-progress resource toolkit intended for use with classic Fallout games, Fallout Tactics, and FOnline.

Compatibility and feature availability may vary by format and file revision. Always keep backups of original game assets and project files when testing conversion tools.

---

**FORT — FallOut Resource Tools**  
*Preserving, exploring, and converting classic Fallout resources.*
