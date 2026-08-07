## FORT: a FallOut Resource Tools

FORT is a **modern** tools pack for modding **old** fallout games (Fallout 1, Fallout 2, Fallout:Tactics & FOnline), currently WIP.

## Configuration Details

* **Fallout Master Extraction:** Set the workspace path to extract the original Fallout `master.dat` archive directly into your target folder.
* **FOnline Root Mapping:** Point the FOnline engine and asset paths directly to your main project root directory to correctly resolve assets, maps, and server configurations.

## Updates & Recent Changes (2026)

* Updated and modified the source code using **Visual Studio Code (C++ 2026)** to successfully resolve map conversion bottlenecks.
* Improved compatibility and code logic for converting legacy Fallout `.map` files into modern FOnline `.fomap` format using FORT.

## What application contains at this time:

1. Fonline Tools
1. Fonline2D Graphics format reader (new revs.), converter to `.png`

2. `.fotxtb` text format reader (new revs.), converter to `.msg`



2. Fallout 1/2 Tools
1. Fallout `.map` reader, converter to FOnline `.fomap` *(Updated/Fixed via C++ 2026 codebase modifications)*

2. Fallout `.frm` reader, viewer, converter to `.png`

3. Fallout `.pro` reader, viewer


4. Fallout `.rix` reader, viewer, converter to `.png`

5. Fallout `.msk` reader, viewer, converter to `.png`



3. Fallout:Tactics Tools
1. Fallout:Tactics `.zar` format reader, viewer, converter to `.png`

2. Fallout:Tactics `.til` format reader, viewer, converter to `.png`




## What is planned to implement in future:

1. FOnline Tools
1. FOnline `.fomap` reader & some tools (Like map generator)


2. FOnline `.fofrm` reader, viewer, editor


3. FOnline `.fopro` reader, viewer, editor


4. Fonline3D Models format reader (new revs.), converter to `.gltf`



2. Fallout 1/2 Tools
1. Fallout `.acm` reader, converter to `.ogg`

2. Fallout `.mve` reader, viewer, converter to `.ogv`

3. Fallout `.dat` reader, viewer


4. Fallout `SAVE.DAT` reader, viewer, editor


5. Fallout `.aaf` reader, viewer


6. Fallout `.fon` reader, viewer




3. Fallout:Tactics Tools
1. Fallout:Tactics `.spr` reader, viewer, converter to PNGs, (from) Fallout `.frm`, (from) FOnline `.fofrm`

2. Fallout:Tactics `.zar` converter to (from) Fallout `.frm`

3. Fallout:Tactics `.til` converter to (from) Fallout `.frm`, (from) FOnline `.fofrm`



4. Various other tools that related to Fallout, or FOnline



## Thanks To:



* JordanCpp, Using His Byte & Memory Readers from [ArcanumWorld](https://github.com/JordanCpp/ArcanumWorld)

* Cvet, and His [Fonline Engine](https://github.com/cvet/fonline) as Format Reading References.


* TeamX.ru Team for Their Docs About Format Structures.