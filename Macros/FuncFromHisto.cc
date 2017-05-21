using namespace std;

double quadra(double x, double *xx, double *yy){
  double a = ((yy[2]-yy[0])/(xx[2]-xx[0])*(xx[1]-xx[0])-(yy[1]-yy[0]))
         /((xx[2]*xx[2]-xx[0]*xx[0])/(xx[2]-xx[0])*(xx[1]-xx[0])-(xx[1]*xx[1]-xx[0]*xx[0]));
  double b = (yy[1]-yy[0]-a*(xx[1]*xx[1]-xx[0]*xx[0]))/(xx[1]-xx[0]);
  double c = yy[0]-b*xx[0]-a*xx[0]*xx[0];
  return a*x*x+b*x+c;
}

double FuncFromHisto(TH1D* Plot, double x, int smooth=0){


  if (smooth!=0) Plot->Smooth(smooth);

  int ioff;  
  double xx[3],yy[3];

  double hlow     = Plot->GetXaxis()->GetXmin();
  int    xnbin    = Plot->GetNbinsX();
  double binwidth = Plot->GetBinCenter(2)-Plot->GetBinCenter(1);
  
  int ind=(int)floor((x-(hlow+binwidth/2))/binwidth);
    
  if (ind<0) ind=0;
  if (ind>xnbin-2) ind=xnbin-2;
  
  if (ind%2==0) ind+=1;
  if (ind==xnbin-2){
    ioff = -2;
  } else if (ind==xnbin-1){
    ioff = -1;
  } else {
    ioff =  0;
  }
  
  for (int i=0;i<3;i++){
    xx[i] = Plot->GetBinCenter(ind+ioff+i);
    yy[i] = Plot->GetBinContent(ind+ioff+i);
  }
  //  xx[0] -= binwidth/2;
  //  xx[2] += binwidth/2;
  double val;
  if (ind<0 || ind >=xnbin){
    val = 0;
  } else {
    val = quadra(x,xx,yy);
  }
  if (val<0) val = 0;
  
  //  if (ind<3) cout << "Ind = " << xx[0] << " " << xx[1] << " " << xx[2] << endl;
  //  if (ind<3) cout << "Ind = " << ind << "Val = " << val << endl;
  
  return val;
  
}

