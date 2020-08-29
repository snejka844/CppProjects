/*#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

class Bank {

};


struct Wallet {
private:
	char owner[256];
	unsigned int id;
	double fiatMoney;
public:
	void createWallet();
	void addWallet();

};

struct Transaction {
	long long time;
	unsigned receiverid;
	unsigned senderid;
	double fmiCoins;
};

struct Order {
	enum Type{SELL,BUY} type;
	unsigned walletid;
	double fmiCoins;
};
*/

#pragma once
#include "ID.h"

const short ownerNameLength = 256;

struct Wallet {
	char owner[ownerNameLength];
	uint id;
	double fiatMoney;
};

void writeInWalletFile(const Wallet&);

bool readWalletFileByID(Wallet&);

bool readWalletFileByName(Wallet&);

double walletCurrentCoins(const Wallet&);

void addWallet();


