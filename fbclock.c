/* fbclock: framebuffer clock for Linux
 * 
 *
 * Requires: libpng
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <linux/fb.h>

#include "framebuffer.h"
#include "fbclock.h"
#include "pngimage.h"


int main(int argc, char *argv[]) {
    time_t t;
    struct tm *tp;
    struct framebuffer fb;

    /* Display offset from top left of screen, in pixels */
    unsigned int x_offset = 100;
    unsigned int y_offset = 100;
	bool rotate = false;
	
	
    /* Parse command-line options */
    int opt;
	
	
    while ((opt = getopt(argc, argv, "r:x:y:")) != -1) {
        switch (opt) {
        case 'x':
            x_offset = atoi(optarg);
            break;
        case 'y':
            y_offset = atoi(optarg);
            break;
        case 'r':
            rotate = atoi(optarg);
            break;
        default:
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
	
	printf("rotate:  %d\n", rotate);

    /* Set up framebuffer */
    new_framebuffer(&fb, "/dev/fb0");

    /*while (1) {*/
        /* Get current time */
        t = time(NULL);
        tp = localtime(&t);
		
		
		
        /* Display it */
        display_time(tp, &fb, rotate, x_offset, y_offset);

        /* Wait for next update 
        sleep(SLEEP);*/
	/*}*/

    /* Clean up */
    close_framebuffer(&fb);

    return EXIT_SUCCESS;
}


/* display_time: Display time on framebuffer.
 * tp: pointer to tm struct such as that returned by localtime().
 * fb: pointer to framebuffer memory.
 * x_offset, y_offset: x and y position in pixels
 */
void display_time(struct tm *tp, struct framebuffer *fb, bool rotate, int x_offset, int y_offset) {
    
	int x_pos = x_offset;
	int y_pos = y_offset;
	int hours = tp->tm_hour;
	int minutes = tp->tm_min;
	struct image_size png_size;
	
	
	y_pos = fb->screeninfo.yres;
	y_pos = y_pos - 160;
	y_pos = round(y_pos / 2);
	
	x_pos = fb->screeninfo.xres;
	x_pos = x_pos - 600;
	x_pos = round(x_pos / 2);
	
	display_png(fb, "graphics/black.png", 0, 0, 0);
	
	display_png(fb, "graphics/black.png", x_pos, y_pos, 0);
	
	if(rotate == 1){
		x_pos = x_pos + 480;
	}
	
	
	
	
	
	
	
	/*
	if(fb->screeninfo.xres >= 1290){
		display_png(fb, "graphics/black.png", 640, 0, 0);
	}
	*/
	
	printf("display_time: x_pos: %d\n", x_pos);
	printf("display_time: y_pos: %d\n", y_pos);
	
	
	
	/*
    int y_pos = y_offset;
	
    int hours = tp->tm_hour;
    
	int minutes = tp->tm_min;
	
	int mday = tp->tm_mday;
    int month_num = tp->tm_mon;
    int year = tp->tm_year + 1900;
	*/
	
	
	
	
	
	/*
    
	
	
	png_size = display_png(fb, "graphics/black.png", 0, 0);
	*/
    /* TODO: allow user-specified display formats */
	/*
    png_size = display_png(fb, digit_filenames[mday/10], x_pos, y_pos, rotate);
    x_pos += png_size.x;
    png_size = display_png(fb, digit_filenames[mday%10], x_pos, y_pos, rotate);
    x_pos += png_size.x;

    png_size = display_png(fb, short_month_filenames[month_num], x_pos, y_pos, rotate);
    x_pos += png_size.x;

    png_size = display_png(fb, digit_filenames[year/1000], x_pos, y_pos, rotate);
    x_pos += png_size.x;
    png_size = display_png(fb, digit_filenames[(year%1000)/100], x_pos, y_pos, rotate);
    x_pos += png_size.x;
    png_size = display_png(fb, digit_filenames[(year%100)/10], x_pos, y_pos, rotate);
    x_pos += png_size.x;
    png_size = display_png(fb, digit_filenames[year%10], x_pos, y_pos, rotate);
    x_pos += png_size.x;*/

	
    png_size = display_png(fb, digit_filenames[hours/10], x_pos, y_pos, rotate);
	if(rotate){
		x_pos -= png_size.x;
	}else{
		x_pos += png_size.x;
	}
    
	png_size = display_png(fb, digit_filenames[hours%10], x_pos, y_pos, rotate);
	if(rotate){
		x_pos -= png_size.x;
	}else{
		x_pos += png_size.x;
	}
    /*
	png_size = display_png(fb, digit_filenames[hours%10], x_pos, y_pos, rotate);
    x_pos += (png_size.x - 15);
	*/
	
	
	/*
    png_size = display_png(fb, short_month_filenames[12], x_pos, y_pos, rotate);
    x_pos += png_size.x;
	*/
	
	png_size = display_png(fb, "graphics/split.png", x_pos, y_pos, rotate);
	if(rotate){
		x_pos -= png_size.x;
	}else{
		x_pos += png_size.x;
	}
	
	/*
	x_pos += 100;
	*/
	
    png_size = display_png(fb, digit_filenames[minutes/10], x_pos, y_pos, rotate);
	if(rotate){
		x_pos -= png_size.x;
	}else{
		x_pos += png_size.x;
	}
    png_size = display_png(fb, digit_filenames[minutes%10], x_pos, y_pos, rotate);
	
	
	
    /* XXX debug output */
    printf("Time: %s\n", asctime(tp));
    fflush(NULL);

    return;
}


/* print_usage: print a usage message */
void print_usage(char *name) {
    fprintf(stderr, "Usage: %s [-x x_offset] [-y y_offset]\n", name);
    return;
}

