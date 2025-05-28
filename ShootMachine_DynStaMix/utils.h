#pragma once

#include <iostream>
#include <cmath>
//#include <corecrt_math_defines.h>
#include <random>

#ifndef M_PI
const double M_PI = 3.14159265358979323846;   // pi
#endif // !M_PI

const double G = 9800;	//	mm/s^2
const double IDEAL_BASE_RADIAN = M_PI / 4;

struct Point {
	double x;
	double y;
	double z;
};

inline double get_distance(const Point startpoint, const Point endpoint) {

	double delta_x = endpoint.x - startpoint.x;
	double delta_y = endpoint.y - startpoint.y;
	double delta_z = endpoint.z - startpoint.z;

	return sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}	//	返回两点距离

inline double get_distance_xoy(const Point startpoint, const Point endpoint) {

	double delta_x = endpoint.x - startpoint.x;

	//if (delta_x <= 0)
		//return -1;

	double delta_y = endpoint.y - startpoint.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y);
}	//	返回两点XOY平面距离

inline double figure_out_alpha(const Point startpoint, const Point endpoint) {

	double delta_x = endpoint.x - startpoint.x;

	int multi = -1;
	
	if (delta_x <= 0)
		multi = 1;
		//return -1;

	double delta_y = endpoint.y - startpoint.y;

	double len = sqrt(delta_x * delta_x + delta_y * delta_y);

	double normalize_x = delta_x / len;

	double alpha = 0;

	if (normalize_x <= 1)
		alpha = asin(normalize_x);
	else
		return -1;

	return delta_y >= 0 ? (M_PI * (1 + multi) + alpha) : (M_PI +  (multi * alpha));
}	//	返回向量与y轴正方向的夹角

//	velocity*cos(theta) = len / t
//	velocity*sin(theta)*t-0.5*G*t*t= height
//	斜抛 https://zhuanlan.zhihu.com/p/378429301
inline double figure_out_velocity_mini(double distance, double height) {

	double velocity_mini = sqrt(G * (height + sqrt(height * height + distance * distance)));

	std::cout << "\t\t velocity_mini: " << velocity_mini << std::endl;

	return velocity_mini;
}	//	计算最小速度

inline double figure_out_theta(double distance, double height, double velocity) {

	// 计算求根方程系数
	double a = (G * distance * distance) / (2 * velocity * velocity);
	double b = -distance;
	double c = height + (G * distance * distance) / (2 * velocity * velocity);

	double discriminant = b * b - 4 * a * c;

	if (fabs(discriminant) < 1e-6)
		return -b / (2 * a);

	// 计算两个可能的仰角
	double tan_theta1 = (-b + sqrt(discriminant)) / (2 * a);
	double tan_theta2 = (-b - sqrt(discriminant)) / (2 * a);

	double theta1 = atan(tan_theta1);
	double theta2 = atan(tan_theta2);

	std::cout << "\t\t theta_1 = " << theta1 << std::endl;
	std::cout << "\t\t theta_2 = " << theta2 << std::endl;

	return fabs(theta1 - IDEAL_BASE_RADIAN) <= fabs(theta2 - IDEAL_BASE_RADIAN) ? theta1 : theta2;

}	//	依据速度算仰角，返回会更靠近IDEAL_BASE_RADIAN的弧度

inline double generate_gaussian(double mean, double stddev) {
	// 初始化随机数引擎（使用硬件熵源）
	static std::random_device rd;
	static std::mt19937 gen(rd()); // Mersenne Twister 引擎

	// 创建正态分布对象
	std::normal_distribution<double> dist(mean, stddev);

	return dist(gen);
}	// 正态分布生成

//	Dynamic

inline Point vector_subtract_xoy(Point point1, Point point2) {

	Point tmp = { 0,0,0 };
	tmp.x = point2.x - point1.x;
	tmp.y = point2.y - point1.y;

	return tmp;
}	//	向量减法

inline Point vector_reshape(Point& vector, double scale) {

	double length = get_distance_xoy({ 0,0,0 }, vector);
	
	vector.x = vector.x / length * scale;
	vector.y = vector.y / length * scale;

	return vector;
}	//	向量标准化+向量伸缩