#pragma once
#include "doubleNode.h"
class douNodeControl {
public:
	doubNode* head;
	doubNode* get_elem_ptr(int position) const;
	int curLineNum;

	bool insert(int line, const char* e, int size, int lineNum = 0); //�����������д��Ϊǰһ���ڵ��к�+1
	bool insertNewLine(int lineNum, const char* e, int size); //�����п������Һ��������к�+1
	bool deleteLine(int lineNum);//ɾ��ĳ�����������к�-1
	bool XdeleteLine(int lineNum); //ɾ��ĳ�����������кŲ��ı�
	bool showLine(int lineNum); //����ǰ�ȫ�ģ����ÿ���Խ������
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
	bool m_delete(int position); //ɾ��ĳ�����������кŲ��ı�;����������С��д������һ���Ĺ��ܣ����ع�
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




