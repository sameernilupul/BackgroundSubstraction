//
//  SelectROI.h
//  BackgroundSubstraction
//
//  Created by Sameera Nilupul Wijayarathna on 6/29/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef BackgroundSubstraction_SelectROI_h
#define BackgroundSubstraction_SelectROI_h

#include<opencv2/highgui/highgui.hpp>

cv::Rect getSelected(cv::Mat input);
void mouseHandler(int event, int x, int y, int flags, void* param);


#endif
