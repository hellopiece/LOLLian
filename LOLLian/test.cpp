#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<math.h>

struct Backimg {
	IMAGE img_back[8][8];
	int x[8][8];
	int y[8][8];
};

void load();												// ??????
void put();													// ???????
void start();												// ?????
void fill(int i, int j, int ID);							// ?????????????,????????????
void judge();												// ????????
BOOL judge_no_zhe(int x1, int y1, int x2, int y2);			// ????????
BOOL judge_one_zhe(int x1, int y1, int x2, int y2);
BOOL judge_two_zhe(int x1, int y1, int x2, int y2);
void putimage_back(int x1, int y1, int x2, int y2);
void getimage_back();


IMAGE img[24], back[4], img_xy;
int img_x, img_y, imgxy[8][8], mouse_x[2], mouse_y[2], n_time;
int n, picture, imgID, num = 0;
Backimg myback;
MOUSEMSG m;

void main() {

	initgraph(1280, 720);
	srand((unsigned)time(NULL));

	load();
	start();
	put();
	judge();

	_getch();
	closegraph();
}

void load() {
	loadimage(&back[0], L"D:\\Program\\C\\Learn\\LOLLian\\source\\back 1.jpg", 1280, 720);
	loadimage(&img[0], L"D:\\Program\\C\\Learn\\LOLLian\\source\\1.jpg", 65, 65);
	loadimage(&img[1], L"D:\\Program\\C\\Learn\\LOLLian\\source\\2.jpg", 65, 65);
	loadimage(&img[2], L"D:\\Program\\C\\Learn\\LOLLian\\source\\3.jpg", 65, 65);
	loadimage(&img[3], L"D:\\Program\\C\\Learn\\LOLLian\\source\\4.jpg", 65, 65);
	loadimage(&img[4], L"D:\\Program\\C\\Learn\\LOLLian\\source\\5.jpg", 65, 65);
	loadimage(&img[5], L"D:\\Program\\C\\Learn\\LOLLian\\source\\6.jpg", 65, 65);
}

void put() {

	putimage(0, 0, &back[0]);

	getimage_back();
	for (int i = 1; i <= 6; i++) {
		n = 0;
		while (n != 6) {
			img_x = rand() % 6 + 1;
			img_y = rand() % 6 + 1;
			// ??????????
			if (imgxy[img_x][img_y] == -1) {
				putimage(img_x * 80 + 100, img_y * 70 + 100, &img[i - 1]);
				imgID = i;
				fill(img_x, img_y, imgID);

				n++;
			}
		}
	}
}

void getimage_back() {
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			myback.x[i][j] = i * 80 + 100;
			myback.y[i][j] = j * 70 + 100;
			getimage(&myback.img_back[i][j], myback.x[i][j], myback.y[i][j], 80, 70);
		}
	}
}

void start() {
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			imgxy[i][j] = -1;
		}
	}
}

void fill(int i, int j, int ID) {
	imgxy[i][j] = ID;
}

void judge() {

	while (1) {
		while (MouseHit()) {
			m = GetMouseMsg();
			switch (m.uMsg) {
			case WM_LBUTTONDOWN:
				mouse_x[num] = (m.x - 100) / 80;
				mouse_y[num] = (m.y - 100) / 70;
				if (imgxy[mouse_x[num]][mouse_y[num]] != -1) {
					setlinecolor(YELLOW);
					setlinestyle(PS_SOLID, 5);
					rectangle(mouse_x[num] * 80 + 102, mouse_y[num] * 70 + 102, mouse_x[num] * 80 + 162, mouse_y[num] * 70 + 162);
					num++;
				}
				else {
					putimage(mouse_x[0] * 80 + 100, mouse_y[0] * 70 + 100, &img[imgxy[mouse_x[0]][mouse_y[0]] - 1]);
					num = 0;
				}
				if (num == 2) {
					// ??????????
					if (!(mouse_x[0] == mouse_x[1] && mouse_y[0] == mouse_y[1])) {
						if (imgxy[mouse_x[0]][mouse_y[0]] == imgxy[mouse_x[1]][mouse_y[1]]) {
							if (judge_no_zhe(mouse_x[0], mouse_y[0], mouse_x[1], mouse_y[1])) {
								line(mouse_x[0] * 80 + 130, mouse_y[0] * 70 + 130, mouse_x[1] * 80 + 130, mouse_y[1] * 70 + 130);
								Sleep(100);
								putimage_back(mouse_x[0], mouse_y[0], mouse_x[1], mouse_y[1]);
								imgxy[mouse_x[0]][mouse_y[0]] = -1;
								imgxy[mouse_x[1]][mouse_y[1]] = -1;
							}
							else if (judge_one_zhe(mouse_x[0], mouse_y[0], mouse_x[1], mouse_y[1]) || judge_two_zhe(mouse_x[0], mouse_y[0], mouse_x[1], mouse_y[1])) {
								imgxy[mouse_x[0]][mouse_y[0]] = -1;
								imgxy[mouse_x[1]][mouse_y[1]] = -1;
							}
						}
						else {
							putimage(mouse_x[0] * 80 + 100, mouse_y[0] * 70 + 100, &img[imgxy[mouse_x[0]][mouse_y[0]] - 1]);
							putimage(mouse_x[1] * 80 + 100, mouse_y[1] * 70 + 100, &img[imgxy[mouse_x[1]][mouse_y[1]] - 1]);
						}
					}
					else if (mouse_x[0] == mouse_x[1] && mouse_y[0] == mouse_y[1]) {
						putimage(mouse_x[0] * 80 + 100, mouse_y[0] * 70 + 100, &img[imgxy[mouse_x[0]][mouse_y[0]] - 1]);
					}
					// ??????,???????????
					num = 0;
				}
				break;
			case WM_RBUTTONDOWN:
				putimage(m.x, m.y, &img[0]);
				break;
			}
			FlushMouseMsgBuffer();

		}
	}
}

BOOL judge_no_zhe(int x1, int y1, int x2, int y2) {
	int num_x = x1;
	int num_y = y1;
	int judge_lian = 0;
	if (x1 == x2) {
		if (abs(y1 - y2) == 1) {
			judge_lian = 1;
		}
		else if (y1 < y2) {
			num_y += 1;
			for (num_y; num_y < y2; num_y++) {
				if (imgxy[x1][num_y] != -1) {
					return false;
				}
				else {
					judge_lian = 1;
				}
			}
		}
		else if (y1 > y2) {
			num_y -= 1;
			for (num_y; num_y > y2; num_y--) {
				if (imgxy[x1][num_y] != -1) {
					return false;
				}
				else {
					judge_lian = 1;
				}
			}

		}
	}
	else if (y1 == y2) {
		if (abs(x1 - x2) == 1) {
			judge_lian = 1;
		}
		else if (x1 < x2) {
			num_x += 1;
			for (num_x; num_x < x2; num_x++) {
				if (imgxy[num_x][y1] != -1) {
					return false;
				}
				else {
					judge_lian = 1;
				}
			}
		}
		else if (x1 > x2) {
			num_x -= 1;
			for (num_x; num_x > x2; num_x--) {
				if (imgxy[num_x][y1] != -1) {
					return false;
				}
				else {
					judge_lian = 1;
				}
			}

		}
	}
	else {
		judge_lian = 0;
	}

	if (judge_lian == 1) {
		return true;
	}
	else {
		return false;
	}
}

BOOL judge_one_zhe(int x1, int y1, int x2, int y2) {
	if (imgxy[x2][y1] == -1) {
		imgxy[x2][y1] = imgxy[x1][y1];
		if (judge_no_zhe(x1, y1, x2, y1)) {
			if (judge_no_zhe(x2, y1, x2, y2)) {
				line(x1 * 80 + 130, y1 * 70 + 130, x2 * 80 + 130, y1 * 70 + 130);
				line(x2 * 80 + 130, y1 * 70 + 130, x2 * 80 + 130, y2 * 70 + 130);
				Sleep(100);
				BeginBatchDraw();
				putimage_back(x1, y1, x2, y1);
				putimage_back(x2, y1, x2, y2);
				EndBatchDraw();
				imgxy[x2][y1] = -1;
				return true;
			}
		}
		imgxy[x2][y1] = -1;
	}
	if (imgxy[x1][y2] == -1) {
		imgxy[x1][y2] = imgxy[x1][y1];
		if (judge_no_zhe(x1, y1, x1, y2)) {
			if (judge_no_zhe(x1, y2, x2, y2)) {
				line(x1 * 80 + 130, y1 * 70 + 130, x1 * 80 + 130, y2 * 70 + 130);
				line(x1 * 80 + 130, y2 * 70 + 130, x2 * 80 + 130, y2 * 70 + 130);
				Sleep(100);
				BeginBatchDraw();
				putimage_back(x1, y1, x1, y2);
				putimage_back(x1, y2, x2, y2);
				EndBatchDraw();
				imgxy[x1][y2] = -1;
				return true;
			}
		}
		imgxy[x1][y2] = -1;
	}
	return false;
}

BOOL judge_two_zhe(int x1, int y1, int x2, int y2) {
	int i = 0, j = 0;
	for (i; i <= 7; i++) {
		if (imgxy[x1][i] == -1 && imgxy[x2][i] == -1) {
			imgxy[x1][i] = imgxy[x2][i] = imgxy[x1][y1];
			if (judge_no_zhe(x1, y1, x1, i)) {
				if (judge_no_zhe(x1, i, x2, i)) {
					if (judge_no_zhe(x2, y2, x2, i)) {
						line(x1 * 80 + 130, i * 70 + 130, x2 * 80 + 130, i * 70 + 130);
						line(x1 * 80 + 130, y1 * 70 + 130, x1 * 80 + 130, i * 70 + 130);
						line(x2 * 80 + 130, i * 70 + 130, x2 * 80 + 130, y2 * 70 + 130);
						Sleep(100);
						BeginBatchDraw();
						putimage_back(x1, i, x2, i);
						putimage_back(x1, y1, x1, i);
						putimage_back(x2, i, x2, y2);
						EndBatchDraw();
						imgxy[x1][i] = imgxy[x2][i] = -1;
						return true;
					}
				}
			}
			imgxy[x1][i] = imgxy[x2][i] = -1;
		}
	}
	for (j = 0; j <= 7; j++) {
		if (imgxy[j][y1] == -1 && imgxy[j][y2] == -1) {
			imgxy[j][y1] = imgxy[j][y2] = imgxy[x1][y1];
			if (judge_no_zhe(x1, y1, j, y1)) {
				if (judge_no_zhe(j, y1, j, y2)) {
					if (judge_no_zhe(x2, y2, j, y2)) {
						line(x1 * 80 + 130, y1 * 70 + 130, j * 80 + 130, y1 * 70 + 130);
						line(j * 80 + 130, y1 * 70 + 130, j * 80 + 130, y2 * 70 + 130);
						line(j * 80 + 130, y2 * 70 + 130, x2 * 80 + 130, y2 * 70 + 130);
						Sleep(100);
						BeginBatchDraw();
						putimage_back(x1, y1, j, y1);
						putimage_back(j, y1, j, y2);
						putimage_back(j, y2, x2, y2);
						EndBatchDraw();
						imgxy[j][y1] = imgxy[j][y2] = -1;
						return true;
					}
				}
			}
			imgxy[j][y1] = imgxy[j][y2] = -1;
		}
	}
	return false;
}

void putimage_back(int x1, int y1, int x2, int y2) {
	int num_x = x1;
	int num_y = y1;
	if (x1 == x2) {
		if (y1 < y2) {
			for (num_y; num_y <= y2; num_y++) {
				putimage(x1 * 80 + 100, num_y * 70 + 100, &myback.img_back[x1][num_y]);
			}
		}
		if (y1 > y2) {
			for (num_y; num_y >= y2; num_y--) {
				putimage(x1 * 80 + 100, num_y * 70 + 100, &myback.img_back[x1][num_y]);
			}
		}
	}
	if (y1 == y2) {
		if (x1 < x2) {
			for (num_x; num_x <= x2; num_x++) {
				putimage(num_x * 80 + 100, y1 * 70 + 100, &myback.img_back[num_x][y1]);
			}
		}
		if (x1 > x2) {
			for (num_x; num_x >= x2; num_x--) {
				putimage(num_x * 80 + 100, y1 * 70 + 100, &myback.img_back[num_x][y1]);
			}
		}
	}
}