//
// Developed by:  <Your Name> (your@email)
//                http://www.biodataanalysis.de/
//
// With contributions by:
//
//
// Copyright (c) 2024-2028, BioDataAnalysis GmbH
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
#include <vigra/convolution.hxx>

#include <iostream>
#include <string>

using namespace vigra;

const std::string c_LOCAL_SOURCE_IMAGE_PATH = "../images/bDZ17-1I_wE02_s7_z1_t1_cDAPI_u001.tif";
const std::string c_DESTINATION_IMAGE_PATH = "../images/task02_destination_image.tif";

int main(int argc, char** argv)
{
    std::cout << "Task 02 started" << std::endl;

    // You can add your code here
	
	// You can add your code here
	std::cout << "(supported formats: " << vigra::impexListFormats() << " ) " << std::endl;
	
	ImageImportInfo v_info(c_LOCAL_SOURCE_IMAGE_PATH.c_str());
		
	try{
		//create array view for the whole input image
		MultiArray<2, UInt8> v_in(v_info.width(), v_info.height());
		
		//import the input image
		importImage(v_info, v_in);
		
		//create the output image
		MultiArray<2, UInt8> v_out(v_info.width(), v_info.height());
		
		
		//gaussian smooth with scale 3.0
		gaussianSmoothing(v_in, v_out, 3.0);
		
		exportImage(v_out, c_DESTINATION_IMAGE_PATH.c_str());
		
	
	}
	catch(std::exception & a_e){
		std::cout << a_e.what() << std::endl;
		return -1;
	}


    std::cout << "Task 02 finished successfully" << std::endl;
    return 0;
}
