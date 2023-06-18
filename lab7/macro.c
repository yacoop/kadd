void splot(TF1 **f, int k, TH1D *h, int n)
{
    // double l* = new double[n];
    double l;
    for(int i = 0; i < n; i++)
    {
        l = 0;
        for(int j = 0; j < k; j++)
        {
            l += f[j]->GetRandom();
        }
        h->Fill(l);
    }
}

double norm_dist_func(double *val, double *par) {
    double x = val[0];

    double mi = par[0];
    double sigma = par[1];
    // double f = 1.0/(sigma*sqrt(2*TMath::Pi()))*exp(-1/2*pow((x-mi)/sigma, 2)); //OCOCHODZI
    double f = 1.0/(sigma*sqrt(2*TMath::Pi()))*exp(-pow(x-mi,2)/(2*pow(sigma,2)));
    return f;
}

void deskaGaltona(TH1D* h, int n, int l, double p)
{
    double x, a;
    for(int i = 0; i<n; i++)
    {
        a = 0;
        for(int j = 0; j<l; j++)
        {
            x = gRandom->Uniform(0,1);
            if(x>p) a++;
            else a--;
        }
        h->Fill(a);
    }
}

void macro(void)
{
    int n = 10000;

    auto splot1 = new TH1D("splot1", "splot1", 100, 0, 6);
    auto splot2 = new TH1D("splot2", "splot2", 100, 0, 9);
    auto splot_norm = new TH1D("splot normalny", "splot normalny", 100, 0, 6);

    auto f1 = new TF1("funkcja1", "[0]", 0, 3);
    f1->SetParameter(0, 1.0);
    f1->SetParameter(0, 1.0/f1->Integral(0, 3));

    // auto f2 = new TF1("funkcja2", "[0]", 0, 3);
    // f2->SetParameter(0, 1.0);
    // f2->SetParameter(0, 1.0/f2->Integral(0, 3));
    // auto f3 = new TF1("funkcja3", "[0]", 0, 3);
    // f3->SetParameter(0, 1.0);
    // f3->SetParameter(0, 1.0/f3->Integral(0, 3));

    auto f_table = new TF1*[3];
    f_table[0] = f1;
    f_table[1] = f1;
    f_table[2] = f1;

    splot(f_table, 2, splot1, n);
    splot(f_table, 3, splot2, n);

    auto norm_func1 = new TF1("normal distribution1", norm_dist_func, 0, 2, 2);
    norm_func1->SetParameters(1.0, 0.3);

    auto norm_func2 = new TF1("normal distribution2", norm_dist_func, 0, 4, 2);
    norm_func2->SetParameters(2.0, 0.5);

    auto norm_table = new TF1*[2];
    norm_table[0] = norm_func1;
    norm_table[1] = norm_func2;

    splot(norm_table, 2, splot_norm, n);

    auto deska = new TH1D("hist", "hist", 40, -20, 20);
    deskaGaltona(deska, n, 20, 0.5);


    auto can = new TCanvas("c", "c", 1200, 600);
    can->Divide(2,2);
    can->cd(1);
    splot1->Draw();
    can->cd(2);
    splot2->Draw();
    can->cd(3);
    splot_norm->Draw();
    can->cd(4);
    deska->Draw();

    cout << "Srednia1:" << norm_func1->Mean(0, 2) << endl;
    cout << "Odchylenie1:" << sqrt(norm_func1->Variance(0,2)) << endl;

    cout << "Srednia2:" << norm_func2->Mean(0, 4) << endl;
    cout << "Odchylenie2:" << sqrt(norm_func2->Variance(0,4)) << endl;


    cout << "Srednia: " << splot_norm->GetMean() << endl;
    cout << "Odchylenie: " << splot_norm->GetStdDev() << endl;
}