// Copyright (c) 2020 MattKC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <windows.h>

#define WINDOW_STYLE        WS_VISIBLE+WS_OVERLAPPEDWINDOW-WS_THICKFRAME-WS_MAXIMIZEBOX
#define WINDOW_WIDTH        640
#define WINDOW_HEIGHT       480
#define TILE_SIZE           40
#define HORIZONTAL_TILES    WINDOW_WIDTH / TILE_SIZE
#define VERTICAL_TILES      WINDOW_HEIGHT / TILE_SIZE
#define MAX_TILE_COUNT      HORIZONTAL_TILES * VERTICAL_TILES
#define START_X             HORIZONTAL_TILES / 2
#define START_Y             VERTICAL_TILES / 2
#define SNAKE_PADDING       TILE_SIZE / 4
#define SNAKE_SIZE          TILE_SIZE - SNAKE_PADDING - SNAKE_PADDING
#define FOOD_PADDING        TILE_SIZE / 8
#define FOOD_SIZE           TILE_SIZE - FOOD_PADDING - FOOD_PADDING
#define MAX_DIR_QUEUE       8

struct Position {
    int x;
    int y;
};

const char* window_name = "Snake";
RECT window_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
struct Position* snake_pos;
struct Position food_pos;
int snake_len = 1;
int player_dir = 0;
int* dir_queue;
int dir_queue_sz = 0;
int dir_queue_read = 0;
BOOL forgiveness = FALSE;

BOOL PosEqual(struct Position* p1, struct Position* p2)
{
    return p1->x == p2->x && p1->y == p2->y;
}

BOOL PosExists(struct Position* p)
{
    for (int i=0;i<snake_len;i++) {
        if (PosEqual(&snake_pos[i], p)) {
            return TRUE;
        }
    }

    return FALSE;
}

void SetFood()
{
    do {
        food_pos.x = rand() % HORIZONTAL_TILES;
        food_pos.y = rand() % VERTICAL_TILES;
    } while (PosExists(&food_pos));
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
switch (uMsg)
{
case WM_PAINT:
{
PAINTSTRUCT ctx;

HDC device = BeginPaint(hwnd, &ctx);

SelectObject(device, GetStockObject(NULL_PEN));

struct Position food_pos_px;

food_pos_px.x = food_pos.x * TILE_SIZE + FOOD_PADDING;
food_pos_px.y = food_pos.y * TILE_SIZE + FOOD_PADDING;

Rectangle(
        device,
        food_pos_px.x,
food_pos_px.y,
food_pos_px.x + FOOD_SIZE,
food_pos_px.y + FOOD_SIZE);

if (player_dir == -1) {
SelectObject(device, CreateSolidBrush(0x0000FF));
} else if (player_dir == -2) {
SelectObject(device, CreateSolidBrush(0x00FF00));
}

struct Position top_left;
struct Position bottom_right;

RECT draw_rect;

for (int i=0; i<snake_len; i++) {
top_left = snake_pos[i];
bottom_right = snake_pos[i];

if (i > 0) {
top_left.x = min(top_left.x, snake_pos[i-1].x);
top_left.y = min(top_left.y, snake_pos[i-1].y);
bottom_right.x = max(bottom_right.x, snake_pos[i-1].x);
bottom_right.y = max(bottom_right.y, snake_pos[i-1].y);
}

draw_rect.left = top_left.x*TILE_SIZE + SNAKE_PADDING;
draw_rect.top = top_left.y*TILE_SIZE + SNAKE_PADDING;
draw_rect.right = (1+bottom_right.x)*TILE_SIZE - SNAKE_PADDING;
draw_rect.bottom = (1+bottom_right.y)*TILE_SIZE - SNAKE_PADDING;

if (top_left.x == 0 && bottom_right.x == HORIZONTAL_TILES-1) {
// Exception for wrapping around the X axis
Rectangle(
        device,
0,
draw_rect.top,
TILE_SIZE - SNAKE_PADDING,
draw_rect.bottom);

draw_rect.left = WINDOW_WIDTH - TILE_SIZE + SNAKE_PADDING;
draw_rect.right = WINDOW_WIDTH;
} else if (top_left.y == 0 && bottom_right.y == VERTICAL_TILES-1) {
// Exception for wrapping around the Y axis
Rectangle(
        device,
        draw_rect.left,
0,
draw_rect.right,
TILE_SIZE - SNAKE_PADDING);

draw_rect.top = WINDOW_HEIGHT - TILE_SIZE + SNAKE_PADDING;
draw_rect.bottom = WINDOW_HEIGHT;
}

// Draw a long rectangle from the previous position to this one
Rectangle(
        device,
        draw_rect.left,
draw_rect.top,
draw_rect.right,
draw_rect.bottom);
}

EndPaint(hwnd, &ctx);
break;
}
case WM_KEYDOWN:
{
if (player_dir < 0) {
break;
}
switch (wParam) {
case VK_LEFT:
case VK_UP:
case VK_RIGHT:
case VK_DOWN:
dir_queue[dir_queue_sz%MAX_DIR_QUEUE] = wParam;
dir_queue_sz++;
break;
case 0x50: // Pause
case VK_PAUSE: // Pause
player_dir = 0;
dir_queue_read = dir_queue_sz;
break;
}
break;
}
case WM_TIMER:
{
while (dir_queue_read < dir_queue_sz) {
int proposed_dir = dir_queue[dir_queue_read%MAX_DIR_QUEUE];
dir_queue_read++;

if (player_dir != proposed_dir
&& proposed_dir+2 != player_dir
&& proposed_dir-2 != player_dir) {
player_dir = proposed_dir;
break;
}
}

struct Position new_pos = snake_pos[0];
BOOL moved = TRUE;

switch (player_dir) {
case VK_LEFT:
new_pos.x--;
break;
case VK_RIGHT:
new_pos.x++;
break;
case VK_UP:
new_pos.y--;
break;
case VK_DOWN:
new_pos.y++;
break;
default:
moved = FALSE;
}

if (moved) {
if (new_pos.x < 0) {
new_pos.x = HORIZONTAL_TILES-1;
} else if (new_pos.x == HORIZONTAL_TILES) {
new_pos.x = 0;
} else if (new_pos.y < 0) {
new_pos.y = VERTICAL_TILES-1;
} else if (new_pos.y == VERTICAL_TILES) {
new_pos.y = 0;
}

snake_len--;
BOOL collided = PosExists(&new_pos);
snake_len++;

if (collided) { // Check for collision
if (forgiveness) {
player_dir = -1;
dir_queue_read = dir_queue_sz;
InvalidateRect(hwnd, 0, 1);
} else {
forgiveness = TRUE;
}
} else {
BOOL ate_food = PosEqual(&new_pos, &food_pos);

if (ate_food) {
// Ate food, increase snake size
snake_len++;
}

forgiveness = FALSE;

for (int i=snake_len-1; i>0; i--) {
snake_pos[i] = snake_pos[i-1];
}

snake_pos[0] = new_pos;

if (ate_food) {
if (snake_len == MAX_TILE_COUNT) {
food_pos.x = -1;
player_dir = -2;
dir_queue_read = dir_queue_sz;
} else {
SetFood();
}
}

InvalidateRect(hwnd, 0, 1);
}
}
break;
}
case WM_CLOSE:
PostQuitMessage(0);
break;
}
🐍
return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int main()
{
    HMODULE instance = GetModuleHandleA(NULL);

    AdjustWindowRect(&window_rect, WINDOW_STYLE, FALSE);

    WNDCLASSEXA window_class;
    window_class.cbSize = 48;
    window_class.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW ;
    window_class.lpfnWndProc = WindowProc;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = instance;
    window_class.hIcon = LoadIconA(0, IDI_APPLICATION);
    window_class.hCursor = LoadCursorA(0, IDI_APPLICATION);
    window_class.hbrBackground = CreateSolidBrush(0);
    window_class.lpszMenuName = 0;
    window_class.lpszClassName = window_name;
    window_class.hIconSm = 0;

    RegisterClassExA(&window_class);

    // Start game
    HANDLE heap = GetProcessHeap();

    snake_pos = HeapAlloc(heap, 0, sizeof(struct Position)*MAX_TILE_COUNT);
    snake_pos[0].x = START_X;
    snake_pos[0].y = START_Y;

    dir_queue = HeapAlloc(heap, 0, sizeof(struct Position)*MAX_DIR_QUEUE);

    HWND window = CreateWindowExA(
            0,
            window_name,
            window_name,
            WINDOW_STYLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            window_rect.right - window_rect.left,
            window_rect.bottom - window_rect.top,
            0,
            0,
            instance,
            NULL);

    // Don't seem to be necessary? Saves space to remove
    //ShowWindow(window, SW_SHOW);
    //UpdateWindow(window);

    // Set game timer
    SetFood();
    SetTimer(window, 0, 150, 0);

    MSG msg;

    while (GetMessage(&msg, 0, 0, 0)) {
        if (msg.message == WM_QUIT) {
            break;
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    HeapFree(heap, 0, dir_queue);
    HeapFree(heap, 0, snake_pos);

    //ExitProcess(0);

    return 0;
}
