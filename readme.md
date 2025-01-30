# PROJECT FDF FOR 42
By chdonnat (Christophe Donnat from 42 Perpignan, France)

## AIM OF THE PROJECT:
This project involves graphically creating the schematic representation of a terrain in relief
by connecting different points (x, y, z) with segments.
You must use the MiniLibX, either the version available on the school machines or by installing it from the sources.
The rendering must be displayed using an isometric projection.
The terrain coordinates will be stored in a file provided as a parameter.
Each number represents a point in space:
The horizontal position corresponds to its x-coordinate.
The vertical position corresponds to its y-coordinate.
The value corresponds to its altitude (z-coordinate).
Graphic Management
Your program must display an image in a window.
The window management must remain smooth (switching windows, minimizing, etc.).
Pressing the ESC key must close the window and exit the program cleanly.
Clicking on the close button at the top of the window must close the window and exit the program cleanly.
Using MiniLibX images is mandatory.

### BONUS PART:
You will earn additional points if you:
Include an additional projection (e.g., parallel or conical projection).
Implement factor in and factor out.
Implement translation (movement).
Implement rotation (rotating your rendering).
Add an extra bonus feature of your choice.

## SOME COMMANDS YOU CAN USE:
compile the program:

	make

execute the program (you must pass a file containing coordonates)

	./fdf <file>

## ARCHITECTURE:
- mandatory/ directory with files for the mandatory part
	- src/ directory for main files of the project
	- utils/ directory for secondary files
	- include/ directory for headers
- bonus/ directory with files for the bonus part
	- src/ directory for main files of the project
	- utils/ directory for secondary files
	- include/ directory for headers
- test/ directory fot tests files
- libft/ directory with my own library (standard functions, ft_printf, get_next_line)
- mlx_mac/ directory for the mac version of the minilibx library
- mlx_linux/ directory for the linux version of the minilibx library
- Makefile (with rules: make bonus clean fclean re)
- readme.md for quick explanation and main commands of the project

> Note that in my project, mandatory and bonus are exactly the same (the bonus features are also in the mandatory part).

## DOCUMENTATION:

### errno
errno is a global variable defined in <errno.h> that stores an error code set by system calls or library functions when they fail.
Each error code corresponds to a specific failure reason, such as ENOENT for "No such file or directory" or EACCES for "Permission denied."
These codes provide a standardized way to identify errors.
It’s important to check and use errno immediately after a function fails, as its value can be overwritten by subsequent calls.

### perror()
perror is a C standard library function used to display an error message associated with the current value of errno.
It outputs a descriptive string that includes a user-provided message (for context) followed by the error description.
The format is typically:
<user message>: <error description>
For example, if fopen fails to open a file and sets errno to ENOENT, calling perror("File open error") will output:
File open error: No such file or directory

### strerror()
strerror is a C standard library function that converts an error code (typically stored in errno) into a human-readable error message.
It returns a pointer to a string describing the error corresponding to the given error code.
For example, if errno is set to ENOENT, calling strerror(ENOENT) would return "No such file or directory".
This is useful for displaying or manipulating error messages without directly printing them to standard output.
#### Difference Between strerror and perror:
The key difference is that perror directly prints the error message with an optional prefix to standard error (stderr),
while strerror returns the error message as a string, allowing greater flexibility for formatting or logging.
#### Risks of Using strerror:
strerror is not thread-safe because it may use a static internal buffer to store the returned string.
This can lead to unexpected results in multi-threaded programs where multiple threads access strerror simultaneously.
For thread-safe alternatives, use strerror_r.

### common errno error codes
Here are values standardized across UNIX-like systems, including Linux.
The error codes correspond to specific error conditions that might occur in system calls or library functions,
such as file handling, memory allocation, and process management.

**Code	Value	Description**

EPERM	(1)	Operation not permitted

ENOENT	(2)	No such file or directory

EINTR	(4)	Interrupted system call

EIO	(5)	Input/output error

EBADF	(9)	Bad file descriptor

EAGAIN	(11)	Resource temporarily unavailable

ENOMEM	(12)	Out of memory

EACCES	(13)	Permission denied

ENOTDIR	(20)	Not a directory

---

### The math.h library
The math.h library in C provides a wide range of mathematical functions that are essential for performing advanced calculations.
These functions include operations for basic arithmetic, trigonometry, logarithms, exponentiation, and more.
#### Basic Arithmetic Functions
- fabs(): Returns the absolute value of a floating-point number.
- fmod(): Computes the remainder of division of two floating-point numbers.
- pow(): Calculates the power of a number (base raised to the exponent).
- sqrt(): Computes the square root of a number.
#### Trigonometric Functions
- sin(), cos(), tan(): Return the sine, cosine, and tangent of an angle (in radians), respectively.
- asin(), acos(), atan(): Return the arcsine, arccosine, and arctangent of a value, returning the result in radians.
#### Logarithmic and Exponential Functions
- log(): Computes the natural logarithm (base e) of a number.
- log10(): Computes the logarithm to base 10 of a number.
- exp(): Computes the exponential function, returning e raised to the power of the argument.
#### Other Mathematical Functions
- ceil(): Returns the smallest integer value greater than or equal to the given number.
- floor(): Returns the largest integer value less than or equal to the given number.
- round(): Rounds the value to the nearest integer.
- modf(): Breaks a floating-point number into its integral and fractional parts.
These functions help with a broad range of mathematical tasks, from simple arithmetic to complex trigonometric and logarithmic operations,
making math.h an essential tool in any scientific or engineering computation in C.

---
---

## Projection from 3D to 2D: a step-by-step guide

x, y, and z are the original coordinates (z represents altitude).  
Since we want to project from 3D onto a 2D screen, the operation will consist of calculating x_proj and y_proj coordinates to create a 3D effect.

### Preliminary step: Centering the coordinates (calculation to be done only once)  
To center the coordinates, modify the x, y, and z values of each point by subtracting the mean values x_mean, y_mean, and z_mean.  
These averages are calculated simply. For example, to compute x_mean, add the x values of each point on the map and divide the sum by the number of points. This calculation should be done only once before the first projection.  
> x = x - x_mean  
> y = y - y_mean  
> z = z - z_mean

### Basic isometric projection  
Here is the formula to apply to project 3D coordinates onto a 2D plane in isometric view (without rotation, without zoom),
where x_proj and y_proj are the coordinates obtained after applying the 2D projection (there is no z_proj value):
> x_proj = 0.866 * x - 0.866 * y  
> y_proj = 0.5 * x + 0.5 * y - z  
In an isometric projection, the 3D axes are tilted so that the angles between the X, Y, and Z axes are equal (120°), creating a view without depth distortion.
This means that each axis is viewed at a 30° angle from the horizontal plane.
The values 0.866 and 0.5 come from trigonometric functions associated with this angle.
More precisely, 0.866 is an approximation of cos(30°), and 0.5 is sin(30°).
These coefficients project the 3D coordinates (x, y, z) onto a 2D plane while maintaining uniform proportions for the inclined axes, giving the illusion of depth without perspective.

### Adding the possibility of rotations  
To enable rotations, **before the 3D to 2D projection**, calculate intermediate values for x, y, and z (called x_rot, y_rot, and z_rot)
after applying the formulas to account for the rotations.
These rotations are calculated from the angles ox, oy, and oz expressed in radians.
To produce rotations, simply vary the values of ox, oy, or oz.  

#### Step 1: Rotation around the X-axis  
> x_rot = x  
> y_rot = y * cos(ox) - z * sin(ox)  
> z_rot = y * sin(ox) + z * cos(ox)  

#### Step 2: Rotation around the Y-axis  
> x_temp = x_rot  
> x_rot = x_temp * cos(oy) + z_rot * sin(oy)  
> z_rot = -x_temp * sin(oy) + z_rot * cos(oy)  

#### Step 3: Rotation around the Z-axis  
> x_temp = x_rot  
> y_temp = y_rot  
> x_rot = x_temp * cos(oz) - y_temp * sin(oz)  
> y_rot = x_temp * sin(oz) + y_temp * cos(oz)  

#### Step 4: 3D to 2D Projection (isometric view)
> x_proj = 0.866 * x_rot - 0.866 * y_rot  
> y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot  

### Adding the possibility of zooming in and out  
Follow the same steps and simply multiply the projected coordinates by the zoom value to obtain the final coordinates x_out and y_out.  
Simply modify the zoom variable value to zoom in or out.
Zoom can be a value less than 1 for a zoom-out effect, and a value of 1 corresponds to no zoom.
The zoom value must be strictly greater than zero to avoid a strange inversion effect.
So now the steps are:

#### Step 1: Rotation around the X-axis  
> x_rot = x  
> y_rot = y * cos(ox) - z * sin(ox)  
> z_rot = y * sin(ox) + z * cos(ox)  

#### Step 2: Rotation around the Y-axis  
> x_temp = x_rot  
> x_rot = x_temp * cos(oy) + z_rot * sin(oy)  
> z_rot = -x_temp * sin(oy) + z_rot * cos(oy)  

#### Step 3: Rotation around the Z-axis  
> x_temp = x_rot  
> y_temp = y_rot  
> x_rot = x_temp * cos(oz) - y_temp * sin(oz)  
> y_rot = x_temp * sin(oz) + y_temp * cos(oz)  

#### Step 4: 3D to 2D Projection (isometric view)
> x_proj = 0.866 * x_rot - 0.866 * y_rot  
> y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot  

#### Step 5: Applying the zoom  
> x_out = x_proj * Zoom  
> y_out = y_proj * Zoom  

### Adding centering relative to the screen  
To center the projection on the screen, simply add to x_out the screen width (width) divided by 2 and to y_out the screen height (height) divided by 2.
So the steps are:

#### Step 1: Rotation around the X-axis  
> x_rot = x  
> y_rot = y * cos(ox) - z * sin(ox)  
> z_rot = y * sin(ox) + z * cos(ox)  

#### Step 2: Rotation around the Y-axis  
> x_temp = x_rot  
> x_rot = x_temp * cos(oy) + z_rot * sin(oy)  
> z_rot = -x_temp * sin(oy) + z_rot * cos(oy)  

#### Step 3: Rotation around the Z-axis  
> x_temp = x_rot  
> y_temp = y_rot  
> x_rot = x_temp * cos(oz) - y_temp * sin(oz)  
> y_rot = x_temp * sin(oz) + y_temp * cos(oz)  

#### Step 4: 3D to 2D Projection (isometric view)
> x_proj = 0.866 * x_rot - 0.866 * y_rot  
> y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot  

#### Step 5: Applying the zoom  
> x_out = x_proj * Zoom  
> y_out = y_proj * Zoom  

#### Step 6: After zoom, centering relative to the screen  
> x_out = x_out + Width / 2  
> y_out = y_out + Height / 2

---

### Perspective projection  
In a perspective projection, the distance simulates the depth effect by adjusting the size of objects based on their distance from the camera.
This effect is achieved using a reduction factor:  
> factor = Distance / (Distance + z_rot)
The farther an object is (large z_rot), the smaller this factor becomes, and thus the smaller its projected coordinates (x_proj, y_proj).
This creates the visual impression that objects closer to the observer are larger, and distant ones are smaller, reproducing how the human eye perceives depth in the real world.
The Distance variable directly controls this effect, where a large value reduces perspective distortion (making the view closer to isometric), and a small value amplifies it.  

For a perspective, follow the same steps but introduce two new values: distance and factor.  
#### distance:
The distance between the camera and the projection screen (the 2D plane).
Let’s call this distance Distance. This is the value that can be varied to modify the depth effect.  
#### factor:
The "factor" in perspective projection is a value used to simulate the depth effect, i.e., the appearance of an object being smaller as it moves away from the camera.
In other words, it corresponds to a reduction factor that makes closer objects larger and farther objects smaller.
In a perspective projection, the object is projected onto the projection plane based on its distance from the camera.
The farther an object is, the more reduced it will be in the projection.
The "factor" is calculated based on the distance value.  

The complete steps for a perspective with rotations, zoom, depth variation, and centering relative to the screen:

#### Step 1: Rotation around the X-axis  
x_rot = x  
y_rot = y * cos(ox) - z * sin(ox)  
z_rot = y * sin(ox) + z * cos(ox)  

#### Step 2: Rotation around the Y-axis  
x_temp = x_rot  
x_rot = x_temp * cos(oy) + z_rot * sin(oy)  
z_rot = -x_temp * sin(oy) + z_rot * cos(oy)  

#### Step 3: Rotation around the Z-axis  
x_temp = x_rot  
y_temp = y_rot  
x_rot = x_temp * cos(oz) - y_temp * sin(oz)  
y_rot = x_temp * sin(oz) + y_temp * cos(oz)  

#### Step 4: 3D to 2D Projection  
factor = Distance / (Distance + z_rot)  
x_proj = x_rot * factor  
y_proj = y_rot * factor  

#### Step 5: Applying the zoom  
x_out = x_proj * Zoom  
y_out = y_proj * Zoom  

#### Step 6: After zoom, centering relative to the screen  
x_out = x_out + Width / 2  
y_out = y_out + Height / 2

