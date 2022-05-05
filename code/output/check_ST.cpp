void check_ST(){
	TString file="new_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg_38.root";
	TChain chain("mytree");
	Float_t weight[103];
	chain.Add(file);
	chain.SetBranchAddress("LHEPdfWeight",weight);
	for(int j=0;j<1;j++){
		chain.GetEntry(j);
		for(int i=0;i<103;i++){
			//if(weight[i]>1.0){
				cout<<weight[i]<<endl;
				//break;
			//}
		}
	}
		
}