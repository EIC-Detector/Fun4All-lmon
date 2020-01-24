
#ifndef ExitWindowV2_h
#define ExitWindowV2_h

// Exit window version 2

#include <Geant4/globals.hh>
#include <Rtypes.h>

class G4Step;
class G4TouchableHistory;
class G4LogicalVolume;
class TTree;

class ExitWindowV2 {

  public:

    ExitWindowV2(const G4String& nam, G4double zpos, G4LogicalVolume *top);

    //Detector
    virtual const G4String& GetName() const {return fNam;}
    virtual void CreateOutput(TTree *tree);
    virtual void ClearEvent();
    virtual void FinishEvent();

    //G4VSensitiveDetector
    virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory*);

  private:

    G4String fNam; // detector name

    Bool_t fIsHit; // flag set when primary photon makes a step

    Double_t fPhotX; // x position of the photon
    Double_t fPhotY; // y position of the photon
    Double_t fPhotZ; // z position of the photon

    Bool_t fConv; // flag set when e+e- conversion took place

    Double_t fConvX; // x of conversion point
    Double_t fConvY; // y of conversion point
    Double_t fConvZ; // z of conversion point

    Double_t fConvStepLen; // length of step with conversion
    Double_t fPhotConvLen; // length between photon first point and conversion point

};

#endif
