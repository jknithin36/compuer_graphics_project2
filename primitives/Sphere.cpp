#include "Sphere.h"
#include "../Imageio/Imageio.h"
#include <math.h>
#include "../util/RayTracingUtil.cpp"

Intersect_Cond	Sphere::intersection_check(const M3DVector3f start, const M3DVector3f dir, float & distance, M3DVector3f intersection_p)
{
	M3DVector3f ray_to_center;
	m3dSubtractVectors3(ray_to_center,_pos,start);
	float ray_center_length = m3dDotProduct(ray_to_center, ray_to_center); 

	float closest_point = m3dDotProduct( ray_to_center, dir);
	if (closest_point < 0) 
	{
		return _k_miss;
	}

	float halfCord2 = (_rad * _rad) - (ray_center_length - (closest_point * closest_point));   
	if(halfCord2 < 0) 
	{
		return _k_miss;
	}

	Intersect_Cond type;
	M3DVector3f tmp;
	m3dSubtractVectors3(tmp,start,_pos);
	float length = m3dDotProduct(tmp,tmp);
	if (length < _rad2)
	{
		type = _k_inside;
		distance = closest_point + sqrt(halfCord2);
	}else
	{
		type = _k_hit;
		distance = closest_point - sqrt(halfCord2);
	}

	M3DVector3f tmp_v;
	m3dCopyVector3(tmp_v, dir);
	m3dScaleVector3(tmp_v,distance);
	m3dAddVectors3(intersection_p,start,tmp_v);

	return type;
}

void	Sphere::shade(M3DVector3f view,M3DVector3f intersect_p,const Light & sp_light, M3DVector3f am_light, M3DVector3f color, bool shadow)
{

	RayTracingUtil* rt_util = new RayTracingUtil();
	M3DVector3f light_position, light_color;
	M3DVector3f object_position, object_color;
	sp_light.get_light(light_position, light_color);
	memcpy(object_position, _pos, sizeof(M3DVector3f));
	memcpy(object_color, _color, sizeof(M3DVector3f));
	

	//Ambient Component	
	float ambient_component = _ka;
	//Diffuse Component	 
	float diffuse_component = rt_util -> calculate_diffuse_component_sphere(_kd,intersect_p,light_position,object_position);
	//Specular Component
	float specular_component = rt_util->calculate_specular_componenet_sphere(_ks, intersect_p, light_position, object_position, view);

	int red = 0;
	int green = 1;
	int blue = 2;
	
	rt_util->shade(ambient_component,diffuse_component,specular_component,am_light,object_color,light_color, color[red],color[green],color[blue]);

}
