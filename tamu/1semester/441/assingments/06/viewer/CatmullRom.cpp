#include "CatmullRom.h"

ControlPoint CatmullRom::reflectControlPoints (ControlPoint a, ControlPoint b)
{
	ControlPoint c;
	for (unsigned int i = 0; i < MAX_BONES_IN_ASF_FILE; i++)
	{
		c.posture.bone_length[i] = a.posture.bone_length[i] * a.posture.bone_length[i] - b.posture.bone_length[i]; // aren't they the same? anyways...
		c.posture.bone_rotation[i] = a.posture.bone_rotation[i] * a.posture.bone_rotation[i] - b.posture.bone_rotation[i];
		c.posture.bone_translation[i] = a.posture.bone_translation[i] * a.posture.bone_translation[i] - b.posture.bone_translation[i];
	}
	c.frame = 2 * a.frame - b.frame;
	return c;
}