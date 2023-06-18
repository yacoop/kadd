void macro()
{
    auto w = 620;
    auto h = 480;
    
    auto cols = 2;
    auto rows = 2;
    
    auto c1 = new TCanvas("c1", "c1", w, h);
    
    c1->Divide(cols,rows);
    
    
    auto sinfun = new TF1("Funkcja sinus(2x)/x", "sin(2*x)/x", 0, 10);
    sinfun->GetXaxis()->SetTitle("x");
    sinfun->GetYaxis()->SetTitle("y");
    
    auto lapfun = new TF1("Funkcja Laplace'a", "TMath::LaplaceDist(x)", 0 , 10);
    lapfun->GetYaxis()->SetTitle("y");
    lapfun->GetXaxis()->SetTitle("x");
    
    auto hist = new TH1D("hist", "title", 10 ,0 ,10);
    
    int tabx[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int taby[10] = {2, 5, 8, 11, 5, 2, 3, 6, 5, 1};
    
    for(int i=1; i<10; i++)
    {
        hist->SetBinContent(i,taby[i]);
    }


    auto integral = hist->Integral();
    hist->Scale(1.0/integral);
    
    
    
    c1->cd(1);
    sinfun->Draw();
    
    c1->cd(2);
    lapfun->DrawCopy();

    
    c1->cd(3);
    sinfun->Draw();
    lapfun->SetLineColor(kGreen);
    lapfun->Draw("same");
    
    auto legend = new TLegend(0.2, 0.2);
    legend->AddEntry(sinfun, "#frac{sin(2x)}{x}", "l");
    
    legend->Draw();
    
    
    c1->cd(4);
    hist->Draw("histo");
    
    auto c2 = new TCanvas("c2", "c2", w, h);
    

    
    auto gr = new TGraph(10, tabx, taby);
    
     
}
