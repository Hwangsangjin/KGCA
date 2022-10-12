#pragma once

class AIState
{
public:
	AIState(class AIComponent* owner)
		: _owner(owner)
	{}

	// �� ������ ��ü���� �ൿ
	virtual void Update(float deltaTime) abstract;
	virtual void OnEnter() abstract;
	virtual void OnExit() abstract;

	// ������ �̸� ���
	virtual const char* GetName() const abstract;

protected:
	class AIComponent* _owner;
};

class AIPatrol : public AIState
{
public:
	AIPatrol(class AIComponent* owner)
		: AIState(owner)
	{}

	// �� ���¿� ���� ������ ������
	virtual void Update(float deltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual const char* GetName() const override
	{
		return "Patrol";
	}
};

class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner)
		: AIState(owner)
	{}

	virtual void Update(float deltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual const char* GetName() const override
	{
		return "Death";
	}
};

class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* owner)
		: AIState(owner)
	{}

	virtual void Update(float deltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual const char* GetName() const override
	{
		return "Attack";
	}
};