#pragma once

class Component
{
public:
	// ������
	// (������Ʈ �������� �������� ������Ʈ�� �� ���� ���ŵȴ�.)
	Component(class Actor* owner, int updateOrder = 100);

	// �Ҹ���
	virtual ~Component();

	// ��Ÿ �ð����� �� ������Ʈ�� ������Ʈ
	virtual void Update(float deltaTime);

	// ����
	int GetUpdateOrder() const { return _updateOrder; }

protected:
	// ������ ����
	class Actor* _owner;

	// ������Ʈ�� ������Ʈ ����
	int _updateOrder;
};

