//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : ������������_���
//  @ File Name : Goods.h
//  @ Date : 19.10.2018
//  @ Author : Andrew Bondar
//
//


#if !defined(_GOODS_H)
#define _GOODS_H

#include "Base.h"

class Goods : public Base
{
private:
	int amountOfGoods;
	float priceOfGoods;

public:
	Goods * nextItem;
	Subcategory * subcategoryOfThis;
	int getAmountOfGoods();
	void setAmountOfGoods(int);
	void setPriceOfGoods(float);
	float getPriceOfGoods();
	Goods(char* name, int amount, float price);
	~Goods();
};

#endif  //_GOODS_H