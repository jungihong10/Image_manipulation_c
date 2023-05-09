//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blurring (float)
///        This module implements a function that blurs an image with a filter (floating-point 
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
#include "blur.h"

struct Image blur_float(struct Image image, int kernel_size)
{
    struct Image output;
    output.height = image.height - (kernel_size - 1);
    output.width = image.width - (kernel_size - 1);
    output.channels = image.channels;

    output.data = (uint8 *)malloc(output.height * output.width * output.channels * sizeof(uint8));
    if (output.data == NULL)
    {
        abort();
    }

    int kernel_radius = kernel_size / 2;

    for (int y = 0; y < output.height; y++)
    {
        for (int x = 0; x < output.width; x++)
        {
            for (int c = 0; c < output.channels; c++)
            {
                float sum = 0.0;
                int count = 0;

                for (int ky = -kernel_radius; ky <= kernel_radius; ky++)
                {
                    for (int kx = -kernel_radius; kx <= kernel_radius; kx++)
                    {
                        int ny = y + ky + kernel_radius;
                        int nx = x + kx + kernel_radius;

                        if (ny >= 0 && ny < image.height && nx >= 0 && nx < image.width)
                        {
                            sum += PIXEL(image, ny, nx, c);
                            count++;
                        }
                    }
                }

                PIXEL(output, y, x, c) = (uint8)(sum / count);
            }
        }
    }

    return output;
}

