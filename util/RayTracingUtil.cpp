#include "../scene/Light.h"
#include "../primitives/Triangle.h"

#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

class RayTracingUtil {

public:


	float calculate_diffuse_component_sphere(float _kd, M3DVector3f intersect_p, M3DVector3f light_position,M3DVector3f object_position) {

		//Diffuse Component, Ivd ~ kd Id cos 0   where cos 0 = l.n (for l.n normalized) 

		// calculating l =  light_position - intersect_p;
		M3DVector3f light_direction;
		light_direction[0] = light_position[0] - intersect_p[0];
		light_direction[1] = light_position[1] - intersect_p[1];
		light_direction[2] = light_position[2] - intersect_p[2];

		float magnitude_fraction = 1.0f / m3dGetVectorLength(light_direction); //normalizing
		light_direction[0] *= magnitude_fraction;
		light_direction[1] *= magnitude_fraction;
		light_direction[2] *= magnitude_fraction;

		// calculating n = intersect_p - object_position
		M3DVector3f normal_direction;
		normal_direction[0] = intersect_p[0] - object_position[0];
		normal_direction[1] = intersect_p[1] - object_position[1];
		normal_direction[2] = intersect_p[2] - object_position[2];

		float magnitude_fraction2 = 1.0f / m3dGetVectorLength(normal_direction); //normalizing
		normal_direction[0] *= magnitude_fraction2;
		normal_direction[1] *= magnitude_fraction2;
		normal_direction[2] *= magnitude_fraction2;

		float  l_dot_n = light_direction[0] * normal_direction[0] + light_direction[1] * normal_direction[1] + light_direction[2] * normal_direction[2];

		float diffuse_component = _kd * (l_dot_n > 0.f ? l_dot_n : 0.f);
		return diffuse_component;
	}

	float calculate_specular_componenet_sphere(float _ks, M3DVector3f intersect_p, M3DVector3f light_position, M3DVector3f object_position, M3DVector3f view_vector) {

		 // For specular Surface->Ivs ~ks I pow(cos 0, alpha)  alpha = 100 - 200 for metals, 5 - 10 for plastic, cos 0 = v.r	    
	     // Step 1 : r= 2 (l� n) n - l
		 // Step 2 : cos 0 = v.r
		 // Step 3 : ks * pow(cos 0,alpha)
		

		// calculating l =  light_position - intersect_p;
		M3DVector3f light_direction;
		light_direction[0] = light_position[0] - intersect_p[0];
		light_direction[1] = light_position[1] - intersect_p[1];
		light_direction[2] = light_position[2] - intersect_p[2];

		float magnitude_fraction = 1.0f / m3dGetVectorLength(light_direction); //normalizing
		light_direction[0] *= magnitude_fraction;
		light_direction[1] *= magnitude_fraction;
		light_direction[2] *= magnitude_fraction;

		// calculating n = intersect_p - object_position
		M3DVector3f normal_direction;
		normal_direction[0] = intersect_p[0] - object_position[0];
		normal_direction[1] = intersect_p[1] - object_position[1];
		normal_direction[2] = intersect_p[2] - object_position[2];

		float magnitude_fraction2 = 1.0f / m3dGetVectorLength(normal_direction); //normalizing
		normal_direction[0] *= magnitude_fraction2;
		normal_direction[1] *= magnitude_fraction2;
		normal_direction[2] *= magnitude_fraction2;

		//calculating l.n
		float  l_dot_n = light_direction[0] * normal_direction[0] + light_direction[1] * normal_direction[1] + light_direction[2] * normal_direction[2];

		// 2 * (l.n) n
		normal_direction[0] *= 2.f * l_dot_n;
		normal_direction[1] *= 2.f * l_dot_n;
		normal_direction[2] *= 2.f * l_dot_n;

		// r = 2 * (l.n) n - l
		M3DVector3f reflected_direction;
		reflected_direction[0] = light_direction[0] - normal_direction[0];
		reflected_direction[1] = light_direction[1] - normal_direction[1];
		reflected_direction[2] = light_direction[2] - normal_direction[2];
	    

		//calculating v.r
		float v_dot_r = view_vector[0] * reflected_direction[0] + view_vector[1] * reflected_direction[1] + view_vector[2] * reflected_direction[2];		
		float specular_component = _ks * pow(v_dot_r > 0.f ? v_dot_r : 0.f, 150);
		return specular_component;

	}

	void shade(float ambient_component,float diffuse_component,float specular_component,M3DVector3f ambient_light,M3DVector3f object_color,M3DVector3f light_color, float & red, float& green, float& blue) {

		float ambient_color_red = ambient_component * object_color[0] * ambient_light[0];
		float diffuse_color_red = diffuse_component * object_color[0] * light_color[0];
		float specular_color_red = specular_component * light_color[0]; 

		float ambient_color_green = ambient_component * object_color[1] * ambient_light[1];
		float diffuse_color_green = diffuse_component * object_color[1] * light_color[1];
		float specular_color_green = specular_component * light_color[1]; 

		float ambient_color_blue = ambient_component * object_color[2] * ambient_light[2];
		float diffuse_color_blue = diffuse_component * object_color[2] * light_color[2];
		float specular_color_blue = specular_component * light_color[2]; 

		red = ambient_color_red + diffuse_color_red + specular_color_red;
		green = ambient_color_green + diffuse_color_green + specular_color_green;
		blue = ambient_color_blue + diffuse_color_blue + specular_color_blue;

	}

	float calculate_diffuse_component_triangle(float _kd, M3DVector3f intersect_p, M3DVector3f light_position, Triangle & tr) {

		//printf("\n\n\nStep 2");
		
		// calculating l =  light_position - intersect_p;
		M3DVector3f light_direction;
		light_direction[0] = light_position[0] - intersect_p[0];
		light_direction[1] = light_position[1] - intersect_p[1];
		light_direction[2] = light_position[2] - intersect_p[2];

		float magnitude_fraction = 1.0f / m3dGetVectorLength(light_direction); //normalizing
		light_direction[0] *= magnitude_fraction;
		light_direction[1] *= magnitude_fraction;
		light_direction[2] *= magnitude_fraction;


		M3DVector3f normal_direction;
		tr.normal(normal_direction);

		float  l_dot_n = light_direction[0] * normal_direction[0] + light_direction[1] * normal_direction[1] + light_direction[2] * normal_direction[2];

		float diffuse_component = _kd * (l_dot_n > 0.f ? l_dot_n : 0.f);
		return diffuse_component;
    }

	float calculate_specular_componenet_triangle(float _ks, M3DVector3f intersect_p, M3DVector3f light_position, Triangle& tr, M3DVector3f view_vector) {

		M3DVector3f light_direction;
		light_direction[0] = light_position[0] - intersect_p[0];
		light_direction[1] = light_position[1] - intersect_p[1];
		light_direction[2] = light_position[2] - intersect_p[2];

		float magnitude_fraction = 1.0f / m3dGetVectorLength(light_direction); //normalizing
		light_direction[0] *= magnitude_fraction;
		light_direction[1] *= magnitude_fraction;
		light_direction[2] *= magnitude_fraction;

		// calculating n
		M3DVector3f normal_direction;
		tr.normal(normal_direction);

		//calculating l.n
		float  l_dot_n = light_direction[0] * normal_direction[0] + light_direction[1] * normal_direction[1] + light_direction[2] * normal_direction[2];

		// 2 * (l.n) n
		normal_direction[0] *= 2.f * l_dot_n;
		normal_direction[1] *= 2.f * l_dot_n;
		normal_direction[2] *= 2.f * l_dot_n;

		// r = 2 * (l.n) n - l
		M3DVector3f reflected_direction;
		reflected_direction[0] = light_direction[0] - normal_direction[0];
		reflected_direction[1] = light_direction[1] - normal_direction[1];
		reflected_direction[2] = light_direction[2] - normal_direction[2];


		//calculating v.r
		float v_dot_r = view_vector[0] * reflected_direction[0] + view_vector[1] * reflected_direction[1] + view_vector[2] * reflected_direction[2];
		float specular_component = _ks * pow(v_dot_r > 0.f ? v_dot_r : 0.f, 150);
		return specular_component;

	}


};

