// ĳ���� �м��� Ŭ����
// ���� ����ϰ�, ������ �� �ִ� ����� ����.
#pragma once


namespace graphic
{

	class cCharacterAnalyzer : public cCharacter
	{
	public:
		cCharacterAnalyzer(const int id);
		virtual ~cCharacterAnalyzer();

		bool Create(const string &modelName);

		virtual bool Move(const float elapseTime) override;
		virtual void Render(const Matrix44 &tm) override;

		void HighlightBone(const string &boneName);


	private:
		cCube m_selectBoneCube;
		cBoneNode *m_selectBone;
	};

}
