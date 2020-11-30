#include <iostream>
#include <conio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/face.hpp>
#include "drawLandmarks.hpp"
#include <chrono>
#include <thread>
using namespace std;
using namespace cv;
using namespace cv::face;
void face_id()
{
	// розпізнавач обличчя
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");

	Ptr<Facemark> facemark = FacemarkLBF::create();
	facemark->loadModel("lbfmodel.yaml");
	VideoCapture cam(0);
	Mat frame, gray;
	while (cam.read(frame))
	{
		// знаходження обличчя
		vector<Rect> faces;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		faceDetector.detectMultiScale(gray, faces);
		// вектор точок
		vector< vector<Point2f> > landmarks;
		bool check = facemark->fit(frame, faces, landmarks);
		if (check)
		{
			for (int i = 0; i < landmarks.size(); i++)
			{
				drawLandmarks(frame, landmarks[i]);

				float XL = (landmarks[i][45].x + landmarks[i][42].x) / 2;
				float YL = (landmarks[i][45].y + landmarks[i][42].y) / 2;
				float XR = (landmarks[i][39].x + landmarks[i][36].x) / 2;
				float YR = (landmarks[i][39].y + landmarks[i][36].y) / 2;
				// центр
				float X0 = (XL + XR) / 2;
				float Y0 = (YL + YR) / 2;
				// обчислення зміщень
				float dxx = XR - X0; float dyx = -(YR - Y0);
				float dxy = -(landmarks[i][33].x - X0);
				float dyy = landmarks[i][33].y - Y0;
				float dxz = landmarks[i][27].x - X0;
				float dyz = -(landmarks[i][27].y - Y0);
				/////
				float Kx = dyx / dxx;
				float Ky = dyy / dxy;
				float Kz = dyz / dxz;
				/////////////////////////////// Відстань між точками за допомогою теореми Піфагора
				float Lx = sqrt(dxx * dxx + dyx * dyx);
				float Ly = sqrt(dxy * dxy + dyy * dyy);
				float Lz = sqrt(dxz * dxz + dyz * dyz);
				// координати
				float X1 = (landmarks[i][3].x);
				float Y1 = (landmarks[i][3].y);
				float X2 = (landmarks[i][13].x);
				float Y2 = (landmarks[i][13].y);

				////////////
				float DX1 = (X2 - X1);
				float DY1 = (Y2 - Y1);

				/// визначення проекцій точок z координати
				float Xmid = X1 + DX1 / 2; float Ymid = Y1 + DY1 / 2;
				/// переходимо в систему коорд. з центром (х0,у0) і віссю у, напрямленою вверх
				Xmid = Xmid - X0; Ymid = -(Ymid - Y0); // вкс
				// через Xmid i Ymid проводимо пряму, паралельну проекції вісі z до перетину з віссю y
				// координати перетину цих прямих
				float Xint = (Ymid - Kz * Xmid) / (Ky - Kz);
				float Yint = Ky * Xint;
				///
				Xmid = Xmid + X0; Ymid = -(Ymid - Y0);
				Xint = Xint + X0; Yint = -(Yint - Y0);


				// відрізки
				line(frame, Point(X1, Y1), Point(Xmid, Ymid), Scalar(0, 255, 255), 2); // X
				line(frame, Point(X0, Y0), Point(Xint, Yint), Scalar(255, 0, 255), 2); // Y
				line(frame, Point(Xmid, Ymid), Point(Xint, Yint), Scalar(255, 255, 0), 2); // Z

				float x1 = 0.5 * sqrt(DX1 * DX1 + DY1 * DY1) / Lx; // нормалізована координата х1 
				float x2 = -x1; //нормалізована координата х2 (для симетричної точки)

				DX1 = (Xint - X0);
				DY1 = (Yint - Y0);
				float y1 = sqrt(DX1 * DX1 + DY1 * DY1) / Ly; //нормалізовані координати y1 и y2

				DX1 = (Xint - Xmid);
				DY1 = (Yint - Xmid);
				float z1 = sqrt(DX1 * DX1 + DY1 * DY1) / Lz; //нормалізовані координати z1 и z2

				putText(frame, std::to_string(x1), Point(X1 + 150, Y1 + 10), 1, 2, Scalar(0, 255, 255), 2);
				putText(frame, std::to_string(z1), Point(X1 + 150, Y1 - 30), 1, 2, Scalar(255, 255, 0), 2);
				putText(frame, std::to_string(y1), Point(X1 + 150, Y1 - 70), 1, 2, Scalar(255, 0, 255), 2);
				if ((x1 - 2 < 0.1) && (y1 - 1 < 0.1))
				{
					putText(frame, "Bondarenko", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
					//this_thread::sleep_for(chrono::milliseconds(3000));
					//break;
				}
				/*else
					if ((x1 - 2.2 < 0.1) && (y1 - 1.2 < 0.1))
					{
						putText(frame, "Person1", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
					}*/
					else putText(frame, "Can't recognize", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
			}
		}

		// вивести на екран
		imshow("Facial Landmark Detection", frame);

		// esc для виходу
		if (waitKey(1) == 27) break; 

	}
}
int main(int argc, char** argv)
{
	cout << "Orders: " << endl;
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1: face_id();


	}
	
	return 0;
}
