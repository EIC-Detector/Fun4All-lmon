#ifndef RootOut_h
#define RootOut_h

//helper class for ROOT TTree output

#include <string>

class TFile;
class TTree;

class RootOut {

  public:

    RootOut();
    void SetFileName(const std::string &fname) {fOutputName = fname;}
    void Open(); // open the output and create the tree
    void Close(); // write the tree and close outpu file

    TTree *GetTree() {return fDetTree;} // provide the tree to the detectors
    void FillTree(); // call fill for the tree

  private:

    std::string fOutputName; // name of output file

    TFile *fOut; // output file
    TTree *fDetTree; // output tree

};

#endif

