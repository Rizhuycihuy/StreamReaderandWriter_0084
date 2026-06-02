#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;


class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "Televisi";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string(
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!"
            );
        }
    }
};

void bacaBarang() {
    ifstream file("gudang.txt");

    cout << "\n===== DAFTAR BARANG GUDANG =====\n";

    if (!file) {
        cout << "File gudang belum tersedia.\n";
        return;
    }

    string barang;
    int no = 1;

    while (getline(file, barang)) {
        cout << no++ << ". " << barang << endl;
    }

    if (no == 1) {
        cout << "Gudang kosong.\n";
    }

    file.close();
}

void tambahBarang() {
    ofstream file("gudang.txt", ios::app);

    string barang;

    cin.ignore();
    cout << "Masukkan nama barang: ";
    getline(cin, barang);

    file << barang << endl;

    file.close();

    cout << "Barang berhasil ditambahkan.\n";
}

void updateBarang() {
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong.\n";
        return;
    }

    bacaBarang();

    int nomor;
    cout << "\nNomor barang yang akan diubah: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    cin.ignore();

    cout << "Nama barang baru: ";
    getline(cin, barang);

    data[nomor - 1] = barang;

    ofstream tulis("gudang.txt");

    for (const string& item : data) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Data berhasil diperbarui.\n";
}

void hapusBarang() {
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong.\n";
        return;
    }

    bacaBarang();

    int nomor;
    cout << "\nNomor barang yang akan dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    data.erase(data.begin() + (nomor - 1));

    ofstream tulis("gudang.txt");

    for (const string& item : data) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Barang berhasil dihapus.\n";
}

void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n===== SIMULASI ETALASE =====\n";

    try {
        cout << "\nSkenario 1 (Rak 1)\n";
        cout << "Barang ditemukan: " << toko.ambilProduk(1) << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }

    try {
        cout << "\nSkenario 2 (Rak 5)\n";
        cout << "Barang ditemukan: " << toko.ambilProduk(5) << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n================================";
        cout << "\n  TOKO ELEKTRONIK GIBRAN JAYA";
        cout << "\n================================\n";

        bacaBarang();

        cout << "\n===== MENU =====\n";
        cout << "1. Tambah Barang (Create)\n";
        cout << "2. Tampilkan Barang (Read)\n";
        cout << "3. Update Barang (Update)\n";
        cout << "4. Hapus Barang (Delete)\n";
        cout << "5. Simulasi Etalase\n";
        cout << "0. Keluar\n";

        cout << "\nPilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahBarang();
            break;

        case 2:
            bacaBarang();
            break;

        case 3:
            updateBarang();
            break;

        case 4:
            hapusBarang();
            break;

        case 5:
            simulasiEtalase();
            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}