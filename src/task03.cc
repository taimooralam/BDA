//
// Developed by:  <Your Name> (your@email)
//                http://www.biodataanalysis.de/
//
// With contributions by:
//
//
// Copyright (c) 2034-2038, BioDataAnalysis GmbH
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are not permitted. All information contained herein
// is, and remains the property of BioDataAnalysis GmbH.
// Dissemination of this information or reproduction of this material
// is strictly forbidden unless prior written permission is obtained
// from BioDataAnalysis GmbH.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//

#include <vigra/multi_array.hxx>
#include <vigra/impex.hxx>

#include <iostream>
#include <string>

using namespace vigra;

int MAX_INTENSITY = 255;

const std::string c_LOCAL_SOURCE_IMAGE_PATH = "../images/bDZ17-1I_wE02_s7_z1_t1_cDAPI_u001.tif";
const std::string c_JUST_ANOTHER_LOCAL_SOURCE_IMAGE_PATH = "../images/bDZ17-1I_wE02_s7_z1_t1_cGFP_u001.tif";
const std::string c_DESTINATION_IMAGE_PATH = "../images/bDZ17-1I_wE02_s7_z1_t1_cDAPI_u001_Nuclei.tif";

/*
 * ! Returns the bits of the image from the pixel type string
 * / Param bits contains the type of pixel as string
 * */
int getBits(std::string bits){
	if (bits == "UINT8") return 8;
	if (bits == "INT16") return 16;
	if (bits == "UINT16") return 16;
	if (bits == "INT32") return 32;
	if (bits == "UINT32") return 32;
	if (bits == "FLOAT") return 32;
	if (bits == "DOUBLE") return 64;
}

/*
 * ! Computes the pixel histogram of the image
 * / Param a_input containts the input MultiArray<2, <>> of the input image
 * / Param a_hist containts the pointer to the histogram
 * */
void computeHistogram(MultiArray<2, UInt8> a_input, unsigned * a_hist){
	//initializing the histgram
	for (int i = 0 ;  i <= MAX_INTENSITY ; i++) a_hist[i] = 0;
	
	//iterate the image as a one-dimensional array and build the histogram
	for (int i = 0; i < a_input.size() ; i++){
		int v_value = a_input[i];
		a_hist[v_value]++;
	}
	
	std::cout << "Built histogram for total number of pixels: " << a_input.size() << std::endl;
}

/*
 * ! Segments the image from an input image to an output image given a threshold
 * / Param a_input containts the input MultiArray<2, <>> of the input image
 * / Param a_ouput contains the output MultiArray<2, <>> of the output image
 * / Param a_threshold contains the threshold according to which to segment the image
 * */
void segmentImage(MultiArray<2, UInt8> &a_input, MultiArray<2, UInt8> &a_output, int a_threshold){
	//number of pixels
	int N = a_input.size();
	
	//iterate over the image
	for (int i = 0; i < N ; i++){
		int v_value  = (int) a_input[i];
		
		//Build the segmented image
		if(v_value > a_threshold){
			a_output[i] = 255;
		}else{
			a_output[i] = 0;
		}
	}
}

/*
 * ! Computes the OTSUS segmentation and then calls to segment the image
 * / Param a_input containts the input MultiArray<2, <>> of the input image
 * / Param a_hist contains the histogram according to which the threshold is computed
 * / Param a_ouput contains the output MultiArray<2, <>> of the output image
 * / Param a_oversided_threshold contains the arbitrary threshold that is possible to override the computation of threshold
 * */
void computeOTSUSSegmentation(MultiArray<2, UInt8> &a_input, unsigned *a_hist , MultiArray<2, UInt8> &a_output, int a_overridedThreshold = 0){
	int v_threshold = 0; int v_N = a_input.size();
	
	if (a_overridedThreshold != 0){ //threshold was manually entered
		v_threshold = a_overridedThreshold;
	}else{ //compute threshold
		//init variables
		float v_sum = 0;
		float v_sumB = 0;
		int v_q1 = 0;
		int v_q2 = 0;
		float v_varMax = 0;
		
		//auxiliary value for computing m2
		for (int i = 0 ; i < MAX_INTENSITY ; i++){
			v_sum += i * ((int) a_hist[i]);
		}
		
		for (int i = 0 ; i < MAX_INTENSITY ; i++){
			//update q1
			v_q1 += a_hist[i];
			if (v_q1 == 0)  continue;
			
			//update q2
			v_q2 = v_N - v_q1;
			if (v_q2 == 0) break;
			
			//update m1 and m2
			v_sumB += (float) (i * ((int)a_hist[i]));
			float v_m1 = v_sumB / v_q1;
			float v_m2 = (v_sum - v_sumB) / v_q2;
			
			//update the class variance
			float v_varBetween = (float) v_q1 * (float) v_q2 * (v_m1 - v_m2) * (v_m1 - v_m2);
			
			//update threshold if necessary
			if (v_varBetween > v_varMax){
				v_varMax = v_varBetween;
				v_threshold = i;
			}
		}
	}
	
	std::cout << "Threshold calculated: " << v_threshold << std::endl;
	
	//perform segmentation
	segmentImage(a_input, a_output, v_threshold);
}


/*
 * ! The main algorithm that reads the input image, computes the histogram, and segments the image
 * */
int main(int argc, char** argv)
{
    std::cout << "Task 03 started" << std::endl;
	
	// You can add your code here
	std::cout << "(supported formats: " << vigra::impexListFormats() << " ) " << std::endl;
	
	//Import the image from the source
	ImageImportInfo v_info(c_LOCAL_SOURCE_IMAGE_PATH.c_str());
	
	//computing the bits depth or bits per pixel
	int bits = getBits(std::string(v_info.getPixelType()));
	std::cout << "Pixel type i.e. num of bits per pixel: " << bits << std::endl;
	
	//if image is not grayscale, raise error and quits
	if (!v_info.isGrayscale()){
		std::cout << "Error algorithm works only with grayscale image " <<  std::endl;
		return -1;
	}
	
	//creating the histogram
	unsigned v_hist[MAX_INTENSITY+1];
	
		
	try{
		//create array view for the whole input image
		MultiArray<2, UInt8> v_in(v_info.width(), v_info.height());
		
		//import the image into the source multiarray
		importImage(v_info, v_in);
		
		//compute histogram
		computeHistogram(v_in,v_hist);
		
		
		//equate the two images temporarily
		MultiArray<2, UInt8> v_out(Shape2(v_info.width(),v_info.height()));
		
		//computeOTSUSSegmentation
		computeOTSUSSegmentation(v_in, v_hist, v_out, 0);
		
		
		//export the destination multiarray to the destination image path
		exportImage(v_out, c_DESTINATION_IMAGE_PATH.c_str());
	
	}
	catch(std::exception & a_e){
		std::cout << a_e.what() << std::endl;
		return -1;
	}


    std::cout << "Task 03 finished successfully" << std::endl;
    return 0;
}
