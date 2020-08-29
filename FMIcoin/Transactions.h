#pragma once
#include "ID.h"

struct Transaction {
	long long time;
	unsigned int senderId;
	unsigned int receiverId;
	double fmiCoins;
};

double convertToFmiCoin(const double);

double convertToLeva(const double);

void WriteInTransactionFile(const Transaction&);

bool readTransationByRecID(Transaction&);

bool readTransationBySendID(Transaction&);

size_t transactionCountByID(const uint ID);

bool deserializeArrayOfTransByID(const uint, Transaction*);

void createTransaction(const unsigned int, const unsigned int, const double);


