//
// Created by Levi on 10/7/2018.
//

#include "blockChain.h"




//Yo, We should *Eventually* add at least two things to this
//1. Set a resonable mining threshold (A hash to check the hash of the block against) so that you have to
//   actuall mine for a while to succeed.
//2. verifying the previous transaction

// This Method takes the transactions, the time, the hash of the previous block
// and a random number. It hashes all this than adds the block to a vector (basically an array list) that is a 
// class variable.
string blockChain::mine(block blockIn) {


    vector<transaction>::const_iterator i;
    int index=0;
    stringstream stream;
    string hexString="";

    while (true) {
        //mining Threshold is a variable that the mined hash is check against. This is currently set to
        string miningThreshold="ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
        //string miningThreshold="0000000000000000000000000000000000000000000000000000000000000000";
        time_t curTime = time(NULL);
        srand(curTime);
        blockIn.setBlockNumber(blockChain::minedBlocks.size() + 1);
        blockIn.setTime(curTime);
        blockIn.setPrevHash(blockChain::prevHash);
        blockIn.addTransaction(transaction("Pheonix Gen", 50, "Levi Pfantz"));
        //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
        for (i = blockIn.getTransactions().begin(); i != blockIn.getTransactions().end(); ++i) {
            //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
            //then I can't be bothered
            index = std::distance(blockIn.getTransactions().begin(), i);
            stream << blockIn.getTransactions()[index].transactionToString();
        }
        stream << curTime << blockIn.getPrevHash() << rand();
        picosha2::hash256_hex_string(stream.str(), hexString);
       
		//checks if the hash is less than the value of miningThreshold
		if (blockChain::hexComp(static_cast<string>(hexString), miningThreshold)) {
            // This line is just for testing purposes
           // if(blockChain::hexComp("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe", miningThreshold)){

           blockIn.setSelfHash(hexString);
            blockChain::minedBlocks.push_back(blockIn);
            blockChain::prevHash=hexString;

            return hexString;
        } else
            blockIn.removeLatestTransaction();

    }


}

//This function takes in two 64 digit (256 bit) hexadecimal numbers as strings and compares them. It returns true
// if the first parameter is less than or equal to the second one and false otherwise.
// The input needs to be 64 digits or unexpected behaviour may occur. This function should work but could definitely
// use more testing.
bool blockChain::hexComp(string hex1, string hex2){
    //This next line is just for testing the function
    //cout<<endl<<"hexString: "<<hex1<<endl<<"miningThreshold: "<<hex2<<endl;
    string sec1="";
    string sec2="";
    unsigned long long sec1Long=0;
    unsigned long long sec2Long=0;


    for(int i=0;i<8;i++){
        sec1=hex1.substr(i*8,8);
        sec2=hex2.substr(i*8,8);
        sec1Long=std::stoull(sec1,NULL,16);
        sec2Long=std::stoull(sec2,NULL,16);
        //These next two commented lines are just for testing the method.
        //cout<<endl<<"Sec1: "<<sec1<<endl<<"sec2: "<<sec2<<endl;
        //cout<<endl<<"Sec1Long: "<<sec1Long<<endl<<"sec2Long: "<<sec2Long<<endl;
        if(sec1Long<sec2Long){

            return true;
        }
        if(sec1Long>sec2Long){
            return false;
        }
    }

    //This statement is what happens if the two hashes are equal. If its set to return true than it will return true if the
    //hashes are equal. If you set it to return false than the opposite will be true;
    return true;

}


//simply prints the entire block Chain

void blockChain::displayBlockChain() {
    vector<block>::iterator i;
    int index;

    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for(i = blockChain::minedBlocks.begin(); i != blockChain::minedBlocks.end(); ++i){
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index=std::distance(blockChain::minedBlocks.begin(), i);
        blockChain::minedBlocks[index].displayBlock();
        cout<<"------------------------------------------------------------"<<endl;
    }
}

blockChain::blockChain() {}

blockChain::blockChain(const vector<block> &minedBlocks) : minedBlocks(minedBlocks) {}


