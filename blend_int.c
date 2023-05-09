//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blending (int)
///        This module implements a function that blends two images together filter (integer
///        version)
///
/// @author Jungi Hong <junn0103@snu.ac.kr>
///
/// @section changelog Change Log
/// 2023/MM/DD Your Name Comment
///
//-------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include "blend.h"

struct Image blend_int(struct Image img1, struct Image img2, int overlay, int alpha)
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
                int alphacombined = (PIXEL(img2, r, c, 3) * alpha) >> 8;

                for (int i = 0; i < 3; i++) {
                    int channel1 = (PIXEL(img1, r, c, i) * (256 - alphacombined)) >> 8;
                    int channel2 = (PIXEL(img2, r, c, i) * alphacombined) >> 8;
                    PIXEL(blended, r, c, i) = channel1 + channel2;
                }
            } else {
                PIXEL(blended, r, c, 3) = ((PIXEL(img1, r, c, 3) * (256 - alpha)) + (PIXEL(img2, r, c, 3) * alpha) + 127) >> 8;

                for (int i = 0; i < 3; i++) {
                    int img1_fixed = PIXEL(img1, r, c, i) << 1;
                    int img2_fixed = PIXEL(img2, r, c, i) << 1;

                    int blended_fixed = ((img1_fixed * PIXEL(img1, r, c, 3) * (256 - alpha)) + (img2_fixed * PIXEL(img2, r, c, 3) * alpha) + 127) >> 16;

                    PIXEL(blended, r, c, i) = blended_fixed >> 1;
                }
            }
        }
    }

    return blended;
}
