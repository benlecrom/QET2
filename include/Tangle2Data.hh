#ifndef Tangle2Data_hh
#define Tangle2Data_hh

#include "globals.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

#include <fstream>

#include "g4root.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;

// This is a lazy way of sharing memory. To avoid polluting the global
// namespace we define our own distinctive namespace.
namespace Tangle2 {
  extern G4Mutex outFileMutex;
  extern std::ofstream outFile;
  extern G4int nMasterEventsPh;
  // Worker quantities
  extern G4ThreadLocal G4int nEventsPh;
  extern G4ThreadLocal G4double eDepEvent;
  extern G4ThreadLocal G4double eDepCryst[18];
  extern G4ThreadLocal G4int TrueEvent;
  extern G4ThreadLocal G4int nbComptA;
  extern G4ThreadLocal G4int nbComptB;
  extern G4ThreadLocal G4double cosA;
  extern G4ThreadLocal G4double cosB;
}

#endif
