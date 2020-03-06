#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

const char Window[] = "WindowsClass";
MSG Message;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
  case WM_CLOSE:
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;  
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = Window;
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if ((!RegisterClassEx(&wc)))
  {
    MessageBox(0, "Shit happens :)", "Oops!", MB_ICONERROR | MB_OK);
    return 1;
  }

  HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, Window, "That's the window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 720, 526, NULL, NULL, hInstance, NULL);
  ShowWindow(hwnd, iCmdShow);
  UpdateWindow(hwnd);

  if (hwnd == 0)
  {
    MessageBox(0, "ERROR\n Window Creation Failes!", "ERROR", MB_ICONERROR | MB_OK);
    return 0;
  }
  while (GetMessage(&Message, NULL, 0,0)>0)
  {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
  }
  return Message.wParam;

  return 0;
}