
#include <iostream>

using namespace std;


struct Studente {

  ulong Id = 0;
  string Matricola = "N86000000";
  string Cognome = "";
  string Nome = "";

  // friend ostream& operator<<(ostream& outstr, const Studente& stu);

  // friend istream& operator>>(istream& instr, Studente& stu);

// private:

  // ulong SecureNum = 0x25242310;

};

ostream& operator<<(ostream& outstr, const Studente& stu) {
  outstr << "Id: " << stu.Id << "; Matricola: " << stu.Matricola //
    << "; Cognome: " << stu.Cognome << "; Nome: " << stu.Nome;
  // outstr << "; Numero di sicurezza: " << stu.SecureNum;
  return outstr;
}

istream& operator>>(istream& instr, Studente& stu) {
  instr >> stu.Id >> stu.Matricola >> stu.Cognome >> stu.Nome;
  // instr >> stu.SecureNum;
  return instr;
}

enum class Color { Giallo, Verde, Bianco, Rosso };

ostream& operator<<(ostream& outstr, const Color& clr) {
  switch(clr) {
    case Color::Verde:
      outstr << "Green";
      break;
    case Color::Bianco:
      outstr << "White";
      break;
    case Color::Rosso:
      outstr << "Red";
      break;
    default:
      outstr << "Color{ " << int(clr) << " }";
  }
  return outstr;
}


int main() {

  Studente stu1{1, "N86000001", "Alan", "Turing"};

  cout << "Id: " << stu1.Id << endl;
  cout << "Matricola: " << stu1.Matricola << endl;
  cout << "Cognome: " << stu1.Cognome << endl;
  cout << "Nome: " << stu1.Nome << endl;

  Studente stu2{2, "N86000002", "Gödel", "Kurt"};

  cout << "Id: " << stu2.Id << endl;
  cout << "Matricola: " << stu2.Matricola << endl;
  cout << "Cognome: " << stu2.Cognome << endl;
  cout << "Nome: " << stu2.Nome << endl;

  // cout << stu1 << endl;
  // cout << stu2 << endl;

  // Studente stu3;
  // cin >> stu3;
  // cout << stu3 << endl;

  // Studente stu;
  // cout << stu << endl;
  // cin >> stu;
  // cout << stu << endl;

  // Color clr = Color::Bianco;
  // cout << clr << endl;
  // clr = Color::Giallo;
  // cout << clr << endl;

  return 0;
}
