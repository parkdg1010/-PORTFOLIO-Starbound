#include "stdafx.h"
#include "saveData.h"
#include "player.h"

HRESULT saveData::init()
{
	return S_OK;
}

void saveData::release()
{
	_saveHandle = CreateFile("SAVE/save.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	//_stprintf_s(_data, "%f", _hp);
	WriteFile(_saveHandle, _T(_data), sizeof(float), &_result, NULL);
}
