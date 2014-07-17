#pragma once


namespace graphic
{

	namespace RESOURCE_TYPE {
		enum TYPE {
			NONE,
			MESH,
			ANIMATION,
		};
	};


	// ���ڽ� min max ��.
	struct sMinMax
	{
		Vector3 Min;
		Vector3 Max;
		sMinMax() : Min(Vector3(0,0,0)), Max(Vector3(0,0,0)) {}
	};


}
