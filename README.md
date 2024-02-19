# CUBE3D

This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever.

## Raycasting Summary exploring 3D Rendering

Raycasting is a rendering technique used to simulate a 3D perspective in a 2D environment. Unlike traditional 3D rendering methods which employ complex polygonal models, 
raycasting relies on casting rays from the viewpoint (typically the player's position) to calculate the intersections with objects in the scene. 
These intersections are then used to determine the visible surfaces and render the scene accordingly.


# Key Concepts


### Rays
Virtual lines cast from the viewpoint into the scene, representing the player's line of sight.

### Intersection Detection
Calculation of intersections between rays and objects in the scene, often using techniques like bounding box or bounding sphere intersection tests.

### Wall Rendering
Determination of the distance to the nearest wall along each ray, allowing for rendering of walls in the scene.

### Textures and Shading
Application of textures and shading techniques to the rendered walls to enhance realism.

### Field of View (FOV)
Adjustment of the angle of the rays to control the player's field of view, influencing the perceived depth and perspective of the scene.
