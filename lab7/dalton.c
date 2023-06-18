

void dalton(void)
{
    auto can = new TCanvas("c", "c", 1200, 600);
    auto hist = new TH1D("hist", "hist", 40, -20, 20);
    deskaGaltona(hist, 100, 10, 0.5);

    hist->Draw();
}