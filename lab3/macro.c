#define V_NUM 1
#define X_MIN 0
#define X_MAX TMath::Pi()/2
#define Y_MIN 0
#define Y_MAX TMath::Pi()/2

double func (double *val, double *par)
{
    double x = val[0];
    double y = val[1];

    if(x*y >= 0 && x*y <= TMath::Pi())
    {
        double c = par[0];

        double f = c*sin(x*y);

        return f;
    }
    else return 0;
}

void macro()
{
    auto width = 620;
    auto height = 480;
    
    auto cols = 2;
    auto rows = 2;
    
    auto c1 = new TCanvas("c1", "c1", width, height);
    
    c1->Divide(cols,rows);
    
    
    auto fun = new TF2("c*sin(x*y)", "func", X_MIN, X_MAX, Y_MIN, Y_MAX, V_NUM);
    fun->GetXaxis()->SetTitle("x");
    fun->GetYaxis()->SetTitle("y");

    fun->SetParameter(0, 1.);

    double norm_par = 1./fun->Integral(X_MIN, X_MAX, Y_MIN, Y_MAX);

    fun->SetParameter(0, norm_par);

    //cout << fun->Integral(X_MIN, X_MAX, Y_MIN, Y_MAX); <- unormowana funkcja

    auto den_hist = new TH2D("den", "dystrybuanta", 20, X_MIN, X_MAX, 20, Y_MIN, Y_MAX);

    double rx, ry;

    for(int i = 1; i<=10000000; i++)
    {
        fun->GetRandom2(rx, ry);
        den_hist->Fill(rx, ry);
    }

    double dist_norm_par = den_hist->Integral();
    den_hist->Scale(1./dist_norm_par);

    den_hist->GetXaxis()->SetTitle("x");
    den_hist->GetYaxis()->SetTitle("y");
    den_hist->GetZaxis()->SetTitle("f(x,y)");

    auto dist_hist = new TH2D("dist", "dystrybuanta", 20, X_MIN, X_MAX, 20, Y_MIN, Y_MAX);

    for(int i = 1; i<=20; i++)
    {
        for(int j = 1; j<=20; j++)
        {
            dist_hist->SetBinContent(i, j, den_hist->Integral(1, i, 1, j));
        }
    }

    dist_hist->GetXaxis()->SetTitle("x");
    dist_hist->GetYaxis()->SetTitle("y");
    dist_hist->GetZaxis()->SetTitle("d(x,y)");

    auto g = den_hist->ProjectionX();

    g->GetXaxis()->SetTitle("x");
    g->GetYaxis()->SetTitle("y");


    auto h = den_hist->ProjectionY();

    h->GetXaxis()->SetTitle("x");
    h->GetYaxis()->SetTitle("y");



    c1->cd(1);
    den_hist->Draw("lego2");

    c1->cd(2);
    dist_hist->Draw("lego2");

    c1->cd(3);
    g->Draw("histo");

    c1->cd(4);
    h->Draw("histo");

    double e_x = g->GetMean();// w nawiaise ktora os z 2d
    double e_y = h->GetMean();
    double sigma_x = g->GetStdDev();
    double sigma_y = h->GetStdDev();
    double cov_xy = den_hist->GetCovariance();
    double rho_xy = den_hist->GetCorrelationFactor();


    cout << "E(X): " << e_x << endl;
    cout << "E(Y): " << e_y << endl;
    cout << "sigma(X): " << sigma_x << endl;
    cout << "sigma(Y): " << sigma_y << endl;
    cout << "cov(X,Y): " << cov_xy << endl;
    cout << "rho(X,Y): " << rho_xy << endl;

     
}
