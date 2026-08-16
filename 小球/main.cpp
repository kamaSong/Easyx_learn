#include<graphics.h>
//不加cleardevice出现有很多圆，
// 目前问题圆会闪烁需要加双缓冲
//beginbacthdraw（）endbatchdraw（）
//全局变量
int x = 300, y = 300;
int main() {
	initgraph(1280, 720);
	BeginBatchDraw();

	//需要使用循环卡住窗口初始化
	while (true) {

		ExMessage msg;
		//peekmessage 传入msg的地址
		while (peekmessage(&msg)) {
			if (msg.message == WM_MOUSEMOVE) {
				//小球跟随鼠标移动圆心
				x = msg.x;
				y = msg.y;
			}

		}
		//清空绘图 cleardevice
		cleardevice();
		
		solidcircle(x, y, 20);
		FlushBatchDraw();
		
	}
	EndBatchDraw();
	return 0;
}