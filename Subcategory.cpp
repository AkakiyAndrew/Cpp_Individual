//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : ������������_���
//  @ File Name : Subcategory.cpp
//  @ Date : 19.10.2018
//  @ Author : Andrew Bondar
//
//

#define _CRT_SECURE_NO_WARNINGS
#include "Subcategory.h"
#include "Goods.h"

Subcategory::Subcategory(char* arg)
{
	name = new char[sizeof(arg) + 2];
	strcpy(name, arg);

	this->firstGoods = nullptr;
	this->nextItem = nullptr;
	this->numberOfGoods = 0;
}

Subcategory::~Subcategory()
{
	if (this->numberOfGoods!=0)
	{
		Goods *link=firstGoods, *buff;
		for (int i = 0; i < numberOfGoods; i++)
		{
			buff = link;
			buff->~Goods();
			link = link->nextItem;
		}
	}
	//delete this->name;
}