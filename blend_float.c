//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blending (float)
///        This module implements a function that blends two images together filter (floating-point
///        version). Note that CPython uses the 'double' data type for floating point numbers, 
///        so one may observe small differences in the output if the 'float' data type is used.
///
/// @author Jungi Hong <junn0103@snu.ac.kr>
///
/// @section changelog Change Log
/// 2023/MM/DD Your Name Comment
///
//-------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include "blend.h"

struct Image blend_float(struct Image img1, struct Image img2, int overlay, double alpha)
{
    if (img1.channels != 4 || img2.channels != 4) {
        abort(); // Invalid number of channels
    }

    // Initialize blended image
    struct Image blended = {
        .height = img1.height,
        .width = img1.width,
        .channels = img1.channels
    };
    blended.data = malloc(blended.height * blended.width * blended.channels * sizeof(uint8_t));
    if (blended.data == NULL) {
        abort();
    }

    for (int r = 0; r < blended.height; r++) {
        for (int c = 0; c < blended.width; c++) {
            if (overlay) {
                PIXEL(blended, r, c, 3) = PIXEL(img1, r, c, 3);
                double alphacombined = PIXEL(img2, r, c, 3) * alpha;

                for (int i = 0; i < 3; i++) {
                    PIXEL(blended, r, c, i) = (uint8_t)((((1 - (alphacombined / 255.0)) * (PIXEL(img1, r, c, i) / 255.0)) + (alphacombined / 255.0 * (PIXEL(img2, r, c, i) / 255.0))) * 255);
                }
            } else {
                double alpha1 = PIXEL(img1, r, c, 3) * (1.0 - alpha);
                double alpha2 = PIXEL(img2, r, c, 3) * alpha;
                PIXEL(blended, r, c, 3) = (uint8_t)(alpha1 + alpha2);

                for (int i = 0; i < 3; i++) {
                    PIXEL(blended, r, c, i) = (uint8_t)(((PIXEL(img1, r, c, i) * alpha1) + (PIXEL(img2, r, c, i) * alpha2)) / 255.0);
                }
            }
        }
    }

    return blended;
}
