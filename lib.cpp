#include <iostream>
#include <emscripten/bind.h>
#include <opencv2/opencv.hpp>
#include <vector>

float add_two_numbers(float a, float b){
	return a + b;
}

std::vector<uint8_t> img_to_grey(const int &in_addr,  const size_t width, const size_t height){
	uint8_t *in_data = reinterpret_cast<uint8_t *>(in_addr);
	cv::Mat orig_img(height, width, CV_8UC4, in_data);

	cv::Mat grey_img;

	cv::cvtColor(orig_img, grey_img, cv::COLOR_RGBA2GRAY);

	cv::Mat simpleChannel[4];

	cv::split(grey_img, simpleChannel);
	
	//Source: https://stackoverflow.com/questions/26681713/convert-mat-to-array-vector-in-opencv
	std::vector<uint8_t> array;
	if (grey_img.isContinuous()) {
		array.assign(grey_img.datastart, grey_img.dataend); // <- has problems for sub-matrix like mat = big_mat.row(i)
		array.assign(grey_img.data, grey_img.data + grey_img.total()*grey_img.channels());
		} 
	else {
		for (int i = 0; i < grey_img.rows; ++i) {
			array.insert(array.end(), grey_img.ptr<uchar>(i), grey_img.ptr<uchar>(i)+grey_img.cols*grey_img.channels());
		}
	}
	return array;
	}



EMSCRIPTEN_BINDINGS(my_module){
	//emscripten::class_<cv::Mat>("Mat");
	emscripten::register_vector<uint8_t>("array");
	emscripten::function("add_two_numbers", &add_two_numbers);
	emscripten::function("img_to_grey", &img_to_grey, emscripten::allow_raw_pointers());
}



