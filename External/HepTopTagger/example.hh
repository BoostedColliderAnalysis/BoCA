void ReadEvent(ifstream & fin, vector<PseudoJet> & vec_jets)
{
  while(!fin.eof()){
    double e,x,y,z;
    PseudoJet p;
    fin >> e >> x >> y >> z;
    if(!fin.eof()){
      p.reset(x,y,z,e);
      vec_jets.push_back(p);
    }
  }
  cout << "ReadEvent: " << vec_jets.size() << " particles are read" << endl;
  return;
}


void output_vec_pseudojet(  ofstream & fout, vector<PseudoJet> & vec_jets)
{
  for(unsigned idum=0;idum<vec_jets.size();idum++){    
    fout << vec_jets.at(idum).perp() << " ";
    fout << vec_jets.at(idum).eta() << " ";
    fout << vec_jets.at(idum).phi_std() << endl;
  }
  return;
}


vector<fastjet::PseudoJet> gran_jets ( vector<fastjet::PseudoJet> & ori_hadrons,
				       const double & eta_cell, const double & phi_cell, const double & pt_cutoff)
{
	
       double pi = 3.142592654;
	vector<fastjet::PseudoJet> granulated_jets;
	granulated_jets.clear();
	
	ori_hadrons = sorted_by_pt(ori_hadrons);
	granulated_jets.push_back(ori_hadrons[0]);		
	for (unsigned i= 1; i < ori_hadrons.size(); i++)
	{
		int new_jet= 0;
		for (unsigned j=0; j < granulated_jets.size(); j++)
		{						
			double eta_cell_diff = abs(ori_hadrons[i].pseudorapidity() -
									   granulated_jets[j].pseudorapidity())/eta_cell;
			double phi_cell_diff = abs(ori_hadrons[i].phi() -
									   granulated_jets[j].phi());
			if(phi_cell_diff > pi) 	phi_cell_diff = 2*pi - phi_cell_diff;
			phi_cell_diff = phi_cell_diff/phi_cell;	
			
			if( eta_cell_diff < 1 && phi_cell_diff < 1)
			{						
				new_jet = 1;
				
				double total_energy  = ori_hadrons[i].e() + granulated_jets[j].e();
				double rescale_factor = sqrt( pow(ori_hadrons[i].px()+granulated_jets[j].px(),2) +
											 pow(ori_hadrons[i].py()+granulated_jets[j].py(),2) +
											 pow(ori_hadrons[i].pz()+granulated_jets[j].pz(),2) );
				double rescaled_px = total_energy*(ori_hadrons[i].px()+granulated_jets[j].px()) /rescale_factor ;
				double rescaled_py = total_energy*(ori_hadrons[i].py()+granulated_jets[j].py()) /rescale_factor ;
				double rescaled_pz = total_energy*(ori_hadrons[i].pz()+granulated_jets[j].pz()) /rescale_factor ;
				
				fastjet::PseudoJet comb_jet( rescaled_px, rescaled_py,rescaled_pz, total_energy);
				
				comb_jet.set_user_index(ori_hadrons[i].user_index()+granulated_jets[j].user_index());
				
				granulated_jets.erase(granulated_jets.begin()+j);
				granulated_jets.push_back(comb_jet);
				break;
			}
		}
		if(new_jet != 1)
		{
			granulated_jets.push_back(ori_hadrons[i]);
			granulated_jets = sorted_by_pt(granulated_jets);
		}	
	}
	

	for(unsigned ii=0; ii <granulated_jets.size();ii++)
	  {
	
	    if((granulated_jets[ii].perp() < pt_cutoff))
	      {	
		granulated_jets.erase(granulated_jets.begin()+ii);
		ii--;
	      }
	  }
	
	return(granulated_jets);
	
}	
