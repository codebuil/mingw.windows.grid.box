#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 10000
#define MAX_BUFFER_SIZE 1024
#define lines 60
static HWND hStartEdit,hEndEdit,hButton,hButton2,thew,tthew[lines*2+1];
int xx = 2; // Define a posição horizontal
int yy = 2; // Define a posição vertical
 int nn,nnn;   
  static char startStr[1024], endStr[1024];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Temporizador");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Este programa requer Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("Temporizador"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
        thew=CreateWindowEx(
                    0, "STATIC", NULL,
                    WS_CHILD | WS_VISIBLE | WS_VSCROLL,
                    0, 0, 640, 4000,
                    hwnd, NULL, NULL, NULL
                );
for(nn=0;nn<lines;nn++){
                for(nnn=0;nnn<2;nnn++){
                int randomNumber = rand() % 50 + 1;
                sprintf(startStr,  "%d", randomNumber);
                if(nnn==0)sprintf(startStr,  "%d", nn);
                
                tthew[nn*2+nnn]=CreateWindow(TEXT("EDIT"), startStr,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        4+100*nnn, 30*nn+4, 100, 30,  thew, (HMENU)40+nn*2+nnn, GetModuleHandle(NULL), NULL);

                }
                
                
            }
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szBuffer[80];
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    
    time_t rawtime;
    struct tm *timeinfo;
    
   
    char buffer[MAX_BUFFER_SIZE];

    

    switch (message)
    {
        case WM_CREATE:
        
       
        hButton = CreateWindow("BUTTON", "up", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            650, 10, 50, 30,  hwnd, (HMENU)3, GetModuleHandle(NULL), NULL);
        hButton2 = CreateWindow("BUTTON", "down", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            650, 350, 50, 30,  hwnd, (HMENU)4, GetModuleHandle(NULL), NULL);
            for(nn=0;nn<lines;nn++){
                nnn=0;
                
                
            }
        
        break;
        case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            case 3:
            yy=yy+20;
            if(yy>4)yy=4;
           SetWindowPos(thew, NULL, xx, yy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            break;
            case 4:
            yy=yy-20; 
            if(yy<-3800)yy=3800;
           SetWindowPos(thew, NULL, xx, yy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            break;
        }
    break;   

    case WM_PAINT:
            
            hdc = BeginPaint(hwnd, &ps);
            
            // Define a cor de fundo da janela para azul
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            // Define a cor das linhas para branco
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);
            
            // Desenha as linhas com base nas coordenadas fornecidas
            
            
            // Libera os recursos utilizados
            DeleteObject(hPen);
            EndPaint(hwnd, &ps);
            break;
    

    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
