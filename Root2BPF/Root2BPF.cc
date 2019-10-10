#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdarg>

#include <TFile.h>
#include <TTree.h>

using std::cout;	using std::endl;
using namespace std;

int main(int argc, char *argv[])
{
  cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;  

  TFile* fichierROOT = new TFile(argv[1], "update");
  TTree* tree = (TTree*)fichierROOT->Get("phase");
  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
  // Now the data
  fichierROOT->cd();
  float t[4], v[4], u[4], wepl, angle;
  float x0,y0,z0;
  float x1,y1,z1;
  float px0,py0,pz0;
  float px1,py1,pz1;
  float Einit = 200.0;
  Float_t WET_prob, Y_prob, Z_prob;
  Int_t MaxEnergyTransFilter, ThresholdFilter, dEEFilter, ThreeSigma;

  tree->SetBranchAddress("t", &t);
  tree->SetBranchAddress("v", &v);
  tree->SetBranchAddress("u", &u);
  tree->SetBranchAddress("wepl", &wepl);
  tree->SetBranchAddress("angle", &angle);

  tree->SetBranchAddress("x0",&x0);
  tree->SetBranchAddress("y0",&y0);
  tree->SetBranchAddress("z0",&z0);

  tree->SetBranchAddress("x1",&x1);
  tree->SetBranchAddress("y1",&y1);
  tree->SetBranchAddress("z1",&z1);

  tree->SetBranchAddress("px0",&px0);
  tree->SetBranchAddress("py0",&py0);
  tree->SetBranchAddress("pz0",&pz0);

  tree->SetBranchAddress("px1",&px1);
  tree->SetBranchAddress("py1",&py1);
  tree->SetBranchAddress("pz1",&pz1);

  tree->SetBranchAddress("MaxEnergyTransFilter",&MaxEnergyTransFilter);
  tree->SetBranchAddress("ThresholdFilter",&ThresholdFilter);
  tree->SetBranchAddress("dEEFilter",&dEEFilter);
  tree->SetBranchAddress("ThreeSigma",&ThreeSigma);
  tree->SetBranchAddress("WET_prob",&WET_prob);
  tree->SetBranchAddress("Y_prob",&Y_prob);
  tree->SetBranchAddress("Z_prob",&Z_prob);

  tree->GetEntry(0);
  float projection_angle = angle;
  ofstream outfile(Form("projection_%d.dat",int(2*projection_angle)), ios::binary);
  // Calorimeter mode
  int pass =0;
  for(int i =0; i<tree->GetEntries() ; i++){
    tree->GetEntry(i);
    // Filters
    if(wepl<0) continue;
    if(MaxEnergyTransFilter==0)continue;
    if(ThresholdFilter==0) continue;
    if(dEEFilter==0) continue;
    //if(ThreeSigma==0) continue;
    //if(WET_prob<0.6) continue; // Prior Filter
    x0/=10;    y0/=10;    z0/=10;
    x1/=10;    y1/=10;    z1/=10;
    wepl/=10;
    pass++;
    outfile.write(reinterpret_cast<const char*>(&x0) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&y0) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&z0) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&px0) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&py0) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&pz0) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&Einit) ,sizeof(float));

    outfile.write(reinterpret_cast<const char*>(&x1) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&y1) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&z1) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&px1) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&py1) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&pz1) ,sizeof(float));
    outfile.write(reinterpret_cast<const char*>(&wepl) ,sizeof(float));
  }
  outfile.close();  
  cout<<pass<<"/"<<tree->GetEntries()<<endl;
  return 0;
}
