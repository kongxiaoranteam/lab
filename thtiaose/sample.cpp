#include "motion.h"

#include "objectdetector.h"

#include <iostream>

#include <signal.h>



void got_signal(int);



int main(int argc, char ** argv)

{

	//���ø����˳��źţ����������ճ�������got_signal������������һ��������

	signal(SIGABRT, got_signal);

	signal(SIGTERM, got_signal);

	signal(SIGQUIT, got_signal);

	signal(SIGINT, got_signal);



	const int x_speed = 30;

	const int speed_up_msec = 200;



	//����һ��ObjectDetector��Ķ��󣬸����Ӿ�׷�٣���һ������Ϊ���֣��ڶ�����������ʾ��Щ���ڣ����Բ���

	ObjectDetector obj("test",  ShowSource|ShowBinary|ShowDrawing);

	//������ɫ�����Զ�����Ϊ�ļ����´λ��Զ���ȡ

	obj.adjust_color();



	getchar();

	//��ʼ���ߣ�ԭ��̤����

	//Motion::ins().walk_start();

	//���������ٶȣ���һ��������ֱ���ٶȣ��ڶ����������ٶȣ������Ҹ���������������Ϊ��������ʱ�䣨���룩�����Բ���

	//Motion::ins().walk(x_speed, 0, speed_up_msec);
         Motion::ins().head_move(0,40,0);


	int c = 0;

	while (c != 27) {

		//����һ֡ͼ�񣬲���Ϊ֡��������룩,�ڶ�������Ϊ����ѡ��ɲ���

		c = obj.process_by_color(10, Vertical);

		//�ж��Ƿ񲶻񵽾���

		if (!obj.empty()) {

			//ͨ��postion��Ա�������Ի�ȡ�����λ�ã�width��Ա�������Ի�ȡ����Ŀ�ȣ����ຯ����objectdetector.h�ļ�

			std::cout << "Postion: " << obj.postion() << " Width: " << obj.width() << std::endl;

		}

		//�����������Զ�������������true

		if (Motion::ins().fall_up()) {

			//������֮��������ǲ����ģ����¿�ʼ���߲������ٶ�

			Motion::ins().walk_start();

			Motion::ins().walk(x_speed, 0, speed_up_msec);

		}

	}

	return 0;

}



void got_signal(int)

{

	exit(0);

}
