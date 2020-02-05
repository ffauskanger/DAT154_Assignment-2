// Assignment2.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "Assignment2.h"
#include "Draw.h"
#include <list>
#include "Car.h"

using namespace std;


#define MAX_LOADSTRING 100



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int eastState = 0;
int southState = 2;
list <Car> northList;
list <Car> westList;
list <Car> eastList;
list <Car> southList;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASSIGNMENT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT2));

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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASSIGNMENT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
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




//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // States for traffic lights
    bool state1[] = { true, false, false }; // red
    bool state2[] = { true, true, false }; // red and yellow
    bool state3[] = { false, false, true }; // green
    bool state4[] = { false, true, false }; // yellow

    bool** states; 
    states = new bool* [4];
    states[0] = state1;
    states[1] = state2;
    states[2] = state3;
    states[3] = state4;

    int rpn = 0;
    int rpw = 0;

    int pw = 50;
    int pn = 50;

    // Size
    RECT rect;
    GetWindowRect(hWnd, &rect);
        
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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

    case WM_CREATE:
        SetTimer(hWnd, TIMER_TRAFFIC, 3000, (TIMERPROC)NULL);
        SetTimer(hWnd, TIMER_RANDOM_SPAWN, 1000, (TIMERPROC)NULL);
        SetTimer(hWnd, TIMER_CAR, 100, (TIMERPROC)NULL);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            // Drawing instructions


            // Roads


            roads(hdc, rect);

            // Traffic lights
            // East + West
            trafficlight(hdc, 750, 550, states[eastState]);
            trafficlight(hdc, 1100, 230, states[eastState]);


            // South + North
            trafficlight(hdc, 750, 230, states[southState]);
            trafficlight(hdc, 1100, 550, states[southState]);


            // Cars

            for (Car car : westList)
            {
                car.Draw(hdc);
            }

            for (Car car : eastList)
            {
                car.Draw(hdc);
            }

            for (Car car : northList)
            {
                car.Draw(hdc);
            }

            for (Car car : southList)
            {
                car.Draw(hdc);
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0); 
        break;
    case WM_LBUTTONDOWN:
    {

        westList.push_back(*(new Car(true, false, 0, 500)));
        eastList.push_back(*(new Car(true, true, 1600, 400)));
        northList.push_back(*(new Car(false, false, 900, 0)));
        southList.push_back(*(new Car(false, true, 980, 900)));
        InvalidateRect(hWnd, NULL, true);
        break;

        // Part 2: Traffic light change state
        //if (state == 0) state = 1; else if(state == 1) state = 2; else if(state == 2) state = 3; else state = 0;
        //if (southState == 0) southState = 1; else if (southState == 1) southState = 2; else if (southState == 2) southState = 3; else southState = 0;
        //InvalidateRect(hWnd, NULL, true);
    }
    case WM_RBUTTONDOWN:
    {
        break;
    }

   case WM_KEYDOWN:
    {
       switch (wParam)
       {
       case VK_LEFT:
           pw -= 10;
           break;
       case VK_RIGHT:
           pw += 10;
           break;
       case VK_UP:
           pn += 10;
           break;
       case VK_DOWN:
           pn -= 10;
           break;
       }
    }
    

    case WM_TIMER:


        switch (wParam)
        {
        case TIMER_RANDOM_SPAWN:
        {
            rpn = rand() % 100;
            rpw = rand() % 100;


            if (rpn > pn)
            {
                northList.push_back(*(new Car(false, false, 900, 0)));
                southList.push_back(*(new Car(false, true, 980, 900)));
            }

            if (rpw > pw)
            {
                westList.push_back(*(new Car(true, false, 0, 500)));
                eastList.push_back(*(new Car(true, true, 1500, 400)));
            }
            InvalidateRect(hWnd, NULL, true);
            break;
        }
        case TIMER_TRAFFIC:
        {
            // Setting states for traffic lights
            if (eastState == 0) eastState = 1; else if (eastState == 1) eastState = 2; else if (eastState == 2) eastState = 3; else eastState = 0;
            if (southState == 0) southState = 1; else if (southState == 1) southState = 2; else if (southState == 2) southState = 3; else southState = 0;
            InvalidateRect(hWnd, NULL, true);
            break;
        }
        case TIMER_CAR:
        {
            int lastWest = 50000;
            for (Car& c : westList)
            {
                if ((eastState == 2 || (c.getX() < 800 || c.getX() > 801)) && c.getX() < (lastWest - 50))
                {
                    c.Move();
                }
                lastWest = c.getX();
            }

            int lastEast = -50000;
            for (Car& c : eastList)
            {
                if ((eastState == 2 || (c.getX() < 1100 || c.getX() > 1101) && c.getX() > lastEast + 50))
                {
                    c.Move();
                }
                lastEast = c.getX();
            }

            int lastNorth = 50000;
            for (Car& c : northList)
            {
                if ((southState == 2 || (c.getY() < 300 || c.getY() > 301) && c.getY() < lastNorth - 50))
                {
                    c.Move();
                }
                lastNorth = c.getY();
            }


            int lastSouth = -50000;
            for (Car& c : southList)
            {
                if ((southState == 2 || (c.getY() < 550 || c.getY() > 551) && c.getY() > lastSouth + 50))
                {
                    c.Move();
                }
                lastSouth = c.getY();
            }

            InvalidateRect(hWnd, NULL, true);
            break;
        }
        default: break;
        }
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
