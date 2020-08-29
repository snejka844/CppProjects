/*#include "Wallet.h"

void Wallet::createWallet()
{
	std::cout << "Enter the name of the owner\n";
	std::cin.ignore();
	std::cin.getline(owner, 256);
	srand(time(NULL));
	for (unsigned i = 0; i < (1<<31); ++i) {
		rand() % 10 + 1;
	}
	std::cout << "Enter amount of money\n";
	std::cin >> fiatMoney;


}

void Wallet::addWallet()
{
	Wallet wallet;
	std::ofstream outfile;
	outfile.open("wallets.dat", std::ios::binary | std::ios::app);
	wallet.createWallet();
	outfile.write(reinterpret_cast<char *> (&wallet), sizeof(Wallet));
	outfile.close();
	
}
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include "Wallet.h"
#include "ID.h"
#include "HelperFunctions.lh"
#include "Transactions.h"

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::cerr;
using std::ios;

const unsigned int systemWalletID = 4294967295;
const char* walletsFileName = "wallets.dat";

void writeInWalletFile(const Wallet& wallet) {
	ofstream file(walletsFileName, ios::binary | ios::app);
	if (!file.good()) {
		cerr << walletsFileName << " Writing in file stream failed!" << endl;
		return;
	}
	file.write((const char*)&wallet, sizeof(wallet));
	file.close();
}
bool readWalletFileByID(Wallet& wallet) {
	ifstream file(walletsFileName, ios::binary);
	if (!file.good()) {
		cerr << walletsFileName << " Reading file failed!" << endl;
		return false;
	}
	Wallet temp;
	while (!file.eof()) {
		file.read((char*)&temp, sizeof(temp));
		if (temp.id == wallet.id) {
			wallet = temp;
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

bool readWalletFileByName(Wallet& wallet) {
	ifstream file(walletsFileName, ios::binary);
	if (!file.good()) {
		cerr << walletsFileName << " Reading file failed!" << endl;
		return false;
	}
	Wallet temp;
	while (!file.eof()) {
		file.read((char*)&temp, sizeof(temp));
		if (strcmp(wallet.owner, temp.owner)) {
			wallet = temp;
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}
/*Not sure how this works
double walletCurrentCoins(const Wallet& wallet) {
	size_t arrSize = transactionCountByID(wallet.id);
	Transaction* tranArr = new (std::nothrow) Transaction[arrSize];
	double count = 0.0;
	if (!deserializeArrayOfTransByID(wallet.id, tranArr)) {
		//    cout << "No transaction with that ID were found" << endl;
		// return 0;
	}
	for (int i = 0; i < arrSize; i++) {
		if (tranArr[i].receiverId == wallet.id) {
			count += tranArr[i].fmiCoins;
		}
		else { // else (tranArr[i].senderId == wallet.id) == true
			count -= tranArr[i].fmiCoins;
		}
	}
	delete[] tranArr;
	return count;
}
*/
void addWallet() {
	Wallet wallet;
	cin >> wallet.fiatMoney;
	readName(wallet.owner, ownerNameLength);
	wallet.id = getAndIncrementID();//I dont think its random check how to make with srand
	createTransaction(systemWalletID, wallet.id, convertToFmiCoin(wallet.fiatMoney));
	writeInWalletFile(wallet);
}
