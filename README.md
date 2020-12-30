# rotationMatrix3DinC
One of my first C projects

Program accepts a single coordinate in the form [x,y.z] and then allows the user to either 
translate or rotate the coordinates.

Translation simply adds a vector in the form [a,b,c] to the coordinate, and then prints coordinates before and after translation.

Rotation allows the 6 orders of rotation 1: x,y,x  2: x,z,y  3: y,x,z  4: y,z,x  5: z,x,y  6: z,y,x.
The user will input the angle of rotation in each axis in degrees or radians, followed by the 
order of rotation required. Then the coordinates are then printed before and after rotation are printed.
