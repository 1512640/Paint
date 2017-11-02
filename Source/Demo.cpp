// Demo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Demo.h"
#define MAX_LOADSTRING 100
HINSTANCE hInst;    


WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Khai báo

void tinh_toan_hv_elip(diem&, diem&);


class hinh
{
public:
	diem diem_bat_dau;
	diem diem_ket_thuc;
	COLORREF mau_but_ve; 
	virtual void ve(HDC hdc) = 0;
	virtual hinh* khoi_tao(diem bat_dau, diem ket_thuc) = 0;
	virtual void mau_but(COLORREF mau) = 0;
	hinh() {};
};
class duong_thang :public hinh
{
public:
	void mau_but(COLORREF mau)
	{
		mau_but_ve = mau;
	}
	void ve(HDC hdc)
	{
		MoveToEx(hdc,diem_bat_dau.x, diem_bat_dau.y, NULL);
		LineTo(hdc, diem_ket_thuc.x,diem_ket_thuc.y);
	}
	duong_thang(diem x, diem y)
	{
		diem_bat_dau = x;
		diem_ket_thuc = y;
	}
	hinh* khoi_tao(diem x, diem y)
	{
		return new duong_thang(x,y);
	}
	duong_thang() {};

};
class hinh_chu_nhat :public hinh
{
public:
	void mau_but(COLORREF mau)
	{
		mau_but_ve = mau;
	}
	void ve(HDC hdc)
	{
		Rectangle(hdc,diem_bat_dau.x , diem_bat_dau.y, diem_ket_thuc.x, diem_ket_thuc.y);
	}
	hinh_chu_nhat(diem x, diem y) //Khoi tao mac dinh co tham so
	{
		diem_bat_dau = x;
		diem_ket_thuc = y;
	}
	hinh* khoi_tao(diem x, diem y)
	{
		return new hinh_chu_nhat(x, y);
	}
	hinh_chu_nhat() {};
};
class hinh_vuong :public hinh
{
public:
	void mau_but(COLORREF mau)
	{
		mau_but_ve = mau;

	}
	void ve(HDC hdc)
	{
		if (shift)
		{
			tinh_toan_hv_elip(diem_bat_dau, diem_ket_thuc);
			Rectangle(hdc, diem_bat_dau.x, diem_bat_dau.y, diem_ket_thuc.x, diem_ket_thuc.y);
		}
	}
	hinh_vuong(diem x, diem y)
	{
		diem_bat_dau = x;
		diem_ket_thuc = y;
	}
	hinh* khoi_tao(diem x, diem y)
	{
		return new hinh_vuong(x, y);
	}
	hinh_vuong() {};
};

class hinh_elip : public hinh
{
public:
	void mau_but(COLORREF mau)
	{
		mau_but_ve = mau;
	}
	void ve(HDC hdc)
	{
		Ellipse(hdc, diem_bat_dau.x, diem_bat_dau.y, diem_ket_thuc.x, diem_ket_thuc.y);
	}

	hinh_elip(diem x, diem y)
	{
		diem_bat_dau = x; 
		diem_ket_thuc = y;
	}
	hinh* khoi_tao(diem x, diem y)
	{
		return new hinh_elip(x, y);
	}
	hinh_elip() {};
};

class hinh_tron : public hinh
{
public:
	void mau_but(COLORREF mau)
	{
		mau_but_ve = mau;
	}
	void ve(HDC hdc)
	{
		if (shift)
		{
			tinh_toan_hv_elip(diem_bat_dau, diem_ket_thuc);
			Ellipse(hdc, diem_bat_dau.x, diem_bat_dau.y, diem_ket_thuc.x, diem_ket_thuc.y);
		}
	}

	hinh_tron(diem x, diem y)
	{
		diem_bat_dau = x;
		diem_ket_thuc = y;
	}
	hinh* khoi_tao(diem x, diem y)
	{
		return new hinh_tron(x, y);
	}
	hinh_tron() {};
};
vector <hinh*> mang_vi_tri;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMO));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEMO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
hinh* temp = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
	case WM_MOUSEMOVE:
	{
		if (chuot_trai)
		{
			diem tam;
			tam.x = GET_X_LPARAM(lParam);
			tam.y = GET_Y_LPARAM(lParam);


			WCHAR buf[1000];
			wsprintf(buf, L"%d  %d", tam.x,tam.y);
			SetWindowText(hWnd, buf);

			if (ve_Tam )
			{
				ket_Thuc = tam;
				temp = temp->khoi_tao(bat_Dau, ket_Thuc);
				InvalidateRect(hWnd, 0, FALSE); //Goi ham WM_PAINT
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		
		bat_Dau.x = GET_X_LPARAM(lParam);
		bat_Dau.y = GET_Y_LPARAM(lParam);
		chuot_trai = true;
		break;
	}
	case WM_LBUTTONUP:
	{
		chuot_trai = false;
		//ve_Tam = false;
		if (temp != NULL & co) // nguoi dung da chon cong cu ve
			mang_vi_tri.push_back(temp);
		//temp = NULL;
		break;
	}
	case WM_KEYDOWN:
	{
		if (wParam == VK_SHIFT)
		{
			shift = true;
			co = true;
		}
		break;
	}
	case WM_KEYUP:
	{
		if (wParam == VK_SHIFT)
		{
			shift = false;
			co = false;
		}
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				
                break;
			case ID_BUT_VUA:
				kich_thuoc_but = 1;
				break;
			case ID_BUT_DAM:
				kich_thuoc_but = 2;
				break;
			case ID_BUT_R32778:
				kich_thuoc_but = 4;
				break;
			case ID_H32782: //duong thang
			{
				temp = new duong_thang;	
				//temp->mau_but(mau_ve);
				//temp->mau_but_ve = mau_ve;
				ve_Tam = true;
				co = true;
				break;
			}
				
			case ID_H32779: // hình chữ nhật
			{	
				temp = new hinh_chu_nhat;
				//temp->mau_but(mau_ve);
				ve_Tam = true;
				co = true;
				break;
			}
			
		
			case ID_H32783: //hình vuông
			{
				temp = new hinh_vuong;
				//temp->mau_but(mau_ve);
				ve_Tam = true;
				break;
			}
				
			case ID_H32781: // hình elip
			{
				temp = new hinh_elip;
				//temp->mau_but(mau_ve);
				ve_Tam = true;
				co = true;
				break;
			}
			case ID_H32784: //hinh tròn
			{
				temp = new hinh_tron;
				//temp->mau_but(mau_ve);
				ve_Tam = true;
				break;
			}
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_EDIT_C:
				mau_ve = ShowColorDialog(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
			HPEN hpen = CreatePen(PS_SOLID, kich_thuoc_but, mau_ve); // màu bút vẽ, loại bút vẽ
			RECT rect;
			GetClientRect(hWnd, &rect);
			//HBRUSH hrush = GetSockBrush(NULL_BRUSH);
			hdc_ao = CreateCompatibleDC(hdc); // tao 1 hdc_ao
			bitmap_ao = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);	//tạo 1 bitmap ảo
			SelectObject(hdc_ao, bitmap_ao);
			FillRect(hdc_ao, &rect, (HBRUSH)(COLOR_WINDOW + 1));   //tô màu cho hdc ảo
			SelectObject(hdc_ao, hpen);
			bool tt_ban_dau = shift; // trang thai nhan hay ko nhan

			// bật shift để vẽ lại 
			shift = true;
			for (int i = 0; i < mang_vi_tri.size(); i++)
			{
				//HPEN hpen_s = CreatePen(PS_SOLID, kich_thuoc_but,mang_vi_tri[i]->mau_but_ve); // màu bút vẽ, loại bút vẽ
				//SelectObject(hdc_ao, hpen_s);
				mang_vi_tri[i]->ve(hdc_ao);
			}
			// trả về trạng thái
			shift = tt_ban_dau;
			
			if (ve_Tam && chuot_trai) 
			{
				temp->ve(hdc_ao);
			}
		
			//DeleteObject(hpen);
			BitBlt(hdc, 0, 0, rect.right, rect.bottom,hdc_ao, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

COLORREF ShowColorDialog(HWND hwnd)
{
	CHOOSECOLOR cc;
	static COLORREF crCustClr[16];
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)crCustClr;
	cc.rgbResult = RGB(0, 255, 0);		// nếu không chọn bảng thì trả về mặt định là màu xanh lá
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	ChooseColor(&cc);
	return cc.rgbResult;
}
void tinh_toan_hv_elip(diem &diem_bat_dau,diem &diem_ket_thuc)
{
	int bd = abs(diem_bat_dau.x - diem_ket_thuc.x); //do dai canh trục x
	int kt = abs(diem_bat_dau.y - diem_ket_thuc.y); //do dai canh truc y
	if (bd < kt)
	{
		if (diem_bat_dau.y < diem_ket_thuc.y)
			diem_ket_thuc.y = diem_bat_dau.y + bd;
		else diem_ket_thuc.y = diem_bat_dau.y - bd;
	}
	else
	{
		if (diem_bat_dau.x < diem_ket_thuc.x)
			diem_ket_thuc.x = diem_bat_dau.x + kt;
		else diem_ket_thuc.x = diem_bat_dau.x - kt;
	}
}