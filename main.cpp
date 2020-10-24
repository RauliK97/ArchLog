#define WINVER 0x0500
#include <fstream>
#include <iostream>
#include <windows.h>

#define LOG_ID 1
#define ADDACC_ID 2
#define RMVACC_ID 9
#define  ID_ID 3
#define ID_ADDOK 4
#define ID_ADDCANCEL 5
#define ID_USEREDIT 6
#define ID_PASSEDIT 7
#define ID_COMBOBOX 8

using namespace std;

void AccRead(),
     AccWrite( int remove ),
     AddAcc(),
     SendKey ( int key, bool shift );
     

int GetSelectedName(),
    ChToScan( char letter );

int Accounts;

INPUT input;
HWND Archlord;

char path[100] = "Accounts.txt";
char user[100][100];
char pass[100][100];
char Username[100];
char Password[100];

HWND LogButton;
HWND AddAccButton;
HWND RmvAccButton;
HWND UserEdit;
HWND PasswordEdit;
HWND AddButtonOk;
HWND AddButtonCancel;
HWND AccList;
HWND hwnd;               /* This is the handle for our window */
HWND child;

int NameChk();

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedure2 (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";
char szClassName2[ ] = "ChildApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HINSTANCE hInstance = hThisInstance;
    input.type = INPUT_KEYBOARD;
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    
    system("start /MIN JUSTArchlord.exe");

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(200,200,200));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "ArchLog",           /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           300,       /* Windows decides the position */
           400,       /* where the window ends up on the screen */
           300,                 /* The programs width */
           125,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
    
    WNDCLASSEX winclc;        /* Data structure for the windowclass */
    
    /* The Window structure */
    winclc.hInstance = hThisInstance;
    winclc.lpszClassName = szClassName2;
    winclc.lpfnWndProc = WindowProcedure2;      /* This function is called by windows */
    winclc.style = CS_DBLCLKS;                 /* Catch double-clicks */
    winclc.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    winclc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    winclc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    winclc.hCursor = LoadCursor (NULL, IDC_ARROW);
    winclc.lpszMenuName = NULL;                 /* No menu */
    winclc.cbClsExtra = 0;                      /* No extra bytes after the window class */
    winclc.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    winclc.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(200,200,200));
    RegisterClassEx (&winclc);
    
    child = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName2,        /* Classname */
           "Add Account",       /* Title Text */
           WS_OVERLAPPED,       /* default window */
           300,       /* Windows decides the position */
           550,       /* where the window ends up on the screen */
           300,                 /* The programs width */
           125,                 /* and height in pixels */
           hwnd,                /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
    
    /* Make the window visible on the screen */

    ShowWindow (hwnd, nFunsterStil);
    //ShowWindow (child, nFunsterStil);
    RegisterHotKey ( NULL, 1, 0, 'X' );  //0x42 is 'b'

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        switch ( messages.message )
            {
                case WM_HOTKEY:
                {
                     if ( messages.wParam == 1 )
                     {
                          ifstream fin("X.txt");
                          /*char x[200];
                          fin >> n*/
                          int i;
                          while ( !fin.eof() )
                          {
                                fin >> i;
                                SendKey(i);
                          }
                     {
                     break;
                }
            }
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
             LogButton    = CreateWindow( "BUTTON", "Log In",
                                          WS_VISIBLE | WS_CHILD,
                                          30, 55, 100, 20,
                                          hwnd, (HMENU)LOG_ID, NULL, NULL );
             AddAccButton = CreateWindow( "BUTTON", "Add Account",
                                          WS_VISIBLE | WS_CHILD,
                                          165, 55, 100, 20,
                                          hwnd, (HMENU)ADDACC_ID, NULL, NULL );
             RmvAccButton = CreateWindow( "BUTTON", "Remove Acc",
                                          WS_VISIBLE | WS_CHILD,
                                          165, 18, 100, 20,
                                          hwnd, (HMENU)RMVACC_ID, NULL, NULL );
             AccList      = CreateWindow( "COMBOBOX", "",
                                          WS_VISIBLE | WS_CHILD | WS_TABSTOP | CBS_DROPDOWN,
                                          20, 15, 125, 150,
                                          hwnd, (HMENU)ID_COMBOBOX, NULL, NULL );
             AccRead();
             break;
        }
        case WM_COMMAND:
        {
             switch ( wParam )
             {
                    case LOG_ID:
                    {
                         int row = SendMessage(AccList , CB_GETCURSEL, 0, 0 );
                         if ( row == -1 )
                         {
                              MessageBox(0,"Username does not exist","ERROR", MB_OK | MB_SYSTEMMODAL);
                         }
                         else
                         {
                              Archlord = FindWindow(NULL, "Archlord Patch Client");
                              SetForegroundWindow( Archlord );
                              
                              SendKey( 0x1F, 0 );
                              Sleep(100);
                              int userLen = strlen(user[row]);
                              int passLen = strlen(pass[row]);
                              
                              for ( int i = 0; i < userLen; i++ )
                              {
                                  int shift = false;
                                  if ( user[row][i] >= 'A' && user[row][i] <= 'Z'  )
                                  {
                                       shift = true;
                                  }
                                  int key = ChToScan(user[row][i]);
                                  SendKey ( key, shift );
                              }
                              SendKey ( 0x0F, 0 );
                              for ( int i = 0; i < passLen; i++ )
                              {
                                  int shift = false;
                                  if ( pass[row][i] >= 'A' && pass[row][i] <= 'Z'  )
                                  {
                                       shift = true;
                                  }
                                  int key = ChToScan(pass[row][i]);
                                  SendKey ( key, shift );
                              }
                              SendKey( 0x1C, 0 );
                              exit(0);
                         }
                         break;
                    }
                    case ADDACC_ID:
                    {
                         ShowWindow (child, SW_SHOW);
                         break;
                    }
                    case RMVACC_ID:
                    {
                         int row = SendMessage(AccList , CB_GETCURSEL, 0, 0 );
                         if ( row == -1 )
                         {
                              MessageBox(0,"Username does not exist","ERROR", MB_OK | MB_SYSTEMMODAL);
                         }
                         else
                         {
                              AccWrite(row);
                              AccRead();
                         }
                         break;
                    }
             }
             break;
        }
        case WM_DESTROY:
             PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
             break;
        default:                      /* for messages that we don't deal with */
             return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK WindowProcedure2 (HWND child, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
              UserEdit        = CreateWindow ( "EDIT", "",
                                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                                               50, 20, 100, 20,
                                               child, (HMENU)ID_USEREDIT, NULL, NULL );
                                CreateWindow ( "STATIC", "ID:",
                                               WS_VISIBLE | WS_CHILD | SS_CENTER | WS_TABSTOP,
                                               10, 22, 20, 20,
                                               child, (HMENU)ID_ID, NULL, NULL );
              PasswordEdit    = CreateWindow ( "EDIT", "",
                                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                                               50, 50, 100, 20,
                                               child, (HMENU)ID_PASSEDIT, NULL, NULL );
                                CreateWindow ( "STATIC", "PW:",
                                               WS_VISIBLE | WS_CHILD | SS_CENTER | WS_TABSTOP,
                                               10, 54, 30, 20,
                                               child, (HMENU)ID_ID, NULL, NULL );
              AddButtonOk     = CreateWindow ( "BUTTON", "Ok",
                                               WS_VISIBLE | WS_CHILD,
                                               175, 20, 100, 20,
                                               child, (HMENU)ID_ADDOK, NULL, NULL );
              AddButtonCancel = CreateWindow ( "BUTTON", "Cancel",
                                               WS_VISIBLE | WS_CHILD,
                                               175, 50, 100, 20,
                                               child, (HMENU)ID_ADDCANCEL, NULL, NULL );
        }
        case WM_CTLCOLORSTATIC:
        {
             DWORD CtrlID = GetDlgCtrlID((HWND)lParam); //Window Control ID
             if ( CtrlID == ID_ID ) //If desired control
             {
                  HDC hdcStatic = (HDC) wParam;
                  SetTextColor(hdcStatic, RGB(50,50,200));
                  SetBkColor(hdcStatic, RGB(200,200,200));
                  return (INT_PTR)CreateSolidBrush(RGB(200,200,200));
             }
        }
        case WM_COMMAND:
        {
             switch ( wParam )
             {
                    case ID_ADDOK:
                    {
                         for ( int i = 0; i <= strlen(Username); i++ )
                         {
                             Username[i] = 0;
                         }
                         for ( int i = 0; i <= strlen(Password); i++ )
                         {
                             Password[i] = 0;
                         }
                         GetDlgItemText( child, ID_USEREDIT, Username, 100 );
                         GetDlgItemText( child, ID_PASSEDIT, Password, 100 );
                         //MessageBox(NULL,Username,"ERROR",MB_OK);
                         if ( !strlen(Username) )
                         {
                              MessageBox(NULL,"Please enter a Username!","ERROR",MB_OK);
                         }
                         else if ( !strlen(Password) )
                         {
                              MessageBox(NULL,"Please enter a Password!","ERROR",MB_OK);
                         }
                         else if ( NameChk() )
                         {
                              MessageBox(NULL,"Username already exists!","ERROR",MB_OK);
                         }
                         else
                         {
                              AddAcc();
                              AccWrite(-1);
                              AccRead();
                              SetWindowText( GetDlgItem( child, ID_USEREDIT ), "" );
                              SetWindowText( GetDlgItem( child, ID_PASSEDIT ), "" );
                              ShowWindow ( child, SW_HIDE );
                         }
                         break;
                    }
                    case ID_ADDCANCEL:
                    {
                         ShowWindow ( child, SW_HIDE );
                         break;
                    }
             }
             break;
        }
        case WM_DESTROY:
             PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
             break;
        default:                      /* for messages that we don't deal with */
             return DefWindowProc (child, message, wParam, lParam);
    }
    return 0;
}
void AddAcc()
{
     for ( int i = 0; i < strlen(Username); i++ )
     {
         user[Accounts][i] = Username[i];
     }
     for ( int i = 0; i < strlen(Password); i++ )
     {
         pass[Accounts][i] = Password[i];
     }
     Accounts++;
}
void AccRead()
{
     SendDlgItemMessage(hwnd, ID_COMBOBOX, CB_RESETCONTENT, 0, 0);
     ifstream fin(path);
     int i = 0;
     while (!fin.eof() )
     {
           char *point = user[i];
           fin >> user[i] >> pass[i];
           if ( *point != 0 )
           {
                i++;
           }
     }
     Accounts = i;
     fin.close();
     for ( int i = 0; i < Accounts; i++ )
     {
         SendMessage(AccList,CB_ADDSTRING,0,reinterpret_cast<LPARAM>((LPCTSTR)user[i]));
     }
}
int NameChk()
{
    int i, j;
    bool good = true;
    for ( i = 0; i < Accounts; i++ )
    {
        good = true;
        if ( strlen(user[i]) == strlen(Username) )
        {
             for ( j = 0; j < strlen(user[i]); j++ )
             {
                 if ( user[i][j] != Username[j] )
                 {
                      good = false;
                 }
             }
        }
        else
        {
            good = false;
        }
        if ( good == true )
        {
             return 1;
             break;
        }
    }
    return 0;
}
void AccWrite( int remove )
{
     int i;
     ofstream fout(path);
     for ( i = 0; i < Accounts; i++ )
     {
         if ( i != remove )
         {
              if ( i == 0 )
              {
                   fout << user[i] << "    " << pass[i];
              }
              else
              {
                   fout << endl << user[i] << "    " << pass[i];
              }
         }
     }
     fout.close();
}
void SendKey( int key, bool shift )
{
     if ( shift )
     {
          input.ki.wScan = 0x2A;//DIKEYBOARD_A;//0x041E;//DIKEYBOARD_1;//
          input.ki.dwFlags = KEYEVENTF_SCANCODE; // there is no KEYEVENTF_KEYDOWN
          SendInput(1, &input, sizeof(INPUT));
     }
     input.ki.wScan = key;
     input.ki.dwFlags = KEYEVENTF_SCANCODE;
     SendInput(1, &input, sizeof(INPUT));
     
     input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
     SendInput(1, &input, sizeof(INPUT));
     if ( shift )
     {
          input.ki.wScan = 0x2A;
          input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
          SendInput(1, &input, sizeof(INPUT));
     }
}
int ChToScan( char letter )
{
    /*if ( letter >= 'A' && letter <= 'Z'  )
         return 0x2A;*/
    if ( letter == 'a' || letter == 'A' )
         return 0x1E;
    if ( letter == 'b' || letter == 'B' )
         return 0x30;
    if ( letter == 'c' || letter == 'C' )
         return 0x2E;
    if ( letter == 'd' || letter == 'D' )
         return 0x20;
    if ( letter == 'e' || letter == 'E' )
         return 0x12;
    if ( letter == 'f' || letter == 'F' )
         return 0x21;
    if ( letter == 'g' || letter == 'G' )
         return 0x22;
    if ( letter == 'h' || letter == 'H' )
         return 0x23;
    if ( letter == 'i' || letter == 'I' )
         return 0x17;
    if ( letter == 'j' || letter == 'J' )
         return 0x24;
    if ( letter == 'k' || letter == 'K' )
         return 0x25;
    if ( letter == 'l' || letter == 'L' )
         return 0x26;
    if ( letter == 'm' || letter == 'M' )
         return 0x32;
    if ( letter == 'n' || letter == 'N' )
         return 0x31;
    if ( letter == 'o' || letter == 'O' )
         return 0x18;
    if ( letter == 'p' || letter == 'P' )
         return 0x19;
    if ( letter == 'q' || letter == 'Q' )
         return 0x10;
    if ( letter == 'r' || letter == 'R' )
         return 0x13;
    if ( letter == 's' || letter == 'S' )
         return 0x1F;
    if ( letter == 't' || letter == 'T' )
         return 0x14;
    if ( letter == 'u' || letter == 'U' )
         return 0x16;
    if ( letter == 'v' || letter == 'V' )
         return 0x2F;
    if ( letter == 'w' || letter == 'W' )
         return 0x11;
    if ( letter == 'x' || letter == 'X' )
         return 0x2D;
    if ( letter == 'y' || letter == 'Y' )
         return 0x15;
    if ( letter == 'z' || letter == 'Z' )
         return 0x2C;
    if ( letter == '1' )
         return 0x02;
    if ( letter == '2' )
         return 0x03;
    if ( letter == '3' )
         return 0x04;
    if ( letter == '4' )
         return 0x05;
    if ( letter == '5' )
         return 0x06;
    if ( letter == '6' )
         return 0x07;
    if ( letter == '7' )
         return 0x08;
    if ( letter == '8' )
         return 0x09;
    if ( letter == '9' )
         return 0x0A;
    if ( letter == '0' )
         return 0x0B;
}
