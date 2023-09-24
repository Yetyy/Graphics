#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Исходный цвет заливки - красный
int squareX = 100; // Начальное положение квадрата по X
int squareY = 100; // Начальное положение квадрата по Y
int squareSize = 100; // Размер квадрата
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

        // Рисуем квадрат с текущим цветом заливки
        SelectObject(hdc, hBrush);
        Rectangle(hdc, squareX, squareY, squareX + squareSize, squareY + squareSize);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_RBUTTONDOWN: // Правая кнопка мыши - движение вправо
    {
        squareX += n; // Изменяем положение квадрата
        InvalidateRect(hWnd, NULL, TRUE); // Перерисовываем окно
        break;
    }
    case WM_LBUTTONDOWN: // Левая кнопка мыши - движение влево
    {
        squareX -= n; // Изменяем положение квадрата
        InvalidateRect(hWnd, NULL, TRUE); // Перерисовываем окно
        break;
    }
    case WM_KEYDOWN:
    {
        if (wParam == 'C') // Клавиша 'C' - изменить цвет заливки
        {
            DeleteObject(hBrush); // Удаляем текущий кисть
            hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)); // Создаем случайный цвет заливки
            InvalidateRect(hWnd, NULL, TRUE); // Перерисовываем окно
        }
        break;
    }
    case WM_DESTROY:
    {
        DeleteObject(hBrush); // Освобождаем кисть перед выходом
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
