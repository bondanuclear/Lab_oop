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
void face_id_3d()
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
void face_id_2d()
{
	
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	Ptr<Facemark> facemark = FacemarkLBF::create();
	facemark->loadModel("lbfmodel.yaml");
	VideoCapture cam(0);
	// зберегти frame та grayscale
	Mat frame, gray;
	while (cam.read(frame))
	{
		
		vector<Rect> faces;
		// перетворити frame до grayscale image
		// бо faceDetector вимагає grayscale image.
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		// розппізнавач обличчя
		faceDetector.detectMultiScale(gray, faces);
		 
		vector< vector<Point2f> > landmarks;
		bool check = facemark->fit(frame, faces, landmarks);

		if (check)
		{
			
			for (size_t i = 0; i < faces.size(); i++)
			{
				cv::rectangle(frame, faces[i], Scalar(0, 255, 0), 3);
			}

			for (int i = 0; i < landmarks.size(); i++)
			{
				
				drawLandmarks(frame, landmarks[i]);

				/*for (size_t j = 0; j < landmarks[i].size(); j++) {
					circle(frame, Point(landmarks[i][j].x, landmarks[i][j].y), 1, Scalar(255, 0, 0), 2);
				}*/
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
				// відстань від переносиці до підборіддя
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
					putText(frame, std::to_string(abs(L1 / L)), Point(landmarks[i][30].x, landmarks[i][30].y), 1, 2, Scalar(0, 0, 255), 2);
					//putText(frame, std::to_string(abs(L1)), Point(landmarks[i][8].x, landmarks[i][8].y), 1, 2, Scalar(0, 255, 0), 2);
					//putText(frame, std::to_string(abs(L)), Point(landmarks[i][13].x, landmarks[i][13].y), 1, 2, Scalar(255, 0, 0), 2);
					if (abs((L1 / L) - 1.8) < 0.1)
					{
						putText(frame, "Bondarenko", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
					}

					/*if (abs((L1 / L) - 2.0) < 0.1)
					{
						putText(frame, "Person1", Point(landmarks[i][27].x, landmarks[i][27].y), 1, 2, Scalar(0, 0, 255), 2);
					}*/


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
}
int main(int argc, char** argv)
{
	
		cout << "Orders: " << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1: face_id_3d();
		case 2: face_id_2d();
		default: cout << "Choose again" << endl;
		}
	
	return 0;
}
