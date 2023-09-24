#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // �������� ���� ������� - �������
int squareX = 100; // ��������� ��������� �������� �� X
int squareY = 100; // ��������� ��������� �������� �� Y
int squareSize = 100; // ������ ��������
const int n = 10;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("SquareMover");
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, TEXT("Square Mover"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // ������ ������� � ������� ������ �������
        SelectObject(hdc, hBrush);
        Rectangle(hdc, squareX, squareY, squareX + squareSize, squareY + squareSize);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_RBUTTONDOWN: // ������ ������ ���� - �������� ������
    {
        squareX += n; // �������� ��������� ��������
        InvalidateRect(hWnd, NULL, TRUE); // �������������� ����
        break;
    }
    case WM_LBUTTONDOWN: // ����� ������ ���� - �������� �����
    {
        squareX -= n; // �������� ��������� ��������
        InvalidateRect(hWnd, NULL, TRUE); // �������������� ����
        break;
    }
    case WM_KEYDOWN:
    {
        if (wParam == 'C') // ������� 'C' - �������� ���� �������
        {
            DeleteObject(hBrush); // ������� ������� �����
            hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)); // ������� ��������� ���� �������
            InvalidateRect(hWnd, NULL, TRUE); // �������������� ����
        }
        break;
    }
    case WM_DESTROY:
    {
        DeleteObject(hBrush); // ����������� ����� ����� �������
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
