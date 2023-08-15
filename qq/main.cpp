#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <ctime>
#include <limits>
using namespace std;
#pragma warning(disable:4996) // 无视4996错误码

int fun() // 发送
{
    HWND targetWindow = FindWindowW(L"TXGuiFoundation", L"网安协会干事群"); // 寻找窗口句柄
    // cout << "QQ handle:" << targetWindow << endl;

    // 将窗口从最小化还原
    ShowWindow(targetWindow, SW_RESTORE);
    if (targetWindow) {
        WCHAR text[] = L"👀";    // 发送的字符
        for (int i = 0; i < wcslen(text); i++) {
            SendMessageW(targetWindow, WM_CHAR, text[i], 0);
        }
        // 模拟按下回车键
        SendMessage(targetWindow, WM_KEYDOWN, VK_RETURN, 0);
        // 模拟释放回车键
        SendMessage(targetWindow, WM_KEYUP, VK_RETURN, 0);
        // 取消窗口的顶层设置，使其不再一直在其他窗口之上
        SetWindowPos(targetWindow, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        return 1;
    }
    else {
        cout << "[*]未找到协会聊天框:" << targetWindow << endl;
        return 0;
    }
}

void yes() // 成功日志
{
    // 获取当前时间
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    // 格式化时间为字符串
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
    cout << timeStr << " 发送成功:)" << std::endl;
}

void no() // 失败日志
{
    // 获取当前时间
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    // 格式化时间为字符串
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
    cout << timeStr << " 发送失败:(" << endl;
}

void out() // 程序启动画面
{
    const char* content = R"(
 _                _            _   _                                  
| |__   __ _  ___| | _____  __| | | |__  _   _    ___ _   _  ___  ___ 
| '_ \ / _` |/ __| |/ / _ \/ _` | | '_ \| | | |  / _ \ | | |/ _ \/ __|
| | | | (_| | (__|   <  __/ (_| | | |_) | |_| | |  __/ |_| |  __/\__ \
|_| |_|\__,_|\___|_|\_\___|\__,_| |_.__/ \__, |  \___|\__, |\___||___/
                                         |___/        |___/           
    )";
    cout << content << endl;
}
int main() {
    out(); // 输出启动画面
    int minutes = 0; // 定义一个计时器
    bool hasGuessedCorrectly = false;
    while (!hasGuessedCorrectly)
    {
        cout << "打开协会聊天框并输入每多少分钟发送一次: ";
        cin >> minutes;
        if (cin.fail())
        {
            cout << "[*]请输入有效的整数。" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        else if (minutes <= 0)
        {
            cout << "[*]请输入一个大于零的分钟数。" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            hasGuessedCorrectly = true;
        }
    }
    cout << "开始发送协会文化 ";
    while (true) {
        int a = fun();
        if (a == 1) // 判断是否发送成功
        {
            yes(); // 输出成功日志
        }
        else
        {
            no(); // 输出失败日志
        }
        this_thread::sleep_for(chrono::minutes(minutes));
    }
    return 0;
}