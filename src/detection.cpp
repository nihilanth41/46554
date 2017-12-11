#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

/* TODO:
 - Nonmaxima supression
 - detectMultiscale parameters (scales?) 
 - Moar sample data (see README)
*/

void testDetector(void);
void detection(char *);

void testDetector(void) {
	static int i;
	static int image_max = 460;
	char buf[512];
	for(i=1; i<image_max+1; i++) {
		sprintf(buf, "../persons/person_%03d.bmp", i);
		cout << "Opening file: " << buf << endl;
		detection(buf);
	}
}

void detection(char *image_path) {
	Mat image;
	image = imread(image_path, CV_LOAD_IMAGE_COLOR); // Read file
	if(! image.data) {
		cout << "Could not open image: " << image_path <<  endl;
		exit(-2);
	}

	/* http://answers.opencv.org/question/22420/human-detection-with-hog-how-to-improve-it/ */
	/* Default people detector */
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	/* For holding the objects */
	vector<Rect> found, found_filtered; 

	/* args: image, foundlocations, hit_thresh, winStride, Padding, scale, finalthresh, usemeanshift grouping bool */
	hog.detectMultiScale(image, found, 0, Size(8,8), Size(32,32), 1.05, 3);
	size_t i, j;
	for (i=0; i<found.size(); i++)
	{
		Rect r = found[i];
		for (j=0; j<found.size(); j++)
			if (j!=i && (r & found[j])==r)
				break;
		if (j==found.size())
			found_filtered.push_back(r);
	}

	cout << "Number of people detected: " << found_filtered.size() << endl;
	for (i=0; i<found_filtered.size(); i++)
	{
		Rect r = found_filtered[i];
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.06);
		r.height = cvRound(r.height*0.9);
		rectangle(image, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
	}

	if(found_filtered.size() > 0) {
		namedWindow("Display window", WINDOW_AUTOSIZE);
		imshow("Display window", image);
		waitKey(0);
	}
}

int main(int argc, char **argv) {
	if(argc != 2) {
		cout << "Usage: ./detection.bin <path/to/image>" << endl;
		return -1;
	}
	testDetector();

	return EXIT_SUCCESS;
}
