#include "StudentManager.h"

using namespace std;

int main()
{
	// �л� ���� �Ŵ����� �����ϰ� ����
	auto& studentmanager = *StudentManager::create();
	studentmanager.run();

	return 0;
}