# Pucman
Several years ago I coded my first computer game via C++ - pucman. It was build of procedural code (without classes and other OOP features) and had a one huge program file with more than thousand lines and big number of global variables and crutches. Now I have decided to refactor and recoded it with OOP principles. The repository contains both versions of my masterpiece, you can find their builds in "OLD version" and "OOP version" folders (A control is standard - WASD to move and ESC to pause (make sure you are using english keyboard). There are two screenshots for you to compare below, first from new game and second from old one.

#### OOP version
![image](https://user-images.githubusercontent.com/61201241/205916746-56c492f2-aa33-4a7b-96b5-829e7bb0bd4e.png)
#### OLD version 
![image](https://user-images.githubusercontent.com/61201241/202021568-40954dc4-e121-479a-b8f0-982c71c1b6b7.png)

As you can see, there are many differences between two versions. That because during the developing I decided to not only recoded, but also improve game design and engine. A list of main upgrades is following:
* **Graphics.** Graphics primitives were detached to separeted graphics library - Primitives (it is also one of my old progects which I decided to reconstruct), I used a refactor branch edition: https://github.com/skomaroh1845/Primitives/tree/Refactor_Branch. This simplified my developing thanks to using done objects for drawing, that let me made more detailed graphics with less forces.
* **New font.** In old version I created my own font (I knew that glut has it own fonts, but I knew only about bitmap fonts which could not be scaled, and so they didn't suit to my purposes) and a big number of functions which were drawing text on a screen. In that time I found out that glut has stroke fonts which could be scaled, so I used them.
* **Animations.** I added animation to coins, now they swing up and down. Also I left ghost's eyes motion during a game pause. This features make the game more alive.
* **Mobs intelligence.** In first edition of my game mobs had a randomized movement (they just chose a random way on each turn), now they have more complex behavior: generally ghosts compute a gradient vector to player's position and go accodring to it's direction, but each second turn are randomized to make behavior unpredictable.
