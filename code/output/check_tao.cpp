void check_tao(){
	TChain chain("Events");
    TString indir=".";
    TString inputFile ="TT_2018.root";
    chain.Add(indir+"/"+inputFile);
    Int_t LHEPart_pdgId[9];
    UInt_t nLHEPart;
    int LHE_nhad,LHE_ele,LHE_tao,LHE_mu;
    int ee=0,em=0,et=0;
    chain.SetBranchAddress("LHEPart_pdgId", LHEPart_pdgId);
    chain.SetBranchAddress("nLHEPart", &nLHEPart);
    for(int entry=0;entry<10000;entry++){
    	chain.GetEntry(entry);
    	LHE_nhad=0;
    	LHE_ele=0;
    	LHE_mu=0;
    	LHE_tao=0;
    	for(int i = nLHEPart-6; i < nLHEPart; i++) {
	        if(LHEPart_pdgId[i] == 2 || LHEPart_pdgId[i] == 4 || LHEPart_pdgId[i] == -2 || LHEPart_pdgId[i] == -4)
	            LHE_nhad++;
	        if(LHEPart_pdgId[i] == 1 || LHEPart_pdgId[i] == 3 || LHEPart_pdgId[i] == -1 || LHEPart_pdgId[i] == -3)
	            LHE_nhad++;
	        if(LHEPart_pdgId[i] == 11 || LHEPart_pdgId[i] == -11)
	            LHE_ele++;
	        if(LHEPart_pdgId[i] == 13 || LHEPart_pdgId[i] == -13)
	            LHE_mu++;
	        if(LHEPart_pdgId[i] == 15 || LHEPart_pdgId[i] == -15)
	            LHE_tao++;
	    }
	    ee+=LHE_ele;
	    em+=LHE_mu;
	    et+=LHE_tao;
    }
	cout<<"number of electron:"<<ee<<endl;
	cout<<"number of muon:"<<em<<endl;
	cout<<"number of tao:"<<et<<endl;	   
}