#pragma once


namespace graphic
{

	class cCharacter : public cModel
	{
	public:
		cCharacter(const int id);
		virtual ~cCharacter();

		bool Create(const string &modelName);
		void LoadWeapon(const string &fileName);
		virtual bool Move(const float elapseTime) override;
		virtual void Render(const Matrix44 &tm) override;

		// debug �� �Լ�.
		void SetRenderWeaponBoundingBox(const bool isRenderBoundingBox);


	private:
		cModel *m_weapon;
		cBoneNode *m_weaponNode1; // reference
		cBoneNode *m_weaponNode2; // reference
		cBoneNode *m_weaponBoneNode1; // reference
		cBoneNode *m_weaponBoneNode2; // reference
	};

}
