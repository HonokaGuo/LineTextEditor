// ProjectExe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <fstream>
#include <cstring>
#include "doubleNode.h"
#include "douNodeControl.h"
#include "KMP.h"
#define NAMELEN 80   //i know using define is not a good practice, but it won't harm here
#define STRLEN 200

void read_file(douNodeControl& pannel) {
	std::fstream file;
	pannel.clear();
	char inputFileName[NAMELEN];
	char block[1000];
	bool success = 0;
	char ch;
	std::cout << "Please enter input file name: ";
	std::cin.getline(inputFileName, NAMELEN, '\n');
	file.open(inputFileName, std::ios::in);
	success = file.is_open();
	while (!success) {
		std::cout << "input file doesn't exist, please try again" << std::endl;
		std::cout << "enter q to quit" << std::endl;
		std::cin.getline(inputFileName, NAMELEN, '\n');
		file.open(inputFileName, std::ios::in);
		success = file.is_open();
		if (inputFileName[0] == 'q' && inputFileName[1] == '\0') {
			exit (0);
		}
	}
	int lineNum = 1;
	while (file.getline(block, 1000)) {
		pannel.insert(lineNum, block, strlen(block) + 2);
		lineNum++;
		file.clear();
	} 
	file.close();
	std::cout << "done!" << std::endl;
	std::cout << "---------------------" << std::endl;
}

void write_file(douNodeControl& pannel) {
	std::ofstream file;
	char outputFileName[NAMELEN];
	bool success = 0;
	doubNode* tmp = pannel.head;
	char ch;
	std::cout << "Please enter output file name: " << std::endl;
	while (ch = getchar() != '\n');
	std::cin.getline(outputFileName, NAMELEN, '\n');
	file.open(outputFileName, std::ios::out);
	success = file.is_open();
	while (tmp->next != nullptr) {
			tmp = tmp->next;
			file << tmp->data << std::endl;
	}
	std::cout << "done!" << std::endl;
	file.close();
}

void display_all(douNodeControl& pannel) {
	for (int i = 1; i <= pannel.length(); ++i) {
		pannel.showLine(i);
	}
}

void change_sentence(int lineNum, douNodeControl& pannel) {
	doubNode* p;
	pannel.lineNumtoPos(lineNum, p);    //use side effects to get p
	//p指向要修改的节点
	if(!pannel.m_delete(lineNum)){
		std::cout<<"not found!"<<std::endl;
		return;
	}
	std::cout << "enter new line:";
	char c;
	while ((c = getchar()) != '\n');    //this is very important!!!!! clean the cin buffer
	char block[1000];
	std::cin.getline(block, 1000);
	if(p!=nullptr) pannel.insert(lineNum, block, strlen(block) + 2);
	display_all(pannel);
}

void insert_sentence(int lineNum, douNodeControl& pannel) {
	//p指向要修改的节点
	std::cout << "enter new line:";
	char c;
	while ((c = getchar()) != '\n');    //this is very important!!!!! clean the cin buffer
	char block[1000];
	std::cin.getline(block, 1000,'\n');
	pannel.insertNewLine(lineNum, block, strlen(block) + 2);
	display_all(pannel);
}

bool line_search_substring_replace(int lineNum,douNodeControl& pannel, char*& substr, char*& replace){
	int location = 0;
	int flag=0;
	doubNode* p;
	pannel.lineNumtoPos(lineNum,p);
	while (location != -1) {
		location = KMP(p->data, substr, location);
		// 替换操作：
		char block[1000];
		if (location > -1) {
			flag=1;
			strncpy_s(block, 1000, p->data, location);
			strcat_s(block, 600, replace);
			strcat_s(block + strlen(block), 500, p->data + location + strlen(substr));
			block[strlen(block)] = '\0';
			p = p->prev;
			pannel.m_delete(p->next->line);
			pannel.insert(p->line + 1, block, strlen(block) + 2);
			location++;
			p = p->next;
		}
	}
	if(flag==0) std::cout<<"not found!"<<std::endl;
	return true;
}

bool search_substring_replace(douNodeControl& pannel, char*& substr, char*& replace) {
	int location = 0;
	int flag=0;
	doubNode* p = pannel.head->next;
	while (p != nullptr) {
		location = 0;
		while (location != -1) {
			location = KMP(p->data, substr, location);
			// 替换操作：
			char block[1000];
			if (location > -1) {
				flag=1;
				strncpy_s(block, 1000, p->data, location);
				strcat_s(block, 600, replace);
				strcat_s(block + strlen(block), 500, p->data + location + strlen(substr));
				block[strlen(block)] = '\0';
				p = p->prev;
				pannel.m_delete(p->next->line);
				pannel.insert(p->line + 1, block, strlen(block) + 2);
				location++;
				p = p->next;
			}
		}
		p = p->next;
	}
	if(flag==0) std::cout<<"not found!"<<std::endl;
	return true;
}

bool line_search_substing_show(int lineNum, douNodeControl& pannel, char*& substr){
	int location=0,flag=0;
	doubNode *p;
	pannel.lineNumtoPos(lineNum,p);
	while (location != -1) {
		location = KMP(p->data, substr, location);
		if (location > -1) {
			flag=1;
			std::cout << "line" << ":" << p->line << "    location: " << location << std::endl;
			std::cout << p->data << std::endl;
			location++;
		}
	}
	if(flag==0) std::cout<<"not found!"<<std::endl;
	return true;
}

bool search_substring_show(douNodeControl& pannel, char*& substr) {
	int location = 0,flag=0;
	doubNode* p = pannel.head->next;
	while (p != nullptr) {
		location = 0;
		while (location != -1) {
			location = KMP(p->data, substr, location);
			if (location > -1) {
				flag=1;
				std::cout << "line" << ":" << p->line << "    location: " << location << std::endl;
				std::cout << p->data << std::endl;
				location++;
			}
		}
		p = p->next;
	}
	if(flag==0) std::cout<<"not found!"<<std::endl;
	return true;
}


int main(void) {
	douNodeControl pannel;
	char outputFileName[NAMELEN];
	read_file(pannel);
	display_all(pannel);
	char op;
	int p;
	char ch;
	char* pat = new char[STRLEN];
	char* replace = new char[STRLEN];
		std::cout << "Enter h to view the operation command and its meaning" << std::endl;
	while (1) {
		p = 0;
		ch = 0;
		std::cout << "Enter operation command:" << std::endl;
		std::cin >> op;
		switch (op) {
		case 'h':
			std::cout << "[b:Display current file content] [f:Go to the first line] \n[l:Go to the last line] [p:Go to the previous line] [n:Go to the next line]" << std::endl;
			std::cout << "[a:Go to a specific line] [i:Insert a line] [d:Delete a line] \n[w:Replace a line] [t:Replace a substring] [z:Find a specific substring]" << std::endl;
			std::cout << "[c:Count the number of lines and characters in the file] \n[r:Reload the file] [s:Save the current file] [e:Exit the system]" << std::endl;
			break;
		case 'b':
			display_all(pannel);
			break;//显示当前文件内容
		case 'f':
			pannel.showLine(1);
			break;
		case 'l':
			pannel.showLine(pannel.length());
			break;
			//最后一行
		case 'p':
			pannel.showLineTo(pannel.curLineNum - 1);
			break;
			//到前一行
		case 'n':
			pannel.showLineTo(pannel.curLineNum + 1);
			break;
			//到下一行
		case 'a':
			std::cout << "Enter the line number you want to jump to (enter 0 to return)" << std::endl;
			std::cin >> p;
			pannel.showLineTo(p);
			break;
			//调用函数
			//到指定的某一行
		case 'i':
			std::cout << "Enter 0 to exit the current function, -1 to insert at the current line position, or enter a number to insert at the corresponding line" << std::endl;
			std::cin >> p;
			if (p == 0) {
				break;
			}
			else if (p == -1) {
				insert_sentence(pannel.curLineNum, pannel);
			}
			else {
				insert_sentence(p, pannel);
			}
			break;
			//调用插入一行函数
			//插入一行
		case 'd':
			std::cout << "Enter 0 to return" << std::endl;
			std::cout << "Enter the line number you want to delete and execute" << std::endl;
			std::cin >> p;
			if(!pannel.deleteLine(p)) std::cout<<"not found!"<<std::endl;
			break;
			//删除一行
		case 'w':
			std::cout << "Enter 0 to exit the current function, -1 to modify the current line, or enter a number to modify the corresponding line." << std::endl;
			std::cin >> p;
			if (p == 0) {
				break;
			}
			else if (p == -1) {
				change_sentence(pannel.curLineNum, pannel);
			}
			else {
				change_sentence(p, pannel);
			}
			break;
			//调用替换函数
			//替换当前行
		case 't':
			while (ch = getchar() != '\n');   //clean cin buffer
			std::cout << "Please enter pattern: ";
			std::cin.getline(pat, 200, '\n');
			std::cout << "Please enter replacement: ";
			std::cin.getline(replace, 200, '\n');
			char ch;
			std::cout<<"enter f : fileRelpace; enter l : lineReplace"<<std::endl;
			std::cin>>ch;
			if(ch=='f'){
				search_substring_replace(pannel, pat, replace);
				display_all(pannel);
			//文本替换某个子串
			}
			if(ch=='l'){
				std::cout<<"Please enter position:";
				int lineNum;
				std::cin>>lineNum;
				line_search_substring_replace(lineNum,pannel,pat,replace);
				display_all(pannel);
			//具体一行替换某个字串
			}	
			break;
		case 'z':
			while (ch = getchar() != '\n');   //clean cin buffer
			std::cout << "Please enter pattern: ";
			std::cin.getline(pat, 200, '\n');
			std::cout<<"enter f : fileSearch; enter l : lineSearch"<<std::endl;
			std::cin>>ch;
			if(ch=='f'){
				search_substring_show(pannel, pat);
			//文本查找某个子串
			}
			if(ch=='l'){
				std::cout<<"Please enter position:";
				int lineNum;
				std::cin>>lineNum;
				line_search_substing_show(lineNum,pannel,pat);
			}
			break;
		case 'c':
			pannel.run_statistics();
			break;
			//统计文件行数及字符数
		case 'r':
			while ((ch = getchar()) != '\n');
			read_file(pannel);
			break;
			//重新读入文件
		case 's':
			write_file(pannel);
			break;
			//保存当前文件
		case 'e':
			exit(0);
			//退出系统
		default:
			std::cout << "The command input is incorrect, please re-enter" << std::endl;
			std::cout << "Enter 'h' to view help" << std::endl;
			break;

		}
	}
	delete[]pat;
	delete[]replace;
	return 0;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
