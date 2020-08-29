#pragma once
#include "ID.h"

struct Order {
	enum Type { INVALID = -1, SELL, BUY } type;
	uint walletId;
	double fmiCoins;
};

void serializeOrder(const Order&);

void deserializeOrder();

bool isSellOrderValid(const Order&);

bool isBuyOrderValid();

void createOrder();

