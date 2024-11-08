#pragma once
#include "Basic_Primitive.h"
#include "Triangle.h"
#include <vector>
#include <string>
using namespace std;



class TriangleMesh :public Basic_Primitive {


public:
	TriangleMesh(string object_path) : Basic_Primitive(_k_my_object), it_tr(nullptr)
	{
		_color[0] = 0.2;
		_color[1] = 1.0;
		_color[2] = 0.9;

		_object_path = object_path;

		_ka = 0.2;
		_kd = 0.6;
		_ks = 0.2;


		_ks2 = _ks;
		_kt = 0.0;
		_ws = 0.0;
		_wt = 0.0;	//No Refraction

	}

public:
	Intersect_Cond	intersection_check(const M3DVector3f start, const M3DVector3f dir, float& distance, M3DVector3f intersection_p);
	void	shade(M3DVector3f view, M3DVector3f intersect_p, const Light& sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow);	
	void    set_object_color(M3DVector3f color) {_color[0] = color[0];	_color[1] = color[1];_color[2] = color[2];}
	void	get_reflect_direct(const M3DVector3f direct, const M3DVector3f intersect_p, M3DVector3f reflect_direct) {}
	void	get_properties(float& ks, float& kt, float& ws, float& wt) const { ks = _ks2; kt = _kt; ws = _ws; wt = _wt; }	
	void load_object();
	void transform_object(M3DMatrix44f matrix);

private:
	vector<Triangle> triangles; // array of triangles
	Triangle* it_tr;
	M3DVector3f _color;
	string _object_path;

	float		_kd;
	float		_ks;
	float		_ka;

	float		_ks2;
	float		_kt;
	float		_ws;
	float		_wt;


};