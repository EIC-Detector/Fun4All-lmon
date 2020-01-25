#ifndef G4LMONEVENTACTION_H
#define G4LMONEVENTACTION_H

#include <g4main/PHG4EventAction.h>

class G4LmonDetector;
class G4Event;
class RootOut;

class G4LmonEventAction: public PHG4EventAction
{

public:
  G4LmonEventAction(RootOut *rootout, G4LmonDetector *det);
  virtual ~G4LmonEventAction();

  void BeginOfEventAction(const G4Event*) ;
  void EndOfEventAction(const G4Event*) ;
private:
RootOut *rootoutput;
G4LmonDetector *m_Detector;
};


#endif
