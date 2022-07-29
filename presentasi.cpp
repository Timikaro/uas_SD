#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <fstream>

#define n 10

using namespace std;

    ofstream db_produk;
    string antrian[10] = {"Pertama", "Kedua", "Ketiga", "Keempat", "Kelima", "Keenam", "Ketujuh", "Kedelapan", "Kesembilan", "Terakir"};

struct DataPaket{
    string nama_pengirim,
           nama_penerima,
           alamat_pengirim,
           alamat_penerima,
           kode_tujuan,
           desk;
    float beban;
    float biaya;
}Pkt[n];

struct PaketSorting{
    string nama_pengirim,
           nama_penerima,
           alamat_pengirim,
           alamat_penerima,
           kode_tujuan,
           desk;
    float beban;
    float biaya;
}PktSrt[n];

struct queue{
    int awal, akhir,pilih;
}Queue;

void hapus_data();
void menu();
void tambah_data();
void tampil();

bool isFull(){
    if(Queue.akhir == n - 1){
        return true;
    } else {
        return false;
    }
}

bool isEmpty(){
    if(Queue.akhir == -1){
        return true;
    }else {
        return false;
    }
}

void info_pengiriman(){
    system("cls");
     cout << "[===================================]\n";
    cout << "|       PROGRAM PENGIRIMAN PAKET    |\n";
    cout << "|                area               |\n";
    cout << "|             Jawa Tengah           |\n";
    cout << "[===================================]\n";
    cout << "Rincian tarif harga tiap kota dan estimasi waktu\n";
    cout << "Pengiriman dari kota solo\n\n";
    cout << "No\t Kode\t   Kota\t\t\t tarif/kg\t estimasi"<<endl;
    cout << "[==================================================================]"<<endl;
    cout << "1. ||\t A\t || Klaten\t      || Rp.10.000\t || 1-2 hari"<<endl;
    cout << "2. ||\t B\t || Batang\t      || Rp.14.000\t || 3-5 hari"<<endl;
    cout << "3. ||\t C\t || Semarang\t      || Rp.13.000\t || 2-3 hari"<<endl;
    cout << "4. ||\t D\t || Purbalingga\t      || Rp.15.000\t || 3-6 hari"<<endl;
    cout << "5. ||\t E\t || Purworejo\t      || Rp.16.000\t || 4-6 hari"<<endl;
    cout << "6. ||\t F\t || Salatiga\t      || Rp.12.000\t || 1-2 hari"<<endl;
    cout << "[==================================================================]";

    cout<<"\nklik Enter untuk kembali ke menu...";
    getch();
	menu();
}

void hitung_biaya(){

    if ((Pkt[Queue.akhir].kode_tujuan == "A")||(Pkt[Queue.akhir].kode_tujuan == "a"))
    {
        Pkt[Queue.akhir].biaya = 10000 * Pkt[Queue.akhir].beban;

    }else if ((Pkt[Queue.akhir].kode_tujuan == "B")||(Pkt[Queue.akhir].kode_tujuan == "b"))
    {
        Pkt[Queue.akhir].biaya = 14000 * Pkt[Queue.akhir].beban;

    }else if ((Pkt[Queue.akhir].kode_tujuan == "C")||(Pkt[Queue.akhir].kode_tujuan == "c"))
    {
        Pkt[Queue.akhir].biaya = 13000 * Pkt[Queue.akhir].beban;

    }else if ((Pkt[Queue.akhir].kode_tujuan == "D")||(Pkt[Queue.akhir].kode_tujuan == "d"))
    {
        Pkt[Queue.akhir].biaya = 15000 * Pkt[Queue.akhir].beban;

    }else if ((Pkt[Queue.akhir].kode_tujuan == "E")||(Pkt[Queue.akhir].kode_tujuan == "e"))
    {
        Pkt[Queue.akhir].biaya = 16000 * Pkt[Queue.akhir].beban;

    }else if ((Pkt[Queue.akhir].kode_tujuan == "F")||(Pkt[Queue.akhir].kode_tujuan == "f"))
    {
        Pkt[Queue.akhir].biaya = 12000 * Pkt[Queue.akhir].beban;

    }
    
}

void Dscbubble(){
    int i, x, temp, tmp_biaya;
    string tmp_nama, tmp_desk, tmp_kode;
    for ( i = 0; i < Queue.akhir; i++)
    {
        for ( x = 0; x < Queue.akhir; x++)
        {
            if (PktSrt[x].beban < PktSrt[x+1].beban)
            {
                temp = PktSrt[x].beban;
                tmp_nama = PktSrt[x].nama_pengirim;
                tmp_desk = PktSrt[x].desk;
                tmp_kode = PktSrt[x].kode_tujuan;
                tmp_biaya = PktSrt[x].biaya;
                PktSrt[x].beban = PktSrt[x+1].beban;
                PktSrt[x].nama_pengirim = PktSrt[x+1].nama_pengirim;
                PktSrt[x].desk = PktSrt[x+1].desk;
                PktSrt[x].kode_tujuan = PktSrt[x+1].kode_tujuan;
                PktSrt[x].biaya = PktSrt[x+1].biaya;
                PktSrt[x+1].beban = temp;
                PktSrt[x+1].nama_pengirim = tmp_nama;
                PktSrt[x+1].desk = tmp_desk;
                PktSrt[x+1].kode_tujuan = tmp_kode;
                PktSrt[x+1].biaya = tmp_biaya;

            } 
        }  
    }
}

void Ascbubble(){
    int i, x, temp, tmp_biaya;
    string tmp_nama, tmp_desk, tmp_kode;
    for ( i = 0; i < Queue.akhir; i++)
    {
        for ( x = 0; x < Queue.akhir; x++)
        {
            if (PktSrt[x].beban > PktSrt[x+1].beban)
            {
                temp = PktSrt[x].beban;
                tmp_nama = PktSrt[x].nama_pengirim;
                tmp_desk = PktSrt[x].desk;
                tmp_kode = PktSrt[x].kode_tujuan;
                tmp_biaya = PktSrt[x].biaya;
                PktSrt[x].beban = PktSrt[x+1].beban;
                PktSrt[x].nama_pengirim = PktSrt[x+1].nama_pengirim;
                PktSrt[x].desk = PktSrt[x+1].desk;
                PktSrt[x].kode_tujuan = PktSrt[x+1].kode_tujuan;
                PktSrt[x].biaya = PktSrt[x+1].biaya;
                PktSrt[x+1].beban = temp;
                PktSrt[x+1].nama_pengirim = tmp_nama;
                PktSrt[x+1].desk = tmp_desk;
                PktSrt[x+1].kode_tujuan = tmp_kode;
                PktSrt[x+1].biaya = tmp_biaya;

            } 
        }  
    }
}

void tambah_data(){
    if(!isFull()){
         system("cls");
        cout << endl;
        cout << "=========Tambah Paket========="<<endl;
        cout << "Input Data Sebagai berikut...\n";
        string namapengirim,
               alamatpengirim,
               namapenerima,
               alamatpenerima,
               deks,
               tujuan;
        int beban;
        time_t now = time(0);
        string waktu = ctime(&now);
        
        cout << "*info pengirim"<<endl;
        cout << "Nama Pengirim\t: ";
        cin.ignore();
        getline(cin,namapengirim);
        Pkt[Queue.akhir].nama_pengirim = namapengirim;
        cout << "Alamat Pengirim: ";
        getline(cin, alamatpengirim);
        Pkt[Queue.akhir].alamat_pengirim = alamatpengirim;
        cout << "*info penerima"<<endl;
        cout << "Nama Penerima\t: ";
        getline(cin,namapenerima); 
        Pkt[Queue.akhir].nama_penerima = namapenerima;
        cout << "Alamat Penerima\t: ";
        getline(cin,alamatpenerima); 
        Pkt[Queue.akhir].alamat_penerima = alamatpenerima;
        cout<<"Kode Tujuan\t: ";
        getline(cin,tujuan);
        Pkt[Queue.akhir].kode_tujuan=tujuan;
        cout << "Beban berat(Kg)\t: ";
        cin >> beban; Pkt[Queue.akhir].beban = beban;
        cout << "Deskripsi Paket\t: ";
        cin.ignore();
        getline(cin,deks); Pkt[Queue.akhir].desk = deks;
        cout << "\nPaket berhasil ditambahkan.!\n";

        hitung_biaya();

        db_produk.open("File.txt", ios::app);
        db_produk <<"Di Tambah " << "Paket dari =  " << Pkt[Queue.akhir].nama_pengirim << " pada => " << waktu;
        db_produk.close(); 

        ++Queue.akhir;
        cout << endl;
        menu();
    }else {
        cout << "Data penuh";
        cout<<"\nklik Enter untuk kembali ke menu";
        getch();
    	menu();
    }
}

void kirim_paket(){
    if(!isEmpty()){
        system("cls");
         time_t now = time(0);
         string waktu = ctime(&now);
         string namadihapus;

        for(int i = Queue.awal; i < Queue.akhir; i++){
            if (i == 0)
            {
                namadihapus = Pkt[i].nama_pengirim;
            }
            Pkt[i].nama_pengirim = Pkt[i+1].nama_pengirim;
            Pkt[i].nama_penerima = Pkt[i+1].nama_penerima;
            Pkt[i].alamat_penerima = Pkt[i+1].alamat_penerima;
            Pkt[i].alamat_pengirim = Pkt[i+1].alamat_pengirim;
            Pkt[i].beban = Pkt[i+1].beban;
            Pkt[i].biaya = Pkt[i+1].biaya;
            Pkt[i].desk = Pkt[i+1].desk;
            Pkt[i].kode_tujuan = Pkt[i+1].kode_tujuan;

        }Queue.akhir--;
        cout << "Paket berhasil dikirim" << endl;
        db_produk.open("File.txt", ios::app);
        db_produk <<"Terkirim " << " Paket dari = " << namadihapus << " pada =>" << waktu;
        db_produk.close(); 
        cout << endl;

    }else{
        cout << "data kosong" << endl;
    }
    cout<<"\nklik Enter untuk kembali ke menu";
    getch();
    	menu();
}

void kirim_semua(){
    
    system("cls");
    cout << "[===================================]\n";
    cout << "|       PROGRAM ANTRIAN PAKET       |\n";
    cout << "[===================================]\n";
    time_t now = time(0);
    string waktu = ctime(&now);
    Queue.awal = -1;
    Queue.akhir = -1;

    db_produk.open("File.txt", ios::app);
    db_produk << "Terkirim Semua paket = pada =>" << waktu ;
    db_produk.close(); 
    
    cout << "Paket telah terkirim semua" << endl << endl;
	cout<<"\nklik Enter untuk kembali ke menu";
    getch();
    menu();
    
}

void tampil(){
    if(!isEmpty()){
        system("cls");
        cout << "[===================================]\n";
        cout << "|       PROGRAM ANTRIAN PAKET       |\n";
        cout << "[===================================]\n";
        cout << "==========Data Paket==========="<<endl<<endl;
        for(int i = 0; i < Queue.akhir; i++){
        	cout<<"=========================================="<<endl;
        	cout << "| Antrian Paket | "<<antrian[i]<<endl;
            cout<<"=========================================="<<endl;
        	cout << "Nama Pengirim\t: " << Pkt[i].nama_pengirim << endl;
        	cout << "Alamat Pengirim\t: " << Pkt[i].alamat_pengirim << endl;
        	cout << "Nama Penerima\t: " << Pkt[i].nama_penerima << endl;
        	cout << "Alamat Penerima\t: " << Pkt[i].alamat_penerima << endl;
            cout << "Kode Tujuan \t: " << Pkt[i].kode_tujuan << endl;
      		cout << "Beban berat\t: " << Pkt[i].beban<<" Kg" << endl;
      	    cout << "Deskripsi\t: "<< Pkt[i].desk << endl;
            cout << "Biaya\t\t: Rp."<< Pkt[i].biaya <<endl;
            cout<<"==========================================="<<endl;
     	}
     	if (Queue.akhir==0){
     		cout << "      KOSONG!!!\n\n";
        }
    }else {
        cout << "data kosong!!!";
        cout << endl << endl;
    }
    cout<<"\nklik Enter untuk kembali ke menu";
    getch();
	menu();
}

void tampilipksort(){
    if (!isEmpty()){

        int pilih;

        for (int i = 0; i < Queue.akhir; i++)
        {
            PktSrt[i].beban = Pkt[i].beban;
            PktSrt[i].nama_penerima = Pkt[i].nama_penerima;
            PktSrt[i].nama_pengirim = Pkt[i].nama_pengirim;
            PktSrt[i].biaya = Pkt[i].biaya;
            PktSrt[i].kode_tujuan = Pkt[i].kode_tujuan;
        }
        cout << "[===================================]\n";
        cout << "|       PROGRAM ANTRIAN PAKET       |\n";
        cout << "[===================================]\n";
        cout << "sorting berat beban:"<<endl;
        cout << "1. Besar ke kecil"<<endl;
        cout << "2. Kecil ke Besar"<<endl;
        cout << "Masukan pilihan : ";
        cin >> pilih;
        if (pilih == 1)
        {
        Dscbubble();
        }else if (pilih == 2)
        {
        Ascbubble();
        }else{
            cout << "pilihan di luar jangkauan!!!";
            menu();
        }   
        cout << "=========Hasil Sorting=========="<<endl<<endl;
       if(Queue.akhir == 0){
        		cout <<"DATA KOSONG.!\n\n";
			}
        for(int i = 0; i < Queue.akhir; i++){
        	cout<<"============================"<<endl;
      		cout << "Beban berat\t: " << PktSrt[i].beban<<" Kg" << endl;
        	cout << "Nama Pengirim\t: " << PktSrt[i].nama_pengirim << endl;
        	cout << "Nama penerima\t: " << PktSrt[i].nama_penerima << endl;
            cout << "Kode Tujuan \t: " << PktSrt[i].kode_tujuan << endl;
      	    cout << "Biaya\t: "<< PktSrt[i].biaya <<endl;
        }
    } else{
        cout << "Paket kosong !!!"<<endl<<endl;
    }
    cout<<"\nKlik (ENTER) untuk kembali ke Menu";
    getch();
	menu();
}

void cari(){
    lagi:
    system("cls");
    string cari;
    int ketemu, pcc;
    cout << "[===================================]\n";
    cout << "|       PROGRAM ANTRIAN PAKET       |\n";
    cout << "[===================================]\n";
    cout << "Nama Pengirim yang dicari (besar/kecil perlu huruf diperhatikan!)\n ";
    cout << "Masukan Pencarian : ";
    cin >> cari;

    ketemu = 0;
    for (int i = 0; i < Queue.akhir; i++)
    {
        if ((Pkt[i].nama_pengirim == cari)||(Pkt[i].nama_penerima == cari))
        {
        ketemu = 1 ;pcc = i;
        i = 5;
        }  
    }
    if (ketemu == 0)
    {
        cout << "Paket tidak ada!!!!"<<endl;
        cout << "Silahkan masukan data pada menu pertama tambah paket"<< endl<<endl;
    }else{
      	cout << "\n";
       	cout << "======Paket Ditemukan======="<<endl<<endl;
      	cout<<"============================"<<endl;
      	cout << "Antrian Paket "<<antrian[pcc]<<endl;
        cout << "Kode Tujuan \t: " << Pkt[pcc].kode_tujuan << endl;
   		cout << "Beban berat\t: " << Pkt[pcc].beban<<"Kg" << endl;
   	    cout << "Deskripsi\t: "<< Pkt[pcc].desk<< endl;
   	    cout<<"============================"<<endl<<endl;
        cout<<"+================================================+"<<endl;
        cout <<"|Paket yang di cari berada pada antrian " << antrian[pcc] <<endl;
        cout<<"+================================================+"<<endl<<endl; 
    }
    char ulang;
    cout<<"Apakah Anda ingin Mencari lagi? (Y/N) : ";
    cin>>ulang;
    if(ulang=='Y'||ulang=='y'){
        goto lagi;
    }
    cout<<"\nKlik (ENTER) untuk kembali ke Menu";
    getch();
    menu();
}


void menu(){
    system("cls");
    int pilih;
    cout << "[===================================]\n";
    cout << "|       PROGRAM PENGIRIMAN PAKET    |\n";
    cout << "|                Area               |\n";
    cout << "|             Jawa Tengah           |\n";
    cout << "[===================================]\n";
    cout << "[===============Menu===============]\n";
    cout << "|1. Informasi Pengiriman           |\n";
    cout << "|2. Input Paket                    |\n";
    cout << "|3. Tampilkan Antrian Paket        |\n";
    cout << "|4. Kirim Paket Pertama            |\n";
    cout << "|5. Cari Data                      |\n";
    cout << "|6. Sort Paket Berdasarkan Berat   |\n";
    cout << "|7. Kirim Semua Paket              |\n";
    cout << "|8. keluar                         |\n";
    cout << "[==================================]\n";
    cout << "Masukkan pilihan anda: ";
    cin >> pilih;
    cout << endl;
    if(pilih == 1){
        info_pengiriman();
    }else if(pilih == 2){
        tambah_data();
    }else if(pilih == 3){
        tampil();
    }else if(pilih == 4){
        kirim_paket();
    }else if(pilih == 5){
        cari();
    }else if(pilih == 6){
        tampilipksort();
    }else if(pilih == 7){
        kirim_semua();
    }else if(pilih == 8){
        exit;
    }else { 
        cout<<"\nAnda Telah Keluar Dari Program";
        cout<<"Terima kasih :)";
    }
}

int main(){
	menu();
    return 0;
}

// kelompok 2 strukdat
