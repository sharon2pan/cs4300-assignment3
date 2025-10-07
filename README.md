# cs4300-assignment3

**Program Expectations**

This program should create a solar system within a wireframe box. The solar system consists of planets that orbit a sun and satellites that orbit the planets. The user is also able to rotate the screen by using their mouse to drag. 

**Program Design**
- I used the CameraViews demo as started code for this assignment
- I used spheres to draw the planets and cylinders to draw the satellites
- I set different rotations along the x and z axes for the planets to give them unique orientations
- For the satellite with an elliptical orbit, I used the orbit equation with eccentricity to find the positions
- In the View, I ensured that the planet transformations were correctly applied to each satellite before applying the satellite transformations
- For drawing the orbits, I took advantage of matrix-vertex multiplication to find the appropriate position
- Rotating the screen involves taking into account the cursor's starting position when the left mouse button is clicked and the final position when the left mouse button is released, then finding the appropriate amount to rotate

**List of Working Features**
- Box is drawn as a wireframe
- Sun is stationary in the center
- At least 4 planets orbit the sun
- Planets' orbits are oriented in different ways
- Planets are not in danger of colliding
- At least 2 planets have satellites
    - The dark blue and purple planets have satellites 
- At least 1 planet has at least 1 satellite with an off-center orbit
    - The purple planet has an off-center satellite
- All orbits are drawn with white lines (only 200 points are saved to make the program more efficient, but if needed, the full orbit without deleting any points can also be shown)
- All planets are different colors
- The screen rotates as the mouse is dragged
