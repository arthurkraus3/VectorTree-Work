#include <iostream>
#include <ostream>
#include <memory>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"

void VectorTree() {
  //Credit for the bones to this code goes to Alexei Tam

    /*
    
    My goal is to separately load up four different branches with different vector sizes
    
        Size 1: 1 entry
        Size 2: 10 entries
        Size 3: 100 entries
        Size 4: 1000 entries    
    
    */



  std::cout << "Initializing..." << std::endl;
  
  //CREATING FILE AND TREE
  std::cout << "creating file and tree..." << std::endl;
  
  std::unique_ptr<TFile> myFile = std::make_unique<TFile>("VectorTreeFile.root", "RECREATE");
  TTree *tree = new TTree("myTree","myTree");
  
  if(!myFile) {
    std::cout << "Error: file creation failed" << std::endl;
  }
  
  //INITIALIZING VARIABLES
  std::cout << "initializing variables and vector" << std::endl;
  
  const Int_t NEvents = 1000; // N = 1,000,000
  Int_t NEntries0;
  Int_t NEntries1;
  Int_t NEntries2;
  Int_t NEntries3;
  
      //vectors
      std::vector<float> vten0; //10^0 = 1 entry
      std::vector<float> vten1;//10^1 = 10 entries
      std::vector<float> vten2;//10^2 = 100 entries
      std::vector<float> vten3;// 10^3 = 1000 entries
      
  
      //variables
      float f0;
      float f1;
      float f2;
      float f3;
  
  
  //INITIALIZING BRANCHES
  std::cout << "creating branches" << std::endl;
  
  tree->Branch("bOnes", &f0);
  tree->Branch("bTens", &f1);
  tree->Branch("bHundreds", &f2);
  tree->Branch("bThousands", &f3);
  
  
  //EVENTS LOOP
  std::cout << "generating events..." << std::endl;
  
  for (int j = 0; j < NEvents; j++) {
    
    //randomizing number of entries
    int NEntries0 = 1;
    int NEntries1 = 10;
    int NEntries2 = 100;
    int NEntries3 = 1000;
   
    //clearing events
    v0.clear();
    v1.clear();
    v2.clear();
    v3.clear();
          
        //generating vector elements, filling vectors
        
        //generating v0
        for(int m = 0; m < NEntries0; m++) {
          f0 = gRandom->Rndm()*10;
          v0.emplace_back(f0);
        }
    
        //generating v1
        for(int n = 0; n < NEntries1; n++) {
          f1 = gRandom->Rndm()*10;
          v1.emplace_back(f1);
        }
    
        //generating vd
        for(int b = 0; b < NEntries2; b++) {
          f2 = gRandom->Rndm()*10;
          v2.emplace_back(f2);
        }
    
        //generating vs
        for(int a = 0; a < NEntries3; a++) {
          f3 = gRandom->Rndm()*10;
          v3.emplace_back(f3);
        }
    
        
    tree->Fill();
    
  }
  
  //saving tree and file
  tree->Write();
  
    //let's look in the tree:
    tree->Scan();
    tree->Print();
  
  myFile->Save();
  myFile->Close();
  
  


}