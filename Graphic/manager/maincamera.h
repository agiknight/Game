// ���� ī�޶� Ŭ����.
//

#pragma once


namespace graphic
{

	class cMainCamera : public cCamera
									, public common::cSingleton<cMainCamera>
	{
	public:
		cMainCamera();
		virtual ~cMainCamera();

	};

}
