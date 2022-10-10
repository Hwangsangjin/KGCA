#pragma once

#include <vector>
#include "Math.h"

class Actor
{
public:
	// 액터의 상태를 추적하는데 사용된다.
	enum State
	{
		Active,
		Paused,
		Dead
	};

	// 생성자
	Actor(class Game* game);
	// 소멸자
	virtual ~Actor();

	// Game에서 호출하는 Update 함수 (가상 함수 아님)
	void Update(float deltaTime);
	// 액터에 부착된 모든 컴포넌트를 업데이트 (가상 함수 아님)
	void UpdateComponents(float deltaTime);
	// 특정 액터에 특화된 업데이트 코드 (오버라이딩 가능)
	virtual void UpdateActor(float deltaTime);

	// Game이 호출하는 ProcessInput 함수 (재정의되지 않음)
	void ProcessInput(const uint8_t* keyState);
	// 특정 액터를 위한 입력 코드 (재정의 됨)
	virtual void ActorInput(const uint8_t* keyState);

	// 게터와 세터
	const Vector2& GetPosition() const { return _position; }
	void SetPosition(const Vector2& position) { _position = position; }
	float GetScale() const { return _scale; }
	void SetScale(float scale) { _scale = scale; }
	float GetRotation() const { return _rotation; }
	void SetRotation(float rotation) { _rotation = rotation; }

	Vector2 GetForward() const { return Vector2(Math::Cos(_rotation), -Math::Sin(_rotation)); }

	State GetState() const { return _state; }
	void SetState(State state) { _state = state; }

	class Game* GetGame() { return _game; }

	// 컴포넌트 추가, 제거
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// 액터의 상태
	State _state;

	// 변환
	Vector2 _position;	// 액터의 중심점
	float _scale;		// 액터의 배율 (100%의 경우 1.0f)
	float _rotation;	// 회전 각도 (라디안)

	// 이 액터가 보유한 컴포넌트들
	std::vector<class Component*> _components;
	class Game* _game;
};

