#pragma once
//=============================================================
//	## commonMacroFunction ## (�ʿ��� �κ��� ���� ���� �߰��Ұ�)
//=============================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//�� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT �߽����� �����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width *0.5, y - height *0.5, x + width *0.5, y + height *0.5 };
	return rc;
}

//���ʱ��Լ� �̿��ؼ� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - width * 0.5, y - height * 0.5, x + width * 0.5, y + height * 0.5);
}

inline void Rectangle(HDC hdc, RECT _rc)
{
	Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

//�ϸ����Լ� �̿��ؼ� �׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//�ϸ����Լ� �̿��ؼ� ������ �߽����� �׸���
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//�ϸ����Լ� �����ε�
inline void Ellipse(HDC hdc, RECT _rc)
{
	Ellipse(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

//ADDED
//�簢���� �׸���
inline void RectangleLine(HDC hdc, RECT _rc, COLORREF color = RGB(0, 0, 0))
{
	HPEN myPen, oldPen;
	myPen = CreatePen(PS_SOLID, 1, color);
	oldPen = (HPEN)SelectObject(hdc, myPen);

	MoveToEx(hdc, _rc.left, _rc.top, NULL);
	LineTo(hdc, _rc.left, _rc.bottom);
	LineTo(hdc, _rc.right, _rc.bottom);
	LineTo(hdc, _rc.right, _rc.top);
	LineTo(hdc, _rc.left, _rc.top);

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
	DeleteObject(oldPen);
}

inline void RectangleLine(HDC hdc, LONG left, LONG top, LONG right, LONG bottom, COLORREF color = RGB(0, 0, 0))
{
	HPEN myPen, oldPen;
	myPen = CreatePen(PS_SOLID, 1, color);
	oldPen = (HPEN)SelectObject(hdc, myPen);

	MoveToEx(hdc, left, top, NULL);
	LineTo(hdc, left, bottom);
	LineTo(hdc, right, bottom);
	LineTo(hdc, right, top);
	LineTo(hdc, left, top);

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
	DeleteObject(oldPen);
}

