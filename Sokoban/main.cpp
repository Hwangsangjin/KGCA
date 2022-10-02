#include "GameLib/Framework.h"
#include "State.h"
#include "File.h"

using namespace GameLib;
using namespace std;

// 함수 프로토 타입
void MainLoop();

// 전역 변수
State* gState = nullptr;
bool gPrevInputA = false;
bool gPrevInputD = false;
bool gPrevInputW = false;
bool gPrevInputS = false;

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
	Framework f = Framework::instance();

	// 프레임 초기화
	if (!gState)
	{
		File file("../../../Resource/Sokoban/StageData.txt");
		if (!(file.GetData()))
		{
			// 데이터 없음
			cout << "Stage file could not be read." << endl;
		}

		gState = new State(file.GetData(), file.GetSize());
	}

	// 클리어 확인
	bool cleared = false;

	if (gState->IsCleared())
	{
		cleared = true;
	}

	// 입력
	int dx = 0;
	int dy = 0;
	bool inputA = f.isKeyOn('a');
	bool inputD = f.isKeyOn('d');
	bool inputW = f.isKeyOn('w');
	bool inputS = f.isKeyOn('s');

	if (inputA && (!gPrevInputA))
	{
		dx -= 1;
	}
	else if (inputD && (!gPrevInputD))
	{
		dx += 1;
	}
	else if (inputW && (!gPrevInputW))
	{
		dy -= 1;
	}
	else if (inputS && (!gPrevInputS))
	{
		dy += 1;
	}

	gPrevInputA = inputA;
	gPrevInputD = inputD;
	gPrevInputW = inputW;
	gPrevInputS = inputS;

	// 업데이트
	gState->Update(dx, dy);

	// 렌더
	gState->Draw();

	// 종료 버튼이 눌린 경우
	if (f.isKeyOn('q'))
	{
		f.requestEnd();
	}

	if (f.isEndRequested())
	{
		if (gState)
		{
			delete gState;
			gState = nullptr;
		}
	}
}
