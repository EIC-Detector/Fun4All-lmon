#include "G4LmonEventAction.h"
#include "G4LmonDetector.h"

#include "RootOut.h"

#include <iostream>

using namespace std;

G4LmonEventAction::G4LmonEventAction(RootOut *rootout, G4LmonDetector *det):
  rootoutput(rootout)
  , m_Detector(det)
{}

G4LmonEventAction::~G4LmonEventAction()
{
  rootoutput->Close();
}

void G4LmonEventAction::BeginOfEventAction(const G4Event*)
{
  m_Detector->ClearEvent();
}

void G4LmonEventAction::EndOfEventAction(const G4Event*)
{
  m_Detector->FinishEvent();
rootoutput->FillTree();
}
