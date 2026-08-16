#include<graphics.h>

int main() {
	initgraph(1270, 720);
	IMAGE img_backround;
	loadimage(&img_backround, _T("img\\background.png"));
	bool running = true;
	//缓冲
	BeginBatchDraw();
	while (running) {
		//通过gettickcount()获取当前时间，计算两次循环的时间差，控制帧率
		//操作处理
		ExMessage msg;
		while (peekmessage(&msg)) {

		}
	//数据处理
	// 
		//图形绘制
		cleardevice();
		putimage(0, 0, &img_backround);
		FlushBatchDraw();
	}
	EndBatchDraw();
	return 0;
}