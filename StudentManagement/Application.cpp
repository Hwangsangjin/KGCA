#include "StudentManager.h"

using namespace std;

int main()
{
	// �л� ���� �Ŵ����� �����ϰ� ����
	auto& studentManager = *StudentManager::Instance();
	studentManager.Run();

	return 0;
}