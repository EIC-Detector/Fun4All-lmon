
//_____________________________________________________________________________
//
// spectrometer dipole magnet
//
//_____________________________________________________________________________

//local headers
#include "Magnet.h"

//Geant headers
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4NistManager.hh>
#include <Geant4/G4Box.hh>
#include <Geant4/G4SystemOfUnits.hh>
#include <Geant4/G4PVPlacement.hh>
#include <Geant4/G4FieldManager.hh>
#include <Geant4/G4UniformMagField.hh>
#include <Geant4/G4VisAttributes.hh>


//_____________________________________________________________________________
Magnet::Magnet(G4double zpos, G4LogicalVolume *top) {

  G4Material *mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

  //magnet shape
  G4double dz = 60.*cm;
  G4double xysiz = 10*cm;

  G4String nam = "Magnet";
  G4Box *mshape = new G4Box(nam, xysiz, xysiz, dz/2.);
  G4LogicalVolume *mvol = new G4LogicalVolume(mshape, mat, nam);

  G4VisAttributes *vis = new G4VisAttributes();
  //vis->SetColor(1, 1, 0); // yellow
  vis->SetColor(1, 0, 1); // magenta
  //vis->SetLineWidth(2);
  mvol->SetVisAttributes(vis);

  //maginetic field
  G4UniformMagField *field = new G4UniformMagField(G4ThreeVector(0.5*tesla, 0, 0));
  G4FieldManager *fman = new G4FieldManager();
  fman->SetDetectorField(field);
  fman->CreateChordFinder(field);

  mvol->SetFieldManager(fman, true);

  new G4PVPlacement(0, G4ThreeVector(0, 0, zpos-dz/2.), mvol, nam, top, false, 0);

}//Magnet

























