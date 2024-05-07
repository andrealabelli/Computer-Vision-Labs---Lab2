#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class max_min_filter {

public:
Mat max_filter(int size, Mat img) {
Mat img_max = img.clone();

if(size % 2 == 0){
    cout << "\nInvalid kernel size!\n";
    throw invalid_argument("Wrong kernel size"); 
} 

int pos_ker = (size - 1)/2;

int f_row, l_row, f_col, l_col;     //Variables for the start/finish of the kernel

    for(int i = 0; i < img.cols; i++){
        for(int j = 0; j < img.rows; j++){
            
            f_row = j - pos_ker;
            l_row = j + pos_ker;
            f_col = i - pos_ker;
            l_col = i + pos_ker;

            if(f_row < 0) f_row = 0;
            if(f_col < 0) f_col = 0;

            if(l_row >= img.rows) l_row = img.rows - 1;
            if(l_col >= img.cols) l_col = img.cols -1;
            
            int max_value=0;
            for(int m = f_row; m <= l_row; m++){
                for(int l = f_col; l <= l_col; l++){
                    int pixel_value = img.at<uchar>(m, l);
                    if(pixel_value > max_value) max_value = pixel_value;
                }
               
            }
            img_max.at<uchar>(j, i) = max_value;
        }
}
return img_max;
}


Mat min_filter(int size, Mat img) {
Mat img_min = img.clone();

if(size % 2 == 0){
    cout << "\nInvalid kernel size!\n";
    throw invalid_argument("Wrong kernel size"); 
} 

int pos_ker = (size - 1)/2;

int f_row, l_row, f_col, l_col;     //Variables for the start/finish of the kernel

    for(int i = 0; i < img.cols; i++){
        for(int j = 0; j < img.rows; j++){
            
            f_row = j - pos_ker;
            l_row = j + pos_ker;
            f_col = i - pos_ker;
            l_col = i + pos_ker;

            if(f_row < 0) f_row = 0;
            if(f_col < 0) f_col = 0;

            if(l_row >= img.rows) l_row = img.rows - 1;
            if(l_col >= img.cols) l_col = img.cols -1;
            
            int min_value = 300;
            for(int m = f_row; m <= l_row; m++){
                for(int l = f_col; l <= l_col; l++){
                    int pixel_value = img.at<uchar>(m, l);
                    if(pixel_value < min_value) min_value = pixel_value;
                }
               
            }
            img_min.at<uchar>(j, i) = min_value;
        }
}
return img_min;
}
};



