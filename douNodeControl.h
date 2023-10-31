#pragma once
#include "doubleNode.h"
class douNodeControl {
public:
	doubNode* head;
	doubNode* get_elem_ptr(int position) const;
	int curLineNum;

	bool insert(int line, const char* e, int size, int lineNum = 0); //第四项参数不写则为前一个节点行号+1
	bool insertNewLine(int lineNum, const char* e, int size); //插入行块链并且后续块链行号+1
	bool deleteLine(int lineNum);//删除某块链，后续行号-1
	bool XdeleteLine(int lineNum); //删除某块链，后续行号不改变
	bool showLine(int lineNum); //这个是安全的，不用考虑越界问题
	bool showLineTo(int lineNum);
	void run_statistics(void);
	doubNode* nextLine();
	doubNode* prevLine();  
	doubNode* findLine(int lineNum);
	int lineNumtoPos(int lineNum);
	int lineNumtoPos(int lineNum, doubNode*& p);
	//below are more basic operations 
	bool get_elem(int position, char* e);
	bool append(const char* e);
	int  length() const;
	bool is_empty();
	bool m_delete(int position); //删除某块链，后续行号不改变;聪明！！不小心写了两遍一样的功能！等重构
	void clear();

	douNodeControl() {
		head = new doubNode;
		curLineNum = 0;
	};
	~douNodeControl() {
		//this->clear();
		delete head;
	};
	
	
};




