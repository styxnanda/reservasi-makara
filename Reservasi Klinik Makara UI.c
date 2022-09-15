#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct id {
    char nama[40]; 
    int mhsUI; //apakah mahasiswa ui? 1 -> iya, 0 -> tidak
    char email[40];
    int tanggalLahir[3]; //elemen [0] untuk tanggal, elemen[1] untuk bulan, elemen[2] untuk tahun
    long long NPM;
    long long noHP;
    long long noTiket;
    char jenisLayanan[20];
    int pilihJadwal[3]; //elemen [0] untuk tanggal, elemen[1] untuk bulan, elemen[2] untuk tahun
    long long hargaLayanan;
}id;		//sizeof(id) = 160

//prototype function
void menuUtama(id*, int, int);
int cekTiket(id*, int);
void moreInfo(id*, int);
void helpMenu(id*, int);
void loginAwal(id*, int);
void menuLayanan(id*, int);
void vaksin(id*, int);
void tesCovid(id*, int);
void klinik(id*, int);
void daftarLayanan(id*, int);
void reservasiJadwal(id*, int);
int getTicketNum(void);
void displayTiket(id*, int, int);
void displayDate (int*);
void biayaLayanan(id*, int, int, int);
void clearAndPrintHeader(void);
void errorHand(void);
void exitScreen (id*, int);

int main(void) {
    int i = 0;

    id* idPtr = (id*) malloc (sizeof(id));
	
    menuUtama(idPtr, i, 0);
    free(idPtr);
    return 0;
}

/*fungsi menuUtama -> menampilkan menu utama dari program
fungsi ini ada 2 kondisi, saat newUser = 0 dan saat newUser = 1
saat newUser = 1 -> menambah elemen dari array of struct untuk user baru
saat newUser = 0 -> tidak menambah elemen*/
void menuUtama(id* ptr, int i, int newUser) { 
	if(newUser == 1){
		i++;
        /*realloc untuk menambah size dari array of struct dan mereallocate 
        memory untuk user baru*/
		ptr = (id*) realloc (ptr, (i+1)* sizeof(id));
	}
	clearAndPrintHeader();
    printf("Selamat Datang di Klinik Satelit Makara Universitas Indonesia!\n");
    puts("1. Daftar layanan");
    puts("2. Cek tiket layanan");
    puts("3. More info");
    puts("4. Help");
    puts("5. Exit");
    puts("Pilih untuk lanjut: ");
    //meminta input user dengan getch dan mengubahnya ke integer
    //contoh '1' (input char ASCII) - '0' -> 1 (integer)
    int ans = getch() - '0'; 
    switch(ans) {
    	case 1: 
    		loginAwal(ptr, i);
            break;
    	case 2:
    		displayTiket(ptr, i, cekTiket(ptr, i));
            break;
        case 3:
            moreInfo(ptr, i);
            break;
        case 4:
            helpMenu(ptr, i);
            break;
        case 5:
            exitScreen(ptr, i);
            break;
    	default:
            errorHand();
            menuUtama(ptr, i, 0);
            break;
	}
}

//fungsi cekTiket -> mendisplay dan mengecek tiket dari input no tiket user
int cekTiket(id* ptr, int i) { 
    int j;
    long long tempNoTiket;
    clearAndPrintHeader();
    printf("Masukkan nomor tiket Anda untuk dicek: ");
    scanf("%lld", &tempNoTiket);
    for (j = 0; j < i+1; j++) {
        if (tempNoTiket == ptr[j].noTiket){
            return j; //mereturn index dari no tiket yang cocok dengan input
        }
    }
    return -2; //mereturn -2 apabila tidak ditemukan tiket dengan no tiket input
}

//fungsi moreInfo -> print info lebih lanjut dari satelit makara UI dan program ini
void moreInfo(id* ptr, int i) {
	clearAndPrintHeader();
    puts(">> About Us <<");
    puts("Selamat datang di Reservasi Daring Klinik Satelit UI.\nFasilitas klinik ini terletak di Kampus UI Depok dan sudah dilengkapi dengan layanan "
	"vaksinasi COVID-19, tes COVID-19, dan klinik.\n"
	"Sivitas UI mendapatkan semua layanan secara gratis tanpa dipungut biaya sepeser pun.\n"
	"\nLayanan vaksinasi COVID-19 yang tersedia saat ini:\n1. Sinovac\n2. Pfizer\n\n"
	"Layanan tes COVID-19 yang tersedia saat ini:\n1. Tes PCR\n2. Tes Antigen\n3. Tes Antibodi\n\n"
	"Layanan klinik yang tersedia saat ini:\n1. Apotek\n2. Lab\n3. Poli Umum\n4. Poli Gigi\n\n");
    puts("press any key to exit...");
	getch();
	menuUtama(ptr, i, 0);
}

//fungsi helpMenu -> panduan untuk menggunakan program dan daftar layanan
void helpMenu(id* ptr, int i){
	clearAndPrintHeader();
	puts(">> HELP MENU <<");
	puts("Panduan menggunakan program:\n"
	"1. Program memandu navigasi user dengan menampilkan angka untuk menu dan pilihan tertentu. User hanya perlu mengetik input sesuai dengan pilihan pada layar.\n"
	"2. Sivitas dan mahasiswa UI akan diminta untuk memasukkan email UI dan NPM, sedangkan non-sivitas hanya perlu memasukkan email yang dapat dihubungi.\n"
	"3. User bisa mendaftar layanan sebanyak-banyaknya dengan catatan wajib login setiap mendaftar.\n\n"
	"Alur pendaftaran layanan:\n"
	"1. Masuk ke menu Daftar Layanan.\n"
	"2. Pilih jenis layanan yang diinginkan.\n"
	"3. Pilih sub-layanan yang diinginkan.\n"
	"4. Masukkan biodata yang diminta, yaitu Nama Lengkap, Tanggal Lahir, No. HP\n"
	"5. Konfirmasi biodata dengan mengetik 'y', jika ingin membatalkan pengisian biodata, ketik 'n' untuk reset dan kembali ke input awal.\n"
	"6. Setelah konfirmasi, pilih jadwal reservasi. Jadwal hanya tersedia untuk 5 hari termasuk hari yang sama.\n"
	"7. Nomor tiket beserta isi tiket akan muncul. Harap mencatat nomor tiket!\n"
	"8. Untuk mengecek tiket, pilih menu Cek Tiket Pendaftaran pada menu utama dan masukkan nomor tiket yang sudah diberikan.\n\n");
	
	puts("press any key to exit...");
	getch();
	menuUtama(ptr, i, 0);
}

//fungsi loginAwal -> menampilkan menu yang meminta data awal yaitu email (dan NPM)
void loginAwal(id* ptr, int i) {
	clearAndPrintHeader();
	char tempStr[40];
	char checkStr[20];
    puts("Apakah Anda mahasiswa UI? ");
    puts("1. Iya");
    puts("2. Tidak");
    puts("3. Kembali");
	int ans = getch() - '0';
    if (ans == 1) {
        ptr[i].mhsUI = 1;
        clearAndPrintHeader();
        printf("Mohon masukkan email UI Anda: ");
        scanf("%[^@]s", tempStr);
        scanf("%s", checkStr);
        if (strcmp(checkStr, "@ui.ac.id")!= 0) {
        	clearAndPrintHeader();
        	puts("Email yang Anda masukkan bukan email UI, mohon coba kembali.");
        	Sleep(2000);
        	loginAwal(ptr, i);
		}
		strcpy(ptr[i].email, strcat(tempStr, checkStr));
        printf("Mohon masukkan NPM Anda: ");
        scanf("%lld", &ptr[i].NPM);
        menuLayanan(ptr, i);
    } else if (ans == 2) {
       	ptr[i].mhsUI = 0;
        clearAndPrintHeader();
        printf("Mohon masukkan email Anda: ");
        scanf("%[^@]s", tempStr);
        scanf("%s", checkStr);
        if (checkStr[0] != '@' || strlen(checkStr) < 2) {
            clearAndPrintHeader();
            puts("Mohon masukkan email yang valid!");
            Sleep(2000);
            loginAwal(ptr, i);
        }
        strcpy(ptr[i].email, strcat(tempStr, checkStr));
        menuLayanan(ptr, i);
    } else if (ans == 3){
    	menuUtama(ptr, i, 0);
	} else {
        errorHand();
        loginAwal(ptr, i);
    }
}

//fungsi menuLayanan -> menu yang menampilkan layanan yang tersedia
//dan user dapat memilih layanan yang diinginkan
void menuLayanan(id* ptr, int i) {
    clearAndPrintHeader();
    puts("Berikut merupakan layanan yang tersedia untuk Anda:");
    puts("1. Vaksin COVID-19");
    puts("2. Tes COVID-19");
    puts("3. Klinik");
    puts("4. Input ulang email");
    puts("5. Exit ke menu utama");
    puts("Pilih untuk lanjut: ");
    int ans = getch() - '0';
    switch(ans) {
        case 1:
            vaksin(ptr, i);
            break;
        case 2:
            tesCovid(ptr,i);
            break;
        case 3:
        	klinik(ptr, i);
            break;
        case 4:
        	loginAwal(ptr, i);
        	break;
        case 5:
            menuUtama(ptr, i, 0);
            break;
        default:
        	errorHand();
        	menuLayanan(ptr, i);
        	break;
    }
}

// fungsi vaksin -> menu pemilihan jenis vaksin
void vaksin(id* ptr, int i) { 
  clearAndPrintHeader();
	int ans;
	puts("Pilih jenis vaksin:");
	puts("1. Sinovac");
	puts("2. Pfizer");
	puts("3. Kembali");
	scanf("%d", &ans);
	switch(ans) {
		case 1:
			strcpy(ptr[i].jenisLayanan, "Vaksin Sinovac");
			biayaLayanan(ptr, i, 1, 1);
			break;
		case 2:
			strcpy(ptr[i].jenisLayanan, "Vaksin Pfizer");
			biayaLayanan(ptr, i, 1, 2);			
			break;
		case 3:
			puts("Mengembalikan anda...");
			Sleep(1000);
			menuLayanan(ptr, i);
			break;
		default:
			puts("Masukkan angka sesuai pilihan, mohon isi kembali...");
			vaksin(ptr, i);
			break;
	}
	daftarLayanan(ptr, i);
}

// fungsi vaksin -> menu pemilihan tes covid yang tersedia
void tesCovid(id* ptr, int i){ 
    clearAndPrintHeader();
	int ans;
	puts("Pilih jenis tes covid!");
	puts("1. Test PCR");
	puts("2. Test Antigen");
	puts("3. Test Antibodi");
	puts("4. Kembali");
	scanf("%d",&ans);
	switch(ans){
		case 1:
			strcpy(ptr[i].jenisLayanan, "Test PCR");
			biayaLayanan(ptr, i, 2, 1);
			break;
		case 2:
			strcpy(ptr[i].jenisLayanan, "Test Antigen");
			biayaLayanan(ptr, i, 2, 2);			
			break;
		case 3:
			strcpy(ptr[i].jenisLayanan, "Test Antibodi");
			biayaLayanan(ptr, i, 2, 3);		
			break;
		case 4:
			puts("Mengembalikan anda...");
			Sleep(2000);
			menuLayanan(ptr, i);
			break;
		default:
			puts("Masukkan angka sesuai petunjuk. Mohon isi kembali....");
			Sleep(2000);
			klinik(ptr, i);
			break;
	}
	daftarLayanan(ptr, i);
}

//fungsi klinik -> menu pemilihan layanan yang tersedia di klinik
void klinik(id* ptr, int i){
	clearAndPrintHeader();
	puts("Pilih layanan klinik:");
	puts("1. Apotek");
	puts("2. Lab");
	puts("3. Poli Umum");
	puts("4. Poli Gigi");
	puts("5. Kembali");
	int answer = getch() - '0';
	switch(answer){
		case 1:
			strcpy(ptr[i].jenisLayanan, "Apotek");
			biayaLayanan(ptr, i, 3, 1);
			break;
		case 2:
			strcpy(ptr[i].jenisLayanan, "Lab");
			biayaLayanan(ptr, i, 3, 2);
			break;
		case 3:
			strcpy(ptr[i].jenisLayanan, "Poli Umum");
			biayaLayanan(ptr, i, 3, 3);
			break;
		case 4:
			strcpy(ptr[i].jenisLayanan, "Poli Gigi");
			biayaLayanan(ptr, i, 3, 4);
			break;
		case 5:
			puts("Mengembalikan anda...");
			Sleep(2000);
			menuLayanan(ptr, i);
			break;
		default:
			puts("Masukkan angka sesuai petunjuk. Mohon isi kembali....");
			Sleep(2000);
			klinik(ptr, i);
			break;
	}
	daftarLayanan(ptr, i);	
}

//fungsi daftarLayanan -> menampilkan menu form data diri yang dapat diisi user 
void daftarLayanan(id* ptr, int i) { 
	clearAndPrintHeader();
	fflush(stdin);
	puts(">> Untuk mendaftar dibutuhkan data pribadi Anda <<\n");
	puts("Mohon masukkan data Anda di bawah sesuai dengan keterangan yang tertera");
	printf("Apa nama lengkap Anda? ");
	scanf("%[^\n]", ptr[i].nama);
	printf("Berapa tanggal lahir Anda (DD MM YYYY)? ");
	scanf("%d%d%d", &ptr[i].tanggalLahir[0], &ptr[i].tanggalLahir[1], &ptr[i].tanggalLahir[2]);
    ptr[i].tanggalLahir[1]--; //set index bulan dari 0 s.d 11
	printf("Berapa nomor HP Anda? ");
	scanf("%lld", &ptr[i].noHP);
	
	puts("Apakah data yang sudah Anda input di atas benar (y/n)?");
	switch (getch()) {
		case 'y':
			if (ptr[i].tanggalLahir[1] < 0 || ptr[i].tanggalLahir[1] > 11) {
				puts("\nTanggal lahir yang Anda masukkan invalid, mohon isi ulang kembali...");
				Sleep(2000);
				daftarLayanan(ptr, i);
			}
			ptr[i].noTiket = getTicketNum();
			break;
		case 'n':
			printf("\nData Anda sebelumnya akan direset, mohon isi ulang kembali...");
			Sleep(2000);
			daftarLayanan(ptr, i);
			break;
		default:
			printf("Data Anda sebelumnya akan direset, mohon isi ulang kembali...");
			Sleep(2000);
			daftarLayanan(ptr, i);
			break;	
	}
	reservasiJadwal(ptr, i);
	displayTiket(ptr, i, -1);
}

// fungsi reservasiJadwal -> menu yang menampilkan jadwal yang tersedia dan dapat dipilih oleh user
void reservasiJadwal(id* ptr, int i){ 
	time_t date = time(NULL); //set time sesuai dengan waktu lokal dalam bentuk long integer
	struct tm *now;
	int p, j; 
	int choices[5], tanggal[5];
	int user_Choice;
	int COUNT = 5;
	int max_Pilihan = 0;
	char *bulan[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
	now = localtime(&date);	// konversi date menjadi komponen-komponen waktu sehingga bisa diakses pada struct now
	
	clearAndPrintHeader();
	//tm_year adalah variabel tahun mulai terhitung dari tahun 1900, jadi perlu ditambah 1900 untuk menampilkan tahun yang diharapkan
	printf("Sekarang: %d %s %d\n", now->tm_mday, bulan[now->tm_mon], now->tm_year + 1900);
	puts("Pilih jadwal Anda: ");
	for(p = 0; p < COUNT; p++){
		tanggal[p] = now->tm_mday + p;
	}
	
	int cek_Bulan = now->tm_mon + 1;
	for(j = 1; j <= COUNT; j++){
		//error handling untuk bulan-bulan yang tidak sampai tanggal 31
		if(cek_Bulan == 2 || cek_Bulan == 4 || cek_Bulan == 6 || cek_Bulan == 9 || cek_Bulan == 11){
			if(cek_Bulan == 2){
					if(tanggal[j-1] > 29){	//error handling bulan Februari
						max_Pilihan = j-1;
						break;
					}
			} else {
				if(tanggal[j-1] > 30){	//error handling bulan yang hanya terdiri atas 30 hari
					max_Pilihan = j-1;
					break;
				}
			}
		} else {
			if(tanggal[j-1] > 31){
				max_Pilihan = j-1;
				break;
			} else {
				choices[j] = tanggal[j-1];
				max_Pilihan += 1;
			}
		}
		printf("%d. %d %s %d\n", j, tanggal[j-1], bulan[now->tm_mon], now->tm_year + 1900);
	}
	
	puts("\nJadwal pilihan: ");
	scanf("%d", &user_Choice);
    if (user_Choice < 1 || user_Choice > max_Pilihan) { //error handling opsi
        errorHand();
        reservasiJadwal(ptr, i);
    } else {
    	ptr[i].pilihJadwal[0] = choices[user_Choice];
		ptr[i].pilihJadwal[1] = now->tm_mon;
		ptr[i].pilihJadwal[2] = now->tm_year + 1900;
	}
}

//fungsi getTicketNum -> mereturn suatu nomor ticket yang digenerate secara random
int getTicketNum(void) {
    //set seed agar selalu beda (mengacu pada waktu lokal yang tidak akan pernah sama)
    srand(time(NULL)); 
    //return -> mendapatkan angka random dari 100.000 sampai 999.999
    return (rand() % (999999 + 1 - 100000) + 100000); 
}

// fungsi displayTiket -> berfungsi untuk menampilkan tiket
// memiliki tiga kondisi, saat j = -2, j = -1 dan saat j bernilai selain itu
void displayTiket(id* ptr, int i, int j) { 
    int nextIndex, createNewUser, index;
    clearAndPrintHeader();
    if (j == -2) { // saat dipass j = -2 -> menampilkan bahwa no tiket tidak ditemukan
        puts("Mohon maaf kami tidak menemukan tiket dengan nomor tersebut");
        Sleep(500);
        puts("Mengembalikan Anda ke menu utama...");
        Sleep(1500);
        menuUtama(ptr, i, 0);
        return;
    }
    /* saat dipass j = -1 -> menampilkan detail dari tiket tersebut dan akan memanggil 
    fungsi menu dengan index yang diincrement dan argumen newUser = 1*/
    else if (j == -1) { 
        index = i;
        nextIndex = i++;
        createNewUser = 1;
    }
    /* saat j selain -2 atau -1 -> menampilkan detail dari tiket dan akan memanggil 
    fungsi menu dengan index yang sama dengan argumen newUser = 0*/
     else { 
        index = j;
        nextIndex = i;
        createNewUser = 0;
    }
    //print detail dari tiket
    puts("Berikut merupakan tiket reservasi Anda:");
    printf("      >> No. Tiket: %lld <<\n", ptr[index].noTiket);
    printf("Nama\t\t: %s\n", ptr[index].nama);
    printf("Tanggal lahir\t: ");
    displayDate (ptr[index].tanggalLahir);
    printf("\n");
    if (ptr[index].mhsUI == 1) 
        printf("NPM\t\t: %lld\n", ptr[index].NPM);
    printf("No. HP\t\t: 0%lld\n", ptr[index].noHP);
    printf("Jenis layanan\t: %s\n", ptr[index].jenisLayanan);
    printf("Jadwal Reservasi: "); displayDate(ptr[index].pilihJadwal);
    printf("\nBiaya Layanan\t: ");
    if (ptr[index].mhsUI == 1)
        printf("Rp0,00 (sudah ditanggung oleh UI)");
    else {
        printf("Rp%lld.000,00", ptr[index].hargaLayanan / 1000);
    }
    puts("\n\npress any key to exit...");
	getch();
	menuUtama(ptr, nextIndex, createNewUser);	
}

//fungsi displayDate -> mengambil array berisi komponen tanggal dan mendisplaynya menjadi format TANGGAL BULAN TAHUN
void displayDate (int* arr) {
    printf("%d ", arr[0]);
    switch (arr[1]) {
        case 0: printf("Januari"); break;
        case 1: printf("Februari"); break;
        case 2: printf("Maret"); break;
        case 3: printf("April"); break;
        case 4: printf("Mei"); break;
        case 5: printf("Juni"); break;
        case 6: printf("Juli"); break;
        case 7: printf("Agustus"); break;
        case 8: printf("September"); break;
        case 9: printf("Oktober"); break;
        case 10: printf("November"); break;
        case 11: printf("Desember"); break;
        default: printf("Unknown"); break;
    }
    printf(" %d", arr[2]);
}

//fungsi biayaLayanan -> set nilai dari biaya layanan tergantung dengan pilihan user
void biayaLayanan(id* ptr, int i, int layanan, int sub_layanan){
	if(layanan == 1){	//layanan vaksin
		switch(sub_layanan){
			case 1:
				ptr[i].hargaLayanan = 240000;	//sinovac
				break;
			case 2:
				ptr[i].hargaLayanan = 300000;	//pfizer
				break;
		}
	} else if(layanan == 2){	//layanan tes covid
		switch(sub_layanan){
			case 1:
				ptr[i].hargaLayanan = 250000;	//pcr
				break;
			case 2:
				ptr[i].hargaLayanan = 200000;	//antigen
				break;
			case 3:
				ptr[i].hargaLayanan = 150000;	//antibodi
				break;
		}
	} else if(layanan == 3){	//klinik
		switch(sub_layanan){
			case 1:
				ptr[i].hargaLayanan = 150000;	//apotek
				break;
			case 2:
				ptr[i].hargaLayanan = 110000;	//lab
				break;
			case 3:
				ptr[i].hargaLayanan = 100000;	//poli umum
				break;
			case 4:
				ptr[i].hargaLayanan = 80000;	//poli gigi
				break;
		}
	}
}

void clearAndPrintHeader() { //fungsi untuk clear terminal dan mendisplay header
	system("cls");
	puts("\t<< Aplikasi Reservasi Pelayanan >>");
	puts("  \t  << Klinik Satelit Makara UI >>\n");
}

void errorHand() { //clear screen dan print error message
    clearAndPrintHeader();
    puts("Mohon masukkan angka sesuai dengan opsi!");
    Sleep(1000);
}

//fungsi exitScreen -> menu jika user ingin mengakhiri program 
void exitScreen (id* ptr, int i) {
	clearAndPrintHeader();
	puts("Apakah Anda yakin ingin keluar dari program ini?");
	puts("1. Iya");
	puts("2. Tidak, balik ke menu utama");
	switch(getch()) {
		case '1':
			clearAndPrintHeader();
			puts("Terima kasih telah menggunakan aplikasi ini! :)");
			free(ptr);
			exit(0);
			break;
		case '2':
			menuUtama(ptr, i, 0);
			break;
		default:
			exitScreen(ptr,i);
			break;
	}
}
