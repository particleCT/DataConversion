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
  ifstream infile(argv[1], ios::binary);
  char* outfolder = argv[2];
  //Check File Type
  char magic_number[5];
  infile.read(magic_number, 4);
  magic_number[4] = '\0';
  cout<<magic_number<<endl;
  cout<<magic_number<<" "<<strcmp(magic_number,"PCTD")<<endl;
  if( strcmp(magic_number, "PCTD") ) {
    printf("Error: unknown file type (should be PCTD)!\n");
    exit(1);
    }

  int version_id;
  cout<<version_id<<endl;
  infile.read((char*)&version_id, sizeof(int));
  if(version_id != 0){
    printf("ERROR: Unsupported Format version (%d)!\n", version_id);
    exit(1);
    }
  
  int num_histories;
  infile.read((char*)&num_histories, sizeof(int));
  cout << "num_histories = " << num_histories << endl;
  
  printf("Reading headers from file...\n");
  
  float projection_angle, beam_energy;
  int generation_date, preprocess_date;
  int phantom_name_size, data_source_size, prepared_by_size;
  char *phantom_name,*data_source, *prepared_by;

  
  infile.read((char*)&projection_angle, sizeof(float));
  infile.read((char*)&beam_energy, sizeof(float));
  infile.read((char*)&generation_date, sizeof(int));
  infile.read((char*)&preprocess_date, sizeof(int));
  infile.read((char*)&phantom_name_size, sizeof(int));
  phantom_name = (char*)malloc(phantom_name_size);
  infile.read(phantom_name, phantom_name_size);
  infile.read((char*)&data_source_size, sizeof(int));
  data_source = (char*)malloc(data_source_size);
  infile.read(data_source, data_source_size);
  infile.read((char*)&prepared_by_size, sizeof(int));
  prepared_by = (char*)malloc(prepared_by_size);
  infile.read(prepared_by, prepared_by_size);

  if(phantom_name==NULL) phantom_name =="Not determined";
  cout<< "projection_angle = " << projection_angle <<" "<<argv[1]<<endl;
  cout<< "beam_energy = " << beam_energy <<endl;
  cout<< "generation_date = " << generation_date <<endl;
  cout<< "preprocess_date = " << preprocess_date <<endl;
  cout<< "phantom_name = " << phantom_name <<endl;
  cout<< "data_source = " << data_source <<endl;
  cout<< "prepared_by = " << prepared_by <<endl;
  

  printf("Loading %d histories from file\n", num_histories);
  
  int data_size = num_histories * sizeof(float);

  /////////////////////

  int max_hist_per_projection = num_histories;
  unsigned int mem_size_hist_floats = sizeof(float) * max_hist_per_projection;
  unsigned int mem_size_hist_ints = sizeof(int) * max_hist_per_projection;
  
  // Allocate memory
  float* t_in1_h         = (float*) malloc(mem_size_hist_floats);
  float* t_in2_h         = (float*) malloc(mem_size_hist_floats);
  float* t_out1_h        = (float*) malloc(mem_size_hist_floats);
  float* t_out2_h        = (float*) malloc(mem_size_hist_floats);
  float* u_in1_h         = (float*) malloc(mem_size_hist_floats);
  float* u_in2_h         = (float*) malloc(mem_size_hist_floats);
  float* u_out1_h        = (float*) malloc(mem_size_hist_floats);
  float* u_out2_h        = (float*) malloc(mem_size_hist_floats);
  float* v_in1_h         = (float*) malloc(mem_size_hist_floats);
  float* v_in2_h         = (float*) malloc(mem_size_hist_floats);
  float* v_out1_h        = (float*) malloc(mem_size_hist_floats);
  float* v_out2_h        = (float*) malloc(mem_size_hist_floats);
  float* WEP_h           = (float*) malloc(mem_size_hist_floats);
  float* proj_angle      = (float*) malloc(mem_size_hist_floats);

  
  // Initialize memory
  memset(t_in1_h, 0, mem_size_hist_floats);
  memset(t_in2_h, 0, mem_size_hist_floats);
  memset(t_out1_h, 0, mem_size_hist_floats);
  memset(t_out2_h, 0, mem_size_hist_floats);
  memset(v_in1_h, 0, mem_size_hist_floats);
  memset(v_in2_h, 0, mem_size_hist_floats);
  memset(v_out1_h, 0, mem_size_hist_floats);
  memset(v_out2_h, 0, mem_size_hist_floats);
  memset(u_in1_h, 0, mem_size_hist_floats);
  memset(u_in2_h, 0, mem_size_hist_floats);
  memset(u_out1_h, 0, mem_size_hist_floats);
  memset(u_out2_h, 0, mem_size_hist_floats);
  memset(WEP_h, 0, mem_size_hist_floats);
  memset(proj_angle, 0, mem_size_hist_floats);
  /////////////////////
  
  infile.read((char*)t_in1_h, data_size);
  infile.read((char*)t_in2_h, data_size);
  infile.read((char*)t_out1_h, data_size);
  infile.read((char*)t_out2_h, data_size);
  infile.read((char*)v_in1_h, data_size);
  infile.read((char*)v_in2_h, data_size);
  infile.read((char*)v_out1_h, data_size);
  infile.read((char*)v_out2_h, data_size);
  infile.read((char*)u_in1_h, data_size);
  infile.read((char*)u_in2_h, data_size);
  infile.read((char*)u_out1_h, data_size);
  infile.read((char*)u_out2_h, data_size);
  infile.read((char*)WEP_h, data_size);
  infile.read((char*)proj_angle, data_size);

  Float_t t[4], v[4], u[4], wepl, angle;
  Float_t x0,y0,z0;
  Float_t x1,y1,z1;
  Float_t px0,py0,pz0;
  Float_t px1,py1,pz1;
  
  char* filename = Form("%s/projection_%1.1f.root",outfolder,projection_angle);
  cout<<projection_angle<<endl;
  TFile* fichierROOT = new TFile(filename,"recreate");

  TTree* header = new TTree("header", "meta-data");
  header->Branch("projection_angle",&projection_angle,"projection_angle/F");
  header->Branch("beam_energy",&beam_energy,"beam_energy/F");
  header->Branch("generation_date",&generation_date,"generation_date/I");
  header->Branch("preprocess_date",&preprocess_date,"preprocess_date/I");
  header->Branch("phantom_name_size",&phantom_name_size,"phantom_name_size/I");
  header->Branch("data_source_size",&data_source_size,"data_source_size/I");
  header->Branch("prepared_by_size",&prepared_by_size,"prepared_by_size/I");

  string data_source_string = string(data_source);
  string phantom_name_string = string(phantom_name);
  string prepared_by_string = string(prepared_by);
  header->Branch("phantom_name",&phantom_name_string);
  header->Branch("data_source",&data_source_string);
  header->Branch("prepared_by",&prepared_by_string);

  header->Fill();
  fichierROOT->cd();

  Int_t MaxEnergyTransFilter, ThresholdFilter, dEEFilter;
  TTree* tree = new TTree("phase", "bin tree");
  /*tree->Branch("t", &t, "t[4]/F");  // duplicate information
  tree->Branch("v", &v, "v[4]/F");
  tree->Branch("u", &u, "u[4]/F");*/
  tree->Branch("wepl", &wepl, "wepl/F");
  tree->Branch("angle", &angle, "angle/F");

  tree->Branch("x0",&x0,"x0/F");
  tree->Branch("y0",&y0,"y0/F");
  tree->Branch("z0",&z0,"z0/F");

  tree->Branch("x1",&x1,"x1/F");
  tree->Branch("y1",&y1,"y1/F");
  tree->Branch("z1",&z1,"z1/F");

  tree->Branch("px0",&px0,"px0/F");
  tree->Branch("py0",&py0,"py0/F");
  tree->Branch("pz0",&pz0,"pz0/F");

  tree->Branch("px1",&px1,"px1/F");
  tree->Branch("py1",&py1,"py1/F");
  tree->Branch("pz1",&pz1,"pz1/F"); 
  tree->Branch("MaxEnergyTransFilter",&MaxEnergyTransFilter,"MaxEnergyTransFilter/I");
  tree->Branch("ThresholdFilter",&ThresholdFilter,"ThresholdFilter/I");
  tree->Branch("dEEFilter",&dEEFilter,"dEEFilter/I");
  
  for( int i = 0; i < num_histories; i++ ){
     dEEFilter = 1;
     MaxEnergyTransFilter = 1;
     ThresholdFilter = 1;
     t[0] = t_in1_h[i];
     t[1] = t_in2_h[i];
     t[2] = t_out1_h[i];
     t[3] = t_out2_h[i];
     v[0] = v_in1_h[i];
     v[1] = v_in2_h[i];
     v[2] = v_out1_h[i];
     v[3] = v_out2_h[i];
     u[0] = u_in1_h[i];
     u[1] = u_in2_h[i];
     u[2] = u_out1_h[i];
     u[3] = u_out2_h[i];

     if(WEP_h[i] >= 5000){
       wepl = WEP_h[i]-5000;
       dEEFilter = 0;
       MaxEnergyTransFilter = 1;
       ThresholdFilter = 1;
     }

     else if(WEP_h[i] >= 2000 && WEP_h[i] < 5000){
       wepl = WEP_h[i]-2000;
       dEEFilter = 1;
       ThresholdFilter = 0;
       MaxEnergyTransFilter = 1;

     }

     else if(WEP_h[i] >= 1000 && WEP_h[i] < 2000){
       wepl = WEP_h[i]-1000;
       dEEFilter = 1;
       ThresholdFilter = 1;
       MaxEnergyTransFilter = 0;

     }
     else{
       wepl = WEP_h[i];
     }
     angle = fmod(proj_angle[i],360);


     x0   = u_in2_h[i];
     y0   = t_in2_h[i];  
     z0   = v_in2_h[i];

     x1   = u_out1_h[i];
     y1   = t_out1_h[i];  
     z1   = v_out1_h[i];

     px0  = u_in2_h[i] -  u_in1_h[i];
     py0  = t_in2_h[i] -  t_in1_h[i];
     pz0  = v_in2_h[i] -  v_in1_h[i];
     double Length_0 = sqrt(px0*px0 + py0*py0 + pz0*pz0);
     px0  = px0 /Length_0;
     py0  = py0 /Length_0;
     pz0  = pz0 /Length_0;

     px1  = u_out2_h[i] - u_out1_h[i];
     py1  = t_out2_h[i] - t_out1_h[i];
     pz1  = v_out2_h[i] - v_out1_h[i];
     double Length_1 = sqrt(px1*px1 + py1*py1 + pz1*pz1);
     px1  = px1 /Length_1;
     py1  = py1 /Length_1;
     pz1  = pz1 /Length_1;

     tree->Fill();
     if(i==0)      printf("Vin1 Vin2 Vout1 Vout2 Tin1 Tin2 Tout1 Tout2 WEP\n");
     if (i<10) {
      printf("%8.4f \t %8.4f \t %8.4f \t %8.4f \t %8.4f \t %8.4f \t %8.4f \t %8.4f \t %8.4f \n",   //
	   v_in1_h[i], v_in2_h[i],  v_out1_h[i], v_out2_h[i],  t_in1_h[i],  t_in2_h[i], //
	   t_out1_h[i], t_out2_h[i], WEP_h[i]);		
      cout<<"py0 "<<py0<<" pz0 "<<pz0<<endl;
      cout<<"py1 "<<py1<<" pz1 "<<pz1<<endl;
     }
  }
  header->Write("",TObject::kOverwrite);
  tree->Write("",TObject::kOverwrite);
  cout<< "Wrote into output tree b " << tree->GetEntries() << " events" <<endl;
  fichierROOT->Close();




  return 0;
}
