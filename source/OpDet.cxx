
//_____________________________________________________________________________
//
// detector for optical photons, uniform quantum efficiency
//
//_____________________________________________________________________________

//local headers
#include "OpDet.h"

//Geant
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4NistManager.hh>
#include <Geant4/G4Box.hh>
#include <Geant4/G4SystemOfUnits.hh>
#include <Geant4/G4PVPlacement.hh>
#include <Geant4/G4VisAttributes.hh>
#include <Geant4/G4MaterialPropertiesTable.hh>
#include <Geant4/G4OpticalPhoton.hh>
#include <Geant4/G4Scintillation.hh>
#include <Geant4/G4Cerenkov.hh>

//ROOT
#include <TTree.h>


//C++
#include <string>


//_____________________________________________________________________________
OpDet::OpDet(const G4String& name, G4double xysiz, G4double zpos, G4double xmid, G4double ymid, G4LogicalVolume *top):
  fNam(name) {

  //detector for optical photons

//  G4cout << "  OpDet: " << fNam << G4endl;

  //OpDet shape
  G4double dz = 0.3*mm; // 300 micro m thickess
  G4Box *shape = new G4Box(name, xysiz/2., xysiz/2., dz/2.);

  //quantum efficiency
  fQE = 0.8;

  //logical volume
  G4Material *mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
  G4LogicalVolume *vol = new G4LogicalVolume(shape, mat, name);

  //visibility
  G4VisAttributes *vis = new G4VisAttributes();
  vis->SetColor(1, 0, 1); // magenta
  vis->SetForceSolid(true);
  vol->SetVisAttributes(vis);

  //add to the top
  fPhys = new G4PVPlacement(0, G4ThreeVector(xmid, ymid, zpos-dz/2.), vol, name, top, false, 0);

  //random generator for quantum efficiency
  fRand = new CLHEP::HepRandom();

  //indices to identify scintillation and Cerenkov processes
  G4Scintillation scin;
  fScinType = scin.GetProcessType();
  fScinSubType = scin.GetProcessSubType();
  G4Cerenkov cer;
  fCerenkovType = cer.GetProcessType();
  fCerenkovSubType = cer.GetProcessSubType();

}//OpDet

//_____________________________________________________________________________
OpDet::~OpDet() {

  delete fRand;

}//~OpDet

//_____________________________________________________________________________
G4bool OpDet::ProcessHits(const G4Step *step, G4TouchableHistory*) {

  //total energy deposition in optical detector
  fEdep += step->GetTotalEnergyDeposit();

  //optical photons only since now
  G4Track *track = step->GetTrack();
  if(track->GetDynamicParticle()->GetParticleDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) {
    return true;
  }

  //energy from optical photons
  fEopt += step->GetTotalEnergyDeposit();

  //apply the quantum efficiency
  if(fRand->flat() > fQE) return true;

  //scintillation or Cerenkov photon
  G4int ptype = track->GetCreatorProcess()->GetProcessType();
  G4int pstype = track->GetCreatorProcess()->GetProcessSubType();
  //scintillation photons
  if(ptype == fScinType && pstype == fScinSubType) fNscin++;
  //Cerenkov photons
  if(ptype == fCerenkovType && pstype == fCerenkovSubType) fNcerenkov++;

  //time of the photon
  G4double tim = step->GetPostStepPoint()->GetGlobalTime();
  if(tim < fTmin) fTmin = tim;
  if(tim > fTmax) fTmax = tim;
  fTavg += tim;

  //number of optical photons
  fNphot++;

  return true;

}//ProcessHits

//_____________________________________________________________________________
void OpDet::CreateOutput(TTree *tree) {

  AddBranch("_en", &fEdep, tree);
  AddBranch("_eopt", &fEopt, tree);

  AddBranch("_nphot", &fNphot, tree);
  AddBranch("_nscin", &fNscin, tree);
  AddBranch("_ncerenkov", &fNcerenkov, tree);

  AddBranch("_tmin", &fTmin, tree);
  AddBranch("_tmax", &fTmax, tree);
  AddBranch("_tavg", &fTavg, tree);

}//CreateOutput

//_____________________________________________________________________________
void OpDet::FinishEvent() {

  //G4cout << "OpDet::FinishEvent" << G4endl;

  //average time
  if(fNphot > 0) {
    fTavg = fTavg/fNphot;
  } else {
    fTavg = -999.;
    fTmin = -999.;
    fTmax = -999.;
  }

}//FinishEvent

//_____________________________________________________________________________
void OpDet::ClearEvent() {

  fEdep = 0.;
  fEopt = 0.;
  fNphot = 0;

  fNscin = 0;
  fNcerenkov = 0;

  fTmin = 1.e12;
  fTmax = -1.;
  fTavg = 0.;

}//ClearEvent

//_____________________________________________________________________________
void OpDet::AddBranch(const std::string& nam, Double_t *val, TTree *tree) {

  //add branch for one Double_t variable

  std::string name = fNam + nam; // branch name from detector name and variable name
  std::string leaf = name + "/D"; // leaflist for Double_t
  tree->Branch(name.c_str(), val, leaf.c_str()); // create the branch

}//AddBranch

//_____________________________________________________________________________
void OpDet::AddBranch(const std::string& nam, ULong64_t *val, TTree *tree) {

  //add branch for one ULong64_t variable

  std::string name = fNam + nam; // branch name from detector name and variable name
  std::string leaf = name + "/l"; // leaflist for Double_t
  tree->Branch(name.c_str(), val, leaf.c_str()); // create the branch

}//AddBranch


































































