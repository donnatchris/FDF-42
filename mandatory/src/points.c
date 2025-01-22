/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:43:07 by christophed       #+#    #+#             */
/*   Updated: 2025/01/23 00:10:01 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function to generate x_out and y_out
void    project_isometric_map(t_fdf *fdf)
{
    int i;
    
    fill_color(fdf);
    i = 0;
    while(fdf->point[i])
    {
        project_isometric_point(fdf->point[i], fdf);
        i++;
    }

}



// OLD ISO - view ok but not rotation
// Function to project the points from 3D to 2D
// using a isometric projection
// void	project_isometric_point(t_point *point, t_fdf *fdf)
// {
//     float   x;
//     float	y;
//     float	z;

//     // x = point->x - fdf->x_mid;
//     // y = point->y - fdf->y_mid;
//     // z = point->z * fdf->depth;
//     point->x_out = fdf->originX + fdf->factor * (x * cos(fdf->Ox) - y * cos(fdf->Oy));
//     point->y_out = fdf->originY + fdf->factor * (x * sin(fdf->Ox) + y * sin(fdf->Oy) - z);
// }


// void project_isometric_point(t_point *point, t_fdf *fdf)
// {
//     point->x_out = fdf->originX + fdf->factor * (point->x - point->y);
//     point->y_out = fdf->originY + fdf->factor * ((point->x + point->y) / 2 - point->z);
// }



// LAST VERSION
void    project_isometric_point(t_point *point, t_fdf *fdf)
{
    t_rotation	rot;

    // Appliquer la profondeur
    rot.temp_z = point->z * fdf->depth;
    // Step 1: Rotation autour de l'axe X
	// Rotation selon X
	rot.x = point->x;
	rot.y = point->y * cos(fdf->Ox) - rot.temp_z * sin(fdf->Ox);
	rot.z = point->y * sin(fdf->Ox) + rot.temp_z * cos(fdf->Ox);
    // Step 2: Rotation autour de l'axe Y
	rot.temp_x = rot.x;
	rot.x = rot.temp_x * cos(fdf->Oy) + rot.z * sin(fdf->Oy);
	rot.z = -rot.temp_x * sin(fdf->Oy) + rot.z * cos(fdf->Oy);
    // Step 3: Rotation autour de l'axe Z
    rot.temp_x = rot.x;
    rot.temp_y = rot.y;
    rot.x = rot.temp_x * cos(fdf->Oz) - rot.temp_y* sin(fdf->Oz);
    rot.y = rot.temp_x* sin(fdf->Oz) + rot.temp_y * cos(fdf->Oz);
    // Step 4: Projection 3D vers 2D
    rot.x_proj = 0.866 * rot.x - 0.866 * rot.y;
    rot.y_proj = 0.5 * rot.x + 0.5 * rot.y - rot.z;
    // Step 5: Application du zoom
    point->x_out = rot.x_proj * fdf->factor;
    point->y_out = rot.y_proj * fdf->factor;
    // Step 6: Après zoom, centrer par rapport à l’écran
    point->x_out = point->x_out + fdf->originX;
    point->y_out = point->y_out + fdf->originY;
}

// // Fonction pour multiplier deux matrices 4x4
// void matrix_multiply(double result[4][4], double mat1[4][4], double mat2[4][4])
// {
//     int i, j, k;
//     for (i = 0; i < 4; i++)
//     {
//         for (j = 0; j < 4; j++)
//         {
//             result[i][j] = 0;
//             for (k = 0; k < 4; k++)
//             {
//                 result[i][j] += mat1[i][k] * mat2[k][j];
//             }
//         }
//     }
// }

// // Fonction pour appliquer une matrice de rotation à un point
// void apply_matrix_to_point(double point[4], double matrix[4][4])
// {
//     double temp[4];
//     for (int i = 0; i < 4; i++)
//     {
//         temp[i] = 0;
//         for (int j = 0; j < 4; j++)
//         {
//             temp[i] += matrix[i][j] * point[j];
//         }
//     }
//     for (int i = 0; i < 4; i++)
//     {
//         point[i] = temp[i];
//     }
// }

// // Fonction de projection iso avec rotation par matrices
// void project_isometric_point(t_point *point, t_fdf *fdf)
// {
//     // Matrices de rotation autour des axes X, Y et Z
//     double Rx[4][4] = {
//         {1, 0, 0, 0},
//         {0, cos(fdf->Ox), -sin(fdf->Ox), 0},
//         {0, sin(fdf->Ox), cos(fdf->Ox), 0},
//         {0, 0, 0, 1}
//     };

//     double Ry[4][4] = {
//         {cos(fdf->Oy), 0, sin(fdf->Oy), 0},
//         {0, 1, 0, 0},
//         {-sin(fdf->Oy), 0, cos(fdf->Oy), 0},
//         {0, 0, 0, 1}
//     };

//     double Rz[4][4] = {
//         {cos(fdf->Oz), -sin(fdf->Oz), 0, 0},
//         {sin(fdf->Oz), cos(fdf->Oz), 0, 0},
//         {0, 0, 1, 0},
//         {0, 0, 0, 1}
//     };

//     // Matrice résultante (combinée)
//     double rotation_matrix[4][4];

//     // Multiplier les matrices de rotation: Rz * Ry * Rx
//     double temp_matrix[4][4];
//     matrix_multiply(temp_matrix, Rz, Ry);
//     matrix_multiply(rotation_matrix, temp_matrix, Rx);

//     // Représenter le point comme un vecteur colonne [x, y, z, 1]
//     double point_vec[4] = {point->x, point->y, point->z, 1};

//     // Appliquer la matrice de rotation au point
//     apply_matrix_to_point(point_vec, rotation_matrix);

//     // Calculer la projection 2D après la rotation
//     double x_proj = 0.866 * point_vec[0] - 0.866 * point_vec[1];
//     double y_proj = 0.5 * point_vec[0] + 0.5 * point_vec[1] - point_vec[2];

//     // Application du zoom
//     point->x_out = x_proj * fdf->factor;
//     point->y_out = y_proj * fdf->factor;

//     // Après zoom, centrer par rapport à l'écran
//     point->x_out += fdf->originX;
//     point->y_out += fdf->originY;
// }
