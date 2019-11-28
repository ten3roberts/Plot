#include <Windows.h>
#include <cmath>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

#define PI 3.1415
#define TAU 6.28318530718
#define TORAD PI/180

struct vec2
{
	int x, y;
	vec2() : x(0), y(0) {}
	vec2(int x, int y) : x(x), y(y) {}
	bool operator==(const vec2& vec) { return x = vec.x && y == vec.y; }
	bool operator!=(const vec2& vec) { return x != vec.x || y != vec.y; }
};

vec2* pixels;
size_t pixels_size;
size_t pixels_it;

void Draw(HDC hdc, int width, int height, int limit, double step)
{
	COLORREF COLOR = RGB(255, 255, 255);
	double k = 0;
	pixels_it = 0;
	for (size_t i = 0; i < limit; i++)
	{
		double radius = sqrt(i) * 10;
		double circ = i * PI;

		for (double j = 0; j <= 1; j += step, k += step)
		{
			SetPixel(hdc, pixels[pixels_it].x, pixels[pixels_it].y, RGB(0, 0, 0));
			COLOR = RGB(radius, cos(radius / 50) * 255, sin(radius / 50) * 255);
			//COLOR = RGB(radius, 0, 0);
			vec2 pos(cos(k * TAU) * radius + width / 2.0f, sin(k * TAU) * radius + height / 2);
			SetPixel(hdc, pos.x, pos.y, COLOR);
			if (pixels_it >= pixels_size)
				return;
			pixels[pixels_it] = pos;
			pixels_it++;
		}
		//std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
	size_t i = pixels_it;
	while (pixels[i] != vec2(0, 0))
	{
		SetPixel(hdc, pixels[i].x, pixels[i].y, RGB(0, 0, 0));

		i++;
		if (i >= pixels_size)
			break;
	}

}

int main()
{
	//Choose any color
	//printf("Enter step ratio : ");

	//Get a console handle
	HWND hconsole = GetConsoleWindow();
	//Get a handle to device context
	HDC hdc = GetDC(hconsole);

	int pixel = 0;

	RECT rect;
	int width = 0, height = 0;
	if (GetWindowRect(hconsole, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	pixels = new vec2[width * height];
	pixels_size = width * height;
	pixels_it = 0;
	double step = 0.1;

	while (true)
	{
		Draw(hdc, width, height, 1000, step);
		std::this_thread::sleep_for(200ms);

		step += 0.001f;
	}




	ReleaseDC(hconsole, hdc);
	std::this_thread::sleep_for(101.0s);
	return 0;
}