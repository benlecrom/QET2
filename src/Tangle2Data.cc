#include "Tangle2Data.hh"

G4Mutex Tangle2::outFileMutex = G4MUTEX_INITIALIZER;
std::ofstream Tangle2::outFile("outFile.csv");

G4int Tangle2::nMasterEventsPh = 0;

// Worker quantities
G4ThreadLocal G4int Tangle2::nEventsPh = 0;
G4ThreadLocal G4double Tangle2::eDepEvent = 0.;
G4ThreadLocal G4double Tangle2::eDepCryst[18] ={0.};
G4ThreadLocal G4int Tangle2::TrueEvent = 0;
G4ThreadLocal G4int Tangle2::nbComptA = 0;
G4ThreadLocal G4int Tangle2::nbComptB = 0;
G4ThreadLocal G4double Tangle2::cosA = -1.;
G4ThreadLocal G4double Tangle2::cosB = -1.;

