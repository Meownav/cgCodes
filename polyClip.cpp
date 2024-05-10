#include <iostream>

const int MAX_POINTS = 20;

// Function to return x-value of point of intersection of two lines
int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}

// Function to return y-value of point of intersection of two lines
int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}

// Function to clip the polygon edges against one clip edge of clipping area
void clip(int poly_points[][2], int &poly_size, int x1, int y1, int x2, int y2)
{
    int new_points[MAX_POINTS][2], new_poly_size = 0;

    for (int i = 0; i < poly_size; i++)
    {
        // i and k form a line in polygon
        int k = (i + 1) % poly_size;
        int ix = poly_points[i][0], iy = poly_points[i][1];
        int kx = poly_points[k][0], ky = poly_points[k][1];

        // Calculate position of the first point w.r.t. clipper line
        int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);

        // Calculate position of the second point w.r.t. clipper line
        int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

        // Case 1: Both vertices are inside
        if (i_pos < 0 && k_pos < 0)
        {
            // Only second vertex is added
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }

        // Case 2: First vertex is outside, second is inside
        else if (i_pos >= 0 && k_pos < 0)
        {
            // Point of intersection with edge and second vertex is added
            new_points[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;

            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }

        // Case 3: First vertex is inside, second is outside
        else if (i_pos < 0 && k_pos >= 0)
        {
            // Only point of intersection with edge is added
            new_points[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }
    }

    // Copying new points into original array and changing the no. of vertices
    poly_size = new_poly_size;
    for (int i = 0; i < poly_size; i++)
    {
        poly_points[i][0] = new_points[i][0];
        poly_points[i][1] = new_points[i][1];
    }
}

// Function to implement Sutherland–Hodgman algorithm
void suthHodgClip(int poly_points[][2], int poly_size, int clipper_points[][2], int clipper_size)
{
    // Clip polygon with all edges of clipper
    for (int i = 0; i < clipper_size; i++)
    {
        int k = (i + 1) % clipper_size;
        clip(poly_points, poly_size, clipper_points[i][0], clipper_points[i][1], clipper_points[k][0], clipper_points[k][1]);
    }

    // Printing vertices of clipped polygon
    std::cout << "The coordinates of the clipped polygon are:" << std::endl;
    for (int i = 0; i < poly_size; i++)
    {
        std::cout << "(" << poly_points[i][0] << ", " << poly_points[i][1] << ")" << std::endl;
    }
}

int main()
{
    int poly_size, clipper_size;
    int poly_points[MAX_POINTS][2], clipper_points[MAX_POINTS][2];

    // Input the vertices of polygon
    std::cout << "Enter the number of vertices of the polygon: ";
    std::cin >> poly_size;
    std::cout << "Enter the coordinates of the polygon:" << std::endl;
    for (int i = 0; i < poly_size; i++)
    {
        std::cin >> poly_points[i][0] >> poly_points[i][1];
    }

    // Input the vertices of clipping area
    std::cout << "Enter the number of vertices of the clipping area: ";
    std::cin >> clipper_size;
    std::cout << "Enter the coordinates of the clipping area:" << std::endl;
    for (int i = 0; i < clipper_size; i++)
    {
        std::cin >> clipper_points[i][0] >> clipper_points[i][1];
    }

    // Call the clipping function
    suthHodgClip(poly_points, poly_size, clipper_points, clipper_size);

    return 0;
}
