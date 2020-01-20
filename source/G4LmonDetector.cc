#include "G4LmonDetector.h"

#include <g4main/PHG4Detector.h>  // for PHG4Detector

#include <Geant4/G4Box.hh>
#include <Geant4/G4Color.hh>
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4NistManager.hh>
#include <Geant4/G4Material.hh>
#include <Geant4/G4PVPlacement.hh>
#include <Geant4/G4SubtractionSolid.hh>
#include <Geant4/G4SystemOfUnits.hh>
#include <Geant4/G4Tubs.hh>
#include <Geant4/G4UnionSolid.hh>
#include <Geant4/G4VisAttributes.hh>

#include <cmath>
#include <iostream>  // for operator<<, endl, bas...

class G4VSolid;
class PHCompositeNode;

using namespace std;

G4LmonDetector::G4LmonDetector(PHG4Subsystem *subsys, PHCompositeNode *Node, const std::string &dnam)
  : PHG4Detector(subsys, Node, dnam)
{
}

//_______________________________________________________________
//_______________________________________________________________
int G4LmonDetector::IsInDetector(G4VPhysicalVolume *volume) const
{
  set<G4VPhysicalVolume *>::const_iterator iter = m_PhysicalVolumesSet.find(volume);
  if (iter != m_PhysicalVolumesSet.end())
  {
    return 1;
  }

  return 0;
}

void G4LmonDetector::ConstructMe(G4LogicalVolume *logicWorld)
{
  G4Material* top_m = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
  G4VSolid *top_s = new G4Box("top_s", 2*meter, 2*meter, 3500*cm);
  G4LogicalVolume *top_l = new G4LogicalVolume(top_s, top_m, "top_l");
  G4VPhysicalVolume *top_p = new G4PVPlacement(0, G4ThreeVector(), top_l, "top_p", 0, false, 0);
/*
  G4VisAttributes *vis = new G4VisAttributes(G4Color(G4Colour::Grey())); // grey is good to see the tracks in the display
  vis->SetForceSolid(true);
  logical->SetVisAttributes(vis);
  G4VPhysicalVolume *phy = new G4PVPlacement(nullptr, G4ThreeVector(0,0, 0),
                                               logical, "BoxWithHole",
                                               logicWorld, 0, false, OverlapCheck());
*/
// add it to the list of placed volumes so the IsInDetector method
// picks them up
    m_PhysicalVolumesSet.insert(top_p);
  return;
}

void G4LmonDetector::Print(const std::string &what) const
{
  cout << "Example01 Detector:" << endl;
  if (what == "ALL" || what == "VOLUME")
  {
    cout << "Version 0.1" << endl;
  }
  return;
}
