#include "StudentManager.h"

using namespace std;

int main()
{
	// �л� ���� �Ŵ����� �����ϰ� ����
	auto& sm = *StudentManager::create();
	sm.run();

	return 0;
}