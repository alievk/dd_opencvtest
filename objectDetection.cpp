#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String defect_cascade_name = "cascade.xml";
CascadeClassifier defect_cascade;
String window_name = "defects";

/** @function main */
int main( void )
{
    Mat img;


    //-- 1. Load the cascade
    if( !defect_cascade.load( defect_cascade_name ) ){ printf("--(!)Error loading defect cascade\n"); return -1; };

    //-- 2. Load the images
    img = imread("6.jpg", CV_LOAD_IMAGE_COLOR);
    resize(img, img, Size(), 2., 2.); // CASCADE IS SENSETIVE TO TESTING IMAGE SIZE, THE TESTING IMAGES ARE TOO SMALL THAT'S WHY THEY ARE RESIZED HERE

    if ( !img.data ){ printf("--(!)Error loading source image\n"); return -1; };

    //-- 3. Apply the classifier to the frame
    detectAndDisplay( img );

    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat img )
{
    std::vector<Rect> defects;
    Mat img_gray;

    cvtColor( img, img_gray, COLOR_BGR2GRAY );
    equalizeHist( img_gray, img_gray );

    //-- Detect defects
    // For the documentation of detectMultiScale look into the OpenCV Reference
    double scaleFactor = 1.1;
    int minNeighbours = 2;
    Size minSize = Size(20, 20);
    Size maxSize = Size(200, 200);
    defect_cascade.detectMultiScale( img_gray, defects, scaleFactor, minNeighbours);//, 0, minSize, maxSize );

    for ( size_t i = 0; i < defects.size(); i++ )
    {
        Point center( defects[i].x + defects[i].width/2, defects[i].y + defects[i].height/2 );
        ellipse( img, center, Size( defects[i].width/2, defects[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    }

    //-- Show what you got
    cvNamedWindow( "defects", CV_WINDOW_AUTOSIZE );
    imshow( window_name, img );
    
    // Write down the processed file
    imwrite( "processed6.jpg", img );
}
