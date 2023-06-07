#include <iostream>
#include <ostream>
#include <memory>
#include <vector>
#include <cmath>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"

union floatint_t {
     float fvalue;
     uint32_t ivalue;
  };  

uint32_t getBitMask(int lastNBits) {
    uint32_t bitmask = 0;
    for(auto i = 0; i < lastNBits; ++i ) { 
      bitmask |= (0x1 << i); 
    }   
    return ~bitmask;
  }

float truncate(float input, int lastNBits) {
    ::floatint_t value;
    value.fvalue = input; 
    value.ivalue &= ::getBitMask(lastNBits);
    return value.fvalue;
  }

void VectorTree(int n) {
  //Credit for the bones to this code goes to Alexei Tam
    /*
  
    My goal is to separately load up four different branches with different vector sizes
    
        Size 4: 1000 entries    
    
    */



  std::cout << "Initializing..." << std::endl;
  
  //CREATING FILE AND TREE
  std::cout << "creating file and tree..." << std::endl;
  
  std::unique_ptr<TFile> myFile = std::make_unique<TFile>("VectorTreeFile.root", "RECREATE");
  TTree *tree = new TTree("myTree","myTree");
 
  //tree->SetAutoFlush(0);
  //tree->SetAutoSave(0);

  if(!myFile) {
    std::cout << "Error: file creation failed" << std::endl;
  }
  
  //INITIALIZING VARIABLES
  std::cout << "initializing variables and vector" << std::endl;
  
  const Int_t NEvents = 150000; // N = 1,000,000
  Int_t NEntries3;
  
      //vectors
      std::vector<float> vten3;// 10^3 = 1000 entries
      
  
      //variables
      float f3;
  
  
  //INITIALIZING BRANCHES
  std::cout << "creating branches" << std::endl;
  
  tree->Branch("bThousands", &vten3);

  int power = pow(2,n);

  int bSize = power*4000;

  tree->SetBasketSize("*",bSize);
  tree->SetMaxBasketSize(256000); // added June 7, 12:28 PM
 
  //===EVENTS LOOP===
  std::cout << "generating events..." << std::endl;
  
  for (int j = 0; j < NEvents; j++) {
    
    //randomizing number of entries
    int NEntries3 = 400;
    ::floatint_t truncated;
    
    //clearing events
    vten3.clear();
          
    //generating vten3
    for(int a = 0; a < NEntries3; a++) {
	if(a < NEntries3/2) { 
       		f3= gRandom->Rndm() * gRandom->Gaus(0,1);
       		truncated.fvalue = ::truncate(f3,16); // 8 for 16 dp, 15 for 8 dp.
		vten3.emplace_back(truncated.fvalue);
	} else  { 
		f3 = 1;
		vten3.emplace_back(f3); 
	}
    }
    tree->Fill(); 
  }
  
  //saving tree and file
  tree->Write(); 
  //let's look in the tree:
  //tree->Scan();
  tree->Print();
  myFile->Save();
  myFile->Close();
}

int main(){
	for(int i = 1; i < 13;i++){
		VectorTree(i);
	}

return 0;
}
