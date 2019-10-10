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

  //  //  //  //  //  //  //  //  //  //  //  //  //  //
  // Loading the files
  TFile* fichierROOT = new TFile(argv[1], "update");
  TTree* tree = (TTree*)fichierROOT->Get("phase");
  TTree* header = (TTree*)fichierROOT->Get("header");

  //  //  //  //  //  //  //  //  //  //  //  //  //  //
  // Defining the branches variables
  float projection_angle, beam_energy;
  int generation_date, preprocess_date;
  int phantom_name_size, data_source_size, prepared_by_size;
  char *phantom_name, *data_source, *prepared_by;
  std::string* phantom_name_string= new std::string;
  std::string* data_source_string= new std::string;
  std::string* prepared_by_string= new std::string;
  //*data_source_string=0, prepared_by_string=0;

  Float_t t[4], v[4], u[4], wepl, angle;
  Float_t x0,y0,z0;
  Float_t x1,y1,z1;
  Float_t px0,py0,pz0;
  Float_t px1,py1,pz1;
  Float_t WET_prob, Y_prob, Z_prob;
  Int_t MaxEnergyTransFilter, ThresholdFilter, dEEFilter, ThreeSigma;

  //  //  //  //  //  //  //  //  //  //  //  //  //  //
  // Setting the branches address
  header->SetBranchAddress("projection_angle",&projection_angle);
  header->SetBranchAddress("beam_energy",&beam_energy);
  header->SetBranchAddress("generation_date",&generation_date);
  header->SetBranchAddress("preprocess_date",&preprocess_date);
  header->SetBranchAddress("phantom_name_size",&phantom_name_size);
  header->SetBranchAddress("data_source_size",&data_source_size);
  header->SetBranchAddress("prepared_by_size",&prepared_by_size);
  header->SetBranchAddress("phantom_name",&phantom_name_string);
  header->SetBranchAddress("data_source",&data_source_string);
  header->SetBranchAddress("prepared_by",&prepared_by_string);
  header->GetEntry(0);

  tree->SetBranchAddress("t", &t);
  tree->SetBranchAddress("v", &v);
  tree->SetBranchAddress("u", &u);

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

  tree->SetBranchAddress("wepl", &wepl);
  tree->SetBranchAddress("angle", &angle);

  tree->SetBranchAddress("MaxEnergyTransFilter",&MaxEnergyTransFilter);
  tree->SetBranchAddress("ThresholdFilter",&ThresholdFilter);
  tree->SetBranchAddress("dEEFilter",&dEEFilter);
  tree->SetBranchAddress("ThreeSigma",&ThreeSigma);
  tree->SetBranchAddress("WET_prob",&WET_prob);
  tree->SetBranchAddress("Y_prob",&Y_prob);
  tree->SetBranchAddress("Z_prob",&Z_prob);


  //  //  //  //  //  //  //  //  //  //  //  //  //  //
  // Counting the new number of entries after filtering

  int num_histories = tree->GetEntries();
  int num_filtered_histories = 0;
  for(int i =0; i<num_histories; i++){
    tree->GetEntry(i);
    // Filters                                                                                                                                                                                                                              
    if(wepl<0) continue;
    if(MaxEnergyTransFilter==0)continue;
    if(ThresholdFilter==0) continue;
    if(dEEFilter==0) continue;
    //if(ThreeSigma==0) continue;    
    //if(WET_prob<0.95) continue;
    //if(Y_prob<0.1) continue;
    //if(Z_prob<0.1) continue;
    num_filtered_histories++;
  }


  //  //  //  //  //  //  //  //  //  //  //  //  //  //
  // Writing the header

  printf("Writing headers to file...\n");
  ofstream outfile(Form("projection_%1.1f.bin",projection_angle), ios::binary);
  //Check File Type
  char* magic_number = "PCTD" ;
  outfile.write(magic_number, 4);

  int version_id = 0;
  outfile.write((char*)&version_id, sizeof(int));
  // write the header
  cout << "num_histories written = " << num_filtered_histories << " out of "<< num_histories <<endl;
  outfile.write((char*)&num_filtered_histories, sizeof(int));  
  outfile.write((char*)&projection_angle, sizeof(float));
  outfile.write((char*)&beam_energy, sizeof(float));
  outfile.write((char*)&generation_date, sizeof(int));
  outfile.write((char*)&preprocess_date, sizeof(int));
  outfile.write((char*)&phantom_name_size, sizeof(int));
  outfile.write(phantom_name_string->c_str(), phantom_name_size);
  outfile.write((char*)&data_source_size, sizeof(int));
  outfile.write(data_source_string->c_str(), data_source_size);
  outfile.write((char*)&prepared_by_size, sizeof(int));
  outfile.write(prepared_by_string->c_str(), prepared_by_size);

  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
  // Now the data


  int data_size = num_filtered_histories * sizeof(float);
  // Allocate memory
  float* t_in1_h         = (float*) malloc(data_size);
  float* t_in2_h         = (float*) malloc(data_size);
  float* t_out1_h        = (float*) malloc(data_size);
  float* t_out2_h        = (float*) malloc(data_size);
  float* u_in1_h         = (float*) malloc(data_size);
  float* u_in2_h         = (float*) malloc(data_size);
  float* u_out1_h        = (float*) malloc(data_size);
  float* u_out2_h        = (float*) malloc(data_size);
  float* v_in1_h         = (float*) malloc(data_size);
  float* v_in2_h         = (float*) malloc(data_size);
  float* v_out1_h        = (float*) malloc(data_size);
  float* v_out2_h        = (float*) malloc(data_size);
  float* WEP_h           = (float*) malloc(data_size);

  // Initialize memory
  memset(t_in1_h, 0, data_size);
  memset(t_in2_h, 0, data_size);
  memset(t_out1_h, 0, data_size);
  memset(t_out2_h, 0, data_size);
  memset(v_in1_h, 0, data_size);
  memset(v_in2_h, 0, data_size);
  memset(v_out1_h, 0, data_size);
  memset(v_out2_h, 0, data_size);
  memset(u_in1_h, 0, data_size);
  memset(u_in2_h, 0, data_size);
  memset(u_out1_h, 0, data_size);
  memset(u_out2_h, 0, data_size);
  memset(WEP_h, 0, data_size);
  
  int counter = 0;

  for(int i =0; i<num_histories; i++){
    tree->GetEntry(i);
    if(wepl<0) continue;
    if(MaxEnergyTransFilter==0)continue;
    if(ThresholdFilter==0) continue;
    if(dEEFilter==0) continue;
    //if(ThreeSigma==0) continue;
    //if(WET_prob<0.95) continue;

    t_in1_h[counter]  = t[0];
    t_in2_h[counter]  = t[1];
    t_out1_h[counter] = t[2];
    t_out2_h[counter] = t[3];
    v_in1_h[counter]  = v[0];
    v_in2_h[counter]  = v[1];
    v_out1_h[counter] = v[2];
    v_out2_h[counter] = v[3];
    u_in1_h[counter]  = u[0];
    u_in2_h[counter]  = u[1];
    u_out1_h[counter] = u[2];
    u_out2_h[counter] = u[3];
    WEP_h[counter]    = wepl;
    counter++;
  }

  outfile.write((char*)t_in1_h, data_size);
  outfile.write((char*)t_in2_h, data_size);
  outfile.write((char*)t_out1_h, data_size);
  outfile.write((char*)t_out2_h, data_size);
  outfile.write((char*)v_in1_h, data_size);
  outfile.write((char*)v_in2_h, data_size);
  outfile.write((char*)v_out1_h, data_size);
  outfile.write((char*)v_out2_h, data_size);
  outfile.write((char*)u_in1_h, data_size);
  outfile.write((char*)u_in2_h, data_size);
  outfile.write((char*)u_out1_h, data_size);
  outfile.write((char*)u_out2_h, data_size);
  outfile.write((char*)WEP_h, data_size);
  outfile.close();  
  return 0;
}
