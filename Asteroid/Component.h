#pragma once

#include <cstdint>

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

	// ������Ʈ�� ���� ���μ��� �Է�
	virtual void ProcessInput(const uint8_t* keyState) {}

	// ����
	int GetUpdateOrder() const { return _updateOrder; }

protected:
	// ������ ����
	class Actor* _owner;

	// ������Ʈ�� ������Ʈ ����
	int _updateOrder;
};

