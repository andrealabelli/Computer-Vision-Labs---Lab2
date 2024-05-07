#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "task2_lab2.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
    //Task 1
    Mat img = imread("C:/Users/andre/OneDrive/Desktop/Lab_2/img.jpg");
    if (!img.data)
    {
        printf(" No image found in the path! \n");
        return -1;
    }

    namedWindow("Original img", WINDOW_KEEPRATIO);
    imshow("Original img", img);

    Mat gray_img;
    cvtColor(img, gray_img, COLOR_BGR2GRAY);
    namedWindow("Grayscale img", WINDOW_KEEPRATIO);
    imshow("Grayscale img", gray_img);
    imwrite("C:/Users/andre/OneDrive/Desktop/Lab_2/image_grayscale.jpg", gray_img);

/*---------------------------------------------------------------------------------------------------------------------*/

    //Task 2
    int size;
    cout << "\n\nInsert the dimension for the kernel (odd): ";
    cin >> size;

    max_min_filter mmf;
    Mat img_max = mmf.max_filter(size, gray_img);
    namedWindow ("Max filter img", WINDOW_KEEPRATIO);
    imshow ("Max filter img", img_max);
    //imwrite("C:/Users/andre/OneDrive/Desktop/Foto_Lab2/max_filter.jpg", img_max);
    
    Mat img_min = mmf.min_filter(size, gray_img);
    namedWindow ("Min filter img", WINDOW_KEEPRATIO);
    imshow ("Min filter img", img_min);
    //imwrite("C:/Users/andre/OneDrive/Desktop/Foto_Lab2/min_filter.jpg", img_min);
    
/*---------------------------------------------------------------------------------------------------------------------*/

    //Task 3
    cout << "\n\nInsert the dimension for the kernel of median and gaussian filter (odd): ";
    cin >> size;

    if(size % 2 == 0){
    cout << "\nInvalid kernel size! Kernel size must be odd!\n"; 
    return -1;
    } 

    Mat med_filter_img;
    medianBlur(gray_img, med_filter_img, size);
    namedWindow("Median filter img", WINDOW_KEEPRATIO);
    imshow("Median filter img", med_filter_img);
    //imwrite("C:/Users/andre/OneDrive/Desktop/Foto_Lab2/med_filter.jpg", med_filter_img);

    Mat gauss_filter_img;
    Size s(size, size);
    GaussianBlur(gray_img, gauss_filter_img, s, 0, 0);
    namedWindow("Gaussian filter img", WINDOW_KEEPRATIO);
    imshow("Gaussian filter img", gauss_filter_img);
    //imwrite("C:/Users/andre/OneDrive/Desktop/Foto_Lab2/gauss_filter.jpg", gauss_filter_img);

/*---------------------------------------------------------------------------------------------------------------------*/

    //Task 4
    Mat hist;

    //Compute the histogram
    int histSize = 256;       //Number of bins
    float range[] = { 0, 256 };   //Histogram range
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    calcHist( &gray_img, 1, 0, Mat(), hist, 1, &histSize, histRange, uniform, accumulate );

    int hist_w = 2048, hist_h = 1600;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
              Scalar(0, 0, 255), 2, 8, 0  );
    }

    namedWindow("Histogram of the image", WINDOW_KEEPRATIO);
    imshow("Histogram of the image", histImage);
    //imwrite("C:/Users/andre/OneDrive/Desktop/Foto_Lab2/hist_img.jpg", histImage);

/*---------------------------------------------------------------------------------------------------------------------*/

    //Task 5
    Mat Hist_eq_image;
    equalizeHist(gray_img, Hist_eq_image);
    namedWindow("Image with histogram equalization", WINDOW_KEEPRATIO);
    imshow("Image with histogram equalization", Hist_eq_image);
    //imwrite("C:/Users/andre/OneDrive/Desktop/Foto_Lab2/hist_eq_image.jpg", Hist_eq_image);

    //Compute the histogram 
    Mat hist_eq;
    int hist_Size = 256;       //Number of bins
    float rang[] = { 0, 256 };   //Histogram range
    const float* hist_Range[] = { rang };
    bool uniforme = true, accumulatee = false;
    calcHist( &Hist_eq_image, 1, 0, Mat(), hist_eq, 1, &hist_Size, hist_Range, uniforme, accumulatee );

    int hist__w = 2048, hist__h = 1600; 
    int bin__w = cvRound( (double) hist__w/hist_Size );
    Mat hist_eq_img( hist__h, hist__w, CV_8UC3, Scalar( 0,0,0) );
    normalize(hist_eq, hist_eq, 0, hist_eq_img.rows, NORM_MINMAX, -1, Mat() );
    for( int i = 1; i < hist_Size; i++ )
    {
        line( hist_eq_img, Point( bin__w*(i-1), hist__h - cvRound(hist_eq.at<float>(i-1)) ),
              Point( bin__w*(i), hist__h - cvRound(hist_eq.at<float>(i)) ),
              Scalar(0, 0, 255), 2, 8, 0  );
    }

    namedWindow("Histogram of the image equalized", WINDOW_KEEPRATIO);
    imshow("Histogram of the image equalized", hist_eq_img);
    //imwrite("C:/Users/andre/OneDrive/Desktop/Foto_Lab2/hist_of_eq_img.jpg", hist_eq_img);

    waitKey(0);
    return 0;
}