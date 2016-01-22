#include "CatmullRom.h"

// not used...
ControlPoint CatmullRom::reflectControlPoints (ControlPoint a, ControlPoint b)
{
	ControlPoint c;
	for (unsigned int i = 0; i < MAX_BONES_IN_ASF_FILE; i++)
	{
		c.posture.bone_length[i] = a.posture.bone_length[i] * a.posture.bone_length[i] - b.posture.bone_length[i]; // aren't they the same? anyways...
		c.posture.bone_rotation[i] = a.posture.bone_rotation[i] * a.posture.bone_rotation[i] - b.posture.bone_rotation[i];
		c.posture.bone_translation[i] = a.posture.bone_translation[i] * a.posture.bone_translation[i] - b.posture.bone_translation[i];
	}
	c.posture.root_pos = a.posture.root_pos + a.posture.root_pos - b.posture.root_pos;
	c.frame = 2 * a.frame - b.frame;
	return c;
}


// Performs the CatmullRom interpolation of two control points
//
Posture CatmullRom::interpolate (ControlPoint p0, ControlPoint p1, ControlPoint p2, ControlPoint p3, unsigned int frame)
{
	// The CatmullRom interpolation works is described as:
	//	Q(t) = [t^3 t^2 t 1] * C * p 
	//	Where C is the CatmullRom matrix that guarantees that:
	//  Q(0) = p_1
	//  Q(1) = p_2
	//	Q'(0) = tau * (p2 - p0)
	//  Q'(1) = tau * (p3 - p1)
	//  p = [p0, p1, p2, p3] and t = (frame - p1.frame) / (p2.frame - p1.frame)
	Posture final_posture;
	if (p1.frame == p2.frame)
	{
		cout << "Attempt to interpolate same frames detected" << endl;
		return p1.posture;
	}

	float t = (float)(frame - p1.frame) / (p2.frame - p1.frame);
	

	// First interpolate the root position
	for (unsigned int i = 0; i < 3; i++)
	{
		float answ = interpolate_values (p0.posture.root_pos[i], p1.posture.root_pos[i],
										 p2.posture.root_pos[i], p3.posture.root_pos[i],
										 t);
		final_posture.root_pos[i] = answ;
	}

	// Then interpolate bones rotation and translation
	for (unsigned int i = 0; i < MAX_BONES_IN_ASF_FILE; i++)
	{
		for (unsigned int k = 0; k < 3; k++)
		{
			float answ = interpolate_values (p0.posture.bone_length[i].p[k], p1.posture.bone_length[i].p[k],
											 p2.posture.bone_length[i].p[k], p3.posture.bone_length[i].p[k],
											 t);
			final_posture.bone_length[i].p[k] = answ;

			answ = interpolate_values (p0.posture.bone_rotation[i].p[k], p1.posture.bone_rotation[i].p[k],
											 p2.posture.bone_rotation[i].p[k], p3.posture.bone_rotation[i].p[k],
											 t);
			final_posture.bone_rotation[i].p[k] = answ;

			answ = interpolate_values (p0.posture.bone_translation[i].p[k], p1.posture.bone_translation[i].p[k],
											 p2.posture.bone_translation[i].p[k], p3.posture.bone_translation[i].p[k],
											 t);
			final_posture.bone_translation[i].p[k] = answ;
		}
	}
	return final_posture;
}



float CatmullRom::interpolate_values (float p0, float p1, float p2, float p3, float t)
{
	float v_t[4] = {t* t * t, t * t, t, 1};
	float * C_p = calculate_Cp (p0, p1, p2, p3);
	
	float answ = 0;
	for (unsigned int i = 0; i < 4; i++)
		answ += v_t[i] * C_p[i];
	
	return answ;
}


float * CatmullRom::calculate_Cp (float p0, float p1, float p2, float p3)
{
	float tau = 0.5;
	float C[4][4] = {  - tau, 2 - tau,     tau - 2,   tau,
					 2 * tau, tau - 3, 3 - 2 * tau, - tau,
					    -tau,       0,         tau,     0,
					       0,       1,          0,      0};
	
	float p[] = {p0, p1, p2, p3};
	float * answ = new float[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		float x = 0;
		for (unsigned int j = 0; j < 4; j++)
		{
			x += C[i][j] * p[j];
		}
		answ[i] = x;
	}
	return answ;
}