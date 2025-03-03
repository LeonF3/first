#include <windows.h>
#include <string>
#include <sstream>
#include <stack>
#include <cctype>
#include <algorithm>
using namespace std;

HFONT CreateScaledFont(int size) {
    return CreateFont(size, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                      CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                      DEFAULT_PITCH | FF_SWISS, "Arial");
}


const char g_szClassName[] = "Calculator";
// Global variables
HWND hDisplay; // Text box for displaying input/output
HWND hButtons[16]; // Buttons for numbers and operations

// Button labels (0-9, +, -, *, /, =, C)
const char *buttonLabels[] = { "7", "8", "9", "/", "4", "5", "6", "*", 
                               "1", "2", "3", "-", "0", "C", "=", "+" };

// Function to evaluate a basic math expression
double evaluateExpression(const std::string &expression) {
    std::istringstream input(expression);
    double result = 0, num;
    char op = '+';
    std::stack<double> numbers;

    while (input >> num) {
        if (op == '+') numbers.push(num);
        else if (op == '-') numbers.push(-num);
        else if (op == '*') {
            double top = numbers.top();
            numbers.pop();
            numbers.push(top * num);
        } else if (op == '/') {
            if (num == 0) return 0;  // Prevent division by zero
            double top = numbers.top();
            numbers.pop();
            numbers.push(top / num);
        }
        input >> op;  // Read next operator
    }

    while (!numbers.empty()) {
        result += numbers.top();
        numbers.pop();
    }

    return result;
}

// Function to handle button clicks
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
static bool isFullscreen = false;
static RECT windowRect;

   switch (msg) {

case WM_SIZE:
{
    int width = LOWORD(lParam);
    int height = HIWORD(lParam);

    if (width < 400) width = 400;
    if (height < 600) height = 600;

int displayHeight = height / 8;
    MoveWindow(hDisplay, 10, 10, width - 20, displayHeight, TRUE);

    int buttonWidth = (width - 50) / 4;
    int buttonHeight = (height - displayHeight - 100) / 4;

    int xPos = 10, yPos = (height / 8) + 20;
    for (int i = 0; i < 16; i++) {
        MoveWindow(hButtons[i], xPos, yPos, buttonWidth, buttonHeight, TRUE);

        xPos += buttonWidth + 10;
        if ((i + 1) % 4 == 0) {
            xPos = 10;
            yPos += buttonHeight + 10;
        }
    }

     // ✅ Keep button font size correct
 int buttonFontSize = buttonHeight / 2.5;  // Keep button fonts as they were
    HFONT buttonFont = CreateScaledFont(buttonFontSize);
    for (int i = 0; i < 16; i++) {
        SendMessage(hButtons[i], WM_SETFONT, (WPARAM)buttonFont, TRUE);
    }

    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW);

 // ✅ Scale output text font but prevent it from getting too large
    int maxFontSize = height / 10;  // Set a max font size to prevent overflow
    int outputFontSize = min(static_cast<int>(buttonFontSize * 1.1), maxFontSize);  // Use the smaller value
    HFONT outputFont = CreateScaledFont(outputFontSize);
    SendMessage(hDisplay, WM_SETFONT, (WPARAM)outputFont, TRUE);



}
break;
case WM_PAINT:
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // Set custom background color (Change RGB values for different colors)
    HBRUSH hBrush = CreateSolidBrush(RGB(240, 240, 240));
    FillRect(hdc, &ps.rcPaint, hBrush);
    DeleteObject(hBrush);

    EndPaint(hwnd, &ps);
}
break;


case WM_ERASEBKGND:
    return 1; // Prevents flickering by skipping default background erase



        case WM_KEYDOWN:
            if (wParam == VK_F11) { // Toggle fullscreen when F11 is pressed
                isFullscreen = !isFullscreen;
                if (isFullscreen) {
                    GetWindowRect(hwnd, &windowRect); // Save current window size
                    SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
                    ShowWindow(hwnd, SW_MAXIMIZE);
                } else {
                    SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
                    SetWindowPos(hwnd, NULL, windowRect.left, windowRect.top,
                                 windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
                                 SWP_FRAMECHANGED);
                    ShowWindow(hwnd, SW_NORMAL);
                }
            }
            break;
        case WM_COMMAND:
            for (int i = 0; i < 16; i++) {
                if ((HWND)lParam == hButtons[i]) {
                    int len = GetWindowTextLength(hDisplay);
                    char buffer[256];
                    GetWindowText(hDisplay, buffer, sizeof(buffer));

                    if (i == 13) { // Clear button (C)
                        SetWindowText(hDisplay, "");
                    } else if (i == 14) { // Equals button (=)
                        // Simple evaluation (needs improvement for real calculations)
double result = evaluateExpression(buffer);
sprintf(buffer, "%.2f", result);
SetWindowText(hDisplay, buffer);                        
                    } else {
                        strcat(buffer, buttonLabels[i]); // Append button text
                        SetWindowText(hDisplay, buffer);
                    }
                    return 0;
                }
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}



// WinMain (entry point for GUI programs)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = g_szClassName;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create main calculator window
    HWND hwnd = CreateWindowEx(0, g_szClassName, "Leon's Simple Calculator",
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create display (text box)
    hDisplay = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
        10, 10, 760, 50, hwnd, NULL, hInstance, NULL);

    // Create buttons (4x4 grid)
    int xPos = 10, yPos = 70, width = 100, height = 100;
    for (int i = 0; i < 16; i++) {
        hButtons[i] = CreateWindow("BUTTON", buttonLabels[i],
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            xPos, yPos, width, height, hwnd, reinterpret_cast<HMENU>(static_cast<intptr_t>(100 + i)), hInstance, NULL);

        xPos += 110; // Move right
        if ((i + 1) % 4 == 0) { // Move to next row after 4 buttons
            xPos = 10;
            yPos += 110;
        }
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
