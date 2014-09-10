// ����ü Ŭ����.
#pragma once


namespace graphic
{


	class cFrustum
	{
	public:
		cFrustum();
		virtual ~cFrustum();

		bool Create( const Matrix44 &matViewProj );
		bool IsIn( const Vector3 &point );
		bool IsInSphere( const Vector3 &point, float radius );
		void Render();
		const Vector3& GetPos() const;


	private:
		Vector3 m_Vtx[ 8]; // frustum ���� ��ǥ
		Plane m_Plane[ 6];	// frustum�� 6�� ���
		Vector3 m_vPos; // ����ü ��ġ
	};


	const Vector3& cFrustum::GetPos() const { return m_vPos; }
}
