#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#define FILE_MENU_EASY 1
#define FILE_MENU_MID 2
#define FILE_MENU_HARD 3
#define CHECK 4
using namespace std;
void AddMenus(HWND);
void new_game(HWND);
int n = 0;
HWND hEdit[81];
int mas[81] = {
1,2,3,6,8,9,5,4,7,
5,8,9,2,7,4,1,6,3,
6,7,4,3,5,1,2,8,9,
8,9,5,1,4,7,6,3,2,
3,4,7,5,2,6,8,9,1,
2,6,1,8,9,3,7,5,4,
7,3,6,4,1,8,9,2,5,
9,5,8,7,3,2,4,1,6,
4,1,2,9,6,5,3,7,8,
};
bool flag()
{
	int a = rand() % 100;
	if (a < n)
		return true;
	else
		return false;
}
HMENU hMenu;
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg)
		{
			case WM_CREATE:
			{
				AddMenus(hWnd);
			}
			return 0;
			case WM_COMMAND:
			{
				switch (wParam)
				{
				case FILE_MENU_EASY:
					n = 40;
					new_game(hWnd);
					break;
				case FILE_MENU_MID:
					n = 20;
					new_game(hWnd);
					break;
				case FILE_MENU_HARD:
					n = 10;
					new_game(hWnd);
					break;
				case CHECK:
					TCHAR buff[1024] = { 0 };
					string a = "";
					int schit = 0;
					int prov_mas[81];
					int prov[9];
					int s=0;
					int sm;
					int sm1=0;
					bool win = true;
					for (int i = 0; i < 81; i++)
					{
						GetWindowText(hEdit[i], buff, 1024);
						a = string(buff);
						prov_mas[i] = atoi(a.c_str());
						if (a == "1" || a == "2" || a == "3" || a == "4" || a == "5" || a == "6" || a == "7" || a == "8" || a == "9")
							schit++;
						
					}
					if (schit < 81)
					{
						MessageBox(hWnd, "Не все поля заполнены", "", MB_OK);
						win = false;
					}
					else
					{

						for (int i = 0; i < 9; i++)
						{	for (int j = 0; j < 9; j++)
							{
								prov[j] = prov_mas[i * 9 + j];
							}
							for (int i1 = 0; i1 < 8; i1++)
							{
								for (int j = i1+1; j < 9; j++)
								{
									if (i1 != j && prov[i1] == prov[j])
									{
										i  = 9;
										j  = 9;
										i1 = 8;
										MessageBox(hWnd, "Есть ошибки", "", MB_OK);
										win = false;
									}
								}
							}
						}
						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								prov[j] = prov_mas[j*9+i];
							}
							for (int i1 = 0; i1 < 8; i1++)
							{
								for (int j = i1 + 1; j < 9; j++)
								{
									if (i1 != j && prov[i1] == prov[j])
									{
										i = 9;
										j = 9;
										i1 = 8;
										MessageBox(hWnd, "Есть ошибки", "", MB_OK);
										win = false;
									}
								}
							}
						}
						for (int i = 0; i < 9; i++)
						{
							
							if (i == 0 || i == 3 || i == 6)
								sm = 0;
							if (i == 1 || i == 4 || i == 7)
								sm = 3;
							if (i == 2 || i == 5 || i == 8)
								sm = 6;
							if (i < 3)
								sm1 = 0;
							if(i>2&&i<6)
								sm1 = 3;
							if (i>5 && i<9)
								sm1 = 6;
							for (int j1= (i / 3) * 3;j1<((i / 3) * 3) + 3;j1++)
								for (int j = ((i/3)*3)-sm1; j < (((i / 3) * 3)+3)-sm1; j++)
								{
									prov[s] = prov_mas[j1 * 9 + j+sm];
									s++;
								}
							for (int i1 = 0; i1 < 8; i1++)
							{
								for (int j = i1 + 1; j < 9; j++)
								{
									if (i1 != j && prov[i1] == prov[j])
									{
										i = 9;
										j = 9;
										i1 = 8;
										MessageBox(hWnd, "Есть ошибки", "", MB_OK);
										win = false;
									}
								}
							}
							s = 0;
						}
					}
					if (win == true) 
					{
						MessageBox(hWnd, "Все верно, ура", "", MB_OK);
						for (int i = 0; i < 81; i++)
						{
							EnableWindow(hEdit[i], false);
						}
					}
					break;
				}		
			}
			return 0;
			case WM_DESTROY: 
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};	
	wc.lpszClassName = "MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;
	if (hwnd = CreateWindow(wc.lpszClassName, "Судоку", WS_OVERLAPPEDWINDOW, 600, 270, 315, 400, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}
void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	AppendMenu(hFileMenu, MFT_STRING, FILE_MENU_EASY,"Легкая");
	AppendMenu(hFileMenu, MFT_STRING, FILE_MENU_MID, "Средняя");
	AppendMenu(hFileMenu, MFT_STRING, FILE_MENU_HARD, "Сложная");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "Новая игра");

	SetMenu(hWnd, hMenu);
}
void new_game(HWND hWnd)
{
	CreateWindow(
		"Button",
		"Проверка",
		WS_CHILD | WS_VISIBLE | SS_CENTER,
		100,10,100,20,hWnd,(HMENU)CHECK, NULL, NULL
	);
	int x = 10;
	int y = 50;
	for (int i = 0; i < 81; i++)
	{
		hEdit[i] = CreateWindow(
			"EDIT",
			"",
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			x, y, 20, 20, hWnd, reinterpret_cast<HMENU>(i+1), nullptr, nullptr
		);
		if (flag() == true)
		{
			EnableWindow(hEdit[i], false);
			if (mas[i] == 1)
			{
				SetWindowText(hEdit[i], "1");
			}
			if (mas[i] == 2)
			{
				SetWindowText(hEdit[i], "2");
			}
			if (mas[i] == 3)
			{
				SetWindowText(hEdit[i], "3");
			}
			if (mas[i] == 4)
			{
				SetWindowText(hEdit[i], "4");
			}
			if (mas[i] == 5)
			{
				SetWindowText(hEdit[i], "5");
			}
			if (mas[i] == 6)
			{
				SetWindowText(hEdit[i], "6");
			}
			if (mas[i] == 7)
			{
				SetWindowText(hEdit[i], "7");
			}
			if (mas[i] == 8)
			{
				SetWindowText(hEdit[i], "8");
			}
			if (mas[i] == 9)
			{
				SetWindowText(hEdit[i], "9");
			}
		}
		if ((i + 1) % 27 == 0)
		{
			y += 40;
			x = 10;
		}
		else
		{
			if ((i + 1) % 9 == 0)
			{
				y += 30;
				x = 10;
			}
			else
			{
				if ((i + 1) % 3 == 0)
				{
					x += 40;
				}
				else
				{
					x += 30;
				}
			}
		}
	}
}