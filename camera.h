#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "ray.h"

vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0 * vec3(random_double(), random_double(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

class camera {
public:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lens_radius;
	float shutterSpeed;

	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist, float shutterSpeed) : shutterSpeed(shutterSpeed) {
		lens_radius = aperture / 2;
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(origin - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		//foucus planeにスクリーンを張る
		lower_left_corner = origin
			- half_width * focus_dist * u
			- half_height * focus_dist * v
			- focus_dist * w;
		horizontal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;
	}

	ray get_ray(float s, float t, float time) {
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		double rndTime = std::clamp(time- random_double() * this->shutterSpeed, 0.0, std::numeric_limits<double>::max());
		//焦点があっている場合はベクトルの原点をずらしても(方向ベクトルの"ノルム"は同じ座標を指すように)同じオブジェクトにあたる
		return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, rndTime);
	}
};