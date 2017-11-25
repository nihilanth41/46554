#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
	if(argc != 2) {
		cout << "Usage: ./detection.bin <path/to/image>" << endl;
		return -1;
	}
	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR); // Read file
	if(! image.data) {
		cout << "Could not open image: " << argv[1] <<  endl;
		return -2;
	}

	/* Begin Processing */
	image.convertTo(image, CV_32F, 1/255.0);

	/* Calculate Gradient in x and y direction*/
	Mat gx, gy;
	Sobel(image, gx, CV_32F, 1, 0, 1);
	Sobel(image, gy, CV_32F, 0, 1, 1);

	/* Find magnitude and orientation */
	Mat mag, angle;
	cartToPolar(gx, gy, mag, angle, 1);


	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
	waitKey(0);
	
	imshow("Display window", gx);
	waitKey(0);
	
	imshow("Display window", gy);
	waitKey(0);
	
	imshow("Display window", mag);
	waitKey(0);
	
	imshow("Display window", angle);
	waitKey(0);

	return EXIT_SUCCESS;
}
