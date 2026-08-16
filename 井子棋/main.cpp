#include<graphics.h>
//出现问题：结束的时候未出现最后的棋子图案
//解决方法将判断与绘图位置变化

//问题2：cpu占有大 ，while速度太快 解决方法通过sleep函数来进行降低  先使用GetTickCount获取程序运行到现在的毫秒数


//井子棋使用二维数组 
char board_data[3][3] = { {'-','-','-'},{'-','-','-'} ,{'-','-','-'} };//3*3
//当前的棋子
char cur_piece = 'O';
//检测获胜
bool  CheckWin(char c) {//三个一行或对角线
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)
		return true;
	if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)
		return true;
	if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c)
		return true;
	if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c)
		return true;

	return false;

}
//检测平局
bool CheckDraw() {//平局全部占满
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board_data[i][j] == '-') {
				return false;
			}
		}
	}
	//没有-则返回true
	return true;

}

//棋盘
void drawBoard() {
	//竖线 200 0 600  line(x1,y1,x2,y2)
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
}

//棋子
void drawPiece() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (board_data[i][j]) {
			case 'O':
				//circle(x,y,radius) 中心点计算 xy各加100 即中点
				circle(200*j+100,200*i+100,100);
				break;
			case 'X'://line 链接对角线即可
				line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1));
				line(200 * (j + 1), 200 * i, 200 * j, 200 * (i + 1));
				break;
			case'-':
				break;
		
			}
		}
	}

}
//绘制提示信息
void DrawTipText() {
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型:%c"), cur_piece);

	settextcolor(RGB(225, 175, 45));
	//指定位置输出字符串
	outtextxy(0, 0, str);

}

int main() {
	//初始化窗口
	initgraph(600, 600);
	//防止出现闪烁
	BeginBatchDraw();
	bool isRunning = true;
	//窗口出现加循环
	while (isRunning) {
		DWORD start_time = GetTickCount();
		ExMessage msg;

		//读取操作
		while (peekmessage(&msg)) {
			//对接受信息进行判断
			if (msg.message == WM_LBUTTONDOWN) {
				//对数据信息进行操作
				int x = msg.x;
				int y = msg.y;

				//通过鼠标的xy轴计算当前处于棋盘的哪一个位置
				int index_x = x / 200;
				int index_y = y / 200;
				//判断当前棋盘是否有棋子没有放置
				if (board_data[index_y][index_x] == '-') {
					board_data[index_y][index_x] = cur_piece;//切换完成后更改棋子类型

					if (cur_piece == 'O') {
						cur_piece = 'X';
					}
					else
					{
						cur_piece = 'O';
					}
				}
				
			}
		}
		

		//
		cleardevice();
		//清空后绘制图片
		drawBoard();
		drawPiece();
		DrawTipText();
		FlushBatchDraw();
		//处理数据
		if (CheckWin('X')) {
			//X玩家获胜弹出弹窗 获取父窗口  ，  MB_OK，只有确认按键
			MessageBox(GetHWnd(), _T("玩家X获胜"), _T("游戏结束"), MB_OK);
			//弹出后修改循环条件
			isRunning = false;
		}
		else if (CheckWin('O')) {
			MessageBox(GetHWnd(), _T("玩家O获胜"), _T("游戏结束"), MB_OK);
			isRunning = false;
		}
		//都不满足平局
		else if (CheckDraw()) {
			MessageBox(GetHWnd(), _T("平局！"), _T("游戏结束"), MB_OK);
			isRunning = false;
		}
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		//小于期望时间则剩余时间进行休眠
		if (delta_time < 1000 / 60) {
			//休眠
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();
	return 0;
}