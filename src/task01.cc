//
// Developed by:  <Your Name> (your@email)
//                http://www.biodataanalysis.de/
//
// With contributions by:
//
//
// Copyright (c) 2014-2018, BioDataAnalysis GmbH
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
#include <inttypes.h>

#include <vigra/multi_array.hxx>
#include <vigra/impex.hxx>
#include <vigra/imageinfo.hxx>
#include <vigra/stdimagefunctions.hxx>

#include <iostream>
#include <string>

using namespace vigra;

const std::string c_GLOBAL_SOURCE_IMAGE_PATH = "/home/alam/Documents/code/BioDataAnalysis-WorkAssessment-Vigra/images/bDZ17-1I_wE02_s7_z1_t1_cGFP_u001.tif";
const std::string c_LOCAL_SOURCE_IMAGE_PATH = "../images/bDZ17-1I_wE02_s7_z1_t1_cGFP_u001.tif";
const std::string c_DESTINATION_IMAGE_PATH = "../images/task01_destination_image.tif";

//from and to points to crop the image
const std::pair<int, int> c_from(400,500);
const std::pair<int, int> c_to(900,850);


int main(int argc, char** argv)
{
    std::cout << "Task 01 started" << std::endl;

    // You can add your code here
	std::cout << "(supported formats: " << vigra::impexListFormats() << " ) " << std::endl;
	
	//Import the image from the source
	ImageImportInfo v_info(c_LOCAL_SOURCE_IMAGE_PATH.c_str());
		
	try{
		//create array view for the whole input image
		MultiArray<2, UInt8> v_in(v_info.width(), v_info.height());
		
		//import the image into the source multiarray
		importImage(v_info, v_in);
		
		//create an array view for the desired subregion
		MultiArray<2, UInt8> v_out = v_in.subarray(Shape2(c_from.first,c_from.second) , Shape2(c_to.first,c_to.second));
		
		
		//export the destination multiarray to the destination image path
		exportImage(v_out, c_DESTINATION_IMAGE_PATH.c_str());
		
		std::cout << "Task 01 ended" << std::endl;
	
	}
	catch(std::exception & a_e){
		std::cout << a_e.what() << std::endl;
		return -1;
	}
	
    return 0;
}
