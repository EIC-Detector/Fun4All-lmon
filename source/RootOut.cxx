
//_____________________________________________________________________________
//
// helper class for ROOT TTree output
//_____________________________________________________________________________

//local classes
#include "RootOut.h"

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TClass.h"
#include "TROOT.h"
#include "TSystem.h"

//C++
#include <iostream>
#include <string>


using namespace std;

//_____________________________________________________________________________
RootOut::RootOut(): fOut(0), fDetTree(0) {

  //default name for output file
  fOutputName = "lmon.root";



}//RootOut

//_____________________________________________________________________________
void RootOut::Open() {

  std::string nam(fOutputName.data());

  cout << "RootOut::Open, " << nam << endl;

  //create directory for the output
  if( nam.find_last_of("/") != string::npos ) {
    string dir = nam.substr(0, nam.find_last_of("/"));
    if(!dir.empty()) gSystem->MakeDirectory(dir.c_str());
  }

  //create the output file
  fOut = new TFile(nam.c_str(), "recreate");

  //test if file exists
  if(!fOut->IsOpen()) {
    string description = "Can't open output: " + fOutputName;
    exit(1);
  }

  //output detector tree
  fDetTree = new TTree("DetectorTree", "DetectorTree");

}//Open

//_____________________________________________________________________________
void RootOut::FillTree() {

  fDetTree->Fill();

}//FillTree

//_____________________________________________________________________________
void RootOut::Close() {
  fOut->cd();
  //write the tree
  if(fDetTree) fDetTree->Write();

  //close the output file
  if(fOut) fOut->Close();

}//Close

















