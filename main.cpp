#include <bits/stdc++.h>

using namespace std;

struct Node{
	string name;
	string status; 
	int age;
	int bp; //bp = blood pressure
	Node *next, *prev;
	
};

struct QueueLinkedList{
	int value, x;
	int count = 0;
	int size = 0;
	Node *front, *front1, *rear, *rear1, *head, *head1;
	
	void init(){
		front = front1 = rear = rear1 = head = head1 = NULL;
	}
	
	bool is_empty(){
		return (front == NULL && rear == NULL);
	}
	
	void make_empty(){
		Node *p = front;
        for(int x; size != 0; x++){
            delete p;
            p = p->next;
            size--;
        }
        front = rear = NULL;
	}
	
	void set_size(int x){
		size = x;
	}
	
	int get_size(){
		return size;
	}
	
	void enqueue(string x, int y, int z, string status){
		Node *tmp = new Node;
		tmp->name = x;
		tmp->age = y;
		tmp->bp = z;
		tmp->status = status;
		tmp->next = NULL;
		tmp->prev = NULL;
		if(is_empty()){
			front = tmp;
			rear = tmp;
		} else if(count >= size) {
			if(front1 == NULL){
				front1 = rear1 = tmp;
			} else {
				// rear1->next = tmp;
				// rear1 = tmp;
				tmp->next = front1;
				front1->prev = tmp;
			}
		} else {
            tmp->next = front;
            front->prev = tmp;
		}
		front = tmp;
		count++;
	}

	void printAntre(string nama, string status){
		cout << "ANTRE " << nama << " " << status;
		if(count > size){
			cout << " TUNGGU " << nama;
		}
		cout << endl;
	}

    void printTolak(string nama, string status){
        cout << "TOLAK " << nama << " " << status << " TENSI_TIDAKBOLEH_DIVAKSIN" << endl;
    }

	void dequeue(){
		Node *tmp = rear;
		if(rear == front){
            delete tmp;
            front = rear = NULL;
		}
		else{
                rear->prev->next = NULL;
                rear = tmp->prev;
                delete tmp;
		}
	}
	
	void skip(){
		
	}

	void print(){
		Node *tmp = rear;
		cout << "DAFTAR_ANTRE ";
		while(tmp != NULL){
			cout << tmp->name << "^" << tmp->status << "^" << tmp->bp << " ";
			tmp=tmp->prev;
		}
		cout<<endl;
 	}

 	void print1(){
		Node *tmp = rear1;
		cout << "DAFTAR_TUNGGU ";
		while(tmp != NULL){
			cout << tmp->name << "^" << tmp->status << "^" << tmp->bp << " ";
			tmp=tmp->prev;
		}
		cout<<endl;
 	}

    void InputOutputHandler(string inputs){
        int xyz = 0; // Variabel untuk loop memasukan setiap kata pada input ke setiap array (dipisah)
        int USIA; // Variabel untuk dipass melalui parameter fungsi
        int TENSI; // Variabel untuk dipass melalui parameter fungsi
        int N; // Variabel untuk dipass melalui parameter fungsi
        string inputPerKata[4]; // Array yang menyimpan setiap kata (contoh -> array[0]: BARU, array[1]: Yana, dan seterusnya)
        for(int zyx = 0; zyx < 4; zyx++){ // Inisialisasi array default berisi "Kosong"
            	inputPerKata[zyx] = "KOSONG";
        }
        string NAMA_PENERIMA_VAKSIN; // Variabel untuk dipass melalui parameter fungsi
        string PERINTAH; // Variabel untuk cek perintah (contoh: BARU, UKURAN, dan lain lain)
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
                	// cout << "Masukin " << NAMA_PENERIMA_VAKSIN << " " << USIA << " " << TENSI << endl; // Contoh output aja
                	// Perlu Pengecekan Tensi dan Umur lalu Panggil Fungsi Enqueue(NAMA_PENERIMA_VAKSIN, USIA, TENSI)
					if(USIA>=60){
						status = "LANSIA";
					} else{
						status = "BUKAN_LANSIA";
					}	
					if (TENSI < 180){
						enqueue(NAMA_PENERIMA_VAKSIN, USIA, TENSI, status);
						printAntre(NAMA_PENERIMA_VAKSIN, status);
					} else {
						printTolak(NAMA_PENERIMA_VAKSIN, status);			
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
                	cout << "UKURAN MENJADI " << N << endl; // Contoh output aja
                	// Panggil Fungsi Pengganti Ukuran Ruang Antre Sebesar N (Parameter : N)
            	}
        }
        else if(PERINTAH == "SELESAI"){
            	if(inputPerKata[1] == "KOSONG"){
                	// Exit saat input SELESAI dimasukkan tanpa diikuti variabel jumlah pasien selesai (N)
                	exit(0);
            	}
            	else{
                	N = stoi(inputPerKata[1]); // Casting String ke Integer (Butuh C++ Versi 11 atau Lebih)
                	cout << "SELESAI " << N << " ORANG" << endl; // Contoh output aja
                	// Panggil Fungsi Untuk Menghapus (Selesai Vaksin) N Orang Dari Antrian (Parameter : N)
					for(int x = 0; x < N; x++){
						dequeue();
					}
            	}
        }
        else if(PERINTAH == "SELESAI_NAMA"){
            	if(inputPerKata[1] == "KOSONG"){
                // Exit saat input SELESAI_NAMA dimasukkan tanpa diikuti nama pasien (NAMA_PENERIMA_VAKSIN)
                exit(0);
            	}
            	else{
                	NAMA_PENERIMA_VAKSIN = inputPerKata[1];
                	cout << "SELESAI " << NAMA_PENERIMA_VAKSIN << endl; // Contoh output aja
                	// Panggil Fungsi Untuk Menghapus (Selesai Vaksin) dengan Nama Orang Dari Antrian (Parameter : NAMA_PENERIMA_VAKSIN)
            	}
        }
        else if(PERINTAH == "SKIP"){
            	if(inputPerKata[1] == "KOSONG"){
                	// Exit saat input SELESAI_NAMA dimasukkan tanpa diikuti nama pasien (NAMA_PENERIMA_VAKSIN)
                	exit(0);
            	}
            	else{
                	NAMA_PENERIMA_VAKSIN = inputPerKata[1];
                	cout << "SKIP " << NAMA_PENERIMA_VAKSIN << endl; // Contoh output aja
                	// Panggil Fungsi Untuk Memindahkan Pasien Berdasarkan Nama dari Ruang Antre ke Ruang Tunggu (Parameter : NAMA_PENERIMA_VAKSIN)
            	}
		}
		else if(PERINTAH == "STATUS"){
            	// cout << "STATUS ANTRE DAN TUNGGU" << endl; // Contoh output aja
            	// Panggil Fungsi Untuk Mencetak/Melihat Pasien di Ruang Antre dan Ruang Tunggu
				print();
				print1();
        }
        else{
            	// Exit Saat perintah tidak ada yang cocok
            	exit(0);
        }
    }
};

int main(int argc, char** argv) {
	QueueLinkedList qll;
	int ukuran;
	// Perlu Inisiasilasi Awal Ukuran Ruang Antre Variabel (M) dengan Batas 1 =< M =< 1000
	// cin >> ukuran;
	// cin.ignore();
	qll.set_size(5);
	qll.init();
	int x = 0;
    	string inputs; // Variabel yang dimasukan user pertama kali (contoh: BARU Yana 55 22)
    	string inputFix[10000]; // Menyimpan input pada Array agar dapat input secara banyak lalu output (testcase sampai 10000)
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
    	// Perlu Penghapusan Object/Instance atau Membebaskan Memori
	return 0;
}
