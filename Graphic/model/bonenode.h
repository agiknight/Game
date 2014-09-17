#pragma once


namespace graphic
{

	class cBoneNode : public cNode
	{
	public:
		cBoneNode(const int id, vector<Matrix44> &palette, const sRawBone &rawMesh);
		virtual ~cBoneNode();

		void SetAnimation( const sRawAni &rawAni, const int totalAniFrame, const bool isLoop=false );
		void SetAnimation( const sRawBone &rawBone, const sRawAni &rawAni, const int totalAniFrame, const bool isLoop=false );
		void SetAccTM(const Matrix44 &mat);
		const Matrix44& GetAccTM() const;
		const Matrix44& GetOffset() const;
		Matrix44 GetCalculateAniTM() const;
		void SetOffset(const Matrix44 &mat);

		virtual bool Move(const float elapseTime) override;
		virtual void Render(const Matrix44 &parentTm) override;

		int GetCurrentFrame() const;
		int GetPlayFrame() const;
		void SetCurrentFrame(const int curFrame);
		void UpdateAccTM();
		void SetAnimationOption(DWORD option);
		cMesh* GetMesh();


	private:
		cTrack *m_track;
		vector<Matrix44> &m_palette;
		Matrix44 m_accTM;	// ������ TM
		Matrix44 m_offset;	// inverse( m_matWorld )
		int m_aniStart; // ������ ���۽ð� (������)
		int m_aniEnd; // ������ ����ð� (������)
		int m_totalPlayFrame; // �� ���ϸ��̼� �� ������

		int m_curPlayFrame; // ���� ���ϸ��̼� ������ (AniEnd�� ������ 0���� �ʱ�ȭ�ȴ�.)
		int m_incPlayFrame; // ���ϸ��̼� ���� �� ������
		float m_curPlayTime; // ���� �ִϸ��̼� �ð� (m_aniEnd �� �����ϸ� 0 �� �ȴ�.)
		float m_incPlayTime; // ���� �ִϸ��̼� �ð� (�� �ð�)

		bool m_isAni; // TRUE�ϰ�츸 ���ϸ��̼��� �ȴ�.
		bool m_isLoop; // ���ϸ��̼� �ݺ� ����
		DWORD m_option; // 0x01 = �ִϸ��̼ǿ��� �̵� ������ �����Ѵ�.

		// debug ��.
		cMesh *m_mesh;
	};


	inline void cBoneNode::SetAccTM(const Matrix44& mat) { m_accTM = mat; }
	inline const Matrix44& cBoneNode::GetAccTM() const { return m_accTM; }
	inline const Matrix44& cBoneNode::GetOffset() const { return m_offset; }
	inline void cBoneNode::SetOffset(const Matrix44 &mat) { m_offset = mat; }
	inline int cBoneNode::GetCurrentFrame() const { return m_curPlayFrame; }
	inline int cBoneNode::GetPlayFrame() const { return m_incPlayFrame; }
	inline void cBoneNode::SetAnimationOption(DWORD option) { m_option = option; }
	inline cMesh* cBoneNode::GetMesh() { return m_mesh; }
}
