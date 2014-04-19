#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <string>
#include <vector>
#include <iostream>

//Windows Specific Headers
#include "Windows.h"
#include "Winuser.h"
#include "commdlg.h"

#include "dialogbox_resource.h"

namespace DialogBoxes {
	/**
	*  Display the default Windows Open Dialog Box
	*  @return string Value of the file to be opened.
	*/
	static std::string Open(){

		OPENFILENAME ofn;
		TCHAR szFile[MAX_PATH];

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.hwndOwner = nullptr;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = TEXT("Json files(*.json)\0*.json\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrFileTitle = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR ;

		GetOpenFileName(&ofn);
		return std::string(szFile);
	}
	/**
	*  Display the default Windows Save As Dialog Box
	*  @return string Value of the file to be saved to.
	*/
	static std::string SaveAs(){

		OPENFILENAME ofn;
		TCHAR szFile[MAX_PATH];

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.hwndOwner = nullptr;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = TEXT("Json files(*.json)\0*.json\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrFileTitle = NULL;

		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR ;
		GetSaveFileName (&ofn);
		return ofn.lpstrFile;
	}

	//Dialog Boxes for the Editor
	namespace Editor {
		//Window function
		static BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
		{
			switch(Message)
			{
			case WM_INITDIALOG:
				SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, 
					MAKEINTRESOURCE(IDI_APPLICATION)));
				SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, 
					MAKEINTRESOURCE(IDI_APPLICATION)));
				break;
			case WM_CLOSE:
				EndDialog(hwnd, 0);
				PostQuitMessage( 0 ) ;
				break;
			case WM_COMMAND:
				switch(LOWORD(wParam))
				{
				case IDOK:
					EndDialog(hwnd, 0);
					PostQuitMessage( 0 ) ;
					break;
				}
				break;
			default:
				return FALSE;
			}
			return TRUE;
		}
		/**
		*  Display the dialog box for changing from one tileset to another.
		*  @param list A list of strings with the names of the possible tilesets 
		*  @return int Value of the tileset to be opened.
		*/
		static int ChangeTilebar(std::vector<std::string>* list){
			//Create the Dialog Box
			HWND hwnd =  CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TILESET), NULL, &DialogBoxes::Editor::DlgProc);
			ShowWindow(hwnd, 1);
			UpdateWindow(hwnd);

			//Add the list to the listbox
			HWND hwndList = GetDlgItem(hwnd, IDC_TILESET_LIST);
			std::vector<std::string>::iterator it = list->begin();
			for (; it != list->end(); it++)
				SendMessage (hwndList, LB_ADDSTRING, 0, (LPARAM)it->c_str()) ;

			//Run the window loop until PostQuitMessage(0) is called;
			MSG msg;
			while( GetMessage( &msg, NULL, 0, 0 ) )
			{
				TranslateMessage( &msg );  
				DispatchMessage( &msg );
			}

			//return the selected index
			return SendMessage (hwndList, LB_GETCURSEL, 0, 0) ;
		}
		/**
		*  Display the dialog box for defining a new map size.
		*  @return pair<int,int> Height/width of the new map.
		*/
		static std::pair<int, int> New()
		{
			//Create the Dialog Box
			HWND hwnd =  CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAP), NULL, &DialogBoxes::Editor::DlgProc);
			ShowWindow(hwnd, 1);
			UpdateWindow(hwnd);

			//Run the window loop until PostQuitMessage(0) is called;
			MSG msg;
			while( GetMessage( &msg, NULL, 0, 0 ) )
			{
				TranslateMessage( &msg );  
				DispatchMessage( &msg );
			}

			//Get and store the variables used in the window
			BOOL colSuccess;
			BOOL rowSuccess;
			int columns = GetDlgItemInt(hwnd, IDC_MAP_COLUMNS, &colSuccess, FALSE);
			int rows = GetDlgItemInt(hwnd, IDC_MAP_ROWS, &rowSuccess, FALSE);

			//Return values
			if (colSuccess & rowSuccess)
				return std::pair<int, int>(rows,columns);
			return std::pair<int, int>(0,0);

		}

	}
}

#endif