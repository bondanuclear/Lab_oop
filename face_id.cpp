#include <iostream>
#include <conio.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <opencv2/face.hpp>
#include "drawLandmarks.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;

int main(int argc, char** argv)
{
	// Load Face Detector
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	// Create an instance of Facemark
	Ptr<Facemark> facemark = FacemarkLBF::create();
	// Load landmark detector
	facemark->loadModel("lbfmodel.yaml");
	// Set up webcam for video capture
	VideoCapture cam(0);
	// Variable to store a video frame and its grayscale 
	Mat frame, gray;
	// Read a frame
	while (cam.read(frame))
	{
		// Find face
		vector<Rect> faces;
		// Convert frame to grayscale because
		// faceDetector requires grayscale image.
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		// Detect faces
		faceDetector.detectMultiScale(gray, faces);
		// Variable for landmarks. 
		// Landmarks for one face is a vector of points
		// There can be more than one face in the image. Hence, we 
		// use a vector of vector of points. 
		vector< vector<Point2f> > landmarks;
		// Run landmark detector
		bool success = facemark->fit(frame, faces, landmarks);

		if (success)
		{
			// If successful, render the landmarks on the face
			for (size_t i = 0; i < faces.size(); i++)
			{
				cv::rectangle(frame, faces[i], Scalar(0, 255, 0), 3);
			}

			for (int i = 0; i < landmarks.size(); i++)
			{
				//if((i >=30)&&(i <= 35))
				drawLandmarks(frame, landmarks[i]);

				for (size_t j = 0; j < landmarks[i].size(); j++) {
					circle(frame, Point(landmarks[i][j].x, landmarks[i][j].y), 1, Scalar(255, 0, 0), 2);
				}
				// намалювати лінію від переносиці до підборіддя
				line(frame, Point(landmarks[i][27].x, landmarks[i][27].y), Point(landmarks[i][8].x, landmarks[i][8].y), Scalar(0, 0, 255), 2);
				// координати середини правого і лівого ока
				float XL = (landmarks[i][45].x + landmarks[i][42].x) / 2;
				
				float YL = (landmarks[i][45].y + landmarks[i][42].y) / 2;
			
				float XR = (landmarks[i][39].x + landmarks[i][36].x) / 2;
				
				float YR = (landmarks[i][39].y + landmarks[i][36].y) / 2;
				//////////////////////////////////////////////////
				// Намалювати лінію від середини лівого до середини правого очей
				line(frame, Point(XL, YL), Point(XR, YR), Scalar(0, 0, 255), 2);

				// Відстань між середніми точками очей по Х і Y
				float DX = XR - XL;
				
				float DY = YR - YL;
				// за теоремою Піфагора вираховуємо  відстань між серединами очей
				float L = sqrt(DX * DX + DY * DY);
				// Точка переносиці по х та у
				float X1 = (landmarks[i][27].x);
				
				float Y1 = (landmarks[i][27].y);
				// Точка підборіддя по х та у
				float X2 = (landmarks[i][8].x);
				
				float Y2 = (landmarks[i][8].y);
				///////////
					// 
				float DX1 = abs(X1 - X2);
			
				float DY1 = abs(Y1 - Y2);
				
				float L1 = sqrt(DX1 * DX1 + DY1 * DY1);
				
				float X0 = (XL + XR) / 2;
				
				float Y0 = (YL + YR) / 2;
				// тригонометричні функції повороту
				
				float sin_AL = DY / L;
				
				float cos_AL = DX / L;
				/////////////
				// перехід від системи координат у вікні до координатами в СК користувача
				// точка переносиці
				float X_User_0 = (landmarks[i][27].x - X0) / L;
				
				float Y_User_0 = -(landmarks[i][27].y - Y0) / L;
				
				float X_User27 = X_User_0 * cos_AL - Y_User_0 * sin_AL;
				
				float Y_User27 = X_User_0 * sin_AL + Y_User_0 * cos_AL;
				// в точці кінчика носа
				X_User_0 = (landmarks[i][30].x - X0) / L;
				Y_User_0 = -(landmarks[i][30].y - Y0) / L;
				float X_User30 = X_User_0 * cos_AL - Y_User_0 * sin_AL;
				float Y_User30 = X_User_0 * sin_AL + Y_User_0 * cos_AL;

				if (abs(X_User27 - X_User30) <= 0.1)
				{
					//putText(frame, std::to_string(abs(L1 / L)), Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
					if (abs((L1 / L) - 1.8) < 0.1)
					{
						putText(frame, "Owner", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
					}
					
					if (abs((L1 / L) - 2.0) < 0.1)
					{
						putText(frame, "Taya", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
					}
	
					
				}
				else 
				putText(frame, "Can't recognize", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
			}
		}

		// Display results 
		imshow("Facial Landmark Detection", frame);

		// Exit loop if ESC is pressed
		if (waitKey(1) == 27) break;

	}
	return 0;
}