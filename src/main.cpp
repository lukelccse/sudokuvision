// main.cpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using std::cout;
using std::endl;

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Expecting a image file to be passed to program" << endl;
        return -1;
    }
    
    cv::Mat img = cv::imread(argv[1]);
    
    if (img.empty()) {
        cout << "Not a valid image file" << endl;
        return -1;
    }

    // experiment Here

    // resize
    float resize_factor = 1.0f;
    cv::Mat img_resized;
    cv::resize(img, img_resized, 
                cv::Size(img.cols * resize_factor, img.rows * resize_factor),
                cv::INTER_LINEAR);

    // convert to greyscale image
    cv::Mat img_grey;
    cv::cvtColor(img_resized, img_grey, cv::COLOR_BGR2GRAY);

    // blur
    cv::Mat img_blurred;
    cv::GaussianBlur(img_grey, img_blurred, cv::Size(5, 5), 0);

    // threashold
    cv::Mat img_thresh;
    cv::adaptiveThreshold(img_blurred, img_thresh, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 27, 0);
    
    // mask
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img_thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat drawing = cv::Mat::zeros(img_thresh.size(), CV_8UC3);
    for(size_t i = 0; i< contours.size(); i++ ){
        cv::Scalar color = cv::Scalar( 5+i%256, 5+i%256, 5+i%256 );
        cv::drawContours( drawing, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0);
    }

    for(size_t i = 0; i< contours.size(); i++ ){
        std::cout << hierarchy[i];
    }



    // find contours

    // show and stop here.
    
    cv::namedWindow("Simple Demo", cv::WINDOW_AUTOSIZE);
    cv::imshow("Simple Demo", drawing);
    
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
