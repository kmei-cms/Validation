scram b -j 8
rates.exe new ../mh1000_pl10000/
mv rates_new_cond.root rates_new_cond_pl10000_4L1Jets.root
rates.exe new ../mh1000_pl1000/
mv rates_new_cond.root rates_new_cond_pl1000_4L1Jets.root
rates.exe new ../mh1000_pl500/
mv rates_new_cond.root rates_new_cond_pl500_4L1Jets.root
rates.exe new ../QCD/
mv rates_new_cond.root rates_new_cond_QCD_4L1Jets.root
rates.exe new ../NeutrinoGun/
mv rates_new_cond.root rates_new_cond_nugunTDC_4L1Jets.root
draw_rates.exe
