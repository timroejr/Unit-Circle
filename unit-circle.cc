// The following piece of software has been built upon
// the original project made by hzeller
// https://github.com/hzeller/rpi-rgb-led-matrix/
//
/* The MIT License (MIT)

Copyright (c) 2014-2015 Timothy Roe, Jr. & Roeboat, LLC.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
//
// --Code Starts Below this Line--

#include <stdio.h>
#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"
#include <unistd.h>
#include <math.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;


static void DrawOnCanvas(Canvas *led) {
  

  int center_x = led->width() / 2;
  int center_y = led->height() / 2;
  float radius_max = led->width() / 2;
  float angle_step = 1.0 / 360;
  for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
    float dot_x = cos(a * 2 * M_PI) * r;
    float dot_y = sin(a * 2 * M_PI) * r;
    led->SetPixel(center_x + dot_x, center_y + dot_y,
                    96, 96, 96);
    usleep(1 * 1000); 
	}
	int width = led->width();
	int height = led->height();
	for (int x = 0; x < width; x++) {
		led->SetPixel(x, x, 255, 0, 0);
		led->SetPixel(height - x, x, 255, 0, 0);
		
	}
	for (int x = 0; x < width; x++) {
		led->SetPixel(x, height/2, 0, 255, 0);
		
	}
	for (int y = 0; y < height; y++) {
		led->SetPixel(width/2, y, 0, 255, 0);
		
	}
	int y2;
	int z;
	for (y2 = 16, z = 0; y2 < height;  y2++, z++) {
		float t = 16+1.7321*z;
		led->SetPixel(t, y2, 255, 0, 255);
		led->SetPixel(height - t, y2, 255, 0, 255);
		led->SetPixel(t, width - y2, 255, 0, 255);
		led->SetPixel(height - t, width - y2, 255, 0, 255);
		
	}
	int x2;
	int z2;
	for (x2 = 16, z2 = 0; x2 < width; x2++, z2++) {
		float s = 16+1.7321*z2;
		led->SetPixel(x2, s, 255, 255, 0);
		led->SetPixel(width-x2, s, 255, 255, 0);
		led->SetPixel(x2, height - s, 255, 255, 0);
		led->SetPixel(width - x2, height - s, 255, 255, 0);
		
	}
 
}



int main(int argc, char *argv[]) {

  GPIO io;
  if (!io.Init())
    return 1;
    

  int rows = 32;   // A 32x32 display. Use 16 when this is a 16x32 display.
  int chain = 1;   // Number of boards chained together.
  Canvas *led = new RGBMatrix(&io, rows, chain);
  led->Clear();
  DrawOnCanvas(led);
  
	printf("Press <RETURN> to Reset LEDs\n");
	getchar();
  
  led->Clear();
  delete led;
  return 0;

}

// --END CODE--
