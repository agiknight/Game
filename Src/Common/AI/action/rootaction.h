// ��Ʈ �׼�.
#pragma once

#include "action.h"


namespace ai
{

	class cRootAction : public cAction
	{
	public:
		cRootAction(cObject *obj)
			: cAction(obj, "Root", ACTION_TYPE::ROOT)
		{
		}
	};

}
