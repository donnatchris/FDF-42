#PROJECT FDF FOR 42
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

	./fdf <file.fdf>

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

## DOCUMENTATION:

### errno
errno is a global variable defined in <errno.h> that stores an error code set by system calls or library functions when they fail.
Each error code corresponds to a specific failure reason, such as ENOENT for "No such file or directory" or EACCES for "Permission denied."
These codes provide a standardized way to identify errors.
It’s important to check and use errno immediately after a function fails, as its value can be overwritten by subsequent calls.

### perror
perror is a C standard library function used to display an error message associated with the current value of errno.
It outputs a descriptive string that includes a user-provided message (for context) followed by the error description.
The format is typically:
<user message>: <error description>
For example, if fopen fails to open a file and sets errno to ENOENT, calling perror("File open error") will output:
File open error: No such file or directory

### strerror
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

## 3D-to-2D projection
A 3D-to-2D projection is the mathematical process of converting three-dimensional coordinates (x,y,z)
into two-dimensional coordinates (screenX,screenY) for display on a flat surface, such as a computer screen.
This transformation is essential for visualizing 3D objects in a 2D space.
There are different types of projections, such as perspective projection, which simulates depth by scaling objects based on their distance from the viewer,
and isometric projection, which preserves object proportions and angles without perspective scaling.
Each type uses specific formulas to map 3D points to the 2D plane while accounting for parameters like scaling, translation, and depth.

In a typical 2D coordinate system for a screen:

- The origin (0,0) is located at the top-left corner.
	Coordinates increase to the right (for x) and downward (for y).
	However, in most 3D systems:
- The origin (0,0,0) is usually at the center of the scene.
	A projection without adjustment would center the image on the origin of the 3D system, which could misalign the image on the screen.
	By adjusting with ResX/2, the projection is properly aligned to the center of the 2D screen.

### Isometric Projection  
An **isometric projection** is a type of parallel projection where 3D coordinates are mapped to a 2D plane
while maintaining equal angles (120°) between the \(x\), \(y\), and \(z\) axes.
Unlike perspective projection, isometric projection does not simulate depth,
meaning objects retain their proportions regardless of their distance from the viewer.
#### Key Features:  
- **No perspective scaling**: All objects appear at their true size regardless of depth.  
- **Angles and proportions**: Axes \(x\), \(y\), and \(z\) are displayed as equally spaced angles, typically at 120°.  
- **factor control**: A scaling factor (referred to as "factor") determines the size of the projected objects on the 2D plane.
  Increasing this factor enlarges objects, simulating a factor-in effect, while decreasing it simulates a factor-out effect.  
#### Formula for Isometric Projection  
To transform a 3D point \((x, y, z)\) into 2D coordinates \((screenX, screenY)\), use the following formulas:

	screenX = originx + factor * (x - z)
	screenY = originy + factor * ((x + z) / 2 - y)

#### Explanation of Parameters:  
- **originx, originy**: The 2D origin or reference point on the screen, typically the center of the viewport.  
- **factor**: A scaling factor controlling the size of the objects (factor).  
- **(x, y, z)**: The 3D coordinates of the point being projected.  

Adjusting **factor** dynamically allows you to factor in or out of the scene.

Adjusting **originx** or **originy** allows you to make translations.

### Perspective Projection
In a perspective view, coordinates are calculated differently compared to an isometric projection.
A perspective projection belongs to the category of central projections, where parallel lines in 3D space converge at a vanishing point in the 2D projection.
This introduces a perspective effect, meaning objects appear smaller as they move further away from the viewer.

In a perspective view: The x, y and z axes are represented based on a point of view (camera or observer),
with the z-axis typically representing depth along the viewing direction.
Object sizes reduce as they get further from the viewer, with the z-coordinate influencing the apparent size.

To project a 3D point (x,y,z) to a 2D coordinate (screenX,screenY), a transformation is applied, where the x and y coordinates
are divided by the z-coordinate to simulate the shrinking of objects with distance.

#### Perspective Projection Formulas
The standard formulas for transforming 3D coordinates into 2D in a perspective view are:
	
	screenX = (x / z) * distance + originx
	screenY = (y / z) * distance + originy

#### Explanation of Parameters:  
- **originx, originy**: The reference point on the screen (usually the center or a specific point of the 2D viewport).
- **x, y, z**: The 3D coordinates of the point.
- **distance**: The distance from the viewer or camera to the 3D scene.
#### Differences Between Perspective and Isometric Projection
- Depth (z):
	- Perspective: z significantly affects object size; the larger the z-coordinate, the smaller the object appears.
	- Isometric: z does not affect object size; depth is represented geometrically.
- Angles and Proportions:
	- Perspective: Angles converge at a vanishing point, and proportions change with distance.
	- Isometric: Angles remain fixed (typically 120°), and proportions stay constant.

### factor and translation
#### Adjusting the factor (factor):
- For Isometric Projection:

	The factor (also known as the scale or factor factor) controls the size of the objects on the 2D screen.
	Adjusting the factor dynamically allows you to factor in or out, changing how large or small objects appear without affecting their proportions.
	The factor only affects the size of objects on the screen, but it does not introduce perspective effects
	(since isometric projection does not account for depth or distance like perspective does).
- For Perspective Projection:

	Similarly, adjusting the factor in perspective projection (typically called "distance" from the camera or viewpoint)
	also changes the size of the objects on the screen.
	When you adjust the distance, it affects how far objects appear, and as the distance changes,
	objects will appear smaller or larger depending on their z value (depth), as part of the perspective effect.
	So adjusting this factor also functions as a factor but with the added effect of changing how the scene is perceived in terms of depth
	(objects closer appear larger, and those further away appear smaller).
#### Adjusting originx and originy (translation):
- For Isometric Projection:

	originx and originy are used to translate or shift the entire 2D scene on the screen.
	This is similar to moving the camera in a 3D space but in 2D.
	Adjusting the origin does not change the objects themselves but shifts the entire view, making the scene appear to move without altering object sizes or angles.
- For Perspective Projection:

	Similarly, adjusting originx and originy in perspective projection moves the scene on the screen, translating the entire view without affecting the 3D scene itself.
	However, in perspective, since the view is inherently affected by depth (z-axis),
	the origin shift might also result in changes to how objects are perceived in terms of their relative positions,
	especially when combined with changes in the distance (factor factor).
#### In summary:
Factor (factor): Both isometric and perspective projections allow dynamic factoring by adjusting the factor, with isometric affecting object size directly, and perspective affecting both size and the appearance of depth.

originx and originy (Translation): These adjust the position of the entire scene on the 2D screen, without altering the geometry of the scene itself, in both isometric and perspective projections. However, in perspective, changes in translation may also affect how the scene is perceived due to the depth-based effects.



---

Projection de 3D vers 2D
- x, y et z sont les coordonnées d'origine (z est l'altitude)
- x_mean, y_mean et z_mean sont les valeurs moyennes pour l'ensemble des coordonnées x, y et z des points de la carte
	(on obtient par exemple x_mean en faisant la somme des coordonnées x de chaque point puis en divisant le résultat par le nombre de points)
- ox,oy,oz : Angles de rotation autour des axes (exprimés en radians)
- x_rot, y_rot, z_rot sont les cordonnées transformées une fois appliquées les rotations sur les axes x, y et z
- x_proj et y_proj sont les coordonnées projetées sur le plan en 2D
- distance : Distance de la "caméra" (utilisé uniquement pour la vue en perspective)
- zoom : variable qui permet de zoomer et dezoomer

// Etape préliminaire: Centrer les coordonnées (calcul à faire une seule fois)
x = x - x_mean
y = y - y_mean
z = z - z_mean

// Step 1: Rotation autour de l'axe X
x_rot = x
y_rot = y * cos(ox) - z * sin(ox)
z_rot = y * sin(ox) + z * cos(ox)

// Step 2: Rotation autour de l'axe Y
x_temp = x_rot
x_rot = x_temp * cos(oy) + z_rot * sin(oy)
z_rot = -x_temp * sin(oy) + z_rot * cos(oy)

// Step 3: Rotation autour de l'axe Z
x_temp = x_rot
y_temp = y_rot
x_rot = x_temp * cos(oz) - y_temp * sin(oz)
y_rot = x_temp * sin(oz) + y_temp * cos(oz)

// Step 4: Projection 3D vers 2D
if ProjectionType == "isometric":
x_proj = 0.866 * x_rot - 0.866 * y_rot
y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot

else if ProjectionType == "perspective":
factor = Distance / (Distance + z_rot)
x_proj = x_rot * factor
y_proj = y_rot * factor

// Step 5: Application du zoom
x_out = x_proj * Zoom
y_out = y_proj * Zoom

// Step 6: Après zoom, centrer par rapport à l’écran
x_out = x_out + Width / 2
y_out = y_out + Height / 2

return (x_out, y_out)



Dans une projection isométrique, les axes 3D sont inclinés de manière à ce que les angles entre les axes X, Y, et Z soient égaux (120°), créant une vue sans distorsion de profondeur. Cela signifie que chaque axe est vu sous un angle de 30° par rapport au plan horizontal. Les valeurs 0.866 et 0.5 proviennent des fonctions trigonométriques associées à cet angle. Plus précisément, 0.866 est une approximation de cos(30°), et 0.5 est sin(30°). Ces coefficients permettent de projeter les coordonnées 3D (x, y, z) sur un plan 2D tout en conservant des proportions uniformes pour les axes inclinés, ce qui donne l’illusion de la profondeur sans perspective.

Dans une projection perspective, la distance simule l’effet de profondeur en ajustant la taille des objets en fonction de leur éloignement de la caméra. Cet effet est obtenu grâce à un facteur de réduction : factor = Distance / (Distance + z_rot). Plus un objet est éloigné (z_rot grand), plus ce facteur est petit, et donc plus ses coordonnées projetées (x_proj, y_proj) sont réduites. Cela crée l’impression visuelle que les objets proches de l’observateur sont plus grands et ceux éloignés sont plus petits, reproduisant ainsi la manière dont l’œil humain perçoit la profondeur dans le monde réel. La variable Distance contrôle directement cet effet, où une grande valeur diminue la distorsion perspective (rendant la vue proche de l’isométrique) et une petite valeur l’amplifie.








Projection de 3D vers 2D
x, y et z sont les coordonnées d'origine (z est l'altitude). Comme on veut projeter de la 3D sur un écran 2D, l'opération va consister à calculer des coordonnées x_proj et y_proj pour donner un effet 3D

Etape préliminaire: Centrer les coordonnées (calcul à faire une seule fois)
Afin de centrer les coordonnées, on modifie les valeurs x, y et z de chaque point en leur soustrayant les valeurs moyennes x_mean, y_mean et z_mean
On calcule ces moyennes très simplement. Par exemple pour x_mean, on additionne les valeurs x de chaque point de la carte pouis on divise cette somme par le nombre de points.
Ce calcul doit être réalisé une seule fois avant la première projection.
x = x - x_mean
y = y - y_mean
z = z - z_mean

Projection isometrique de base
Voici la formule à appliquer pour projeter des coordonnées 3D sur un plan 2D en vu isométrique (sans rotation, sans zoom),
où x_proj et y_proj sont les coordonnées obtenues après application de la projection en 2D (il n'y a donc pas de valeur z_proj)
x_proj = 0.866 * x - 0.866 * y
y_proj = 0.5 * x + 0.5 * y - z
Dans une projection isométrique, les axes 3D sont inclinés de manière à ce que les angles entre les axes X, Y, et Z soient égaux (120°), créant une vue sans distorsion de profondeur. Cela signifie que chaque axe est vu sous un angle de 30° par rapport au plan horizontal. Les valeurs 0.866 et 0.5 proviennent des fonctions trigonométriques associées à cet angle. Plus précisément, 0.866 est une approximation de cos(30°), et 0.5 est sin(30°). Ces coefficients permettent de projeter les coordonnées 3D (x, y, z) sur un plan 2D tout en conservant des proportions uniformes pour les axes inclinés, ce qui donne l’illusion de la profondeur sans perspective.

Ajoutons la possibilité d'effectuer des rotations
Afin d'être capable de faire des rotations, avant de faire la projection 3D vers 2D, on calcule des valeurs intermédiaires pour x, y et z (appelées ici x_rot, y_rot et z_rot) après avoir appliqué les formules pour prendre en commte les rotations. Ces rotations sont calculées à partir des angles 0x, oy et oz exprimés en radians. Pour produire des rotations, il suffit donc de faire varier les valeurs ox, oy ou oz.
// Step 1: Rotation autour de l'axe X
x_rot = x
y_rot = y * cos(ox) - z * sin(ox)
z_rot = y * sin(ox) + z * cos(ox)
// Step 2: Rotation autour de l'axe Y
x_temp = x_rot
x_rot = x_temp * cos(oy) + z_rot * sin(oy)
z_rot = -x_temp * sin(oy) + z_rot * cos(oy)
// Step 3: Rotation autour de l'axe Z
x_temp = x_rot
y_temp = y_rot
x_rot = x_temp * cos(oz) - y_temp * sin(oz)
y_rot = x_temp * sin(oz) + y_temp * cos(oz)
// Step 4: Projection 3D vers 2D
x_proj = 0.866 * x_rot - 0.866 * y_rot
y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot

Ajoutons la possibilité de zoomer et dezoomer
On suit les mêmes étapes et on multiplie juste les coordonnées projetées par la valeur du zoom pour obtenir les coordonnées finales x_out et y_out.
Il suffit de mofifier la valeur de la variable zoom pour zommer ou dezoomer.
zoom peut être une valeur inférieure à 1 pour un effet de dézoom, et que la valeur de 1 correspond à l'absence de zoom.
La valeur de zoom doit être maintenue strictement supérieure à zéro afin d'éviter un étrange effet d'inversion.
// Step 1: Rotation autour de l'axe X
x_rot = x
y_rot = y * cos(ox) - z * sin(ox)
z_rot = y * sin(ox) + z * cos(ox)
// Step 2: Rotation autour de l'axe Y
x_temp = x_rot
x_rot = x_temp * cos(oy) + z_rot * sin(oy)
z_rot = -x_temp * sin(oy) + z_rot * cos(oy)
// Step 3: Rotation autour de l'axe Z
x_temp = x_rot
y_temp = y_rot
x_rot = x_temp * cos(oz) - y_temp * sin(oz)
y_rot = x_temp * sin(oz) + y_temp * cos(oz)
// Step 4: Projection 3D vers 2D
if ProjectionType == "isometric":
x_proj = 0.866 * x_rot - 0.866 * y_rot
y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot
// Step 5: Application du zoom
x_out = x_proj * Zoom
y_out = y_proj * Zoom

Ajoutons le centrage par rapport à l'écran
Pour centrer la projection sur l'écran, il suffit d'ajouter à x_out la largeur de l'écran (width) divisée par 2 et à y_out la hauteur (height) de l'écran divisée par 2
// Step 1: Rotation autour de l'axe X
x_rot = x
y_rot = y * cos(ox) - z * sin(ox)
z_rot = y * sin(ox) + z * cos(ox)
// Step 2: Rotation autour de l'axe Y
x_temp = x_rot
x_rot = x_temp * cos(oy) + z_rot * sin(oy)
z_rot = -x_temp * sin(oy) + z_rot * cos(oy)
// Step 3: Rotation autour de l'axe Z
x_temp = x_rot
y_temp = y_rot
x_rot = x_temp * cos(oz) - y_temp * sin(oz)
y_rot = x_temp * sin(oz) + y_temp * cos(oz)
// Step 4: Projection 3D vers 2D
x_proj = 0.866 * x_rot - 0.866 * y_rot
y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot
// Step 5: Application du zoom
x_out = x_proj * Zoom
y_out = y_proj * Zoom
// Step 6: Après zoom, centrer par rapport à l’écran
x_out = x_out + Width / 2
y_out = y_out + Height / 2

Projection en perspective
Dans une projection perspective, la distance simule l’effet de profondeur en ajustant la taille des objets en fonction de leur éloignement de la caméra. Cet effet est obtenu grâce à un facteur de réduction : factor = Distance / (Distance + z_rot). Plus un objet est éloigné (z_rot grand), plus ce facteur est petit, et donc plus ses coordonnées projetées (x_proj, y_proj) sont réduites. Cela crée l’impression visuelle que les objets proches de l’observateur sont plus grands et ceux éloignés sont plus petits, reproduisant ainsi la manière dont l’œil humain perçoit la profondeur dans le monde réel. La variable Distance contrôle directement cet effet, où une grande valeur diminue la distorsion perspective (rendant la vue proche de l’isométrique) et une petite valeur l’amplifie.
Pour une perspective, on suit les mêmes étapes, mais on va faire intervenir deux nouvelles valeurs: la distance et le factor.
distance : C'est la distance entre la caméra et l'écran de projection (le plan 2D). Appelons cette distance Distance. C'est cette valeur qu'on peut faire varier pour modifier l'effet de profondeur.
factor : le "factor" dans la projection perspective est une valeur qui est utilisée pour simuler l'effet de profondeur, c'est-à-dire l'apparition d'un objet plus petit à mesure qu'il s'éloigne de la caméra. En d'autres termes, cela correspond à un facteur de réduction qui rend les objets plus proches plus grands et les objets plus éloignés plus petits.
Dans une projection perspective, l'objet est projeté sur le plan de projection en fonction de sa distance à la caméra. Plus un objet est loin, plus il sera réduit dans la projection. Le "factor" représente cette réduction. Il est calculé à partie de la valeur de distance.
Au final la formule complète pour une perspective avec rotations, zoom, variation de la profondeur et centrage par rapport à l'écran.
// Step 1: Rotation autour de l'axe X
x_rot = x
y_rot = y * cos(ox) - z * sin(ox)
z_rot = y * sin(ox) + z * cos(ox)
// Step 2: Rotation autour de l'axe Y
x_temp = x_rot
x_rot = x_temp * cos(oy) + z_rot * sin(oy)
z_rot = -x_temp * sin(oy) + z_rot * cos(oy)
// Step 3: Rotation autour de l'axe Z
x_temp = x_rot
y_temp = y_rot
x_rot = x_temp * cos(oz) - y_temp * sin(oz)
y_rot = x_temp * sin(oz) + y_temp * cos(oz)
// Step 4: Projection 3D vers 2D
factor = Distance / (Distance + z_rot)
x_proj = x_rot * factor
y_proj = y_rot * factor
// Step 5: Application du zoom
x_out = x_proj * Zoom
y_out = y_proj * Zoom
// Step 6: Après zoom, centrer par rapport à l’écran
x_out = x_out + Width / 2
y_out = y_out + Height / 2

---

### Bresenham algorithm

The Bresenham algorithm is used to draw straight lines on a pixel grid using only simple integer operations like additions and comparisons. The goal is to determine which adjacent pixel to activate at each position to achieve a visually accurate approximation of the line. It works by calculating the horizontal and vertical differences between the start and end points of the line, dx and dy. An error variable is used to track the deviation from the ideal path. At each step, the algorithm advances by one pixel in the primary direction, and if the error exceeds a certain threshold, it adjusts the position in the secondary direction and corrects the error. The algorithm is efficient because it avoids floating-point calculations, making it particularly suitable for resource-limited systems. It can also be adapted to draw circles and other geometric shapes.
