#include "Wall.h"
#include <math.h>
#include "../Imageio/Imageio.h"
#include "../util/RayTracingUtil.cpp"

Intersect_Cond Wall::intersection_check(const M3DVector3f start, const M3DVector3f dir, float &distance, M3DVector3f intersection_p)
{
	if (_tr1.intersection_check(start,dir,distance,intersection_p) == _k_hit)
	{
		return _k_hit;
	}else
	{
		return _tr2.intersection_check(start,dir,distance,intersection_p);
	}
}


void	Wall::shade(M3DVector3f view, M3DVector3f intersect_p,const Light & sp_light, M3DVector3f am_light, M3DVector3f color,bool shadow)
{

	RayTracingUtil* rt_util = new RayTracingUtil();
	M3DVector3f light_position, light_color;
	M3DVector3f object_position, object_color;
	sp_light.get_light(light_position, light_color);	
	memcpy(object_color, _color, sizeof(M3DVector3f));


	//Ambient Component	
	float ambient_component = _ka;
	//Diffuse Component	 
	float diffuse_component = rt_util->calculate_diffuse_component_triangle(_kd, intersect_p, light_position, _tr1);
	//Specular Component
	float specular_component = rt_util->calculate_specular_componenet_triangle(_ks, intersect_p, light_position, _tr1, view);

	int red = 0;
	int green = 1;
	int blue = 2;

	rt_util->shade(ambient_component, diffuse_component, specular_component, am_light, object_color, light_color, color[red], color[green], color[blue]);

}


void	Wall::get_reflect_direct(const M3DVector3f direct0,const M3DVector3f intersect_p, M3DVector3f reflect_direct)
{
	
}


void Wall::load_texture(std::string file_name)
{
	
}

void Wall::texture_color(M3DVector3f pos, M3DVector3f color)
{
}

void	Wall::get_texel(float x, float y, M3DVector3f color)
{
	return;
}