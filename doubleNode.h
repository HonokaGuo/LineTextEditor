#pragma once
#define LEN 80
class doubNode {

public:
	char* data;
	int line;
	doubNode* next;
	doubNode* prev;

	doubNode();
	doubNode(const char* e, int size, doubNode* prev = nullptr, doubNode* next = nullptr);
	~doubNode();
};

