#include<stdio.h>
#include<stdlib.h>
#include<conio.h>       //
#include<string.h>      //                       ismail ertaylan 

#define SIZE 10         //GENEL ACIKLAMA:
#define ALLSIZE 100     //Odevde structa bagli arrayler ile kuyruklari olusturdum. Degiskenlerle kuyruklarin on ve arka kisimlarini tuttum.
                        //Ekle cikar kaydir gibi fonksiyonlarla yas kategorilerine gore elemanlari ekledim ve hizmet edilen musterileri
struct groupE{          // kuyruklardan cikararak outputa ekledim, kuyrukta musteri yoksa ***** yazdirdim.
char name[SIZE];        //File operationsun fonksiyonlari olan fscanf ve fprintf ile input output txtlerini okudum ve yazdirdim.
char age;               //input2 (e-c-a) verisi sayesinde verileri kategorize edebildim.
}groupdiziE[SIZE];      //Koddaki hangi kismin ne yaptigini yanina kisaca acikladim, tekrar eden kisimlarda tek aciklama yaptim.
                        //Kodun tamamini Code::Blocks 20.03 (mingw-w64 v8.1.0) idesiyle yazip GNU GCC Compiler'i ile test ettim.
struct groupA{
char name[SIZE];
char age;
}groupdiziA[SIZE];
                        //Ilk 3 struct yas gruplarina gore 3 farkli queue icin kullaniliyor.
struct groupC{          //Son struct hizmet edilen musterilerin listesinin cikti alinmasi icin kullaniliyor.
char name[SIZE];
char age;
}groupdiziC[SIZE];

struct output{
char name[SIZE];
char age;
}groupdiziO[ALLSIZE];

int onE=0,onA=0,onC=0,onO=0;            //bu degiskenler bizim queue yapilarinda ekleme ve silme yapmak icin
int arkaE=0,arkaA=0,arkaC=0,arkaO=0;    //artirip azalttigimiz arraylerin on ve arka elemanlarinin yerlerini tutan
                                        //degiskenlerdir
char input1[15];
char input3[15];

void kaydir(char);
void ekle(char);
void cikar(int,char);                   //mainin altindaki fonksiyonlarin tanimlanmasini saglamak icin
void ekleO(char,char*);                 //girilen fonksiyon ve parametreler.


int main()
{
    char input2;         //ekleme ve silme islemlerinde yaslari(E-C-A) kategorize etmek icin kullandigimiz degisken
    int inputrepeat;     //musterilere hizmet edildiginde hangi kategoriden kac kisiye hizmet edildigini tutan degisken

    FILE * fp;
    fp = fopen("input.txt","r+");
        while(fscanf(fp,"%s\t%c\t%s", input1, &input2, input3)!=EOF){
            //input.txtdeki elemanlari satir satir 3erli halde cekip degiskenlere atiyoruz
            if(strcmp(input1,"NewCustomer")==0){
                ekle(input2); //satirda newcustomer yaziyorsa yeni musteri ekliyoruz
            }
            else if(strcmp(input1,"ServeCustomers")==0){
                inputrepeat= atoi(input3);  //string olarak aldigimiz inputrepeat degiskeninin int yapiyoruz
                cikar(inputrepeat,input2);  //satirda servecustomers yaziyorsa dondurma sirasindan cikarip outputa ekliyoruz
            }
            else{
                //fonksiyonun adi yanlis demektir
            }
        }
    fclose(fp);
    fp = fopen("output.txt","w");
    for (int i=arkaO-1; i>=0;i--){
        fprintf(fp,"%c\t%s\n",groupdiziO[i].age, groupdiziO[i].name);
    }
    fclose(fp);
}

void ekle(char input2)
{
    if(input2=='E'){
        if(arkaE < 10){ //kuyruk dolulugu kontrolu
	    groupdiziE[arkaE].age=input2;           //input2deki degere gore uygun kuyruga musteri ekleniyor
		strcpy(groupdiziE[arkaE].name,input3);
        arkaE++; //musteri eklenince arkayi gosteren degisken artik bi arkasini gosteriyor
        }
        else
        {
        //kuyruk dolu demektir
        }
    }
    else if(input2=='C'){
        if(arkaC < 10)
        {
		groupdiziC[arkaC].age=input2;
		strcpy(groupdiziC[arkaC].name,input3);
		arkaC++;
        }
        else
        {
		//kuyruk dolu demektir
        }
    }
    else{

        if(arkaA < 10)
        {
		groupdiziA[arkaA].age=input2;
		strcpy(groupdiziA[arkaA].name,input3);
		arkaA++;
        }
        else
        {
		//kuyruk dolu demektir
        }
    }
}

void cikar(int inputrepeat, char input2)
{
    for(int m=0;m<inputrepeat;m++){ //bu dongu kac adet musteriye hizmet verilecekse o kadar donuyor ve cikar() calisiyor
        switch(input2){             //burada if else yerine alternatif olarak switch-case kullanildi
            case 'E':
                if(onE==arkaE){     //kuyruk bos ise hizmet etmeye calistigimiz zaman outputa ***** yaziyor
                    groupdiziO[arkaO].age=input2;
                    strcpy(groupdiziO[arkaO].name,"*****");
                    arkaO++;
                }
                else{   //kuyruk bos degil ise kuyrugun onundeki insana dondurma veriliyor ve outputa yaziliyor
                    ekleO(input2,groupdiziE[onE].name);

                    if(onE==arkaE){ //kuyruk bossa on ve arka degerlerini default yapiyoruz
                        onE=0;
                        arkaE=0;
                    }
                    else
                    {
                    onE++; //kuyruk bos degilse onu gosteren degeri artiriyoruz.
                    }
                }
                kaydir(input2); //ilgili kuyrukta cikarma islemi yapinca kaymayi engellemek icin bastaki hale donduruyoruz
            break;

            case 'C':
                if(onC==arkaC){
                    groupdiziO[arkaO].age=input2;
                    strcpy(groupdiziO[arkaO].name,"*****");
                    arkaO++;

                }
                else{
                    ekleO(input2,groupdiziC[onC].name);
                    if(onC==arkaC){
                        onC=0;
                        arkaC=0;
                    }
                    else{
                    onC++;
                    }
                }
                kaydir(input2);
            break;

            case 'A':
                if(onA==arkaA){
                    groupdiziO[arkaO].age=input2;
                    strcpy(groupdiziO[arkaO].name,"*****");
                    arkaO++;

                }
                else{
                    ekleO(input2,groupdiziA[onA].name);
                    if(onA==arkaA){
                        onA=0;
                        arkaA=0;
                    }
                    else{
                    onA++;
                    }
                }
                kaydir(input2);
            break;
        }
    }
}

void ekleO(char input2, char *name)         //input3le aldigimiz kisi ismi name olarak geldi
{
    if(arkaO < ALLSIZE-1){                  //output kuyruguna eleman eklerken kullanilan fonksiyon
	    groupdiziO[arkaO].age=input2;       //strcpy kullanilmasinin nedeni ismin char dizisi olmasi ancak boyle ataniyor
		strcpy(groupdiziO[arkaO].name,name);
		arkaO++;                            //arka deger artti ki bir sonraki eleman bi arkasina eklensin
	}
	else
	{
		//Output listesi doldu demektir
	}
}

void kaydir(char input2){
                            //kuyruktan cikarma yapildiktan sonra kuyrugu toparlama fonksiyonu
    switch(input2){
        case 'E':
            if(onE!=0){
                for (int i=0; i<SIZE; i++){
                    groupdiziE[i].age=groupdiziE[i+onE].age;
                    strcpy(groupdiziE[i].name,groupdiziE[i+onE].name);
                }              //onemli bolum, kuyrugun on elemanindan itibaren elemanlar basa gelene kadar
            arkaE-=onE;        //kaydiriliyor, sonra da arka elman yerine oturuyor
            onE=0;
        }
        break;

        case 'C':
            if(onC!=0){
                for (int i=0; i<SIZE; i++){
                    groupdiziC[i].age=groupdiziC[i+onC].age;
                    strcpy(groupdiziC[i].name,groupdiziC[i+onC].name);
                }
            arkaC-=onC;
            onC=0;
        }
        break;

        case 'A':
            if(onA!=0){
                for (int i=0; i<SIZE; i++){
                    groupdiziA[i].age=groupdiziA[i+onA].age;
                    strcpy(groupdiziA[i].name,groupdiziA[i+onA].name);
                }
            arkaA-=onA;
            onA=0;
        }
        break;
    }
}
