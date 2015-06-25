void circle(ofstream & ffout, PseudoJet & p, double radius, unsigned ls)
{
  ffout << "," << radius << "*sin(t)+" << p.eta() << ","
	<< radius << "*cos(t)+" << p.phi_std()
	<< " w l ls " << ls << " notitle\\" <<endl;
  return;
}

void cell(ofstream & ffout, PseudoJet & p)
{
  unsigned ps=0;
  if(p.e() > 1.) ps=1;
  if(p.e() > 5.) ps=2;
  if(p.e() > 10.) ps=3;
  if(p.e() > 50.) ps=4;
  if(p.e() > 100.) ps=5;
  ffout << "," << p.eta() << "," <<  p.phi()
	<< " w points " << ps << " notitle\\" <<endl;
  return;
}


void set_header_for_display(ofstream & ffout)
{
  ffout << "unset label" << endl; 
  ffout << "unset arrow" << endl;      
  ffout << "set key outside" << endl;
  ffout << "set xrange [-5:5]" << endl;
  ffout << "set yrange [-pi:pi]" << endl;
  ffout << "set size ratio -1" << endl;
  ffout << "set parametric" << endl;
  ffout << "set style line 1 lt 1 lw 2" << endl; 
  ffout << "set style line 2 lt 2 lw 2" << endl;
  ffout << "set style line 3 lt 3 lw 2" << endl;
  ffout << "set style line 4 lt 4 lw 2" << endl; 
  ffout << "set style line 5 lt 5 lw 2" << endl;
  ffout << "set style line 6 lt 6 lw 2" << endl;
  ffout << "plot 0.4*sin(t)+ 6, 0.4*cos(t)+4 w l ls 1 notitle\\" <<endl;
  return;
}

void output_hadron_to_display(ofstream & ffout, vector< PseudoJet> & hadrons)
{
  for (unsigned idummy=0;idummy<hadrons.size();idummy++){
    cell(ffout, hadrons.at(idummy));
  }  
  return;
}

void output_parton_to_display(ofstream & ffout, vector< PseudoJet> & partons)
{
  for(unsigned idummy=0;idummy<partons.size();idummy++)
    {
      //double rad = 0.05*max();
      double rad = 0.05;
      ffout << "," << rad << "*sin(t)+" 
	    << partons.at(idummy).eta() << ","
	    << rad << "*cos(t)+" 
	    << partons.at(idummy).phi()
	    << " w l ls 1 notitle\\" <<endl;
    }
}

void set_footer_for_display(ofstream & ffout)
{
  ffout << ", \"sample_event_out.dat\" using 2:3 w points title \"cell\" \\" <<endl;
  ffout << ", \"sample_event_parton.dat\" index 0 using 2:3 w points pt 4 title \"top1\" \\" <<endl;
  ffout << ", \"sample_event_parton.dat\" index 1 using 2:3 w points pt 5 title \"top2\" \\" <<endl;
  ffout << ", 0.4*sin(t)+ 6, 0.4*cos(t)+4 w l ls 1 notitle" <<endl;
  return;
}
