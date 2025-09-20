#pragma once

#include <raylib.h>

#define BLUE_BYZANTINE          CLITERAL(Color){61, 82, 213, 255}     // Byzantine blue
#define BLUE_DUKE               CLITERAL(Color){9, 12, 155, 255}      // Duke blue
#define BLUE_POWDER             CLITERAL(Color){180, 197, 228, 255}   // Powder blue
#define BLUE_POWDER_DARKER      CLITERAL(Color){136, 153, 184, 255}   // Powder blue darker
#define JET                     CLITERAL(Color){60, 55, 68, 255}      // Jet
#define IVORY                   CLITERAL(Color){251, 255, 241, 255}   // Ivory
        
#define TRANSPARENT             CLITERAL(Color){0, 0, 0, 0}           // Transparent

/**
 * Helpers
 */

inline bool sameColor(const Color& a, const Color& b)
{
    return a.a == b.a && a.b == b.b && a.g == b.g && a.r == b.r;
}