#include<graphics.h>
#include<string>
using namespace std;
//动画练习  
//序列帧动画：一组动画素材随时切换，形成动画效果
//全局变量
int idx_current_anim = 0;	//当前帧索引

//动画组数
const int ANIM_COUNT = 6;
//动画素材
IMAGE img_left[ANIM_COUNT];//面向左的动画素材

//动画轮换函数
void loadAnimation() {
	//遍历图片拼出路经 easyx中使用的wchar不是char 所以使用wstring 而非string  用法要加L
	for (int i = 0; i < ANIM_COUNT; i++) {
		wstring path = L"player_left_" + to_wstring(i) + L".png";
		//easyx只认c风格库 ，c_str（）将string转化成const char*类型
		loadimage(&img_left[i], path.c_str());

	}
}

int main() {
	//初始化
	initgraph(1270, 720);
	ExMessage msg;
	loadAnimation();//加载动画函数
	BeginBatchDraw();
	bool running = true;
	while (running) {
		DWORD start_time = GetTickCount();
		//消息
		while (peekmessage(&msg)) {

		}
		//数据:更新动画帧索引
		static int count = 0;//让count变成静态变量，保证每次循环都能累加，不会被重置为0
		//每5帧切换一次动画 切换到6之后更新为0
		if (++count % 5 == 0) {
			idx_current_anim++;
		}
		idx_current_anim = idx_current_anim % ANIM_COUNT;
		
	//动画
		cleardevice();
		//绘制
		putimage(500,500,&img_left[idx_current_anim]);
		FlushBatchDraw();
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60) {
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();
	return 0;
}