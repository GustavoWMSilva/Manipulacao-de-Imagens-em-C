#include <stdio.h>
#include "lib_ppm.h"

void paintRedPixels(struct image_s *image_copy, int original_x, int original_y, int color_value);
void paintGreenPixels(struct image_s *image_copy, int original_x, int original_y, int color_value);
void paintBluePixels(struct image_s *image_copy, int original_x, int original_y, int color_value);

int main()
{
	// The Original Image - lena.ppm
	struct image_s data_original;
	struct image_s *image_original = &data_original;

	// The Copy Image - lena_copy.ppm
	struct image_s data_copy;
	struct image_s *image_copy = &data_copy;

	int r_original, r_copy; // Check if the file can be opened, or the memory can be allocated.

	r_original = read_ppm("lena.ppm", image_original); // Open the file

	if (r_original == 0)
	{
		r_copy = new_ppm(image_copy, image_original->width * 3, image_original->height * 3); // Create the new image
		if (r_copy == 0) {

			for (int i = 0; i < image_original->height; i++) { // y axis in image
				for (int j = 0; j < image_original->width; j++) { // x axis in image

					struct pixel_s original_pixel = image_original->pix[j + i * image_original->width]; // get pixel data from image[j, i]

					paintRedPixels(image_copy, j, i, original_pixel.r); // Paint Red Pixels
					paintGreenPixels(image_copy, j, i, original_pixel.g); // Paint Green Pixels
					paintBluePixels(image_copy, j, i, original_pixel.b); // Paint Blue Pixels
					
				}
			}


			write_ppm("lena_copy.ppm", image_copy); // Save the image
			
			free_ppm(image_original); // Deallocates the image_original from the memory
			free_ppm(image_copy); // Deallocates the image_copy from the memory
		}
	}

	return 0;
}

/*

	Subpixel Draw:
	| R G B |
	| R G B |
	| R G B |

*/

void paintRedPixels(struct image_s *image_copy, int original_x, int original_y, int color_value)
{
	int pixelPosition = original_x * 3 + original_y * image_copy->width * 3; // Calculate the pixel position in new image

	struct pixel_s *pixelUpper = &image_copy->pix[pixelPosition]; // Get the upper pixel
	struct pixel_s *pixelMiddle = pixelUpper + image_copy->width; // Get the middle pixel
	struct pixel_s *pixelLower = pixelMiddle + image_copy->width; // Get the botton pixel

	if (color_value >= 180) { // Change to all pixels enable
		pixelUpper->r = 255;
		pixelMiddle->r = 255;
		pixelLower->r = 255;
	} else if (color_value >= 135) { // Change to upper and botton pixels enable
		pixelUpper->r = 255;
		pixelLower->r = 255;
	} else if (color_value >= 75) { // Change to middle pixels enable
		pixelMiddle->r = 255;
	}

}

void paintGreenPixels(struct image_s *image_copy, int original_x, int original_y, int color_value)
{
	int pixelPosition = (original_x * 3 + 1) + original_y * image_copy->width * 3; // Calculate the pixel position in new image

	struct pixel_s *pixelUpper = &image_copy->pix[pixelPosition]; // Get the upper pixel
	struct pixel_s *pixelMiddle = pixelUpper + image_copy->width; // Get the middle pixel
	struct pixel_s *pixelLower = pixelMiddle + image_copy->width; // Get the botton pixel

	if (color_value >= 180) { // Change to all pixels enable
		pixelUpper->g = 255;
		pixelMiddle->g = 255;
		pixelLower->g = 255;
	} else if (color_value >= 135) {
		pixelUpper->g = 255;
		pixelLower->g = 255;
	} else if (color_value >= 75) {
		pixelMiddle->g = 255;
	}
}

void paintBluePixels(struct image_s *image_copy, int original_x, int original_y, int color_value)
{
	int pixelPosition = (original_x * 3 + 2) + original_y * image_copy->width * 3; // Calculate the pixel position in new image

	struct pixel_s *pixelUpper = &image_copy->pix[pixelPosition]; // Get the upper pixel
	struct pixel_s *pixelMiddle = pixelUpper + image_copy->width; // Get the middle pixel
	struct pixel_s *pixelLower = pixelMiddle + image_copy->width; // Get the botton pixel

	if (color_value >= 180) { // Change to all pixels enable
		pixelUpper->b = 255;
		pixelMiddle->b = 255;
		pixelLower->b = 255;
	} else if (color_value >= 135) { // Change to upper and botton pixels enable
		pixelUpper->b = 255;
		pixelLower->b = 255;
	} else if (color_value >= 75) { // Change to middle pixels enable
		pixelMiddle->b = 255;
	}
}
