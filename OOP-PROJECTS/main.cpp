#include<iostream>
using namespace std;
class Numar_Complex {
	float re;
	float im;
public:
	Numar_Complex();
	Numar_Complex(float real, float imaginar); //constructor 
	Numar_Complex& operator=(const Numar_Complex& z); //supraincarcare operator =
	friend ostream& operator<< (ostream& out, const Numar_Complex& z); // supraincarcare operator de afisare nr complex
	friend istream& operator >> (istream& in, Numar_Complex& z); // supraincarcare operator de citire nr complex
	Numar_Complex& operator+(const Numar_Complex& z); //supraincarcare operator + pentru 2 nr complexe
	Numar_Complex& operator*(const Numar_Complex& z); //supraincarcare operator * pentru 2 nr complexe
	friend class Matrice_Complexa; //Matrice_Complexa este prietana Nr_Complex pt a putea accesa zona private(operatia nu e reflexiva)
};
Numar_Complex::Numar_Complex()
{
}
Numar_Complex::Numar_Complex(float real, float imaginar)
{
	//constructor pentru atribuirea partii reale si imaginare
	re = real;
	im = imaginar;
}
ostream& operator << (ostream& out, const Numar_Complex& z)
{
	//supraincarcam afisarea
	out << z.re;
	if (z.im >= 0)
		out << "+" << z.im << "*i";
	else
		out << z.im << "*i";
	return out;
}
istream& operator >> (istream& in, Numar_Complex& z)
{
	//supraincarcam citirea
	cout << "Real:";
	in >> z.re;
	cout << "Imaginar:";
	in >> z.im;
	cout << '\n';
	return in;
}
Numar_Complex& Numar_Complex:: operator+(const Numar_Complex& z)
{
	//supraincarcam adunarea a 2 nr complexe
	Numar_Complex* res = new Numar_Complex();
	res->re = this->re + z.re;
	res->im = this->im + z.im;
	return *res;
}
Numar_Complex& Numar_Complex:: operator*(const Numar_Complex& z)
{
	//supraincarcam inmultirea a 2 nr complexe
	Numar_Complex* res = new Numar_Complex();
	res->re = this->re * z.re - this->im * z.im;
	res->im = this->re * z.im + this->im * z.re;
	return *res;
}
Numar_Complex& Numar_Complex:: operator=(const Numar_Complex& z)
{
	//supraincarcam atribuirea 
	if (this != &z) {
		this->re = z.re;
		this->im = z.im;
	}
	return *this;
}
class Matrice_Complexa {
	Numar_Complex** m;
	int nrl;
	int nrc;
public:
	Matrice_Complexa();
	Matrice_Complexa(Numar_Complex x, int linii, int coloane); //init-constructor #2, cerinta 3
	Matrice_Complexa(int linii, int coloane); //init constructor
	Matrice_Complexa(const Matrice_Complexa& m2); //copy constructor
	Matrice_Complexa& operator+(const Matrice_Complexa& m2); // supraincarcare operator + pe 2 matrici
	Matrice_Complexa& operator*(const Matrice_Complexa& m2); // supraincarcare operator * pe 2 matrici
	friend istream& operator>>(istream& in, Matrice_Complexa& m2); // supraincarcare citire matrice 
	friend ostream& operator<< (ostream& out, const Matrice_Complexa& m2); // supraincarcare afisare matrice
	~Matrice_Complexa(); // destructor
	int getnrl(); // get-er de nr linii
	int getcol(); // get-er de nr coloane
	friend bool verifadunare(Matrice_Complexa& m, Matrice_Complexa& m1); // verificare daca adunarea a 2 matrici se poate realiza
	friend bool verifinmultire(Matrice_Complexa& m, Matrice_Complexa& m1); // verificare daca inmultirea a 2 matrici se poate realiza
};
int Matrice_Complexa::getnrl()
{
	return this->nrl;
}
int Matrice_Complexa::getcol()
{
	return this->nrc;
}
bool verifadunare(Matrice_Complexa& m, Matrice_Complexa& m1)
{
	//adunarea se poate realiza daca nr de linii din cele 2 matrici este egal, la fel pentru nr de coloane
	if (m.getnrl() == m1.getnrl() && m.getcol() == m1.getcol())
		return 1;
	else
		return 0;
}
bool verifinmultire(Matrice_Complexa& m, Matrice_Complexa& m1)
{
	// inmultirea se poate realiza daca nr de coloane ale matricii din partea stanga a operatorului * este egal cu nr de linii al matricii din partea dreapta a operatorului *
	if (m.getcol() == m1.getnrl())
		return 1;
	else
		return 0;
}
Matrice_Complexa::Matrice_Complexa()
{
}
Matrice_Complexa::Matrice_Complexa(int linii, int coloane)
{
	// constructor initializare cu nr lin nr col
	m = new Numar_Complex * [linii];
	for (int i = 0; i < linii; i++)
	{
		m[i] = new Numar_Complex[coloane];
	}
	nrl = linii;
	nrc = coloane;
};

istream& operator>>(istream& in, Matrice_Complexa& m2)
{
	int nrlinii, nrcoloane;
	cout << "Matrice noua\n";
	cout << "Numarul de linii ale matricii: ";
	cin >> nrlinii;
	cout << "Numarul de coloane ale matricii ";
	cin >> nrcoloane;
	m2.nrl = nrlinii;
	m2.nrc = nrcoloane;
	m2.m = new Numar_Complex * [nrlinii];
	for (int i = 0; i < nrlinii; i++)
	{
		m2.m[i] = new Numar_Complex[nrcoloane];
	}
	//supraincarcare >> in functie de operatorul >> de la Numar_Complex
	cout << '\n';
	cout << "Atribuire valori matrice" << '\n';
	Numar_Complex a;
	for (int i = 0; i < m2.nrl; i++)
	{
		for (int j = 0; j < m2.nrc; j++)
		{
			cout << "Linia " << i << " " << "Coloana " << j << '\n';
			in >> a;
			m2.m[i][j] = a;
		}
	}
	return in;
}
ostream& operator<<(ostream& out, const Matrice_Complexa& m2)
{
	//supraincarcare << in functie de operatorul << de la Numar_Complex
	for (int i = 0; i < m2.nrl; i++)
	{
		for (int j = 0; j < m2.nrc; j++)
			out << m2.m[i][j] << " ";
		out << '\n';
	}
	return out;
};
Matrice_Complexa::Matrice_Complexa(const Matrice_Complexa& m2)
{
	//copy-constructor
	m = new Numar_Complex * [m2.nrl];
	for (int i = 0; i < m2.nrl; i++)
	{
		m[i] = new Numar_Complex[m2.nrc];
	}
	for (int i = 0; i < m2.nrl; i++)
		for (int j = 0; j < m2.nrc; j++)
		{
			Numar_Complex* nc = new Numar_Complex(m2.m[i][j]);
			m[i][j] = *nc;
		}
	nrl = m2.nrl;
	nrc = m2.nrc;
};

Matrice_Complexa::Matrice_Complexa(Numar_Complex x, int linii, int coloane)
{
	//constructor care primeste nr linii, nr coloane, un nr si il atribuie tuturor elementelor matricii
	m = new Numar_Complex * [linii];
	for (int i = 0; i < linii; i++)
	{
		m[i] = new Numar_Complex[coloane];
	}
	nrl = linii;
	nrc = coloane;
	for (int i = 0; i < nrl; i++)
	{
		for (int j = 0; j < nrc; j++)
			m[i][j] = x;
	}
}
Matrice_Complexa& Matrice_Complexa::operator+(const Matrice_Complexa& m2)
{
	//supraincarcarea operatorului + in functie de operatorul + de la Numar_Complex
	cout << '\n';
	cout << "Adunarea celor doua matrici este:" << '\n';
	Numar_Complex a(0, 0);
	if (this->nrl == m2.nrl && this->nrc == m2.nrc)
	{
		Matrice_Complexa* msuma = new Matrice_Complexa(a, this->nrl, this->nrc);
		for (int i = 0; i < m2.nrl; i++)
		{
			for (int j = 0; j < m2.nrc; j++)
			{
				msuma->m[i][j] = this->m[i][j] + m2.m[i][j];
			}
		}
		return *msuma;
	}
	else
	{
		cout << "NU SE POATE EFECTUA ADUNAREA" << '\n';
		Matrice_Complexa* msuma = new Matrice_Complexa(a, 0, 0);
		return *msuma;
	}
}
Matrice_Complexa& Matrice_Complexa::operator*(const Matrice_Complexa& m2)
{
	//supraincarcarea operatorului * in functie de operatorul * de la Numar_Complex
	cout << '\n';
	cout << "Inmultirea celor doua matrici este:" << '\n';
	Numar_Complex a(0, 0);
	if (this->nrc == m2.nrl)
	{
		Matrice_Complexa* msuma = new Matrice_Complexa(a, this->nrl, m2.nrc);
		for (int i = 0; i < this->nrl; i++)
		{
			for (int j = 0; j < m2.nrc; j++)
			{
				for (int k = 0; k < m2.nrl; k++)
				{

					msuma->m[i][j] = msuma->m[i][j] + this->m[i][k] * m2.m[k][j];
				}
			}
		}
		return *msuma;
	}
	else
	{
		cout << "NU SE POATE EFECTUA INMULTIREA" << '\n';
		Matrice_Complexa* msuma = new Matrice_Complexa(a, 0, 0);
		return *msuma;
	}
}
Matrice_Complexa::~Matrice_Complexa()
{
	//destructor, care dezaloca matricea alocata dinamic
	delete[] m;
}
int main()
{
	int n;
	cin >> n;
	Matrice_Complexa* v = new Matrice_Complexa[n]; //alocam dinamic un vector de tip Matrice_Complexa
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];//memoram
	}
	cout << '\n';
	cout << "Afisarea matriciilor: " << '\n';
	for (int i = 0; i < n; i++)
	{
		cout << "Matricea de pe pozitia" << " " << i << '\n';
		cout << v[i] << '\n';  //afisam 
	}
	delete[] v;
	return 0;
}
/* solutia a fost testata pentru urmatoarele 2 matrici, fiind verificata dupa rezultatul obtinut "pe hartie":
Fie A(3linii,3coloane):
|1+2*i 3+2*i 1+2*i|
|2+3*i 1+2*i 2+2*i|
|2+1*i 1+2*i 1+2*i|

Fie B(3linii,3coloane):
|3+4*i 2+5*i 5+3*i|
|4+3*i 4+4*i 6+5*i|
|4+3*i 2+1*i 2+3*i|
*/
