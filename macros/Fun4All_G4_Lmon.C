#if ROOT_VERSION_CODE >= ROOT_VERSION(6,00,0)
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllDummyInputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <g4detectors/PHG4DetectorSubsystem.h>
#include <g4histos/G4HitNtuple.h>
#include <g4main/PHG4ParticleGeneratorBase.h>
#include <g4main/PHG4ParticleGenerator.h>
#include <g4main/PHG4SimpleEventGenerator.h>
#include <g4main/PHG4ParticleGun.h>
#include <g4main/PHG4Reco.h>
#include <g4lmondetector/G4LmonSubsystem.h>
#include <phool/recoConsts.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libg4detectors.so)
R__LOAD_LIBRARY(libg4lmondetector.so)
R__LOAD_LIBRARY(libg4histos.so)

#endif

void Fun4All_G4_Lmon(int nEvents = 1)
{

  gSystem->Load("libfun4all");
  gSystem->Load("libg4detectors");
  gSystem->Load("libg4testbench");
  gSystem->Load("libg4histos");
  gSystem->Load("libg4lmondetector.so");

  ///////////////////////////////////////////
  // Make the Server
  //////////////////////////////////////////
  Fun4AllServer *se = Fun4AllServer::instance();
  recoConsts *rc = recoConsts::instance();
// if you want to fix the random seed to reproduce results
// set this flag
// rc->set_IntFlag("RANDOMSEED",12345); 

//
// Particle Generator
//

// the PHG4ParticleGenerator makes cones using phi and eta
   PHG4ParticleGenerator *gen = new PHG4ParticleGenerator();
   gen->set_name("geantino");
   gen->set_vtx(0, 3, 0);
   gen->set_eta_range(-0.9, 0.9);
   gen->set_mom_range(1.0, 10.0);
   gen->set_z_range(0.,0.);
     gen->set_phi_range(0.*TMath::Pi(), 2.*TMath::Pi());
     //              se->registerSubsystem(gen);

  PHG4ParticleGun *gun = new PHG4ParticleGun();
  gun->set_name("gamma");
  //gun->set_name("geantino");
  gun->AddParticle("pi-", 0, 0, -1); // see the magnetic field with this one
  gun->set_vtx(0, 0, 0); // shoots right into the original Examle01 volume
  gun->set_mom(0, 0, -1); // hits the tagger
  se->registerSubsystem(gun);

//
// Geant4 setup
//
  PHG4Reco* g4Reco = new PHG4Reco();
  g4Reco->set_field(0); // no field
  g4Reco->save_DST_geometry(false);
// try non default physics lists
  //g4Reco->SetPhysicsList("FTFP_BERT_HP");

  G4LmonSubsystem *lmon = new G4LmonSubsystem("LumiMon");
  g4Reco->registerSubsystem(lmon);

  se->registerSubsystem( g4Reco );
// this (dummy) input manager just drives the event loop
  Fun4AllInputManager *in = new Fun4AllDummyInputManager( "Dummy");
  se->registerInputManager( in );
// events = 0 => run forever
  if (nEvents <= 0)
  {
    return 0;
  }
  se->run(nEvents);
  lmon->Print();
  se->End();
  std::cout << "All done" << std::endl;
  delete se;
  gSystem->Exit(0);
}
