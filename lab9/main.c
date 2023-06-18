double func(double *val, double *par)
{
    double x = val[0];
    double k = par[0];

    double f = 1/(pow(2, k/2)*ROOT::Math::tgamma(k/2))*pow(x,k/2-1)*exp(-x/2);

    return f;
}

double chi2(TH1D* hist, TF1* fun)
{
    int bins = 9;
    double T = 0;
    for(int i = 1; i < bins+1; i++)
    {
        T += pow(hist->GetBinContent(i)-fun->Eval(hist->GetBinCenter(i)), 2)/fun->Eval(hist->GetBinCenter(i));
    }

    return T;
}

bool testChi2(double T, double alpha, int ndf)
{
    auto chiFun = new TF1("chi", "func", 0, 30, 1);
    chiFun->SetParameters(ndf);
    if(1-alpha < chiFun->Integral(0, T))
        return 0;
    else
        return 1;
}

int main(void)
{
    ifstream ifile;
    ifile.open("dane10.txt");

    auto histogram = new TH1D("hist", "hist", 9, 0, 9);
    double k, n, lambda_1, N = 0;
    while(ifile >> k && ifile >> n)
    {
        N+=n;
        lambda_1 += k*n;
        histogram->Fill(k,n);
    }
    lambda_1 /= N;

    cout << "N: " << N << endl;
    cout << "Lambda_1: " << lambda_1 << endl;

    auto fun = new TF1("funkcja na sztywno", "[1]*TMath::PoissonI(x,[0])", 0, 9);
    fun->SetParameter(0,lambda_1); 
    fun->SetParameter(1, N);

    auto fitFun = new TF1("funkcja fitowana", "[1]*TMath::PoissonI(x,[0])", 0, 9);
    fitFun->FixParameter(1, N);
    fitFun->SetParameter(0, 1);
    fitFun->SetLineColor(3);

    double w = 800;
    double h = 600;
    auto c = new TCanvas("c", "c", w, h);

    double alpha = 0.01;

    histogram->Fit(fitFun, "LR");
    histogram->Draw("histo");
    fun->Draw("Same");
    fitFun->Draw("Same");

    cout << "lambda: " << lambda_1 << endl;
    cout << "statystyka testowa: " << chi2(histogram, fun) << endl;
    cout << "ststTest/NDF: " << chi2(histogram, fun)/(histogram->GetNbinsX()-1-0) << endl;
    cout << "ststTest/NDF: " << histogram->GetNbinsX()-1-0 << " lub " << fun->GetNDF() <<endl << endl;
    // cout << chi2(histogram, fitFun) << endl;
    cout << "lambda: " << fitFun->GetParameter(0) << endl;
    cout << "Chi2: " << chi2(histogram, fun) << " lub " << fitFun->GetChisquare() << endl;
    cout << "Chi2/NDF: " << fitFun->GetChisquare()/fitFun->GetNDF() << endl;
    cout << "NDF: " << histogram->GetNbinsX()-1-1 << " lub " << fitFun->GetNDF() << endl;
    cout << "na poziomie zgodnosci " << alpha << ": ";

    if(testChi2(chi2(histogram, fitFun), alpha, fitFun->GetNDF()))
        cout << "Brak podstaw do odrzucenia hipotezy" << endl;
    else
        cout << "Istnieja podstawy do odrzucenia hipotezy" << endl;


}