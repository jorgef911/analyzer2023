#include "Systematics.h"


Systematics::Systematics(){}

Systematics::Systematics(std::unordered_map<std::string, PartStats> const &distats){

}
Systematics::~Systematics(){}

void Systematics::init(){

}

void Systematics::shiftJet(Particle& jet, TLorentzVector recoJet, std::string& syst_name, int syst){

  jet.addP4Syst(recoJet, syst);
  return;

}

void Systematics::shiftParticle(Particle& jet, TLorentzVector recoJet, double const& corrJetPt, double& corrJetMass, std::string& syst_name, int syst){

  TLorentzVector shiftedRecoJet;
  // Set the new components of the 4-momentum
  shiftedRecoJet.SetPtEtaPhiM(corrJetPt, recoJet.Eta(), recoJet.Phi(), corrJetMass);

  // std::cout << "I get here in shift particle" << std::endl;

  jet.addP4Syst(shiftedRecoJet, syst);
  return;

}

/* void Systematics::shiftLepton(Lepton& lepton, TLorentzVector recoLep, TLorentzVector genLep, double& dPx, double& dPy, int syst){
  if (genLep == TLorentzVector(0,0,0,0)) {
    lepton.addP4Syst(recoLep, syst);
    return;
  }
  double ratio = ((genLep.Pt()*scale) + (recoLep.Pt() - genLep.Pt())*resolution)/recoLep.Pt();
  //cout<<"ratio  "<<ratio<<"  "<<scale<<"  "<<resolution    <<std::endl;
   //add the shifted part up
   dPx+=recoLep.Px()*(ratio-1);
   dPy+=recoLep.Py()*(ratio-1);
   //WARNING change the particle content for the particle
   recoLep*=ratio;
   lepton.addP4Syst(recoLep, syst);
   return;
}
*/

/*void Systematics::loadScaleRes(const PartStats& smear, const PartStats& syst, std::string syst_name) {
  scale = 1;
  resolution = 1;
  if(smear.bfind("SmearTheParticle")) {
    scale = smear.dmap.at("PtScaleOffset");
    resolution = smear.dmap.at("PtResolutionOffset");
  }
  if(syst_name.find("_Res_")) {
    resolution = syst_name.find("_Up") ? 1 + syst.dmap.at("res") : 1 - syst.dmap.at("res");
    scale=1;
  } else if(syst_name.find("_Scale_")) {
    scale = syst_name.find("_Up") ? 1+syst.dmap.at("scale") : 1- syst.dmap.at("scale");
    resolution=1;
  }
}
*/

void Systematics::loadScaleRes(const PartStats& smear, const PartStats& syst, std::string syst_name) {
  scale = 1;
  resolution = 1;
  if(smear.bfind("SmearTheParticle")) {
    scale = smear.dmap.at("PtScaleOffset");
    resolution = smear.dmap.at("PtResolutionOffset");
  }
  if(syst_name.find("_Res_")) {
   resolution = syst_name.find("_Down") ? 1 + syst.dmap.at("res") : 1 - syst.dmap.at("res");
    scale=1;
  }  else if(syst_name.find("_Scale_")){ 
    //if(syst_name.find("_Scale_")){
    std::cout<<"Entering in the loop "<<std::endl;
    scale = syst_name.find("_Up") ? 1+syst.dmap.at("scale") : 1- syst.dmap.at("scale");
    resolution=0;
  }
}


void Systematics::shiftLepton(Lepton& lep, TLorentzVector recoLep, TLorentzVector genLep, double& dPx, double& dPy, int syst){
  if (genLep == TLorentzVector(0,0,0,0)) {
    lep.addP4Syst(recoLep, syst);
    return;
  }
std::cout<<"Systematics working .." << std::endl;
   double ratio = scale+(1-((genLep.Pt())/(recoLep.Pt())))*resolution;
   //double ratio=scale+resolution*( (recoLep.Pt())/(genLep.Pt()) -1   );
   std::cout<<" Ratio: "<<ratio<<"      Scale: "<<scale<<"     Resolution: "<<resolution<< "      GenLep: " << genLep.Pt() <<"     Reco Lep: " << recoLep.Pt()  <<  std::endl;
   dPx+=recoLep.Px()*(ratio-1);
   dPy+=recoLep.Py()*(ratio-1);
   recoLep*=ratio;
   lep.addP4Syst(recoLep, syst);
   return;
}
