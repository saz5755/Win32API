﻿// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd; // 메인 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// 지역
// 전역
// 정적 ( 데이터 영역 )
// 1. 함수 안에
// 2. 파일
// 3. 클래스 안에 

// 외부


class CClass
{
public:

    int m_i;
    static int m_iStatic; // 정적 멤버 ( 데이터 영역 )

public:
    void func()
    {
        m_i;
        m_iStatic = 0;
    }

    // 정적 멤버함수, 객체 없이 호출 가능, this가 없다 (멤버 접근 불가), 정적 멤버는 접근 가능
    static void FUNC()
    {
        m_iStatic = 0;
    }
};

int CClass::m_iStatic = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 참조되지 않는 파라미터라서 주석
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    CClass a;
    a.func();

    CClass::FUNC();
    CClass::m_iStatic = 0;
    
    CCore* pCore = CCore::GetInstance();
    
        // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // PeekMessage
    // 메세지 유무와 관계 없이 반환
    // 메세지 큐에서 메세지를 확인한 경우 true, 아닌경우 fale

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{

            if (WM_QUIT == msg.message)
                break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}	   
        }

        // 메세지가 발생하지 않는 대부분의 시간

        else
        {
            // Game 코드 수행
            // 디자인 패턴(설계 유형)
            // 싱글톤 패턴
        }

	}

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

#include<vector>
using std::vector;

struct tObjInfo
{
	POINT g_ptObjPos;
	POINT g_ptObjScale;
};

// 벡터 자체는 전역 변수지만 관리하고 있는 메모리는 힙 메모리
vector<tObjInfo> g_vecInfo;


// 좌 상단
POINT g_ptLT;

// 우 하단
POINT g_ptRB;

bool bLbtnDown = false;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화 영역(Invalidate)이 발생한 경우
        {
            PAINTSTRUCT ps;
            
            // Device Context 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps);

            // DC의 목적지는 hWnd
            // DC의 펜은 기본펜(Black)
            // DC의 브러쉬는 기본 브러쉬(White)
            
            // 직접 펜을 만들어서 DC에 지급
            HPEN hRedPen =  CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // 기존 펜과 브러쉬 ID 값을 받아 둠
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); 
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            if (bLbtnDown)
            { 
                // 변경된 펜으로 사각형 그림
                Rectangle(hdc,
                    g_ptLT.x, g_ptLT.y,
                    g_ptRB.x, g_ptRB.y);
            }
            
            // 추가된 사각형들도 그려준다.
            for (size_t i = 0; i < g_vecInfo.size(); i++)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x /2,
                    g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y /2,
                    g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x /2,
                    g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y /2);
            }
           
            // DC의 펜과 브러쉬를 원래 것으로 되돌림
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다 쓴 Red 펜 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);

            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			//g_ptObjPos.y -= 10;
			// 강제로 무효화 영역이 발생한 것으로 알림으로써 사각형이 재렌더링 되도록 함
			// 기존 렌더링된 영역을 지우고 다시 그리기 설정
			InvalidateRect(hWnd, nullptr, true);

			break;

        case VK_DOWN:
            //g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_LEFT:
            //g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
            //g_ptObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
		
        default:
			break;
		}
	}
            break;
    case WM_LBUTTONDOWN:
    {
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtnDown = true;
    }
    break;

    case WM_MOUSEMOVE:
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
        break;

    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);

    }
    break;

    case WM_TIMER:
    {
        int a = 0;
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

// 정보 대화 상자의 메시지 처리기입니다.
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
