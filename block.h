//
// Created by Levi on 10/7/2018.
//

#ifndef BLOCKCHAINGOOFIN_BLOCK_H
#define BLOCKCHAINGOOFIN_BLOCK_H
#include <stddef.h>
#include <vector>
#include "transaction.h"
#include <iostream>
using std::vector;
class block {
    int blockNumber=-1;
    string prevHash="";
    vector<transaction> transactions;
   string selfHash="";
   time_t time=-1;
public:

    void displayBlock();

    void removeLatestTransaction();

    string getSelfHash() const;

    time_t getTime() const;

    void setTime(time_t time);

    void setSelfHash(string selfHash);

    void displayTransactions() const;


    void addTransaction(const transaction &trans);


    void addTransaction(const vector<transaction> &trans);


    string getPrevHash() const;

    void setPrevHash(string prevHash);

    const vector<transaction> &getTransactions() const;

    void setTransactions(const vector<transaction> &transactions);

    block(int blockNumber, string prevHash);

    block(int blockNumber, string prevHash, const vector<transaction> &transactions);

    block(transaction trans);


    block();

    int getBlockNumber() const;

    void setBlockNumber(int blockNumber);

};


#endif //BLOCKCHAINGOOFIN_BLOCK_H