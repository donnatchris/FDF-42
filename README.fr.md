# PROJET FDF POUR 42
Par chdonnat (Christophe Donnat de 42 Perpignan, France)

![fdf gif](gif/fdf_gif.gif)

## BUT DU PROJET :
Ce projet consiste à créer graphiquement la représentation schématique d'un terrain en relief
en reliant différents points (x, y, z) par des segments.
Vous devez utiliser la MiniLibX, soit la version disponible sur les machines de l'école, soit en l'installant depuis les sources.
Le rendu doit être affiché en utilisant une projection isométrique.
Les coordonnées du terrain seront stockées dans un fichier fourni en paramètre.
Chaque nombre représente un point dans l'espace :
La position horizontale correspond à sa coordonnée x.
La position verticale correspond à sa coordonnée y.
La valeur correspond à son altitude (coordonnée z).
Gestion Graphique
Votre programme doit afficher une image dans une fenêtre.
La gestion de la fenêtre doit rester fluide (changement de fenêtre, minimisation, etc.).
Appuyer sur la touche ESC doit fermer la fenêtre et quitter le programme proprement.
Cliquer sur le bouton de fermeture en haut de la fenêtre doit fermer la fenêtre et quitter le programme proprement.
L'utilisation des images de la MiniLibX est obligatoire.

### PARTIE BONUS :
Vous obtiendrez des points supplémentaires si vous :
Incluez une projection supplémentaire (par exemple, une projection parallèle ou conique).
Implémentez le zoom avant et le zoom arrière.
Implémentez la translation (déplacement).
Implémentez la rotation (faire pivoter votre rendu).
Ajoutez une fonctionnalité bonus supplémentaire de votre choix.

## QUELQUES COMMANDES QUE VOUS POUVEZ UTILISER :
compiler le programme :

	make

exécuter le programme (vous devez passer un fichier .fdf contenant des coordonnées)

	./fdf <fichier.fdf>

## ARCHITECTURE :
- Répertoire mandatory/ avec les fichiers pour la partie obligatoire
	- Répertoire src/ pour les fichiers principaux du projet
	- Répertoire utils/ pour les fichiers secondaires
	- Répertoire include/ pour les en-têtes
- Répertoire bonus/ avec les fichiers pour la partie bonus
	- Répertoire src/ pour les fichiers principaux du projet
	- Répertoire utils/ pour les fichiers secondaires
	- Répertoire include/ pour les en-têtes
- Répertoire test/ pour les fichiers de tests
- Répertoire libft/ avec ma propre bibliothèque (fonctions standards, ft_printf, get_next_line)
- Répertoire mlx_mac/ pour la version mac de la bibliothèque minilibx
- Répertoire mlx_linux/ pour la version linux de la bibliothèque minilibx
- Makefile (avec les règles : make bonus clean fclean re)
- readme.md pour une explication rapide et les commandes principales du projet

> Notez que dans mon projet, la partie obligatoire et la partie bonus sont exactement les mêmes (les fonctionnalités bonus sont également dans la partie obligatoire).

## DOCUMENTATION :

### errno
errno est une variable globale définie dans <errno.h> qui stocke un code d'erreur défini par les appels système ou les fonctions de bibliothèque lorsqu'ils échouent.
Chaque code d'erreur correspond à une raison d'échec spécifique, telle que ENOENT pour "No such file or directory" ou EACCES pour "Permission denied".
Ces codes fournissent un moyen standardisé d'identifier les erreurs.
Il est important de vérifier et d'utiliser errno immédiatement après l'échec d'une fonction, car sa valeur peut être écrasée par des appels ultérieurs.

### perror()
perror est une fonction de la bibliothèque standard C utilisée pour afficher un message d'erreur associé à la valeur actuelle de errno.
Elle affiche une chaîne descriptive qui inclut un message fourni par l'utilisateur (pour le contexte) suivi de la description de l'erreur.
Le format est généralement :
<message utilisateur>: <description de l'erreur>
Par exemple, si fopen ne parvient pas à ouvrir un fichier et définit errno sur ENOENT, l'appel de perror("Erreur d'ouverture de fichier") affichera :
Erreur d'ouverture de fichier: No such file or directory

### strerror()
strerror est une fonction de la bibliothèque standard C qui convertit un code d'erreur (généralement stocké dans errno) en un message d'erreur lisible par l'homme.
Elle renvoie un pointeur vers une chaîne décrivant l'erreur correspondant au code d'erreur donné.
Par exemple, si errno est défini sur ENOENT, l'appel de strerror(ENOENT) renverrait "No such file or directory".
Ceci est utile pour afficher ou manipuler des messages d'erreur sans les imprimer directement sur la sortie standard.
#### Différence entre strerror et perror :
La principale différence est que perror imprime directement le message d'erreur avec un préfixe facultatif sur l'erreur standard (stderr),
tandis que strerror renvoie le message d'erreur sous forme de chaîne, permettant une plus grande flexibilité pour le formatage ou la journalisation.
#### Risques liés à l'utilisation de strerror :
strerror n'est pas thread-safe car il peut utiliser un tampon interne statique pour stocker la chaîne renvoyée.
Cela peut entraîner des résultats inattendus dans les programmes multi-thread où plusieurs threads accèdent simultanément à strerror.
Pour des alternatives thread-safe, utilisez strerror_r.

### codes d'erreur errno courants
Voici des valeurs standardisées sur les systèmes de type UNIX, y compris Linux.
Les codes d'erreur correspondent à des conditions d'erreur spécifiques qui peuvent survenir dans les appels système ou les fonctions de bibliothèque,
telles que la gestion des fichiers, l'allocation de mémoire et la gestion des processus.

**Code	Valeur	Description**

EPERM	(1)	Opération non permise

ENOENT	(2)	Aucun fichier ou dossier de ce type

EINTR	(4)	Appel système interrompu

EIO	(5)	Erreur d'entrée/sortie

EBADF	(9)	Mauvais descripteur de fichier

EAGAIN	(11)	Ressource temporairement indisponible

ENOMEM	(12)	Mémoire insuffisante

EACCES	(13)	Permission refusée

ENOTDIR	(20)	N'est pas un répertoire

---

### La bibliothèque math.h
La bibliothèque math.h en C fournit une large gamme de fonctions mathématiques essentielles pour effectuer des calculs avancés.
Ces fonctions incluent des opérations pour l'arithmétique de base, la trigonométrie, les logarithmes, l'exponentiation, et plus encore.
#### Fonctions arithmétiques de base
- fabs() : Renvoie la valeur absolue d'un nombre à virgule flottante.
- fmod() : Calcule le reste de la division de deux nombres à virgule flottante.
- pow() : Calcule la puissance d'un nombre (base élevée à l'exposant).
- sqrt() : Calcule la racine carrée d'un nombre.
#### Fonctions trigonométriques
- sin(), cos(), tan() : Renvoient respectivement le sinus, le cosinus et la tangente d'un angle (en radians).
- asin(), acos(), atan() : Renvoient l'arc sinus, l'arc cosinus et l'arc tangente d'une valeur, en renvoyant le résultat en radians.
#### Fonctions logarithmiques et exponentielles
- log() : Calcule le logarithme naturel (base e) d'un nombre.
- log10() : Calcule le logarithme en base 10 d'un nombre.
- exp() : Calcule la fonction exponentielle, renvoyant e élevé à la puissance de l'argument.
#### Autres fonctions mathématiques
- ceil() : Renvoie la plus petite valeur entière supérieure ou égale au nombre donné.
- floor() : Renvoie la plus grande valeur entière inférieure ou égale au nombre donné.
- round() : Arrondit la valeur à l'entier le plus proche.
- modf() : Sépare un nombre à virgule flottante en ses parties entière et fractionnaire.
Ces fonctions aident à réaliser un large éventail de tâches mathématiques, des opérations arithmétiques simples aux opérations trigonométriques et logarithmiques complexes,
faisant de math.h un outil essentiel dans tout calcul scientifique ou d'ingénierie en C.

---

### La Minilibx
La MiniLibX est une bibliothèque graphique légère conçue pour être utilisée sur des systèmes de type Unix, en particulier avec le X Window System.
Elle est couramment utilisée dans des projets éducatifs, comme ceux de l'école 42, pour aider les étudiants à comprendre les bases de l'infographie et de la programmation événementielle.
La bibliothèque fournit des fonctions simples pour créer une fenêtre, dessiner des pixels, des lignes et des images, et gérer les événements du clavier et de la souris.
Pour utiliser la MiniLibX, vous devez d'abord vous assurer qu'elle est installée sur votre système et correctement liée lors de la compilation.
Typiquement, la commande pour compiler un programme avec la MiniLibX est gcc votre_programme.c -lmlx -lXext -lX11.
Une fois votre programme compilé, vous pouvez créer une fenêtre avec **mlx_new_window()** et commencer à dessiner des formes ou des images à l'aide de fonctions comme **mlx_pixel_put()**.
La gestion des événements tels que les pressions de touches ou les interactions de la souris se fait en définissant des hooks avec des fonctions comme **mlx_hook()** et en démarrant la boucle d'événements avec **mlx_loop()**.
Bien qu'elle soit de conception simple, la MiniLibX est un excellent moyen d'acquérir une expérience pratique des concepts de programmation graphique.

**Pour de plus amples explications sur les fonctions de la MiniLibX, référez-vous au man (qui se trouve à l'adresse : [man_page_address](https://qst0.github.io/ft_libgfx/man_mlx.html)).**

> Notez que l'utilisation de la fonction mlx_pixel_put (qui dessine directement dans la fenêtre) est interdite par les consignes du projet.
> Vous devez à la place utiliser des fonctions comme mlx_image pour dessiner dans une image, puis afficher l'image dans la fenêtre.

---

# Projection de la 3D à la 2D : un guide étape par étape

x, y, et z sont les coordonnées d'origine (z représente l'altitude).
Comme nous voulons projeter de la 3D sur un écran 2D, l'opération consistera à calculer des coordonnées x_proj et y_proj pour créer un effet 3D.

### Étape préliminaire : Centrage des coordonnées (calcul à ne faire qu'une seule fois)
Pour centrer les coordonnées, modifiez les valeurs x, y et z de chaque point en soustrayant les valeurs moyennes x_mean, y_mean et z_mean.
Ces moyennes se calculent simplement. Par exemple, pour calculer x_mean, additionnez les valeurs x de chaque point de la carte et divisez la somme par le nombre de points. Ce calcul ne doit être fait qu'une seule fois avant la première projection.
> x = x - x_mean
> y = y - y_mean
> z = z - z_mean

### Projection isométrique de base
Voici la formule à appliquer pour projeter des coordonnées 3D sur un plan 2D en vue isométrique (sans rotation, sans zoom),
où x_proj et y_proj sont les coordonnées obtenues après application de la projection 2D (il n'y a pas de valeur z_proj) :
> x_proj = 0.866 * x - 0.866 * y
> y_proj = 0.5 * x + 0.5 * y - z

Dans une projection isométrique, les axes 3D sont inclinés de sorte que les angles entre les axes X, Y et Z soient égaux (120°), créant une vue sans distorsion de profondeur.
Cela signifie que chaque axe est vu à un angle de 30° par rapport au plan horizontal.
Les valeurs 0.866 et 0.5 proviennent des fonctions trigonométriques associées à cet angle.
Plus précisément, 0.866 est une approximation de cos(30°), et 0.5 est sin(30°).
Ces coefficients projettent les coordonnées 3D (x, y, z) sur un plan 2D tout en maintenant des proportions uniformes pour les axes inclinés, donnant l'illusion de la profondeur sans perspective.

### Ajout de la possibilité de rotations
Pour permettre les rotations, **avant la projection 3D vers 2D**, calculez des valeurs intermédiaires pour x, y et z (appelées x_rot, y_rot et z_rot)
après avoir appliqué les formules pour tenir compte des rotations.
Ces rotations sont calculées à partir des angles ox, oy et oz exprimés en radians.
Pour produire des rotations, il suffit de faire varier les valeurs de ox, oy ou oz.

#### Étape 1 : Rotation autour de l'axe X
> x_rot = x
> y_rot = y * cos(ox) - z * sin(ox)
> z_rot = y * sin(ox) + z * cos(ox)

#### Étape 2 : Rotation autour de l'axe Y
> x_temp = x_rot
> x_rot = x_temp * cos(oy) + z_rot * sin(oy)
> z_rot = -x_temp * sin(oy) + z_rot * cos(oy)

#### Étape 3 : Rotation autour de l'axe Z
> x_temp = x_rot
> y_temp = y_rot
> x_rot = x_temp * cos(oz) - y_temp * sin(oz)
> y_rot = x_temp * sin(oz) + y_temp * cos(oz)

#### Étape 4 : Projection 3D vers 2D (vue isométrique)
> x_proj = 0.866 * x_rot - 0.866 * y_rot
> y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot

### Ajout de la possibilité de zoomer et dézoomer
Suivez les mêmes étapes et multipliez simplement les coordonnées projetées par la valeur du zoom pour obtenir les coordonnées finales x_out et y_out.
Modifiez simplement la valeur de la variable de zoom pour zoomer ou dézoomer.
Le zoom peut être une valeur inférieure à 1 pour un effet de dézoom, et une valeur de 1 correspond à aucun zoom.
La valeur du zoom doit être strictement supérieure à zéro pour éviter un effet d'inversion étrange.
Les étapes sont donc maintenant :

#### Étape 1 : Rotation autour de l'axe X
> x_rot = x
> y_rot = y * cos(ox) - z * sin(ox)
> z_rot = y * sin(ox) + z * cos(ox)

#### Étape 2 : Rotation autour de l'axe Y
> x_temp = x_rot
> x_rot = x_temp * cos(oy) + z_rot * sin(oy)
> z_rot = -x_temp * sin(oy) + z_rot * cos(oy)

#### Étape 3 : Rotation autour de l'axe Z
> x_temp = x_rot
> y_temp = y_rot
> x_rot = x_temp * cos(oz) - y_temp * sin(oz)
> y_rot = x_temp * sin(oz) + y_temp * cos(oz)

#### Étape 4 : Projection 3D vers 2D (vue isométrique)
> x_proj = 0.866 * x_rot - 0.866 * y_rot
> y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot

#### Étape 5 : Application du zoom
> x_out = x_proj * Zoom
> y_out = y_proj * Zoom

### Ajout du centrage par rapport à l'écran
Pour centrer la projection sur l'écran, ajoutez simplement à x_out la largeur de l'écran (width) divisée par 2 et à y_out la hauteur de l'écran (height) divisée par 2.
Les étapes sont donc :

#### Étape 1 : Rotation autour de l'axe X
> x_rot = x
> y_rot = y * cos(ox) - z * sin(ox)
> z_rot = y * sin(ox) + z * cos(ox)

#### Étape 2 : Rotation autour de l'axe Y
> x_temp = x_rot
> x_rot = x_temp * cos(oy) + z_rot * sin(oy)
> z_rot = -x_temp * sin(oy) + z_rot * cos(oy)

#### Étape 3 : Rotation autour de l'axe Z
> x_temp = x_rot
> y_temp = y_rot
> x_rot = x_temp * cos(oz) - y_temp * sin(oz)
> y_rot = x_temp * sin(oz) + y_temp * cos(oz)

#### Étape 4 : Projection 3D vers 2D (vue isométrique)
> x_proj = 0.866 * x_rot - 0.866 * y_rot
> y_proj = 0.5 * x_rot + 0.5 * y_rot - z_rot

#### Étape 5 : Application du zoom
> x_out = x_proj * Zoom
> y_out = y_proj * Zoom

#### Étape 6 : Après le zoom, centrage par rapport à l'écran
> x_out = x_out + Width / 2
> y_out = y_out + Height / 2

---

### Projection en perspective
Dans une projection en perspective, la distance simule l'effet de profondeur en ajustant la taille des objets en fonction de leur distance par rapport à la caméra.
Cet effet est obtenu à l'aide d'un facteur de réduction :
> factor = Distance / (Distance + z_rot)

Plus un objet est éloigné (grand z_rot), plus ce facteur devient petit, et donc plus ses coordonnées projetées (x_proj, y_proj) sont petites.
Cela crée l'impression visuelle que les objets plus proches de l'observateur sont plus grands, et les objets éloignés sont plus petits, reproduisant la façon dont l'œil humain perçoit la profondeur dans le monde réel.
La variable Distance contrôle directement cet effet, où une grande valeur réduit la distorsion de perspective (rapprochant la vue de l'isométrique), et une petite valeur l'amplifie.

Pour une perspective, suivez les mêmes étapes mais introduisez deux nouvelles valeurs : distance et factor.

#### distance :
La distance entre la caméra et l'écran de projection (le plan 2D).
Appelons cette distance Distance. C'est la valeur qui peut être modifiée pour modifier l'effet de profondeur.

#### factor :
Le "facteur" dans la projection en perspective est une valeur utilisée pour simuler l'effet de profondeur, c'est-à-dire l'apparence d'un objet devenant plus petit à mesure qu'il s'éloigne de la caméra.
En d'autres termes, il correspond à un facteur de réduction qui rend les objets plus proches plus grands et les objets plus éloignés plus petits.
Dans une projection en perspective, l'objet est projeté sur le plan de projection en fonction de sa distance par rapport à la caméra.
Plus un objet est éloigné, plus il sera réduit dans la projection.
Le "facteur" est calculé en fonction de la valeur de la distance.

Les étapes complètes pour une perspective avec rotations, zoom, variation de la profondeur et centrage par rapport à l'écran :

#### Étape 1 : Rotation autour de l'axe X
> x_rot = x
> y_rot = y * cos(ox) - z * sin(ox)
> z_rot = y * sin(ox) + z * cos(ox)

#### Étape 2 : Rotation autour de l'axe Y
> x_temp = x_rot
> x_rot = x_temp * cos(oy) + z_rot * sin(oy)
> z_rot = -x_temp * sin(oy) + z_rot * cos(oy)

#### Étape 3 : Rotation autour de l'axe Z
> x_temp = x_rot
> y_temp = y_rot
> x_rot = x_temp * cos(oz) - y_temp * sin(oz)
> y_rot = x_temp * sin(oz) + y_temp * cos(oz)

#### Étape 4 : Projection 3D vers 2D
> factor = Distance / (Distance + z_rot)
> x_proj = x_rot * factor
> y_proj = y_rot * factor

#### Étape 5 : Application du zoom
> x_out = x_proj * Zoom
> y_out = y_proj * Zoom

#### Étape 6 : Après le zoom, centrage par rapport à l'écran
> x_out = x_out + Width / 2
> y_out = y_out + Height / 2

---

### L'algorithme de tracé de ligne de Bresenham
Maintenant que nous avons les coordonnées 2D, nous devons tracer des lignes entre ces points.
L'algorithme de tracé de ligne de Bresenham est un moyen efficace de le faire en déterminant quels pixels colorer pour former une ligne droite entre deux points.
Au lieu d'utiliser des opérations à virgule flottante, il repose sur des calculs entiers, ce qui le rend rapide et adapté au rendu graphique.

L'algorithme fonctionne en passant itérativement du point de départ au point d'arrivée, en choisissant à chaque étape le pixel le plus proche de la ligne théorique.
Il utilise un terme d'erreur pour décider s'il faut se déplacer verticalement, horizontalement ou en diagonale.
Cela minimise la distorsion et garantit des lignes lisses et connectées, ce qui en fait un outil essentiel en infographie.

L'algorithme de Bresenham trace une ligne entre deux points en prenant leurs coordonnées (x0, y0) et (x1, y1) comme paramètres.
Pour connecter plusieurs points, il suffit d'appeler la fonction pour chaque paire de points que vous souhaitez relier.

Une itération simple pourrait être (sans gérer les couleurs) :

	#include <stdio.h>
	#include <stdlib.h>
	
	void draw_pixel(int x, int y)
 	{
	    // Remplacez ceci par le code de dessin réel
	}
	
	void bresenham_line(int x0, int y0, int x1, int y1)
 	{
	    int dx = abs(x1 - x0);
	    int dy = abs(y1 - y0);
	    int sx = (x0 < x1) ? 1 : -1;
	    int sy = (y0 < y1) ? 1 : -1;
	    int err = dx - dy;

	while (x0 != x1 || y0 != y1)
 	{
        draw_pixel(x0, y0); // Remplacez ceci par votre propre fonction de dessin
        int e2 = 2 * err;
        if (e2 > -dy)
	{
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
	{
            err += dx;
            y0 += sy;
        }
	}
   	 draw_pixel(x1, y1); // Dessinez le point final
	}
