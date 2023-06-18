double func(double *val, double *par)
{
    double x = val[0];
    double k = par[0];

    double f = 1/(pow(2, k/2)*ROOT::Math::tgamma(k/2))*pow(x,k/2-1)*exp(-x/2);

    return f;
}

void splot(TF1 *f, int k, TH1D *h)
{
    int n = 50000;
    double l;
    for(int i = 0; i < n; i++)
    {
        l = 0;
        for(int j = 0; j < k; j++)
        {
            l += f->GetRandom();
        }
        h->Fill(l);
    }
}

int main(void)
{
    int n = 1;
    const int size = 19;

    auto func_table = new TF1*[size];

    for(int i = 0; i < size; i++)
    {
        func_table[i] = new TF1("funkcja1", func, 0, 30, 1);
        func_table[i]->SetParameters(i+1);
        func_table[i]->SetLineColor((float)i/2+1);
    }



    auto f1 = new TF1("funkcja1", "[0]", 0, 1);
    f1->SetParameter(0, 1.0);
    f1->SetParameter(0, 1.0/f1->Integral(0, 1));

    auto can = new TCanvas("c", "c", 1200, 600);

    can->Divide(2,2);

    can->cd(1);
    func_table[0]->Draw();
    for(int i = 1; i < size; i++)
    {
        func_table[i]->Draw("Same");
    }

    can->cd(2);
    func_table[0]->DrawIntegral();
    for(int i = 1; i < size; i++)
    {
        func_table[i]->DrawIntegral("Same");
    }

    can->cd(3);


    double warunek = 0;
    do{
        n++;
        auto hist = new TH1D("splot1", "splot1", 100, 0, n);
        splot(f1, n, hist);

        auto fit = new TF1("fit", "gaus", 0, n);
        hist->Fit(fit, "R");
        warunek = fit->GetChisquare()/fit->GetNDF();
        cout << "warunek: " << warunek << endl;

    }while(warunek >= 1);

    cout << "ilosc splotow: " << n << endl;



    return 0;
}