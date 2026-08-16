#include<graphics.h>
int main() {
	//初始化
	initgraph(1280, 720);
	IMAGE img_background;
	bool running = true;
	loadimage(&img_background, _T("background.png"));
	BeginBatchDraw();
	while (running) {
		DWORD start_time = GetTickCount();
		
		
		//操作
		
		//数据
		cleardevice();
		//00坐标开始覆盖全图
		putimage(0, 0, &img_background);
			//图像
			FlushBatchDraw();
			DWORD end_time = GetTickCount();
			DWORD delta_time = end_time - start_time;
			if(delta_time<1000 / 60) {
				Sleep(1000 / 60 - delta_time);
			}
	}
	EndBatchDraw();
	return 0;
}