/**********************************************************************************
* imageproc.c
* Usage: imageproc in_file_name out_file_name width height
 **********************************************************************************/
#define __STDC_WANT_LIB_EXT1__ 1

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
	FILE  *in, *out;
	Mat img;
	int   j, k, width, height;
	int ** image_in, ** image_out;
	float sum1, sum2;
	float new_T, old_T, delta_T;
	long count1, count2;
	int err;

	if(argc<5) { printf("ERROR: Insufficient parameters!\n"); return(1);}

	width = atoi(argv[3]);
	height = atoi(argv[4]);
	
	in = fopen(argv[1], "rb");
	out = fopen(argv[2], "wb");

	Mat output = Mat(height, width, CV_8U);

	//Begin memory allocation

	image_in = (int**) calloc(height, sizeof(int*));
	if(!image_in)
	{
		printf("Error: Can't allocate memory!\n");
		return(1);
	}

	image_out = (int**) calloc(height, sizeof(int*));
	if(!image_out)
	{
		printf("Error: Can't allocate memory!\n");
		return(1);
	}

	for (j=0; j<height; j++)
	{
		image_in[j] = (int *) calloc(width, sizeof(int));
		if(!image_in[j])
		{
			printf("Error: Can't allocate memory!\n");
			return(1);
		}

		image_out[j] = (int *) calloc(width, sizeof(int));
		if(!image_out[j])
		{
			printf("Error: Can't allocate memory!\n");
			return(1);
		}

	}

	//End memory allocation

	//Begin file checking

	if(!(fopen(argv[1], "rb")))
	{
		printf("ERROR: Can't open in_file!\n");
		return(1);
	}

	if(!(fopen(argv[2],"wb")))
	{
		printf("ERROR: Can't open out_file!\n");
		return(1);
	}

	//End file checking
	
	img = imread(argv[1], CV_8U);
	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	    	{
			image_in[j][k] = img.at<int>(j, k);
			// if((image_in[j][k]=getc(in))==EOF)
			// {
			// 	printf("ERROR: Can't read from in_file!\n");
			// 	return(1);
		    //   }
	    	}
    //   if(fclose(in)==EOF)
	// {
	// 	printf("ERROR: Can't close in_file!\n");
	// 	return(1);
	// }



/********************************************************************/
/* Image Processing begins                                          */
/********************************************************************/
/*
	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	    	{
			//image_out[j][k]=image_in[j][k];
			output.at<int>(j, k) = 255 - img.at<int>(j, k);
		}
*/

Laplacian(img, output, CV_8U);


/********************************************************************/
/* Image Processing ends                                          */
/********************************************************************/

	/* save image_out into out_file in RAW format */
	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	    {
	            if((putc(image_out[j][k],out))==EOF)
	            {
		        	printf("ERROR: Can't write to out_file!\n");
				    return(1);
	            }
		}

    if(fclose(out)==EOF)
	{
		printf("ERROR: Can't close out_file!\n");
		return(1);
	}

	imwrite(argv[2], output);

	for (j=0; j<height; j++)
	{
		free(image_in[j]);
		free(image_out[j]);
	}
	free(image_in);
	free(image_out);

    return 0;
}



