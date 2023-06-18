void m_pi (void)
{
    double width = 1200;
    double height = 400;
    auto c = new TCanvas("c", "c", width, height);
    c->Divide(3,1);

    TGraph *gr_acc1 = new TGraph();
    TGraph *gr_rej1 = new TGraph();
    gr_acc1->SetMarkerColor(kGreen);
    gr_rej1->SetMarkerColor(kRed);

    int n1 = 10000;
    int acc1_count = 0;
    int rej1_count = 0;
    // 50000;
    // 5000000;

    double x;
    double y;

    for(int i= 0; i < n1; i++)
    {
        x = gRandom->Uniform(0,1);
        y = gRandom->Uniform(0,1);

        if(x*x+y*y<=1)
        {
            gr_acc1->SetPoint(i, x, y);
            acc1_count++;
        }
        else
        {
          gr_rej1->SetPoint(i, x, y);
          rej1_count++;  
        } 
    }

    auto multi_gr1 = new TMultiGraph();
    multi_gr1->Add(gr_acc1);
    multi_gr1->Add(gr_rej1);
    c->cd(1);
    multi_gr1->Draw("AP");

    TGraph *gr_acc2 = new TGraph();
    TGraph *gr_rej2 = new TGraph();
    gr_acc2->SetMarkerColor(kGreen);
    gr_rej2->SetMarkerColor(kRed);

    int n2 = 50000;
    int acc2_count = 0;
    int rej2_count = 0;

    for(int i= 0; i < n2; i++)
    {
        x = gRandom->Uniform(0,1);
        y = gRandom->Uniform(0,1);

        if(x*x+y*y<=1)
        {
            gr_acc2->SetPoint(i, x, y);
            acc2_count++;
        }
        else
        {
          gr_rej2->SetPoint(i, x, y);
          rej2_count++;  
        } 
    }

    auto multi_gr2 = new TMultiGraph();
    multi_gr2->Add(gr_acc2);
    multi_gr2->Add(gr_rej2);
    c->cd(2);
    multi_gr2->Draw("AP");

    TGraph *gr_acc3 = new TGraph();
    TGraph *gr_rej3 = new TGraph();
    gr_acc3->SetMarkerColor(kGreen);
    gr_rej3->SetMarkerColor(kRed);

    int n3 = 5000000;
    int acc3_count = 0;
    int rej3_count = 0;

    for(int i= 0; i < n3; i++)
    {
        x = gRandom->Uniform(0,1);
        y = gRandom->Uniform(0,1);

        if(x*x+y*y<=1)
        {
            gr_acc3->SetPoint(i, x, y);
            acc3_count++;
        }
        else
        {
          gr_rej3->SetPoint(i, x, y);
          rej3_count++;  
        } 
    }

    auto multi_gr3 = new TMultiGraph();
    multi_gr3->Add(gr_acc3);
    multi_gr3->Add(gr_rej3);
    c->cd(3);
    multi_gr3->Draw("AP");

    cout << "Dla n = " << n1 << ": PI = " << (double) acc1_count/(acc1_count+rej1_count)*4 << "\n";
    cout << "Dla n = " << n2 << ": PI = " << (double) acc2_count/(acc2_count+rej2_count)*4 << "\n";
    cout << "Dla n = " << n3 << ": PI = " << (double) acc3_count/(acc3_count+rej3_count)*4 << "\n";
}