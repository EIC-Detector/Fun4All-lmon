
#ifndef OpTable_h
#define OpTable_h

// optical and scintillation properties of PbWO4 crystals
class G4Material;
class G4LogicalVolume;
class G4VPhysicalVolume;

class OpTable {

  public:

    void CrystalTable(G4Material *mat);
    void SurfaceTable(G4LogicalVolume *vol);
    void MakeBoundary(G4VPhysicalVolume *crystal, G4VPhysicalVolume *opdet);

};

#endif

