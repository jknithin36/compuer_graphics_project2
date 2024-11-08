#include "../scene/Light.h"
#include "../primitives/Triangle.h"
#include "../primitives/MyObject.h"
#include <stdio.h>
#include <fstream>
#include <vector>



using namespace std;

class SceneUtil {

public:
	void set_scene_lighting(Light& _sp_light, M3DVector3f& _amb_light, M3DVector3f _dim) {

		float amb_lt_red = 1.0;
		float amb_lt_green = 1.0;
		float amb_lt_blue = 1.0;

		float point_lt_red = 1.0;
		float point_lt_green = 1.0;
		float point_lt_blue = 1.0;

		float point_lt_pos_x = 480.0f;  
		float point_lt_pos_y = 480.0f; 
		float point_lt_pos_z = 400.0f;  


		_amb_light[0] = amb_lt_red;
		_amb_light[1] = amb_lt_green;
		_amb_light[2] = amb_lt_blue;

		M3DVector3f point_light_position, point_light_color;
		point_light_position[0] = point_lt_pos_x;
		point_light_position[1] = point_lt_pos_y;
		point_light_position[2] = point_lt_pos_z;


		point_light_color[0] = point_lt_red;
		point_light_color[1] = point_lt_green;
		point_light_color[2] = point_lt_blue;

		_sp_light.set_light(point_light_position, point_light_color);

	}
	void transform_object(TriangleMesh & object) {

		M3DMatrix44f identity_matrix,scaled_matrix,rotated_amtrix,translated_matrix;
		m3dLoadIdentity44(identity_matrix);

		m3dScaleMatrix44(identity_matrix, 103, 103,  77);		
		object.transform_object(identity_matrix);
		memcpy(scaled_matrix, identity_matrix, sizeof(M3DMatrix44f));

		m3dRotationMatrix44(scaled_matrix, 0.25, 0, 1, 0);
		object.transform_object(scaled_matrix);
		memcpy(rotated_amtrix, scaled_matrix, sizeof(M3DMatrix44f));

		m3dTranslationMatrix44(rotated_amtrix, 155, 144, 256);
		object.transform_object(rotated_amtrix);
		memcpy(translated_matrix, rotated_amtrix, sizeof(M3DMatrix44f));
	}




};