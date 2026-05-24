#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

string sinh_chuoi(int do_dai, mt19937& may_quay) {
    uniform_int_distribution<int> random_ki_tu(0, 25);
    string ket_qua = "";
    for (int i = 0; i < do_dai; ++i) {
        char ki_tu = 'a' + random_ki_tu(may_quay);
        ket_qua += ki_tu;
    }
    return ket_qua;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Error \n";
        return 1;
    }

    string loai_bai = argv[1];
    string chuoi_so = argv[2];
    int so_thu_tu = stoi(chuoi_so);

    random_device rd;
    mt19937 may_quay(rd());

    if (loai_bai == "int") {
        int n = 100000;
        cout << n << "\n";
        
        uniform_int_distribution<long long> random_so(-2147483648LL, 2147483647LL);

        if (so_thu_tu == 1) {
            // ngau nhien
            for (int i = 0; i < n; ++i) {
                cout << random_so(may_quay) << "\n";
            }
        } 
        else if (so_thu_tu == 2) {
            // da sort giam
            vector<long long> mang(n);
            for (int i = 0; i < n; ++i) {
                mang[i] = random_so(may_quay);
            }
            sort(mang.begin(), mang.end(), greater<long long>());
            
            for (int i = 0; i < n; ++i) {
                cout << mang[i] << "\n";
            }
        }
        else if (so_thu_tu == 3) {
            // trung lap 2 val
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) {
                    cout << 1 << "\n";
                } else {
                    cout << 2 << "\n";
                }
            }
        }
        else if (so_thu_tu == 4) {
            // gan nhu da sort
            
            vector<long long> mang(n);
            for (int i = 0; i < n; ++i) {
                mang[i] = random_so(may_quay);
            }
            sort(mang.begin(), mang.end());
            
            uniform_int_distribution<int> random_vi_tri(0, n - 1);
            for (int i = 0; i < 100; ++i) {
                int vi_tri_1 = random_vi_tri(may_quay);
                int vi_tri_2 = random_vi_tri(may_quay);
                swap(mang[vi_tri_1], mang[vi_tri_2]);
            }
            
            for (int i = 0; i < n; ++i) {
                cout << mang[i] << "\n";
            }
        }
        else if (so_thu_tu == 5) {
            // so max nhat va min nhat
            
            long long so_max = 2147483647LL;
            long long so_min = -2147483648LL;
            
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) {
                    cout << so_max << "\n";
                } else {
                    cout << so_min << "\n";
                }
            }
        }
    }
    else if (loai_bai == "strlexi" || loai_bai == "strlenlexi") {
        int n = 0;
        if (loai_bai == "strlenlexi") {
            n = 10000;
        } else {
            n = 100000;
        }
        
        cout << n << "\n";
        uniform_int_distribution<int> random_do_dai(10, 100);

        if (so_thu_tu == 1) {
            // string random
            for (int i = 0; i < n; ++i) {
                int do_dai = random_do_dai(may_quay);
                cout << sinh_chuoi(do_dai, may_quay) << "\n";
            }
        }
        else if (so_thu_tu == 2) {
            // chi khac ki tu cuoi
            int do_dai_co_dinh = 100;
            string chuoi_goc = sinh_chuoi(do_dai_co_dinh - 1, may_quay);
            
            for (int i = 0; i < n; ++i) {
                uniform_int_distribution<int> random_z(0, 25);
                char ki_tu_cuoi = 'a' + random_z(may_quay);
                cout << chuoi_goc << ki_tu_cuoi << "\n";
            }
        }
        else if (so_thu_tu == 3) {
            // sort giam
            vector<string> mang_chuoi(n);
            for (int i = 0; i < n; ++i) {
                int do_dai = random_do_dai(may_quay);
                mang_chuoi[i] = sinh_chuoi(do_dai, may_quay);
            }
            sort(mang_chuoi.begin(), mang_chuoi.end(), greater<string>());
            
            for (int i = 0; i < n; ++i) {
                cout << mang_chuoi[i] << "\n";
            }
        }
        else if (so_thu_tu == 4) {
            // trung lap
            
            int do_dai_max = 100;
            string chuoi_thu_nhat = sinh_chuoi(do_dai_max, may_quay);
            string chuoi_thu_hai = sinh_chuoi(do_dai_max, may_quay);
            
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) {
                    cout << chuoi_thu_nhat << "\n";
                } else {
                    cout << chuoi_thu_hai << "\n";
                }
            }
        }
        else if (so_thu_tu == 5) {
            // gan giong nhau
            
            int do_dai_ngan = 10;
            int do_dai_duoi = 90;
            
            string tien_to = sinh_chuoi(do_dai_ngan, may_quay); 
            string phan_duoi = sinh_chuoi(do_dai_duoi, may_quay); 
            
            string chuoi_ngan = tien_to;
            string chuoi_dai = tien_to + phan_duoi;
            
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) {
                    cout << chuoi_ngan << "\n";
                } else {
                    cout << chuoi_dai << "\n";
                }
            }
        }
    }



    return 0;
}