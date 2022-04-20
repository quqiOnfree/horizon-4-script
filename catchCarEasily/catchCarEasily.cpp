#include "catchCarEasily.h"
#include <Windows.h>
#include <Winuser.h>
#include <conio.h>
#include <iostream>
#include <thread>
#include <qthread.h>
#include <qpushbutton.h>
#include <QtCore/qdebug.h>

using namespace std;

void down(int vk)
{
	keybd_event(vk, 0, 0, 0);
}

void up(int vk)
{
	keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
}

void press(int vk)
{
	down(vk);
	up(vk);
}

volatile bool closeThr = false;
volatile bool open = false;

bool hasCreateCrtl = false;

std::thread cthr;
std::thread thr;

void catchCarEasily::startThread()
{
	ui.pushButton->setEnabled(false);
	ui.spinBox->setEnabled(false);
	ui.spinBox_2->setEnabled(false);
	ui.spinBox_3->setEnabled(false);
	ui.spinBox_4->setEnabled(false);
	ui.spinBox_5->setEnabled(false);
	ui.spinBox_6->setEnabled(false);
	ui.spinBox_7->setEnabled(false);
	ui.spinBox_8->setEnabled(false);
	ui.spinBox_9->setEnabled(false);
	ui.spinBox_10->setEnabled(false);
	ui.spinBox_11->setEnabled(false);
	ui.spinBox_12->setEnabled(false);
	ui.spinBox_13->setEnabled(false);
	ui.spinBox_14->setEnabled(false);
	ui.spinBox_15->setEnabled(false);

	open = false;
	closeThr = false;

	if (!hasCreateCrtl)
	{
		thr = std::thread([this]() {
			while (true)
			{
				//if (closeThr) return;
				Sleep(ui.spinBox_15->value());
				Sleep(1000);

				if (open)
				{
					//拍卖进入
					for (auto i = 0ll; i < ui.spinBox->value(); i++)
					{
						press(VK_RETURN);
						Sleep(ui.spinBox_2->value());
						if (!open) continue;
					}

					//加载
					Sleep(ui.spinBox_3->value());
					if (!open) continue;

					//520,429
					{
						HWND hWnd = ::GetDesktopWindow();
						HDC hdc = ::GetDC(hWnd);
						COLORREF pixel = ::GetPixel(hdc, (double)520 / (double)1920 * (double)::GetSystemMetrics(SM_CXSCREEN), (double)429 / (double)1080 * (double)::GetSystemMetrics(SM_CYSCREEN));
						qDebug() << (double)520 / (double)1920 * (double)::GetSystemMetrics(SM_CXSCREEN) << (double)429 / (double)1080 * (double)::GetSystemMetrics(SM_CYSCREEN);
						if (pixel != CLR_INVALID) {
							int red = GetRValue(pixel);
							int green = GetGValue(pixel);
							int blue = GetBValue(pixel);
							if (!(255 == red && 255 == green && 255 == blue))
							{
								if (!open) continue;
								press(VK_ESCAPE);
								continue;
							}
						}
						else
						{
							if (!open) continue;
							press(VK_ESCAPE);
							continue;
						}
					}

					//按Y
					for (auto i = 0ll; i < ui.spinBox_4->value(); i++)
					{
						press(0x59);
						Sleep(ui.spinBox_5->value());
						if (!open) continue;
					}

					Sleep(ui.spinBox_6->value());
					if (!open) continue;

					//购买
					press(VK_DOWN);
					Sleep(10);
					for (auto i = 0ll; i < ui.spinBox_8->value(); i++)
					{
						press(VK_RETURN);
						Sleep(ui.spinBox_9->value());
						if (!open) continue;
					}

					Sleep(ui.spinBox_12->value());
					if (!open) continue;

					for (auto i = 0ll; i < ui.spinBox_13->value(); i++)
					{
						press(VK_RETURN);
						Sleep(ui.spinBox_14->value());
						if (!open) continue;
					}

					Sleep(ui.spinBox_7->value());
					if (!open) continue;

					//esc
					for (auto i = 0ll; i < ui.spinBox_10->value(); i++)
					{
						press(VK_ESCAPE);
						Sleep(ui.spinBox_11->value());
						if (!open) continue;
					}
				}
			}
			});
		thr.detach();
		cthr = std::thread([this]() {
			MSG msg = { 0 };
			RegisterHotKey(NULL, 1, MOD_NOREPEAT | MOD_CONTROL, 0x79);
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (msg.message == WM_HOTKEY)
				{
					Beep(500, 100);
					if (!open && ui.pushButton_2->isEnabled()) open = true;
					else open = false;
				}
			}
			});
		cthr.detach();
		hasCreateCrtl = true;
	}

	ui.pushButton_2->setEnabled(true);
}

void catchCarEasily::closeThread()
{
	ui.pushButton_2->setEnabled(false);
	closeThr = true;
	open = false;

	//Sleep(1000);

	ui.pushButton->setEnabled(true);
	ui.spinBox->setEnabled(true);
	ui.spinBox_2->setEnabled(true);
	ui.spinBox_3->setEnabled(true);
	ui.spinBox_4->setEnabled(true);
	ui.spinBox_5->setEnabled(true);
	ui.spinBox_6->setEnabled(true);
	ui.spinBox_7->setEnabled(true);
	ui.spinBox_8->setEnabled(true);
	ui.spinBox_9->setEnabled(true);
	ui.spinBox_10->setEnabled(true);
	ui.spinBox_11->setEnabled(true);
	ui.spinBox_12->setEnabled(true);
	ui.spinBox_13->setEnabled(true);
	ui.spinBox_14->setEnabled(true);
	ui.spinBox_15->setEnabled(true);
}

catchCarEasily::catchCarEasily(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.pushButton_2->setEnabled(false);

	connect(ui.pushButton, &QPushButton::clicked, this, &catchCarEasily::startThread);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &catchCarEasily::closeThread);
	//catchCarEasily::startThread();
}
