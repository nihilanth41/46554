#include <opencv2/core/core.hpp>
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

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);

	waitKey(0);
	return EXIT_SUCCESS;
}
