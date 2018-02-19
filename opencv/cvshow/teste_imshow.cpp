/**
*/

#include <ctime>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

using namespace std; 
using namespace cv;

#define w 600

string int2string( int i )
{
	std::string s;
	std::stringstream out;
	out << i;
	return out.str();
}

// criar uma classe em breve 
double scaleX = w/2; 
double scaleY = w/2;
double shiftX = w/2; 
double shiftY = w/2;   

int raio = 2;  

Mat oneImage;

int loadPointsFromFile(std::vector<Point> &points, std::string fileName, double sx = 1, double sy = 1, double shx = 1, double shy = 1) {
	std::ifstream file;
	
	Point pt;
    
    file.open(fileName.c_str());
    if (!file.good()) {
        std::cout << " File, " << fileName << ", not found! " << std::endl;
        return -1;
    }
    float columns, lines, data;
    file >> lines >> columns;
    for (int i = 0; i < lines; i++) {
        if (file.good()) {
			file >> data;
			pt.x = data*sx+shx; 
			file >> data;
			pt.y = data*sy+shy; 
            points.push_back(pt);            
        }
    }
} 
 
bool drowPointFromTxt(std::string fileName, cv::Scalar color) {
	std::vector<Point> dataPoints;
    if ( loadPointsFromFile(dataPoints,fileName, scaleX, scaleY, shiftX, shiftY) != -1 ) {   
		for ( int i = 0; i < dataPoints.size(); i++ ) {
			//cout << " " << dataPoints[i].x <<" " <<dataPoints[i].y << endl; 
			cv::circle(oneImage,dataPoints[i], raio, color ); 
		}
		return true;	
	}
	else {
		return false; 
	}
}
 
 
int main ( int argc,char **argv ) {
   
	char oneWindow[] = "Drawing ...";
	/// Create black empty images
	oneImage = Mat::zeros( w, w, CV_8UC3 );
  
    cv::namedWindow(oneWindow, cv::WINDOW_AUTOSIZE);
    char keyP; 
    int contEpoch = 1; 
    while((keyP = (char)cv::waitKey(1))!='q'){
		if ( keyP == 'p' ) {
			cerr << keyP << " ";
			oneImage = Mat::zeros( w, w, CV_8UC3 );
			//drowPointFromTxt("../../data/pontos_2d_v1.txt",cv::Scalar(120,0,0)); 
			drowPointFromTxt("../../data/maestro1XY.txt",cv::Scalar(120,0,0)); 
			
			//drowPointFromTxt("/tmp/teste"+int2string(contEpoch)+".txt",cv::Scalar(0,0,255)); 
			drowPointFromTxt("/tmp/somtsp"+int2string(contEpoch)+".txt",cv::Scalar(0,0,255)); 
			contEpoch++; 
		} 
        cv::imshow(oneWindow,oneImage);
    }
     
}
