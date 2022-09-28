#include "GameLib/Framework.h"
#include "State.h"
#include "File.h"

using namespace GameLib;
using namespace std;

// 함수 프로토 타입
void MainLoop();

// 전역 변수
State* gState = nullptr;

// 사용자 구현 기능, 내용은 메인 루프로 전달
namespace GameLib
{
	void Framework::update()
	{
		MainLoop();
	}
}

// 메인 루프
void MainLoop()
{
	// 종료 버튼이 눌린 경우
	if (Framework::instance().isEndRequested())
	{
		if (gState)
		{
			delete gState;
			gState = nullptr;
		}
	}

	// 프레임 초기화
	if (!gState)
	{
		File file("StageData.txt");
		if (!(file.GetData()))
		{
			// 데이터 없음
			cout << "Stage file could not be read." << endl;
		}

		gState = new State(file.GetData(), file.GetSize());

		// 렌더
		gState->Draw();
	}

	// 클리어 확인
	bool cleared = false;

	if (gState->IsCleared())
	{
		cleared = true;
	}

	// 입력
	cout << "a:left d:right w:up s:down. command?" << endl; // 작동 설명
	char input;
	cin >> input;

	// 종료키 선택
	if (input == 'q')
	{
		delete gState;
		gState = nullptr;
		Framework::instance().requestEnd();
	}

	// 갱신
	gState->Update(input);

	// 렌더
	gState->Draw();

	if (cleared)
	{
		// 축하 메시지
		cout << "Congratulation! you win." << endl;

		// 메모리 해제
		delete gState;
		gState = nullptr;
	}
}


