// �ΰ����� ��ü �������̽�
// �ΰ������� �����Ϸ��� ��ü�� �� �������̽��� ��ӹ޾ƾ� �Ѵ�.
#pragma once


namespace ai
{

	class IArtificialIntelligence
	{
	public:
		IArtificialIntelligence();
		virtual ~IArtificialIntelligence();

		void PushAction(cAction *action);

		virtual Matrix44& GetTransform()=0;
		virtual void SetAnimation(const string &animationName) = 0;
	};

}
