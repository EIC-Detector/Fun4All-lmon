
#ifndef Magnet_h
#define Magnet_h

// spectrometer dipole magnet
#include <Geant4/globals.hh>
class G4LogicalVolume;

class Magnet {

  public:

    Magnet(G4double zpos, G4LogicalVolume*);
    virtual ~Magnet() {}

};

#endif

