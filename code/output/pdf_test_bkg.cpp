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
void pdf_test_bkg(TString fileNames){
	//TString fileNames="new_TT_TuneCH3_13TeV-powheg-herwig7_10.root"; 
	Float_t cross_sections;
	if(fileNames.Contains("t-channel_antitop_4f"))                     
		cross_sections=81;
	else if(fileNames.Contains("t-channel_top_4f"))
		cross_sections=136;
	else if(fileNames.Contains("tW_antitop_5f"))
		cross_sections=19.3;
	else if(fileNames.Contains("tW_top_5f"))
		cross_sections=19.3;
	else if(fileNames.Contains("ST_s-channel_4f"))
		cross_sections=3.4;
	Float_t K_Factor=1.0;	
	TString cuts[2]={"(jet_num>=4)","(jet_num==3)"};
	//TString dir="/eos/user/y/yuekai/output3/";
	const int xbin=8, ybin=9;
	Float_t lumi=137.1;
	TString condition="((mass_tt<=2000.0)&&(abs(rapidity_tt)<=5.0)&&(likelihood <19.0))";
	Double_t mtt_edges[9]={0,370,420,500,600,700,800,950,2000};
	Double_t ytt_edges[10]={-5.0,-1.4,-0.9,-0.5,-0.15,0.15,0.5,0.9,1.4,5.0};
	TChain *tree, *tree1;
	Int_t nweight;
	TH1D *h1_max, *h1_min, *nmc, *exp; 
	TH2D *hist[150];
	TString weight;
    ofstream oFile;
	oFile.open("out_bkg.txt", ios::app);
    oFile<<fileNames<<": "<<endl;
    //oFile.setf(ios::fixed, ios::floatfield);
	//fileNames[0]=fileNames[0].ReplaceAll(".root","_1*.root");
	for(int cut=0;cut<2;cut++){
		tree=new TChain("mytree");
		tree1=new TChain("rawtree");
		tree->Add(fileNames);
		tree1->Add(fileNames);
		tree->SetBranchAddress("nLHEPdfWeight",&nweight);
		tree->GetEntry(1);
		nmc=new TH1D("nmc","",50,0,100);
		exp=new TH1D("exp","",50,0,100);
		nmc->Sumw2();
		exp->Sumw2();
		tree1->Draw("nJet>>nmc","Generator_weight");
		tree->Draw("jet_num>>exp",condition+"*"+cuts[cut]+"*"+"Generator_weight");
		double nMC_total=nmc->GetSumOfWeights();
		double global_weight=cross_sections*1000*lumi/nMC_total*K_Factor;
		double expect=exp->GetSumOfWeights()*global_weight;
		weight=Form("%f*%s*%s*Generator_weight",global_weight,condition.Data(),cuts[cut].Data());
		for(int num=0;num<nweight;num++){
			hist[num]=new TH2D(Form("hist%d",num),"",xbin,mtt_edges, ybin, ytt_edges);
			hist[num]->Sumw2();
			tree->Draw(Form("rapidity_tt:mass_tt>>hist%d",num),weight+Form("*LHEPdfWeight[%d]",num));
		}
		h1_max=new TH1D("h1_max","",xbin*ybin,0,xbin*ybin);
		h1_min=new TH1D("h1_min","",xbin*ybin,0,xbin*ybin);
		h1_max->Sumw2();
		h1_min->Sumw2();
		Convert(hist,h1_max,h1_min,nweight);
	    //oFile<<fileNames<<": "<<endl;
		oFile<<"for cut "<<cuts[cut]<<" pdfup is: "<<setprecision(9)<<h1_max->GetSumOfWeights()<<" expected_num is: "<<expect<<" pdfDown is: "<<h1_min->GetSumOfWeights()<<endl;	
		delete tree;
		delete tree1;
		delete nmc;
		delete exp;
		delete h1_min;
		delete h1_max;
		for(int num=0;num<nweight;num++)
			delete hist[num];
	}
    oFile<<endl;
	oFile.close();
}
