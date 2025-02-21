#include <windows.h>
#include <string>

char text1[20],text2[20];
char t[100];
double num1,num2,result=0;
HWND  button,textbox1,textbox2;

//add -lgdi32 when complie
/* This is where all the input to the window goes to */

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {


   
    switch(Message) {

        case WM_CREATE:

            CreateWindow("STATIC",
                        "Please input two numbers",
                        WS_VISIBLE | WS_CHILD | WS_BORDER,
                        20,20,200,30,
                        hwnd, NULL,NULL,NULL);
           
            textbox1 = CreateWindow("EDIT",
                                    "",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    20,60,200,20,
                                    hwnd,NULL,NULL,NULL);

            textbox2 = CreateWindow("EDIT",
                                    "",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    20,90,200,20,
                                    hwnd,NULL,NULL,NULL);                        

            CreateWindow("BUTTON",
                        "+",
                        WS_VISIBLE | WS_CHILD | WS_BORDER,
                        50,120,30,30,
                        hwnd, (HMENU) 1,NULL,NULL);
            CreateWindow("BUTTON",
                        "-",
                        WS_VISIBLE | WS_CHILD | WS_BORDER,
                        90,120,30,30,
                        hwnd, (HMENU) 2,NULL,NULL);
            CreateWindow("BUTTON",
                        "*",
                        WS_VISIBLE | WS_CHILD | WS_BORDER,
                        130,120,30,30,
                        hwnd, (HMENU) 3,NULL,NULL);
            CreateWindow("BUTTON",
                        "/",
                        WS_VISIBLE | WS_CHILD | WS_BORDER,
                        170,120,30,30,
                        hwnd, (HMENU) 4,NULL,NULL);

        break;

        case WM_COMMAND:
           
            GetWindowText(textbox1,text1,20);
            GetWindowText(textbox2,text2,20);
            num1 = atof(text1);
            num2 = atof(text2);



            switch (LOWORD(wParam))

            {
            case 1:
                result = num1 + num2;
                sprintf(t, "%f", result);
                MessageBox(hwnd, t ,"Result" , MB_OK);
            break;
            case 2:
                result = num1-num2;
                sprintf(t, "%f", result);
                MessageBox(hwnd, t ,"Result" , MB_OK);
            break;
            case 3:
                result = num1*num2;
                sprintf(t, "%f", result);
                MessageBox(hwnd, t ,"Result" , MB_OK);
            break;
            case 4:
                result = num1/num2;
                sprintf(t, "%f", result);
                MessageBox(hwnd, t ,"Result" , MB_OK);
            break;
            default: break;
            }

            break;
           
       
        /* Upon destruction, tell the main thread to stop */

        case WM_DESTROY: {

            PostQuitMessage(0);

            break;

        }

       

        /* All other messages (a lot of them) are processed using default procedures */

        default:

            return DefWindowProc(hwnd, Message, wParam, lParam);

    }

    return 0;

}



/* The 'main' function of Win32 GUI programs: this is where execution starts */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wc; /* A properties struct of our window */

    HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */

    MSG msg; /* A temporary location for all messages */



    /* zero out the struct and set the stuff we want to modify */

    memset(&wc,0,sizeof(wc));

    wc.cbSize    = sizeof(WNDCLASSEX);

    wc.lpfnWndProc   = WndProc; /* This is where we will send messages to */

    wc.hInstance     = hInstance;

    wc.hCursor   = LoadCursor(NULL, IDC_ARROW);

   

    /* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */

    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,0,255));

    wc.lpszClassName = "WindowClass";

    wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */

    wc.hIconSm   = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */



    if(!RegisterClassEx(&wc)) {

        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);

        return 0;

    }



    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,

        CW_USEDEFAULT, /* x */

        CW_USEDEFAULT, /* y */

        250, /* width */

        200, /* height */

        NULL,NULL,hInstance,NULL);



    if(hwnd == NULL) {

        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);

        return 0;

    }



    /*

        This is the heart of our program where all input is processed and

        sent to WndProc. Note that GetMessage blocks code flow until it receives something, so

        this loop will not produce unreasonably high CPU usage

    */

    while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */

        TranslateMessage(&msg); /* Translate key codes to chars if present */

        DispatchMessage(&msg); /* Send it to WndProc */

    }

    return msg.wParam;

}
