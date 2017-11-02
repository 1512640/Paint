#pragma once

#include "resource.h"
struct diem
{
	int x; 
	int y;
};

COLORREF ShowColorDialog(HWND hwnd);
COLORREF mau_ve = RGB(0, 0, 0);
diem bat_Dau, ket_Thuc;
HDC	hdc_ao;
HBITMAP	bitmap_ao;


int so_Luong_phanTu = 0;
int kich_thuoc_but = 1;
bool co = false;
bool shift = false;
bool chuot_trai = false;
bool ve_Tam = false;
bool hcn = false;
HDC hdc;