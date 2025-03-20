#include "CImg.h"
using namespace cimg_library;

int main() {
    const int width = 100, height = 120;
    CImg<unsigned char> ghost(width, height, 1, 3, 0); // Image RGB (fond noir)
    
    unsigned char color[] = {255, 0, 0};  // Rouge (couleur du fantôme)
    unsigned char white[] = {255, 255, 255};  // Blanc (yeux)
    unsigned char black[] = {0, 0, 0};  // Noir (pupilles)

    // 1. Dessiner la tête (cercle)
    ghost.draw_circle(width / 2, height / 3, width / 2 - 5, color, 1.0f);

    // 2. Dessiner le corps (rectangle)
    ghost.draw_rectangle(5, height / 3, width - 5, height - 20, color, 1.0f);

    // 3. Dessiner la base en zigzag
    for (int i = 5; i < width - 5; i += 10) {
        ghost.draw_triangle(i, height - 20, i + 5, height, i + 10, height - 20, color, 1.0f);
    }

    // 4. Dessiner les yeux
    ghost.draw_circle(width / 3, height / 3+10, 10, white, 1.0f);
    ghost.draw_circle(2 * width / 3, height / 3+10, 10, white, 1.0f);

    // 5. Dessiner les pupilles (légèrement décalées)
    ghost.draw_circle(width / 3 + 3, height / 3 + 13, 4, black, 1.0f);
    ghost.draw_circle(2 * width / 3 + 3, height / 3 + 13 , 4, black, 1.0f);

    // Affichage
    CImgDisplay disp(ghost, "Fantôme Pac-Man");
    while (!disp.is_closed()) {
        disp.wait();
    }

    return 0;
}
