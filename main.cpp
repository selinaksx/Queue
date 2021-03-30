#include <bits/stdc++.h>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Node{
	string name, age, bp; //bp = blood pressure
	Node *next;
	
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
		while(p != NULL){
			delete p;
			p = p->next;
		}
	}
	
	void set_size(int x){
		size = x;
	}
	
	int get_size(){
		return size;
	}
	
	void enqueue(string x, int y, int z){
		Node *tmp = new Node;
		tmp->name = x;
		tmp->age = y;
		tmp->bp = z;
		tmp->next = NULL;
		
		if(is_empty()){
			front = rear = tmp;
		} else if(count >= size) {
			if(front1 = NULL){
				front1 = rear1 = tmp;	
			} else {
				rear1->next = tmp;
				rear1 = tmp;
			}
		} else {
			rear->next = tmp;
			rear = tmp;
		}
		count++;
	}
	
	void dequeue(){
		if(count <= size){
			Node *tmp = front;
			tmp = tmp->next;
			delete tmp;
		} else if(count > size){
			Node *tmp = front;
			tmp = tmp->next;
			delete tmp;
			
			if(size == 2){
				Node *tmp  = front1;
				Node *done = front1;
				tmp = front1->next;
				front = rear;
				front->next = tmp;
				rear = done;
				rear->next = NULL;
			} else if(size > 2){
				Node *tmp = front1;
				tmp = tmp->next;
				rear = front->next;
				rear->next = tmp;
				rear = tmp;
				rear->next = NULL;
			}
		}
		count--;
	}
	
	void skip(){
		
	}
	
	void print(){
		if(is_empty()){
			cout << "-" << endl;
		} else {
			Node *p = front;
			while(p != NULL){
				cout << "ANTRE " << p->name << endl;
				p = p->next;
			}
		}
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
                		cout << "Masukin " << NAMA_PENERIMA_VAKSIN << " " << USIA << " " << TENSI << endl; // Contoh output aja
                		// Perlu Pengecekan Tensi dan Umur lalu Panggil Fungsi Enqueue(NAMA_PENERIMA_VAKSIN, USIA, TENSI)
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
            		cout << "STATUS ANTRE DAN TUNGGU" << endl; // Contoh output aja
            		// Panggil Fungsi Untuk Mencetak/Melihat Pasien di Ruang Antre dan Ruang Tunggu
        	}
        	else{
            		// Exit Saat perintah tidak ada yang cocok
            		exit(0);
        	}
    	}
};

int main(int argc, char** argv) {
	QueueLinkedList qll;
	// Perlu Inisiasilasi Awal Ukuran Ruang Antre Variabel (M) dengan Batas 1 =< M =< 1000
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
