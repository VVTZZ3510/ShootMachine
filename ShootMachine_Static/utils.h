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
}	//	�����������

inline double get_distance_xoy(const Point startpoint, const Point endpoint) {

	double delta_x = endpoint.x - startpoint.x;

	if (delta_x <= 0)
		return -1;

	double delta_y = endpoint.y - startpoint.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y);
}	//	��������XOYƽ�����

inline double figure_out_alpha(const Point startpoint, const Point endpoint) {

	double delta_x = endpoint.x - startpoint.x;

	if (delta_x <= 0)
		return -1;

	double delta_y = endpoint.y - startpoint.y;

	double len = sqrt(delta_x * delta_x + delta_y * delta_y);

	double normalize_x = delta_x / len;

	double alpha = 0;

	if (normalize_x <= 1)
		alpha = asin(normalize_x);
	else
		return -1;

	return delta_y >= 0 ? alpha : M_PI - alpha;
}	//	����������y��������ļн�


//	velocity*cos(theta) = len / t
//	velocity*sin(theta)*t-0.5*G*t*t= height
//	б�� https://zhuanlan.zhihu.com/p/378429301
inline double figure_out_velocity_mini(double distance, double height) {

	double velocity_mini = sqrt(G * (height + sqrt(height * height + distance * distance)));

	std::cout << "\t\tvelocity_mini: " << velocity_mini << std::endl;

	return velocity_mini;
}	//	������С�ٶ�

inline double figure_out_theta(double distance, double height, double velocity) {

	// �����������ϵ��
	double a = (G * distance * distance) / (2 * velocity * velocity);
	double b = -distance;
	double c = height + (G * distance * distance) / (2 * velocity * velocity);

	double discriminant = b * b - 4 * a * c;

	if (fabs(discriminant) < 1e-6)
		return -b / (2 * a);

	// �����������ܵ�����
	double tan_theta1 = (-b + sqrt(discriminant)) / (2 * a);
	double tan_theta2 = (-b - sqrt(discriminant)) / (2 * a);

	double theta1 = atan(tan_theta1);
	double theta2 = atan(tan_theta2);

	std::cout << "\t\ttheta_1 = " << theta1 << std::endl;
	std::cout << "\t\ttheta_2 = " << theta2 << std::endl;

	return fabs(theta1 - IDEAL_BASE_RADIAN) <= fabs(theta2 - IDEAL_BASE_RADIAN) ? theta1 : theta2;

}	//	�����ٶ������ǣ����ػ������IDEAL_BASE_RADIAN�Ļ���


// ��̬�ֲ�������
inline double generate_gaussian(double mean, double stddev) {
	// ��ʼ����������棨ʹ��Ӳ����Դ��
	static std::random_device rd;
	static std::mt19937 gen(rd()); // Mersenne Twister ����

	// ������̬�ֲ�����
	std::normal_distribution<double> dist(mean, stddev);

	return dist(gen);
}