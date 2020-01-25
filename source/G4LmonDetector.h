// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4LMONDETECTOR_H
#define G4LMONDETECTOR_H

#include <g4main/PHG4Detector.h>

#include <set>
#include <string>  // for string
#include <vector>

class G4LogicalVolume;
class G4Step;
class G4VPhysicalVolume;
class PHCompositeNode;
class PHG4Subsystem;
class PHParameters;

class CompCal;
class Cell;
class ExitWindowV2;
class OpDet;
class RootOut;

class G4LmonDetector : public PHG4Detector
{
 public:
  //! constructor
  G4LmonDetector(PHG4Subsystem *subsys, PHCompositeNode *Node, const std::string &dnam);

  //! destructor
  virtual ~G4LmonDetector() {}

  //! construct
  virtual void ConstructMe(G4LogicalVolume *world);

  virtual void Print(const std::string &what = "ALL") const;

  //!@name volume accessors
  //@{
  int IsInDetector(G4VPhysicalVolume *) const;
  //@}

  void SuperDetector(const std::string &name) { m_SuperDetector = name; }
  const std::string SuperDetector() const { return m_SuperDetector; }

  bool ExecuteSteppingActions(const G4Step* aStep);
  void ClearEvent();
  void FinishEvent();
  void SetRootOutput(RootOut *rout) {rootoutput = rout;}
 protected:
// active volumes
  std::set<G4VPhysicalVolume *> m_PhysicalVolumesSet;

  std::string m_SuperDetector;
  std::vector<Cell *> m_CellVector;
  std::vector<CompCal *> m_CompCalVector;
  std::vector<ExitWindowV2 *> m_ExitWindowV2Vector;
  std::vector<OpDet *> m_OpDetVector;
  RootOut *rootoutput;
};

#endif  // G4LMONDETECTOR_H
