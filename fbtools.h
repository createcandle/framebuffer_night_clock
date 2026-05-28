/*
  Gloabl structures.
*/

#ifndef _FBTOOLS_H
#define _FBTOOLS_H

#include <linux/fb.h>

struct framebuffer {
  int fbfd;                         /* Framebuffer file descriptor. */
  long int screensize;              /* Figure out the size of screen in bytes. */

  char *vramfbp;                    /* Framebuffer pointer in vRAM. */
  char *dbp;                        /* Double buffer pointer. */

  long int pxloffset;               /* Real offset of pixel in vRAM. */
  struct fb_var_screeninfo vinfo;   /* Framebuffer variable video information. */
  struct fb_fix_screeninfo finfo;   /* Framebuffer fixed video information. */
};


/*
  Open the fb devive file for R/W, and alloc double buffer address.
  Parameters : void.
  Return : Framebuffer structure pointer address, or NULL if somthing wrong raised.
*/
struct framebuffer *initfb();

/* 
  Close memory mapped and file descriptor.
  Parameters : Framebuffer structure pointer address.
  Return : -1 if somthing wrong raised, everelse >= 0(see 'man 2 close' return code).
*/
int closefb(struct framebuffer *fb);

#endif