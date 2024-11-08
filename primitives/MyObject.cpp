#include "MyObject.h"
#include "../util/RayTracingUtil.cpp"
#include "Triangle.h"
#include <fstream>

using namespace std;

Intersect_Cond  TriangleMesh::intersection_check(const M3DVector3f start, const M3DVector3f dir, float& distance, M3DVector3f intersection_p) {
	Intersect_Cond intersected_flag = _k_miss;
	distance = 9999999999999.f;	
	for (auto& triangle : triangles) {
		float d = 0.f;
		if (triangle.intersection_check(start, dir, d, intersection_p) == _k_hit && d < distance) {
			distance = d;
			intersected_flag = _k_hit;			
			it_tr = &triangle;
		}
	}
	return intersected_flag;
}

void TriangleMesh::shade(M3DVector3f view, M3DVector3f intersect_p, const Light& sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow) {

	RayTracingUtil* rt_util = new RayTracingUtil();
	M3DVector3f light_position, light_color;
	M3DVector3f object_color;
	sp_light.get_light(light_position, light_color);
	memcpy(object_color, _color, sizeof(M3DVector3f));	
	//Ambient Component
	float ambient_component = _ka;
	//Diffuse Component
	float diffuse_component = rt_util->calculate_diffuse_component_triangle(_kd, intersect_p, light_position, *it_tr);
	//Specular Component
	float specular_component = rt_util->calculate_specular_componenet_triangle(_ks, intersect_p, light_position, *it_tr, view);

	int red = 0;
	int green = 1;
	int blue = 2;

	rt_util->shade(ambient_component, diffuse_component, specular_component, am_light, object_color, light_color, color[red], color[green], color[blue]);
	
}



// f 1/1/1 2/2/1 3/3/1    A face containing a position, texture coordinate and normal
// f 1//1 2//1 3//1  A face containing a position, and a normal
// f 1/1 2/1 3/1    A face containing a position, and a texture coordinate
// f 1 2 3         A face containing only a position
// For ref : https://www.youtube.com/watch?v=KMWUjNE0fYI

void TriangleMesh::load_object()
{
	struct Vertex { 
		float x_point;
		float y_point;
		float z_point;
	};
	struct Face {
		int v1_index;
		int v2_index;
		int v3_index;
	};
	vector<Vertex> vertices;
	vector<Face> faces;

	ifstream file(_object_path.c_str());
	if (!file){ printf("Error Opening File: %s\n", _object_path.c_str()); exit(0);}

	string line;
	while (getline(file, line))
	{
		// read the each vertex coordinates in vertex structure object
		Vertex vertex;
		if (sscanf(line.c_str(), "v %f %f %f", &vertex.x_point, &vertex.y_point, &vertex.z_point) == 3)
		{			
			vertices.push_back(vertex);
		}
		// Read the face and form a triangle from vertex indices
		Face face;
		if (sscanf(line.c_str(), "f %d %d %d", &face.v1_index, &face.v2_index, &face.v3_index) == 3)
		{			
			faces.push_back(face);

			M3DVector3f triangle_vertex_1, triangle_vertex_2, triangle_vertex_3;
			
			triangle_vertex_1[0] = vertices[face.v1_index - 1].x_point;
			triangle_vertex_1[1] = vertices[face.v1_index - 1].y_point;
			triangle_vertex_1[2] = vertices[face.v1_index - 1].z_point;

			triangle_vertex_2[0] = vertices[face.v2_index - 1].x_point;
			triangle_vertex_2[1] = vertices[face.v2_index - 1].y_point;
			triangle_vertex_2[2] = vertices[face.v2_index - 1].z_point;

			triangle_vertex_3[0] = vertices[face.v3_index - 1].x_point;
			triangle_vertex_3[1] = vertices[face.v3_index - 1].y_point;
			triangle_vertex_3[2] = vertices[face.v3_index - 1].z_point;
			
			triangles.push_back({ triangle_vertex_1, triangle_vertex_2, triangle_vertex_3 });
		}
	}
}





void TriangleMesh::transform_object(M3DMatrix44f transform_matrix)
{
	//Transform all triangles
	for (auto& triangle : triangles)
	{
		M3DVector3f current_vertex1, current_vertex2, current_vertex3;

		triangle.get_vertex(current_vertex1, current_vertex2, current_vertex3);

		M3DVector3f transformed_vertex_1, transformed_vertex_2, transformed_vertex_3;

		m3dTransformVector3(transformed_vertex_1, current_vertex1, transform_matrix);
		m3dTransformVector3(transformed_vertex_2, current_vertex2, transform_matrix);
		m3dTransformVector3(transformed_vertex_3, current_vertex3, transform_matrix);

		triangle = Triangle(transformed_vertex_1,transformed_vertex_2,transformed_vertex_3); 
			
	}

}