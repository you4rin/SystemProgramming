/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "Username",              /* name */

    "User ID",     /* student ID */
    "User email",  /* student email */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j, bsize = 32;
    for(i = 0; i < dim; i += bsize){
        for(j = 0; j < dim; ++j){
            dst[RIDX(dim - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
            dst[RIDX(dim - 1 - j, i + 1, dim)] = src[RIDX(i + 1, j, dim)];
            dst[RIDX(dim - 1 - j, i + 2, dim)] = src[RIDX(i + 2, j, dim)];
            dst[RIDX(dim - 1 - j, i + 3, dim)] = src[RIDX(i + 3, j, dim)];
            dst[RIDX(dim - 1 - j, i + 4, dim)] = src[RIDX(i + 4, j, dim)];
            dst[RIDX(dim - 1 - j, i + 5, dim)] = src[RIDX(i + 5, j, dim)];
            dst[RIDX(dim - 1 - j, i + 6, dim)] = src[RIDX(i + 6, j, dim)];
            dst[RIDX(dim - 1 - j, i + 7, dim)] = src[RIDX(i + 7, j, dim)];
            dst[RIDX(dim - 1 - j, i + 8, dim)] = src[RIDX(i + 8, j, dim)];
            dst[RIDX(dim - 1 - j, i + 9, dim)] = src[RIDX(i + 9, j, dim)];
            dst[RIDX(dim - 1 - j, i + 10, dim)] = src[RIDX(i + 10, j, dim)];
            dst[RIDX(dim - 1 - j, i + 11, dim)] = src[RIDX(i + 11, j, dim)];
            dst[RIDX(dim - 1 - j, i + 12, dim)] = src[RIDX(i + 12, j, dim)];
            dst[RIDX(dim - 1 - j, i + 13, dim)] = src[RIDX(i + 13, j, dim)];
            dst[RIDX(dim - 1 - j, i + 14, dim)] = src[RIDX(i + 14, j, dim)];
            dst[RIDX(dim - 1 - j, i + 15, dim)] = src[RIDX(i + 15, j, dim)];
            dst[RIDX(dim - 1 - j, i + 16, dim)] = src[RIDX(i + 16, j, dim)];
            dst[RIDX(dim - 1 - j, i + 17, dim)] = src[RIDX(i + 17, j, dim)];
            dst[RIDX(dim - 1 - j, i + 18, dim)] = src[RIDX(i + 18, j, dim)];
            dst[RIDX(dim - 1 - j, i + 19, dim)] = src[RIDX(i + 19, j, dim)];
            dst[RIDX(dim - 1 - j, i + 20, dim)] = src[RIDX(i + 20, j, dim)];
            dst[RIDX(dim - 1 - j, i + 21, dim)] = src[RIDX(i + 21, j, dim)];
            dst[RIDX(dim - 1 - j, i + 22, dim)] = src[RIDX(i + 22, j, dim)];
            dst[RIDX(dim - 1 - j, i + 23, dim)] = src[RIDX(i + 23, j, dim)];
            dst[RIDX(dim - 1 - j, i + 24, dim)] = src[RIDX(i + 24, j, dim)];
            dst[RIDX(dim - 1 - j, i + 25, dim)] = src[RIDX(i + 25, j, dim)];
            dst[RIDX(dim - 1 - j, i + 26, dim)] = src[RIDX(i + 26, j, dim)];
            dst[RIDX(dim - 1 - j, i + 27, dim)] = src[RIDX(i + 27, j, dim)];
            dst[RIDX(dim - 1 - j, i + 28, dim)] = src[RIDX(i + 28, j, dim)];
            dst[RIDX(dim - 1 - j, i + 29, dim)] = src[RIDX(i + 29, j, dim)];
            dst[RIDX(dim - 1 - j, i + 30, dim)] = src[RIDX(i + 30, j, dim)];
            dst[RIDX(dim - 1 - j, i + 31, dim)] = src[RIDX(i + 31, j, dim)];
        }
    }
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);  
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j, tmp1, tmp2;

    // corners
    dst[0].red = (src[0].red + src[1].red + src[dim].red + src[dim + 1].red) >> 2;
    dst[0].blue = (src[0].blue + src[1].blue + src[dim].blue + src[dim + 1].blue) >> 2;
    dst[0].green = (src[0].green + src[1].green + src[dim].green + src[dim + 1].green) >> 2;
    dst[dim - 1].red = (src[dim - 1].red + src[dim - 2].red + src[dim * 2 - 1].red + src[dim * 2 - 2].red) >> 2;
    dst[dim - 1].blue = (src[dim - 1].blue + src[dim - 2].blue + src[dim * 2 - 1].blue + src[dim * 2 - 2].blue) >> 2;
    dst[dim - 1].green = (src[dim - 1].green + src[dim - 2].green + src[dim * 2 - 1].green + src[dim * 2 - 2].green) >> 2;
    dst[RIDX(dim - 1, 0, dim)].red = (src[RIDX(dim - 1, 0, dim)].red + src[RIDX(dim - 1, 1, dim)].red + src[RIDX(dim - 2, 0, dim)].red + src[RIDX(dim - 2, 1, dim)].red) >> 2;
    dst[RIDX(dim - 1, 0, dim)].blue = (src[RIDX(dim - 1, 0, dim)].blue + src[RIDX(dim - 1, 1, dim)].blue + src[RIDX(dim - 2, 0, dim)].blue + src[RIDX(dim - 2, 1, dim)].blue) >> 2;
    dst[RIDX(dim - 1, 0, dim)].green = (src[RIDX(dim - 1, 0, dim)].green + src[RIDX(dim - 1, 1, dim)].green + src[RIDX(dim - 2, 0, dim)].green + src[RIDX(dim - 2, 1, dim)].green) >> 2;
    dst[RIDX(dim, -1, dim)].red = (src[RIDX(dim, -1, dim)].red + src[RIDX(dim, -2, dim)].red + src[RIDX(dim - 1, -1, dim)].red + src[RIDX(dim - 1, -2, dim)].red) >> 2;
    dst[RIDX(dim, -1, dim)].blue = (src[RIDX(dim, -1, dim)].blue + src[RIDX(dim, -2, dim)].blue + src[RIDX(dim - 1, -1, dim)].blue + src[RIDX(dim - 1, -2, dim)].blue) >> 2;
    dst[RIDX(dim, -1, dim)].green = (src[RIDX(dim, -1, dim)].green + src[RIDX(dim, -2, dim)].green + src[RIDX(dim - 1, -1, dim)].green + src[RIDX(dim - 1, -2, dim)].green) >> 2;
    
    // edges
    for (i = 1; i < dim - 1; i++) {
        dst[i].red = (src[i].red + src[i - 1].red + src[i + 1].red + src[i + dim].red + src[i - 1 + dim].red + src[i + 1 + dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i - 1].blue + src[i + 1].blue + src[i + dim].blue + src[i - 1 + dim].blue + src[i + 1 + dim].blue) / 6;
        dst[i].green = (src[i].green + src[i - 1].green + src[i + 1].green + src[i + dim].green + src[i - 1 + dim].green + src[i + 1 + dim].green) / 6;
    }
    for (i = RIDX(dim - 1, 1, dim); i < RIDX(dim, -1, dim); i++) {
        dst[i].red = (src[i].red + src[i - 1].red + src[i + 1].red + src[i - dim].red + src[i - 1 - dim].red + src[i + 1 - dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i - 1].blue + src[i + 1].blue + src[i - dim].blue + src[i - 1 - dim].blue + src[i + 1 - dim].blue) / 6;
        dst[i].green = (src[i].green + src[i - 1].green + src[i + 1].green + src[i - dim].green + src[i - 1 - dim].green + src[i + 1 - dim].green) / 6;
    }
    for (i = dim; i < RIDX(dim - 1, 0, dim); i += dim) {
        dst[i].red = (src[i].red + src[i - dim].red + src[i + dim].red + src[i + 1].red + src[i + 1 - dim].red + src[i + 1 + dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i - dim].blue + src[i + dim].blue + src[i + 1].blue + src[i + 1 - dim].blue + src[i + 1 + dim].blue) / 6;
        dst[i].green = (src[i].green + src[i - dim].green + src[i + dim].green + src[i + 1].green + src[i + 1 - dim].green + src[i + 1 + dim].green) / 6;
    }
    for (i = dim + dim - 1; i < RIDX(dim, -1, dim); i += dim) {
        dst[i].red = (src[i].red + src[i - dim].red + src[i + dim].red + src[i - 1].red + src[i - 1 - dim].red + src[i - 1 + dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i - dim].blue + src[i + dim].blue + src[i - 1].blue + src[i - 1 - dim].blue + src[i - 1 + dim].blue) / 6;
        dst[i].green = (src[i].green + src[i - dim].green + src[i + dim].green + src[i - 1].green + src[i - 1 - dim].green + src[i - 1 + dim].green) / 6;
    }
    // center
    tmp2 = dim;
    for (i = 1; i < dim - 1; i++){
        for (j = 1; j < dim - 1; j++){
            tmp1 = tmp2 + j;
            dst[tmp1].red = (src[tmp1].red + src[tmp1 - 1].red + src[tmp1 + 1].red + src[tmp1 - dim].red + src[tmp1 - dim - 1].red + src[tmp1 - dim + 1].red + src[tmp1 + dim].red + src[tmp1 + dim - 1].red + src[tmp1 + dim + 1].red) / 9;
            dst[tmp1].green = (src[tmp1].green + src[tmp1 - 1].green + src[tmp1 + 1].green + src[tmp1 - dim].green + src[tmp1 - dim - 1].green + src[tmp1 - dim + 1].green + src[tmp1 + dim].green + src[tmp1 + dim - 1].green + src[tmp1 + dim + 1].green) / 9;
            dst[tmp1].blue = (src[tmp1].blue + src[tmp1 - 1].blue + src[tmp1 + 1].blue + src[tmp1 - dim].blue + src[tmp1 - dim - 1].blue + src[tmp1 - dim + 1].blue + src[tmp1 + dim].blue + src[tmp1 + dim - 1].blue + src[tmp1 + dim + 1].blue) / 9;
        }
        tmp2 += dim;
    }
}

/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

