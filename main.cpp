/*
Kelas : Algoritma dan Struktur Data TKOM - B 
Deskripsi : Tugas 1
Anggota Kelompok : 
                    - Nisrina Fairuz Hafizhah Al Amin   (205150300111021)
                    - Reyhan Naufal Hayyan              (185150307111017)
                    - Selina Kusmiawati                 (185150301111005)
Origin : https://github.com/xjoliez/Queue

**NOTE** : Program Harus dijalankan dengan C++ Versi >= 11 karena menggunakan fungsi stoi.
*/

#include <bits/stdc++.h>

using namespace std;

struct Node{
	string name;
	string status; 
	int age;
	int bp; // bp = Blood Pressure
	Node *next, *prev;
	
};

struct QueueLinkedList{
    int size = 0;
    int totalPasienAntre = 0;
    int totalPasienTunggu = 0;
    int pasienLansia = 0;
    int pasienBukanLansia = 0;
    int totalPasien = pasienLansia + pasienBukanLansia;

	Node *front, *front1, *rear, *rear1, *head, *head1;

	void init(){
		front = front1 = rear = rear1 = head = head1 = NULL;
	}

    void destroy(){
        make_empty();
    }

	bool is_empty_RuangAntre(){
		return (front == NULL && rear == NULL);
	}
	
	bool is_empty_RuangTunggu(){
		return (front1 == NULL && rear1 == NULL);
	}

    bool is_full_RuangAntre(){
        return totalPasienAntre >= size;
    }

    bool is_full_lansia_RuangAntre(){
        return pasienLansia >= size;
    }

	void make_empty(){
		Node *p = front;
        for(int x; totalPasien != 0; x++){
            delete p;
            p = p->prev;
            totalPasien--;
        }
        front = rear = NULL;
	}

    void set_size_RuangAntre(int x){
		if(x >= 1 && x <= 10000){
            size = x;
        }
        else{
            // Size Terlalu Besar atau Terlalu Kecil
            exit(0);
        }
	}
	
	int get_size_RuangAntre(){
		return size;
	}

    void pasien_Increment(string status, string perintah){
        if(status == "LANSIA"){
            pasienLansia++;
            if(perintah == "ruangAntre"){
                totalPasienAntre++;
            }
            else{
                totalPasienTunggu++;
            }
        }
        else{
            pasienBukanLansia++;
            if(perintah == "ruangAntre"){
                totalPasienAntre++;
            }
            else{
                totalPasienTunggu++;
            }
        }
        totalPasien = pasienLansia + pasienBukanLansia;
    }

    void pasien_Decrement(string status, string perintah){
        if(status == "LANSIA"){
            pasienLansia--;
            if(perintah == "ruangAntre"){
                totalPasienAntre--;
            }
            else{
                totalPasienTunggu--;
            }
        }
        else{
            pasienBukanLansia--;
            if(perintah == "ruangAntre"){
                totalPasienAntre--;
            }
            else{
                totalPasienTunggu--;
            }
        }
        totalPasien = pasienLansia + pasienBukanLansia;
    }

    int get_totalPasienAntre(){
        return totalPasienAntre;
    }

    int get_totalPasienTunggu(){
        return totalPasienTunggu;
    }

    int get_totalPasien(){
        return totalPasien;
    }

    int get_PasienLansia(){
        return pasienLansia;
    }

    int get_PasienBukanLansia(){
        return pasienBukanLansia;
    }
    
    bool verify_totalPasien(){
        return pasienLansia + pasienBukanLansia == totalPasienAntre + totalPasienTunggu;
    }

    bool is_exist_pasien_RuangAntre(string nama){
        Node *helper2 = front;
        if(is_empty_RuangAntre()){
            cout << "Ruang Antre Masih Kosong" << endl;
        }
        else{
            while(helper2 != NULL){
                if(helper2->name == nama){
                    return true;
                }
                helper2 = helper2->prev;
            }
        }
        return false; 
    } 
    
	void enqueue_RuangAntre(string nama, int umur, int tensi, string status, int priority){
        Node *tmp = new Node;
		Node *helper = rear;
        Node *helper2 = front;
		tmp->name = nama;
		tmp->age = umur;
		tmp->bp = tensi;
		tmp->status = status;
		tmp->next = NULL;
		tmp->prev = NULL;
		if(is_empty_RuangAntre()){
			front = tmp;
			rear = tmp;
            pasien_Increment(status,"ruangAntre");
		}
        else if(is_full_RuangAntre()){
            if(is_full_lansia_RuangAntre()){
                if(priority == 1){
                    pasien_Increment(status,"ruangTunggu");
                    enqueue_RuangTunggu(nama, umur, tensi, status, 1);
                }
                else{
                    pasien_Increment(status,"ruangTunggu");
                    enqueue_RuangTunggu(nama, umur, tensi, status, 0); 
                }
            }
            else{
                if(priority == 1){
                    if(helper2->status == "BUKAN_LANSIA"){
                        tmp->next = front;
                        tmp->prev = helper2;
                        front->prev = tmp;
                        front = tmp;
                        helper2->next = tmp;
                        pasien_Increment(status,"ruangTunggu");
                        enqueue_RuangTunggu(helper->name, helper->age, helper->bp, helper->status, 1); 
                        cout << " TUNGGU " << helper->name << endl;
                        // Ganti Belakang
                        helper->next->prev = NULL;
                        rear = helper->next;
                        rear->prev == NULL;
                        delete helper;
                    }
                    else{
                        while(helper2 != NULL){
                            if(helper2->status == "BUKAN_LANSIA" && helper2 != rear){
                                tmp->next = helper2->next;
                                helper2->next->prev = tmp;
                                helper2->next = tmp;
                                tmp->prev = helper2;
                                pasien_Increment(status,"ruangTunggu");
                                enqueue_RuangTunggu(helper->name, helper->age, helper->bp, helper->status, 1); 
                                cout << " TUNGGU " << helper->name << endl;
                                // Ganti Belakang
                                helper->next->prev = NULL;
                                rear = helper->next;
                                delete helper;
                                break;
                            }
                            else if(helper2->status == "BUKAN_LANSIA" && helper2 == rear){
                                tmp->next = helper2->next;
                                helper2->next->prev = tmp;
                                helper2->next = tmp;
                                pasien_Increment(status,"ruangTunggu");
                                enqueue_RuangTunggu(helper->name, helper->age, helper->bp, helper->status, 1);
                                cout << " TUNGGU " << helper->name << endl;
                                rear = tmp;
                                rear->prev = NULL;
                                delete helper;
                                break;
                            }
                            helper2 = helper2->prev;
                        }
                    }
                }
                else{
                    pasien_Increment(status,"ruangTunggu");
                    enqueue_RuangTunggu(nama, umur, tensi, status, 0);
                }
            }
        }
        else if(priority == 1){
            if(helper2->status == "BUKAN_LANSIA"){
                helper2->next = tmp;
                tmp->prev = helper2;
                front = tmp;
                pasien_Increment(status,"ruangAntre");
            }
            else{
                while(helper2 != NULL){
                    if(helper2->status == "BUKAN_LANSIA"){
                        tmp->next = helper2->next;
                        helper2->next->prev = tmp;
                        helper2->next = tmp;
                        tmp->prev = helper2;
                        pasien_Increment(status,"ruangAntre");
                        break;
                    }
                    else if(helper2->prev == NULL){
                        tmp->next = helper2;
                        helper2->prev = tmp;
                        rear = tmp;
                        pasien_Increment(status,"ruangAntre");
                        break;
                    }
                    helper2 = helper2->prev;
                }
            }
        }
        else{
            tmp->next = rear;
            rear->prev = tmp;
            rear = tmp;
            pasien_Increment(status,"ruangAntre");
        }
	}        

	void enqueue_RuangTunggu(string nama, int umur, int tensi, string status, int priority){
        Node *tmp = new Node;
		Node *helper = front1;
		tmp->name = nama;
		tmp->age = umur;
		tmp->bp = tensi;
		tmp->status = status;
		tmp->next = NULL;
		tmp->prev = NULL;
        if(is_empty_RuangTunggu()){
            front1 = tmp;
            rear1 = tmp;
        }
        else if(priority == 1){
            if(helper->status == "BUKAN_LANSIA"){
                helper->next = tmp;
                tmp->prev = helper;
                front1 = tmp;
            }
            else{
                while(helper != NULL){
                    if(helper->status == "BUKAN_LANSIA"){
                        tmp->next = helper->next;
                        helper->next->prev = tmp;
                        helper->next = tmp;
                        tmp->prev = helper;
                        break;
                    }
                    else if(helper->prev == NULL){
                        tmp->next = helper;
                        helper->prev = tmp;
                        rear1 = tmp;
                        break;
                    }
                    helper = helper->prev;
                }
            }
        }
        else{
            tmp->next = rear1;
            rear1->prev = tmp;
            rear1 = tmp;
        }
	}

    void dequeue(int N){
        if(N <= totalPasien){
            // Saat N tidak melebihi totalPasien (Ruang Antre + Ruang Tunggu)
            cout << "SELESAI_VAKSIN ";   
            while(N != 0){
                Node *tmp = front;
                Node *helper = front1;
                cout << tmp->name << " ";
                pasien_Decrement(tmp->status,"ruangAntre");
                if(rear == front){
                    delete tmp;
                    front = rear = NULL;
                }
                else{
                    front->prev->next = NULL;
                    front = tmp->prev;
                    delete tmp;
                }
                dequeueManager();
                N--;
            }
            cout << endl;
        }
        else{
            // N terlalu banyak melebihi totalPasien
            exit(0);
        }    
    }

    void dequeue_nama(string nama){
        int toogle = 0;
        Node *tmp = front;
        Node *helper = front1;
        Node *next = NULL;
        Node *before;
        while(tmp != NULL || toogle == 0){
            if(tmp->name == nama){
                pasien_Decrement(tmp->status,"ruangAntre");
                if(next == NULL){
					if(tmp->prev == NULL){
                        // Hanya 1 Pasien Pada Antre
                        front = rear = NULL;
                    }
                    else{
                        // Pasien Pada Antre > 1
                        tmp->prev->next = NULL;
                        front = tmp->prev;
                    }
                    delete tmp;
                    toogle = 1;
                    break;
                }
				else if(tmp == rear){
					tmp->next->prev = NULL;
					rear = tmp->next;
					delete tmp;
                    toogle = 1;
                    break;
				}
                else{
                    tmp->next->prev = tmp->prev;
                    tmp->prev->next = tmp->next;
                    delete tmp;
                    toogle = 1;
                    break;
                }
            }
            else if(tmp->prev == NULL){
                // Tidak ada nama pasien yang dimaksud pada Ruang Antre 
                break;
            }
            next = tmp;
            tmp = tmp->prev;
            before = tmp->prev;
        }
        if(toogle == 1){
            // Saat Penghapusan Berhasil
            dequeueManager();
        }
    }

    void dequeueManager(){
        // Fungsi untuk memastikan setiap Dequeue pada Ruang Antre akan memindahkan 1 orang (front) dari Ruang Tunggu
        // Agar program berjalan secara dinamis
        Node *helper = front1;
        if(is_empty_RuangTunggu()){
            // Saat Ruang Tunggu kosong, tidak perlu ada melakukan apa apa
        }
        else if(totalPasienAntre == size){
            // Saat ukuran diruang Antre sudah Penuh, tidak perlu Enqueue kembali
        }
        else{
            // Saat ada Orang di Ruang Tunggu
            if(totalPasienTunggu == 1){
                // Jika Hanya 1 Orang, Melakukan remove_first, dan Enqueue ke Antre
                if(helper->status == "LANSIA"){
                    enqueue_RuangAntre(helper->name, helper->age, helper->bp, helper->status, 1);
                    pasien_Decrement(helper->status,"ruangTunggu");
                }
                else{
                    enqueue_RuangAntre(helper->name, helper->age, helper->bp, helper->status, 0);
                    pasien_Decrement(helper->status,"ruangTunggu");
                }
                front1 = rear1 = NULL;
                delete helper;
            }
            else{
                // Jika Lebih Dari 1 Orang, Melakukan remove_first, Enqueue ke Antre dan Menyambung Node Belakangnya
                if(helper->status == "LANSIA"){
                    enqueue_RuangAntre(helper->name, helper->age, helper->bp, helper->status, 1);
                    pasien_Decrement(helper->status,"ruangTunggu");
                }
                else{
                    enqueue_RuangAntre(helper->name, helper->age, helper->bp, helper->status, 0);
                    pasien_Decrement(helper->status,"ruangTunggu");
                }
                helper->prev->next = NULL;
                front1 = helper->prev;
                delete helper;
            }
        }
    }

    void skip(string x){
        Node *p = front;
        while(p != NULL){
            if(p->name == x){
                if(p->status=="LANSIA"){
                    enqueue_RuangTunggu(p->name, p->age, p->bp, p->status, 1);
                    break;
                } else {
                    enqueue_RuangTunggu(p->name, p->age, p->bp, p->status, 0);
                    break;
                }
            }
            p = p->prev;
        }
        pasien_Increment(p->status,"ruangTunggu");
        dequeue_nama(x);
    }

    void gantiUkuran(int N){
        string namaRef[1000];
        int ageRef[1000];
        int bpRef[1000];
        string statusRef[1000];
        int oldSize = size;
        int selisihSize = 0;
        int selisihSize2 = 0;
        int ab = 0;
        int loop;
        if(oldSize == N){
            // Ukuran Sama Tidak Ada Yang Berubah
        }
        else if(N > oldSize){
            set_size_RuangAntre(N);
            selisihSize = N - oldSize;
            for(int x = 0; x != selisihSize; x++){
                dequeueManager();
            }
            cout << "SUKSES UBAH " << oldSize << " " << N << endl;
        }
        else{
            set_size_RuangAntre(N);
            Node *tmp = front;
            loop = N;
            selisihSize = (N - oldSize) * -1;
            selisihSize2 = selisihSize;
            // Loop Mencari Node Yang Ingin Dipindahkan
            while(loop != 0){
                tmp = tmp->prev;
                loop--;
            }
            // Loop Menyimpan Sementara Data Yang Ingin Dipindahkan ke Ruang Tunggu di Array
            while(selisihSize != 0){
                // Jika tmp Bernilai NULL, Maka Loop Berhenti Untuk Mencegah Bug Saat List Tidak Full Tapi Dikecilkan
                // Contoh A <- B <- C <- D <- E (Size = 7) -> Diubah Menjadi Size = 5
                // Sehingga Program Hanya Memindahkan D dan E saja Tanpa Harus Loop Hingga Akhir
                if(tmp == NULL){
                    break;
                }
                namaRef[ab] = tmp->name;
                ageRef[ab] = tmp->age;
                bpRef[ab] = tmp->bp;
                statusRef[ab] = tmp->status;
                tmp = tmp->prev;
                selisihSize--;
                ab++;
            }
            // Loop Untuk Dequeue_Nama Berdasarkan Node Yang Ingin Dipindahkan
            for(int yz = 0; yz != ab; yz++){
                dequeue_nama(namaRef[yz]);
            }
            // Loop Untuk Enqueue Kembali Ke Ruang Tunggu Berdasarkan Node Yang Ingin Dipindahkan
            for(int xy = 0; xy != ab; xy++){
                if(statusRef[xy] == "LANSIA"){
                    pasien_Increment(statusRef[xy],"ruangTunggu");
                    enqueue_RuangTunggu(namaRef[xy], ageRef[xy], bpRef[xy], statusRef[xy], 1);
                }
                else{
                    pasien_Increment(statusRef[xy],"ruangTunggu"); 
                    enqueue_RuangTunggu(namaRef[xy], ageRef[xy], bpRef[xy], statusRef[xy], 0);                  
                }
            }
            cout << "SUKSES UBAH " << oldSize << " " << N << endl;
        }
    }

	void print_Antre(string nama, string status){
		if(status == "LANSIA"){
            if(is_full_lansia_RuangAntre()){
                cout << "TUNGGU " << nama << " " << status;
                cout << endl;
            }
            else{
                cout << "ANTRE " << nama << " " << status;
            }
        }
        else{
            if(is_full_RuangAntre()){
                cout << "TUNGGU " << nama << " " << status;
                cout << endl;
            }
            else{
                cout << "ANTRE " << nama << " " << status;
                cout << endl;
            }
        }
	}

    void print_Tolak(string nama, string status){
        cout << "TOLAK " << nama << " " << status << " TENSI_TIDAKBOLEH_DIVAKSIN" << endl;
    }

	void print_DaftarAntre(){
		Node *tmp = front;
		if(is_empty_RuangAntre()){
            cout << "DAFTAR_ANTRE -";
        }
        else{
            cout << "DAFTAR_ANTRE ";
            while(tmp != NULL){
                cout << tmp->name << "^" << tmp->status << "^" << tmp->bp << " ";
                tmp=tmp->prev;
            }
        }
		cout<<endl;
 	}

 	void print_DaftarTunggu(){
		Node *tmp = front1;
		if(is_empty_RuangTunggu()){
            cout << "DAFTAR_TUNGGU -";
        }
        else{
            cout << "DAFTAR_TUNGGU ";
            while(tmp != NULL){
                cout << tmp->name << "^" << tmp->status << "^" << tmp->bp << " ";
                tmp=tmp->prev;
            }
        }
		cout<<endl;
 	}

    void InputOutputHandler(string inputs){
        int xyz = 0; // Variabel untuk loop memasukan setiap kata pada input ke setiap array (dipisah)
        int USIA; // Variabel untuk dipass melalui parameter fungsi
        int TENSI; // Variabel untuk dipass melalui parameter fungsi
        int N; // Variabel untuk dipass melalui parameter fungsi
        int priority;
		string inputPerKata[4]; // Array yang menyimpan setiap kata (contoh -> array[0]: BARU, array[1]: Yana, dan seterusnya)
        for(int zyx = 0; zyx < 4; zyx++){ // Inisialisasi array default berisi "KOSONG"
            	inputPerKata[zyx] = "KOSONG";
        }
        string NAMA_PENERIMA_VAKSIN; // Variabel untuk dipass melalui parameter fungsi
        string PERINTAH; // Variabel untuk seleksi perintah (contoh: BARU, UKURAN, dan lain lain)
        string status;
		// Simpan setiap kata pada input ke Array.
        istringstream iss(inputs);
        string kata;
        while(iss >> kata) { // Mengisi input awal user ke array setiap kata
            	inputPerKata[xyz] = kata;
            	xyz++;
        }
        PERINTAH = inputPerKata[0]; // Mengisi perintah dari nilai elemen pertama inputPerKata
        // Seleksi kondisi input tertentu.
        if(PERINTAH == "BARU"){
            	if(inputPerKata[1] == "KOSONG" || inputPerKata[2] == "KOSONG" || inputPerKata[3] == "KOSONG"){
                	// Exit saat input BARU dimasukkan tanpa diikuti nama pasien/usia/tensi
                	exit(0);
            	}
            	else{
                	NAMA_PENERIMA_VAKSIN = inputPerKata[1];
                	USIA = stoi(inputPerKata[2]);
                	TENSI = stoi(inputPerKata[3]);
					if(USIA>=60){
						status = "LANSIA";
						priority = 1;
					} else{
						status = "BUKAN_LANSIA";
						priority = 0;
					}	
					if (TENSI < 180){
						print_Antre(NAMA_PENERIMA_VAKSIN, status);
                        enqueue_RuangAntre(NAMA_PENERIMA_VAKSIN, USIA, TENSI, status, priority);
					} else {
						print_Tolak(NAMA_PENERIMA_VAKSIN, status);			
					}
            	}
        }

        else if(PERINTAH == "UKURAN"){
            	if(inputPerKata[1] == "KOSONG"){
                	// Exit saat input UKURAN dimasukkan tanpa diikuti variabel ukuran (N)
                	exit(0);
            	}
            	else{
                	N = stoi(inputPerKata[1]); // Casting String ke Integer (Butuh C++ Versi 11 atau Lebih)
                	// Panggil Fungsi Pengganti Ukuran Ruang Antre Sebesar N (Parameter : N)
                    gantiUkuran(N);
            	}
        }
        else if(PERINTAH == "SELESAI"){
            	if(inputPerKata[1] == "KOSONG"){
                	// Exit saat input SELESAI dimasukkan tanpa diikuti variabel jumlah pasien selesai (N)
                	exit(0);
            	}
            	else{
                	N = stoi(inputPerKata[1]); // Casting String ke Integer (Butuh C++ Versi 11 atau Lebih)
                    // Panggil Fungsi Dequeue Dengan Jumlah Data Yang Ingin diEnqueue Sebanyak N (Parameter : N)
                    dequeue(N);
            	}
        }
        else if(PERINTAH == "SELESAI_NAMA"){
            if(inputPerKata[1] == "KOSONG"){
                // Exit saat input SELESAI_NAMA dimasukkan tanpa diikuti nama pasien (NAMA_PENERIMA_VAKSIN)
                exit(0);
            }
            else{
                NAMA_PENERIMA_VAKSIN = inputPerKata[1];
            	if(is_exist_pasien_RuangAntre(NAMA_PENERIMA_VAKSIN)){ // Cek Apakah Nama Pasien terdapat diRuang Antre
                    // Panggil Fungsi Dequeue_Nama Dengan Parameter Pasien Yang Ingin diVaksin
                    dequeue_nama(NAMA_PENERIMA_VAKSIN);
                    cout << "SELESAI_VAKSIN " << NAMA_PENERIMA_VAKSIN << endl;
                }
                else if(is_empty_RuangAntre()){
                    cout << "ANTRE KOSONG " << endl;
                }
                else{
                    // Saat Input Nama Pasien Tidak Ada
                }
            }
        }
        else if(PERINTAH == "SKIP"){
            if(inputPerKata[1] == "KOSONG"){
                // Exit saat input SELESAI_NAMA dimasukkan tanpa diikuti nama pasien (NAMA_PENERIMA_VAKSIN)
                exit(0);
            }
            else{
                NAMA_PENERIMA_VAKSIN = inputPerKata[1];
            	if(is_exist_pasien_RuangAntre(NAMA_PENERIMA_VAKSIN)){  // Skip Pasien Hanya Saat Pasien ada didalam Ruang Antre
                    // Panggil Fungsi Skip Dengan Parameter Pasien Yang Ingin di Skip (Pindah ke Ruang Tunggu)
                    skip(NAMA_PENERIMA_VAKSIN);
                    cout << "SKIP SUKSES" << endl; 
                }
                else{
                    cout << "SKIP GAGAL" << endl;
                }
            }
		}
		else if(PERINTAH == "STATUS"){
				// Panggil Fungsi untuk Mencetak Daftar Antre dan Daftar Tunggu
                print_DaftarAntre();
				print_DaftarTunggu();
        }
        else{
            // Exit Saat Perintah Tidak Ada Yang Cocok
            exit(0);
        }
    }
};

int main(int argc, char** argv) {
	QueueLinkedList qll;
	int ukuran;
	cin >> ukuran;
	cin.ignore();
	qll.set_size_RuangAntre(ukuran);
	qll.init();
	int x = 0;
    // Input Yang Dimasukan User Pertama Kali (contoh: BARU Faridh 55 22)
    string inputs; 
    // Menyimpan input pada Array Agar Dapat Input Secara Banyak Lalu Output (Testcase sampai 10000)
    string inputFix[10000]; 
    while(getline(cin,inputs)){
        inputFix[x] = inputs;
        x++;
        if(inputs.empty()){
            break;
        }
    }
    for(int xy = 0; xy < x; xy++){
        qll.InputOutputHandler(inputFix[xy]);
    }
    qll.destroy();
	return 0;
}
