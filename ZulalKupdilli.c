#include <stdio.h>
#include <string.h> 

void menu();
void ekle();
void listele();
void temizle();
int sayiAl(char *mesaj);

int main() {
    int secim;

    while (1) {
        menu();
        printf("Seciminiz: ");
        if (scanf("%d", &secim) != 1) { 
            printf("Hata! Sadece rakam girin.\n");
            return 1; 
        }

        if (secim == 1) ekle();
        else if (secim == 2) listele();
        else if (secim == 3) temizle();
        else if (secim == 0) {
            printf("Programdan cikildi.\n");
            break;
        } else printf("Gecersiz secim!\n");
    }

    return 0;
}

void menu() {
    printf("\n--- OTEL YONETIM ---\n");
    printf("1. Yeni Kayit\n");
    printf("2. Listele\n");
    printf("3. Verileri Sil\n");
    printf("0. Cikis\n");
}

int sayiAl(char *mesaj) {
    int sayi;
    printf("%s", mesaj);
    scanf("%d", &sayi);
    return sayi;
}

void ekle() {
    int odaNo, yas, gece, puan;
    char ad[50], kat[20];
    float ucret;
    FILE *f = fopen("otel.txt", "a");

    if (f == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    odaNo = sayiAl("Oda No (1-500): ");

    printf("Ad: ");
    scanf("%s", ad); 

    yas = sayiAl("Yas: ");
    gece = sayiAl("Kalacak Gece: ");
    puan = sayiAl("Puan (1-5): ");

    if (yas < 18) strcpy(kat, "Cocuk");
    else strcpy(kat, "Yetiskin");

    ucret = gece * 500.0;
    fprintf(f, "%d\t%s\t%d\t%s\t%d\t%d\t%.2f\n", odaNo, ad, yas, kat, gece, puan, ucret);
    fclose(f);
    printf("Kayit basarili.\n");
}

void listele() {
    int odaNo, yas, gece, puan, sayac = 0, toplamPuan = 0;
    char ad[50], kat[20];
    float ucret, toplamGelir = 0;
    FILE *f = fopen("otel.txt", "r");

    if (f == NULL) {
        printf("Kayit bulunamadi.\n");
        return;
    }

    printf("\nODA\tAD\tKAT\tPUAN\tUCRET\n");
    printf("--------------------------------------------\n");

    while (fscanf(f, "%d\t%s\t%d\t%s\t%d\t%d\t%f\n", &odaNo, ad, &yas, kat, &gece, &puan, &ucret) == 7) {
        printf("%d\t%s\t%s\t%d\t%.2f\n", odaNo, ad, kat, puan, ucret);
        toplamGelir += ucret;
        toplamPuan += puan;
        sayac++;
    }

    if (sayac > 0) {
        printf("--------------------------------------------\n");
        printf("Musteri Sayisi: %d\n", sayac);
        printf("Toplam Gelir: %.2f TL\n", toplamGelir);
        printf("Puan Ortalamasi: %.1f\n", (float)toplamPuan / sayac);
    }

    fclose(f);
}

void temizle() {
    char onay;
    printf("Tum veriler silinsin mi? (e/h): ");
    scanf(" %c", &onay);

    if (onay == 'e') {
        FILE *f = fopen("otel.txt", "w");
        if (f != NULL) {
            fclose(f);
            printf("Veriler temizlendi.\n");
        }
    }
}