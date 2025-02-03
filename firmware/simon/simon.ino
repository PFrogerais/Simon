/*
Projet : Simon 
DATE : 03/02/2025

╔═╗  ╔═╗╦═╗╔═╗╔═╗╔═╗╦═╗╔═╗╦╔═╗
╠═╝  ╠╣ ╠╦╝║ ║║ ╦║╣ ╠╦╝╠═╣║╚═╗
╩    ╚  ╩╚═╚═╝╚═╝╚═╝╩╚═╩ ╩╩╚═╝

L'objectif de ce programme est de reproduire le comportement du jeu SIMON,
4 LEDs et 4 BP Associes et un Buzzer 


*/



// Definitions des broches connectees aux LED
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;

// Definition des broche connectees aux BP
const int BP1 = 6;
const int BP2 = 7;
const int BP3 = 8;
const int BP4 = 9;

const int BUZZ = 10;

int melody[100] = {0};
int son[] = {230, 300, 400, 500};
int k = 0;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(BP1, INPUT);
  pinMode(BP2, INPUT);
  pinMode(BP3, INPUT);
  pinMode(BP4, INPUT);

  pinMode(BUZZ,OUTPUT);

  Serial.begin(9600);
}

// Ajoute une nouvelle note aleatoirement a la melody

void Ajouter_Note()
{
   int n = random(2,6); // Correspond aux LEDS
   melody[k] = n;
   k++;
}

// Le jeu Joue la melodie et led LEDs associees
//
void Simon_Play(void)
{
   for (int i=0; i<k; i++)
   {
      digitalWrite(melody[i],HIGH);
      Serial.print(son[melody[i]-2]);
      tone(BUZZ, son[melody[i]-2]); 
      delay(300);
      noTone(BUZZ);
      Eteindre_LED();
      delay(200);
   }
}

// Sequence de fin lorsque le joueur perd
//
void GameOver(void)
{
  for(int i = 0; i<4; i++)
  {
    Allumer_LED();
    tone(BUZZ,son[i]);
    delay(100);
    Eteindre_LED();
    noTone(BUZZ);
    delay(100);
  }
}
// Fonction loop() 
void loop()
{
  Ajouter_Note();
  Simon_Play();
  for (int i=0; i<k; i++)
  {
      int bouton_saisi = Scan_Boutons();
      if (bouton_saisi != melody[i]-1)
      {
         Serial.println("Game Over");
         GameOver();
         delay(2000);
         k=0;
      }
   delay(1000);
  }
  //
  delay(200);
  //Serial.println(bouton_saisi);
}

// Fonction permettant l'extinction de toutes les LEDs
void Eteindre_LED(void)
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

// Fonction permettant d'allumer toutes les LEDS
void Allumer_LED(void)
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}

// Fonction Bouton_Test(BP, LED) renvoie
// 1 si Appui et allume la LED associee
// 0 sinon
int Bouton_Test(int BP, int LED)
{
    int etat_bouton = digitalRead(BP);
    delay(20);
    if(etat_bouton == 1)
    {
      tone(BUZZ,son[LED-2]);
      digitalWrite(LED,HIGH);
      while(etat_bouton==1)
      {
        etat_bouton = digitalRead(BP);
        delay(10);
      }
      return 1;
    }
    else
    {
      return 0;
    }
}

// Fonction verifiant quel bouton est appuye
// Renvoie 1 -> BP1, 2-> BP2 ...
int Scan_Boutons(void)
{
  int bouton_saisi = 0;
  while(bouton_saisi == 0)
  {
    int etat_bouton = Bouton_Test(BP1,LED1);
    if(etat_bouton == 1)
    {
      bouton_saisi = 1;
    }
    if(Bouton_Test(BP2,LED2)) // Ecriture plus condensee
    {
      bouton_saisi = 2;
    }
    if(Bouton_Test(BP3,LED3))
    {
      bouton_saisi = 3;
    }
    if(Bouton_Test(BP4,LED4))
    {
      bouton_saisi = 4;
    }
  }
  noTone(BUZZ);
  Eteindre_LED();
  return bouton_saisi;
}

