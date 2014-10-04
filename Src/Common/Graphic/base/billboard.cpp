
#include "stdafx.h"
#include "billboard.h"


using namespace graphic;


cBillboard::cBillboard()
{
}

cBillboard::~cBillboard()
{
}


// ������ �ʱ�ȭ.
bool cBillboard::Create( const BILLBOARD_TYPE::TYPE type, 
	const float width, const float height, 
	const Vector3 &pos, const string &textureFileName )
{
	if (!__super::Create(width, height, pos, textureFileName))
		return false;

	m_type = type;
	return true;
}


// ȭ�鿡 ���.
void cBillboard::Render()
{
	Matrix44 mat;
	switch (m_type)
	{
	case BILLBOARD_TYPE::Y_AXIS:
		// Y�� ������ ����� ����Ѵ�.
		mat._11 = cMainCamera::Get()->GetViewMatrix()._11;
		mat._13 = cMainCamera::Get()->GetViewMatrix()._13;
		mat._31 = cMainCamera::Get()->GetViewMatrix()._31;
		mat._33 = cMainCamera::Get()->GetViewMatrix()._33;
		break;

	case BILLBOARD_TYPE::ALL_AXIS:
		// ��� �࿡�� ������ ����� ����Ѵ�.
		mat = cMainCamera::Get()->GetViewMatrix();
		mat._41 = mat._42 = mat._43 = 0;
		break;
	}

	Matrix44 T;
	T.SetTranslate(GetTransform().GetPosition());
	SetTransform(mat.Transpose() * T);
	__super::Render();
}
