//-------------------------------------------------------------------------------------------------
// 4190.308 Computer Architecture                                                       Spring 2023
//
/// @file
/// @brief Image blurring (int)
///        This module implements a function that blurs an image with a filter (integer version)
///
/// @author Jungi Hong <junn0103@snu.ac.kr>
///
/// @section changelog Change Log
/// 2023/MM/DD Your Name Comment
///
//-------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include "blur.h"

struct Image blur_int(struct Image image, int kernel_size)
{
  struct Image output;
  output.height = image.height - kernel_size + 1;
  output.width = image.width - kernel_size + 1;
  output.channels = image.channels;

  output.data = (uint8 *)malloc(output.height * output.width * output.channels * sizeof(uint8));
  if (output.data == NULL) {
    abort();
  }

  int fixed_kernel_value = (1 << 16) / (kernel_size * kernel_size);

  for (int y = 0; y < output.height; y++) {
    for (int x = 0; x < output.width; x++) {
      for (int c = 0; c < image.channels; c++) {
        int fixed_value = 0;

        for (int i = 0; i < kernel_size; i++) {
          for (int j = 0; j < kernel_size; j++) {
            int ny = y + i;
            int nx = x + j;
            int pixel_value = (int)PIXEL(image, ny, nx, c);
            fixed_value += pixel_value * fixed_kernel_value;
          }
        }

        PIXEL(output, y, x, c) = (fixed_value >> 16) & 0xFF;
      }
    }
  }

  return output;
}
