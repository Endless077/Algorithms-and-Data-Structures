
#include <iostream>

using namespace std;


struct Studente {

  ulong Id = 0;
  string Matricola = "N86000000";
  string Cognome = "";
  string Nome = "";

  // Studente() = default;
  // Studente(ulong idx, string mat, string cog, string nom) {
  //   Id = idx; Matricola = mat; Cognome = cog; Nome = nom;
  //   // Id++; Matricola += "XYZ";
  // }

};


// enum class Colore { Bianco, Grigio, Nero }; // Enumeration a la C++
// enum class Colore1 { Bianco, Rosso };
//
// enum Colore2 { Rosso, Giallo, Verde }; // Enumeration a la C
// enum Colore3 { Marrone, Azzurro };
// // enum Colore3 { Rosso, Marrone }; // Error: duplicated value!


int main() {

  // Slide 1

  Studente stu;

  cout << "Id: " << stu.Id << endl;
  cout << "Matricola: " << stu.Matricola << endl;
  cout << "Cognome: " << stu.Cognome << endl;
  cout << "Nome: " << stu.Nome << endl;

  stu.Id = 1;
  stu.Matricola = "N86000001";
  stu.Cognome = "Turing";
  stu.Nome = "Alan";

  cout << "Id: " << stu.Id << endl;
  cout << "Matricola: " << stu.Matricola << endl;
  cout << "Cognome: " << stu.Cognome << endl;
  cout << "Nome: " << stu.Nome << endl;

  // Studente stu1{2, "N86000002", "Gödel"};
  // // Studente stu1 = {2, "N86000002", "Gödel", "Kurt"}; // Equivalente definition
  //
  // cout << "Id: " << stu1.Id << endl;
  // cout << "Matricola: " << stu1.Matricola << endl;
  // cout << "Cognome: " << stu1.Cognome << endl;
  // cout << "Nome: " << stu1.Nome << endl;

  // Studente stu2(3, "N86000003", "Church", "Alonzo");
  //
  // cout << "Id: " << stu2.Id << endl;
  // cout << "Matricola: " << stu2.Matricola << endl;
  // cout << "Cognome: " << stu2.Cognome << endl;
  // cout << "Nome: " << stu2.Nome << endl;

  // // Slide 2
  //
  // Colore color = Colore::Grigio;
  //
  // cout << (color < Colore::Nero) << endl;
  // cout << (color == Colore::Bianco) << endl;
  // // cout << (Colore::Bianco == Colore1::Bianco) << endl;
  //
  // Colore1 color1 = Colore1::Rosso;
  // // Colore1 color1 = Colore::Bianco;
  //
  // Colore2 color2 = Giallo;
  // // Colore2 color2 = Azzurro;

  return 0;
}
