#define edge_min 0.8
#define edge_max 1.2

double tlo(double *x, double *par)
{
    if(x[0]<edge_min || x[0]>edge_max)
    {
        return par[0] + par[1] * x[0] + par[2] * x[0] * x[0];
    }
    else
    {
        TF1::RejectPoint();
        return 0;
    }
}

double tlo2(double *x, double *par)
{
    return par[0] + par[1] * x[0] + par[2] * x[0] * x[0];
}

double myGauss(double* x, double* par)
{
    double mi = par[0];
    double sigma = par[1];
    double c = par[2];
    double f = c/(sigma*sqrt(2*TMath::Pi()))*exp(-pow(x[0]-mi,2)/(2*pow(sigma,2)));
    return f;
}

double all(double* x, double* par)
{
    double tlo = par[0] + par[1] * x[0] + par[2] * x[0] * x[0];

    double mi = par[3];
    double sigma = par[4];
    double c = par[5];
    double gaussian = c/(sigma*sqrt(2*TMath::Pi()))*exp(-pow(x[0]-mi,2)/(2*pow(sigma,2)));
    return tlo+gaussian;
}

int macro(void)
{
    TFile *ifile = new TFile("example_data.root");
    TH1D *hist = (TH1D*)ifile->Get("hist");
    auto hist2 = new TH1D("hist2", "hist2", hist->GetNbinsX(), 0, 2);
    auto tlo = new TF1("tlo1", "tlo", 0, 2, 3);
    auto tlo2 = new TF1("tlo2", "tlo2", 0, 2, 3);
    tlo2->SetLineColor(1);
    auto signal = new TF1("signal", "myGauss", 0, 2, 3);
    signal->SetLineColor(2);
    auto all = new TF1("dopasowanie", "all", 0, 2, 6);
    all->SetLineColor(3);
    signal->SetParameters(1,1,1);
    hist->Fit(tlo, "LR0");
    

    auto c = new TCanvas("c", "c", 800, 600);

    hist->Draw();
    tlo2->SetParameters(tlo->GetParameters());
    tlo2->Draw("same");

    double value;
    for(int i = 0; i < hist2->GetNbinsX(); i++)
    {
        value = hist->GetBinContent(i+1) - tlo2->Eval(hist->GetBinCenter(i+1));
        if(value < 0)
            hist2->SetBinContent(i+1, 0);
        else
            hist2->SetBinContent(i+1, value);
    }
    hist2->GetXaxis()->SetRangeUser(edge_min, edge_max);
    hist2->Fit(signal, "LR0");
    signal->Draw("Same");
    all->SetParameter(0, tlo2->GetParameter(0));
    all->SetParameter(1, tlo2->GetParameter(1));
    all->SetParameter(2, tlo2->GetParameter(2));
    all->SetParameter(3, signal->GetParameter(0));
    all->SetParameter(4, signal->GetParameter(1));
    all->SetParameter(5, signal->GetParameter(2));
    all->Draw("Same");

    double sb = all->Integral(signal->GetParameter(0)-2*signal->GetParameter(1), signal->GetParameter(0)+2*signal->GetParameter(1));
    double s = signal->Integral(signal->GetParameter(0)-2*signal->GetParameter(1), signal->GetParameter(0)+2*signal->GetParameter(1));
    
    cout<<"Purity: " << s/sb << endl;
    return 0;
}