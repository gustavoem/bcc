#include "CatmullRom.h"

Posture CatmullRom::reflectPosture (Posture a, Posture b)
{
	Posture c;
	for (unsigned int i = 0; i < MAX_BONES_IN_ASF_FILE; i++)
	{
		c.bone_length[i] = a.bone_length[i] * a.bone_length[i] - b.bone_length[i]; // aren't they the same? anyways...
		c.bone_rotation[i] = a.bone_rotation[i] * a.bone_rotation[i] - b.bone_rotation[i];
		c.bone_translation[i] = a.bone_translation[i] * a.bone_translation[i] - b.bone_translation[i];
	}
	c.root_pos = a.root_pos + a.root_pos - b.root_pos;
	return c;
}