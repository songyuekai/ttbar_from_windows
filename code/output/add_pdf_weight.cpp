void Convert(TH2D** histo, TH1D* rehist_max,TH1D* rehist_min, int num){
	Double_t max, min, error_max, error_min;
	int k=1;
	for (int i=0;i<histo[0]->GetNbinsX();i++){
		for (int j=0;j<histo[0]->GetNbinsY();j++){
			Int_t nbin=histo[0]->GetBin(i+1,j+1);
			max=histo[0]->GetBinContent(nbin);
			min=histo[0]->GetBinContent(nbin);
			error_max=histo[0]->GetBinError(nbin);
			error_min=histo[0]->GetBinError(nbin);
			for(int m=1;m<num;m++){
				if(max<histo[m]->GetBinContent(nbin)){
					max=histo[m]->GetBinContent(nbin);
					error_max=histo[m]->GetBinError(nbin);
				}
				if(min>histo[m]->GetBinContent(nbin)){
					min=histo[m]->GetBinContent(nbin);
					error_min=histo[m]->GetBinError(nbin);
				}
			}
			rehist_max->SetBinError(k,error_max);
			rehist_max->SetBinContent(k,max);
			rehist_min->SetBinError(k,error_min);
			rehist_min->SetBinContent(k++,min);
		}
	}
}
void check(TH1D* h1){
	for(int i=0;i<h1->GetNbinsX();i++){
		cout<<h1->GetBinContent(i)<<endl;
	}
}
void check(TH2D* h1){
	for(int i=0;i<h1->GetNbinsX();i++){
		for(int j=0;j<h1->GetNbinsX();j++){
			Int_t nbin=h1->GetBin(i+1,j+1);
			cout<<h1->GetBinContent(nbin)<<endl;
		}
	}
}
void add_pdf_weight(){
	const int nsample=18;
	TString fileNames[nsample]={"new_TT_TuneCH3_13TeV-powheg-herwig7.root",
        
                            "new_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                            "new_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                            "new_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                            "new_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",

                            "new_ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                            "new_ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                            "../../output2/new_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg.root",
                            "../../output2/new_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg.root",
                            "new_ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo.root",

                            "new_DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM.root",                           
                            "new_DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                                                                                                                            
                   
	};
							
	Float_t cross_sections[nsample]={832,
									11917.5, 3850.4, 1124, 579.3,
									81, 136, 35.6, 35.6, 3.4,
									169.9, 147.4, 41.0, 5.7, 1.4, 0.63, 0.15, 0.0036,
								    //27990000, 1712000, 347700, 32100, 6831, 1207, 119.9, 25.2,
								    };
	Float_t K_Factor[nsample]={1.0,
						 		1.0, 1.0, 1.0, 1.0, 
						 		1.0,1.0,1.0,1.0,1.0,
								1.23,1.23,1.23,1.23,1.23,1.23,1.23,1.23,
								//1.0, 1.0, 1.0,1.0, 1.0, 1.0,1.0, 1.0,
							};		
	TString filename[2]={"pdfweight_4jets.root","pdfweight_3jets.root"};
	TString cuts[2]={"(jet_num>=4)","(jet_num==3)"};
	TString process[]={"ttbar","WJets","STop","DYJets"};
	//TString dir="/eos/user/y/yuekai/output3/";
	int edge[]={0,1,5,10,18};
	const int xbin=8, ybin=9;
	Float_t lumi=137.1;
	TString condition="((mass_tt<=2000.0)&&(abs(rapidity_tt)<=5.0)&&(likelihood <19.0))";
	Double_t mtt_edges[9]={0,370,420,500,600,700,800,950,2000};
	Double_t ytt_edges[10]={-5.0,-1.4,-0.9,-0.5,-0.15,0.15,0.5,0.9,1.4,5.0};
	TString EW_weight[4]={"weight_ci0000","weight_ci0100","weight_ci0010","weight_ci0001"};
	TFile *file[2];
	for(int cut=0;cut<2;cut++)
		file[cut]=new TFile(filename[cut],"recreate");
	TChain *tree, *tree1;
	Int_t nweight;
	TH1D *h1_max[10], *h1_min[10], *nmc; 
	TH1D *h2_max, *h2_min;
	TH2D *hist[150];
	TString weight;
	//fileNames[0]=fileNames[0].ReplaceAll(".root","_1*.root");
	for(int i=0;i<nsample;i++)
		fileNames[i]=fileNames[i].ReplaceAll(".root","_*.root");
	for(int cut=0;cut<2;cut++){
		cout<<"start to calculate "<<cuts[cut]<<" :"<<endl;
		for(int i=0;i<4;i++){
			cout<<"this is "<<process[i]<<endl;
			if(i==0){
				for(int wnum=0;wnum<4;wnum++){
					cout<<"\t this is "<<EW_weight[wnum]<<" :"<<endl;
					for(int j=edge[0];j<edge[1];j++){
						cout<<"\t\t this is "<<fileNames[j]<<endl;
						tree=new TChain("mytree");
						tree1=new TChain("rawtree");
						tree->Add(fileNames[j]);
						tree1->Add(fileNames[j]);
						tree->SetBranchAddress("nLHEPdfWeight",&nweight);
						tree->GetEntry(1);
						nmc=new TH1D("nmc","",50,0,100);
						nmc->Sumw2();
						tree1->Draw("nJet>>nmc","Generator_weight");
						double nMC_total=nmc->GetSumOfWeights();
						double global_weight=cross_sections[j]*1000*lumi/nMC_total*K_Factor[j];
						weight=Form("%f*%s*%s*%s*Generator_weight",global_weight,EW_weight[wnum].Data(),condition.Data(),cuts[cut].Data());
						for(int num=0;num<nweight;num++){
							hist[num]=new TH2D(Form("hist%d",num),"",xbin,mtt_edges, ybin, ytt_edges);
							hist[num]->Sumw2();
							tree->Draw(Form("rapidity_tt:mass_tt>>hist%d",num),weight+Form("*LHEPdfWeight[%d]",num));
						}
						h2_max=new TH1D("h2_max","",xbin*ybin,0,xbin*ybin);
						h2_min=new TH1D("h2_min","",xbin*ybin,0,xbin*ybin);
						h2_max->Sumw2();
						h2_min->Sumw2();
						Convert(hist,h2_max,h2_min,nweight);
						if(j==0){
							h1_max[wnum]=(TH1D*)h2_max->Clone();
							h1_max[wnum]->SetName(process[i]+"_"+EW_weight[wnum]+"_pdfUp");
							h1_min[wnum]=(TH1D*)h2_min->Clone();
							h1_min[wnum]->SetName(process[i]+"_"+EW_weight[wnum]+"_pdfDown");
						}
						else{
							h1_max[wnum]->Add(h2_max);
							h1_min[wnum]->Add(h2_min);
						}
						delete tree;
						delete tree1;
						delete nmc;
						delete h2_min;
						delete h2_max;
						for(int num=0;num<nweight;num++)
							delete hist[num];
					}
				}
			}
			else{
				for(int j=edge[i];j<edge[i+1];j++){
					cout<<"\t this is "<<fileNames[j]<<endl;
					tree=new TChain("mytree");
					tree1=new TChain("rawtree");
					tree->Add(fileNames[j]);
					tree1->Add(fileNames[j]);
					tree->SetBranchAddress("nLHEPdfWeight",&nweight);
					tree->GetEntry(1);
					nmc=new TH1D("nmc","",50,0,100);
					nmc->Sumw2();
					tree1->Draw("nJet>>nmc","Generator_weight");
					float nMC_total=nmc->GetSumOfWeights();
					float global_weight=cross_sections[j]*1000*lumi/nMC_total*K_Factor[j];
					weight=Form("%f*%s*%s*Generator_weight",global_weight,condition.Data(),cuts[cut].Data());
					for(int num=0;num<nweight;num++){
						hist[num]=new TH2D(Form("hist%d",num),"",xbin,mtt_edges, ybin, ytt_edges);
						hist[num]->Sumw2();
						tree->Draw(Form("rapidity_tt:mass_tt>>hist%d",num),weight+Form("*LHEPdfWeight[%d]",num));
					}
					h2_max=new TH1D("h2_max","",xbin*ybin,0,xbin*ybin);
					h2_min=new TH1D("h2_min","",xbin*ybin,0,xbin*ybin);
					h2_max->Sumw2();
					h2_min->Sumw2();
					Convert(hist,h2_max,h2_min,nweight);
					if(j==edge[i]){
						h1_max[3+i]=(TH1D*)h2_max->Clone();
						h1_max[3+i]->SetName(process[i]+"_pdfUp");
						h1_min[3+i]=(TH1D*)h2_min->Clone();
						h1_min[3+i]->SetName(process[i]+"_pdfDown");
					}
					else{
						h1_max[3+i]->Add(h2_max);
						h1_min[3+i]->Add(h2_min);
					}
					delete tree;
					delete tree1;
					delete nmc;
					delete h2_min;
					delete h2_max;
					for(int num=0;num<nweight;num++)
						delete hist[num];
				}
			}
		}
		file[cut]->cd();
		for(int i=0;i<7;i++){
			h1_max[i]->Write();
			h1_min[i]->Write();
		}
		file[cut]->Close();
	}
}
