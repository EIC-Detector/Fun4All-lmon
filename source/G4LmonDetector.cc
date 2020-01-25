#include "G4LmonDetector.h"
#include "ExitWindowV2.h"
#include "Cell.h"
#include "CompCal.h"
#include "Collimator.h"
#include "Magnet.h"
#include "OpDet.h"
#include "RootOut.h"

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
  new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), top_l, "top_p", logicWorld, false, 0);
  ExitWindowV2 *ew = new ExitWindowV2("ew", -20.75*meter, top_l);
  m_ExitWindowV2Vector.push_back(ew);
  ew->CreateOutput(rootoutput->GetTree());
  new Collimator(-22.1*meter, top_l);
  new Magnet(-22.5*meter, top_l);
  //detectors
  G4double dpos = -3135*cm;
  CompCal *cmpcal = new CompCal("phot", dpos-50*cm, 0, top_l, rootoutput);
  cmpcal->CreateOutput(rootoutput->GetTree());
  m_CompCalVector.push_back(cmpcal);
  cmpcal = new CompCal("up", dpos, 4.2*cm, top_l,rootoutput );
  cmpcal->CreateOutput(rootoutput->GetTree());
  m_CompCalVector.push_back(cmpcal);
  cmpcal = new CompCal("down", dpos, -4.2*cm, top_l, rootoutput);
  cmpcal->CreateOutput(rootoutput->GetTree());
  m_CompCalVector.push_back(cmpcal);
  return;
}

bool  G4LmonDetector::ExecuteSteppingActions(const G4Step* aStep)
{
  bool bret = false;
  
  for (auto iter=m_CellVector.begin(); iter != m_CellVector.end(); ++iter)
  {
    bret |= (*iter)->ProcessHits(aStep, nullptr);
  }
  for (auto iter=m_ExitWindowV2Vector.begin(); iter != m_ExitWindowV2Vector.end(); ++iter)
  {
    bret |= (*iter)->ProcessHits(aStep, nullptr);
  }
  for (auto iter=m_OpDetVector.begin(); iter != m_OpDetVector.end(); ++iter)
  {
    bret |= (*iter)->ProcessHits(aStep, nullptr);
  }
  return bret;
}

void  G4LmonDetector::ClearEvent()
{
  for (auto iter=m_CellVector.begin(); iter != m_CellVector.end(); ++iter)
  {
    (*iter)->ClearEvent();
  }
  for (auto iter=m_ExitWindowV2Vector.begin(); iter != m_ExitWindowV2Vector.end(); ++iter)
  {
    (*iter)->ClearEvent();
  }
  for (auto iter=m_OpDetVector.begin(); iter != m_OpDetVector.end(); ++iter)
  {
    (*iter)->ClearEvent();
  }
  return;
}

void  G4LmonDetector::FinishEvent()
{
  for (auto iter=m_CompCalVector.begin(); iter != m_CompCalVector.end(); ++iter)
  {
    (*iter)->FinishEvent();
  }
  for (auto iter=m_ExitWindowV2Vector.begin(); iter != m_ExitWindowV2Vector.end(); ++iter)
  {
    (*iter)->FinishEvent();
  }
  for (auto iter=m_OpDetVector.begin(); iter != m_OpDetVector.end(); ++iter)
  {
    (*iter)->FinishEvent();
  }
  return;
}

void G4LmonDetector::Print(const std::string &what) const
{
  cout << "Luminosity Monitor Detector:" << endl;
  if (what == "ALL" || what == "VOLUME")
  {
    cout << "Version 0.1" << endl;
  }
  return;
}
