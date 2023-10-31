#include "douNodeControl.h"
#include <iostream>
#include<cstring>

bool douNodeControl::insert(int position, const char* e, int size, int lineNum)
{
	doubNode* tmp_ptrL = get_elem_ptr(position - 1);
	doubNode* tmp_ptr = nullptr;
	if (tmp_ptrL == nullptr) {
		return false;
	}
	else {
		tmp_ptr = tmp_ptrL->next;
	}
	doubNode* p = new doubNode(e, size, tmp_ptrL, tmp_ptr);
	tmp_ptrL->next = p;
	if (tmp_ptr != nullptr) {
		tmp_ptr->prev = p;
	}

	p->line = lineNum;
	if (lineNum == 0) {
		tmp_ptrL->line == 0 ? p->line = 1 : p->line = tmp_ptrL->line + 1;
	}
	return true;
}


int douNodeControl::lineNumtoPos(int lineNum)
{
	doubNode* p = head;
	int pos = 0;
	while (p != nullptr && p->line != lineNum) {
		p = p->next;
		++pos;
	}

	if (p == nullptr) {
		return -1;
	}
	else {
		return pos;
	}
}

int douNodeControl::lineNumtoPos(int lineNum, doubNode*& p)
{
	p = head->next;
	int pos = 1;
	while (p != nullptr && p->line != lineNum) {
		p = p->next;
		++pos;
	}

	if (p == nullptr) {
		return -1;
	}
	else {
		return pos;
	}
	return 0;
}


bool douNodeControl::insertNewLine(int lineNum, const char* e , int size)
{
	doubNode* tmp_ptrL = findLine(lineNum - 1);
	doubNode* tmp_ptr = nullptr;
	if (tmp_ptrL == nullptr) {
		return false;
	}
	else {
		tmp_ptr = tmp_ptrL->next;
	}
	doubNode* p = new doubNode(e, size, tmp_ptrL, tmp_ptr);
	tmp_ptrL->next = p;
	if (tmp_ptr != nullptr) {
		tmp_ptr->prev = p;
	}
	p->line = tmp_ptrL->line + 1;
	tmp_ptr = p->next;
	while (tmp_ptr != nullptr) {
		(tmp_ptr->line)++;
		tmp_ptr = tmp_ptr->next;
	}
	return true;
}
//false if line not exist
bool douNodeControl::deleteLine(int lineNum)
{
	doubNode* p = nullptr;
	int pos = lineNumtoPos(lineNum, p); //pָ��Ҫɾ���Ľڵ�
	if (pos == -1) {
		return false;
	}
	p = p->next;
	m_delete(pos);
	
	while (p != nullptr) {
		(p->line)--;
		p = p->next;
	}

	return true;
}

bool douNodeControl::XdeleteLine(int lineNum)
{
	doubNode* p = nullptr;
	
	int pos = lineNumtoPos(lineNum, p);
	if (pos == -1) {
		return false;
	}

	m_delete(pos);

	return true;
}

bool douNodeControl::showLine(int lineNum)
{
	if (!lineNum) {
		std::cout << " line not exist" << std::endl;
		return false;
	}
	doubNode* p = findLine(lineNum);
	if (p == nullptr) {
		std::cout << " line not exist" << std::endl;
		return false;
	}
	std::cout << lineNum << ": " <<p->data << std::endl;
	return true;
}
bool douNodeControl::showLineTo(int lineNum)
{
	if (!lineNum) {
		std::cout << " line not exist" << std::endl;
		return false;
	}
	doubNode* p = findLine(lineNum);
	if (p == nullptr) {
		std::cout << " line not exist" << std::endl;
		return false;
		}
	p=head;
	while(p->line!=lineNum&&p!=nullptr){
		p=p->next;
		showLine(p->line);
	}
    return false;
}
void douNodeControl::run_statistics(void)
{
	doubNode* p = head;
	int chCount{ 0 };
	while (p->next != nullptr) {
		p = p->next;
		chCount += strlen(p->data);
	}

	std::cout << "total line number is " << p->line << "|||" << "the number of characters is " << chCount << std::endl;
}
//nullptr if line not exist
doubNode* douNodeControl::nextLine()
{
	doubNode* p = findLine(curLineNum + 1);
	if (p != nullptr) {
		//++curLineNum;
	}
	else {
		std::cout << "**alreay at bottom**" << std::endl;
	}
	return p;
}
//nullptr if line not exist
doubNode* douNodeControl::prevLine()
{
	doubNode* p = findLine(curLineNum - 1);
	if (p != nullptr) {
		//--curLineNum;
	}
	else {
		std::cout << "**alreay at bottom**" << std::endl;
	}
	return p;
}
//nullptr if line not exist **Warning**it changes curLineNum!!!!!!
doubNode* douNodeControl::findLine(int lineNum)
{
	doubNode* p = head;
	while (p != nullptr && p->line != lineNum) {
		p = p->next;
	}

	if (p == nullptr) {
		std::cout << "**line not found!**" << std::endl;
		return nullptr;
	}
	curLineNum = lineNum;
	return p;
}



bool douNodeControl::get_elem(int position, char* e)
{
	doubNode* tem_ptr = get_elem_ptr(position);
	if (tem_ptr == nullptr) {
		return false;
	}
	else {
		e = tem_ptr->data;
		return true;
	}
}

bool douNodeControl::append(const char* e)
{
	/*if (insert(length() + 1, e)) {
		return true;
	}
	else {
		return false;
	}*/
	return true;
}

int douNodeControl::length() const
{
	int length = 0;
	doubNode* iter = head->next;
	while (iter != nullptr) {
		++length;
		iter = iter->next;
	}

	return length;
}

bool douNodeControl::is_empty()
{
	return head->next == nullptr;
}

bool douNodeControl::m_delete(int position)
{
	doubNode* tmp_ptrL = get_elem_ptr(position - 1);
	doubNode* tmp_ptr = nullptr;
	if (tmp_ptrL == nullptr || tmp_ptrL->next == nullptr) {
		return false;
	}
	else {
		tmp_ptr = tmp_ptrL->next;
	}

	tmp_ptrL->next = tmp_ptr->next;
	if (tmp_ptr->next != nullptr) {
		tmp_ptr->next->prev = tmp_ptrL;
	}
	delete tmp_ptr;
	return true;
}

void douNodeControl::clear()
{
	while (!this->is_empty()) {
		m_delete(1);
	}
}

doubNode* douNodeControl::get_elem_ptr(int position) const {
	doubNode* ptr = head;
	int i = 0;//dummy head 0, data 1, 2, 3
	while (i < position && ptr != nullptr) {
		ptr = ptr->next;
		++i;
	}

	if (i != position || ptr == nullptr) {
		return nullptr;
	}
	else {
		return ptr;
	}

}