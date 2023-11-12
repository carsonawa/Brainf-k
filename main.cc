#include <iostream>
#include <string>
#include <stack>
#include <fstream>
using namespace std;
// #define debug //调试用

namespace bf
{
	stack <int>stk; //存储‘[’字符位置的栈
	char mem[128]; //申明内存
	short pointer = 0; //申明指针

	void initialize() //初始化
	{
		for (short i = 0; i < 256; i++)
		{
			mem[i] = 0;
		}
		pointer = 0;
		int count = stk.size();
		for (int i = 0; i < count; i++)
		{
			stk.pop();
		}
		
	}

	int run(string code) //跑代码
	{
		bool doIf = true;
		for (int i = 0; i < code.length(); i++)
		{
			char command = code[i];
			if (doIf)
			{
				switch (command)
				{
					case '+':
						if (mem[pointer] == 127)
							mem[pointer] = 0;
						else
							++mem[pointer];
						break;
					case '-':
						if (mem[pointer] == 0)
							mem[pointer] = 127;
						else
							--mem[pointer];
						break;
					case '>':
						if (pointer == 127)
							pointer = 0;
						else
							++pointer;
						break;
					case '<':
						if (pointer == 0)
							pointer = 127;
						else
							--pointer;
						break;
					case '.':
						cout << mem[pointer];
						break;
					case ',':
						char str[256];
						cin >> str;
						mem[pointer] = str[0];
						break;
					case '[':
						if (mem[pointer] == 0)
							doIf = false;
						else
							stk.push(i);
						break;
					case ']':
						if (mem[pointer] != 0)
							i = stk.top();
						else
							stk.pop();
					default:
						break;
				}
			}
			else
			{
				if (command == ']')
				{
					doIf = true;
				}
			}
		}
		return 0;
	}
}

void shell()
{
	cout << "Brainfuck shell" << endl << "version 1.0.0" << endl;
	string uinput;
	while (true)
	{
		cout << ">";
		cin >> uinput; //接受用户输入
		if (uinput == "exit") //如果输入的是exit
		{
			break; //退出程序
		}
		bf::initialize();
		#ifdef debug
			for (int i = 0; i < uinput.length(); i++)
			{
				cout << uinput[i]; //测试用
			}
			
			cout << endl;
		#endif
		bf::run(uinput);
		cout << endl;
	}
}

int main(int argc, char *argv[]) 
{
	#ifdef debug
		cout << argc << endl;
	#endif
	switch (argc) //检查参数个数
	{
		case 1: //如果没有参数传入
			shell(); //交互界面
			return 0;
		default:
			string file = argv[1];
			ifstream t(file);
			string str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());
			#ifdef debug
				cout << "code:" << str << endl;
			#endif
			bf::run(str);
			return 0;
	}
}