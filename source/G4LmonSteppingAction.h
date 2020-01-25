// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4LMONSTEPPINGACTION_H
#define G4LMONSTEPPINGACTION_H

#include <g4main/PHG4SteppingAction.h>

class G4Step;
class G4VPhysicalVolume;
class PHCompositeNode;
class G4LmonDetector;
class PHG4Hit;
class PHG4HitContainer;
class PHParameters;

class G4LmonSteppingAction : public PHG4SteppingAction
{
 public:
  //! constructor
  G4LmonSteppingAction(G4LmonDetector*);

  //! destructor
  virtual ~G4LmonSteppingAction(){}

  //! stepping action
  bool UserSteppingAction(const G4Step*, bool);

  //! reimplemented from base class
  // virtual void SetInterfacePointers(PHCompositeNode*);

 private:
  //! pointer to the detector
  G4LmonDetector* m_Detector;
  //! pointer to hit container
};

#endif  // G4LMONSTEPPINGACTION_H
