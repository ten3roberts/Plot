#include <Windows.h>
#include <cmath>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

#define PI 3.1415
#define TAU 6.28318530718

int main()
{
	//Choose any color
	COLORREF COLOR = RGB(255, 255, 255);
	float step;
	printf("Enter step ratio : ");

	//Get a console handle
	HWND myconsole = GetConsoleWindow();
	//Get a handle to device context
	HDC mydc = GetDC(myconsole);

	int pixel = 0;

	RECT rect;
	int width = 0, height = 0;
	if (GetWindowRect(myconsole, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	std::cin >> step;

	double k = 0;
	int limit = 1000;
	for (int i = 0; i < limit; i++)
	{
		for (float j = 0; j < 1; j += step, k += step)
		{
			float radius = sqrt(i) * 10;
			COLOR = RGB(radius, cos(radius / 50) * 255, sin(radius / 50) * 255);
			//COLOR = RGB(radius, 0, 0);
			SetPixel(mydc, cos(k * TAU) * radius + width / 2.0f, sin(k * TAU) * radius + height / 2, COLOR);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}


	ReleaseDC(myconsole, mydc);
	std::this_thread::sleep_for(101.0s);
	return 0;
}