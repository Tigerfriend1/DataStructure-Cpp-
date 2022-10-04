//소스 코드2.5: Polynomial 클래스
// template으로 구현하고 +, -, *, <<, >> operator를 사용한 버젼으로 구현한다.

#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;

template <class T> class Polynomial;

template <class T>
class Term // Term 정의 / coef와 exp를 가짐
{
public:
  friend Polynomial<T>;
  T coef;
  int exp;
};

template <class T> class Polynomial {
public:
  Polynomial();
  // + 연산자
  Polynomial operator+(const Polynomial &p) const {
    Polynomial c;
    int aPos = start, bPos = p.start;
    c.start = free;
    while ((aPos <= finish) && (bPos <= p.finish)) {
      if (termArray[aPos].exp == p.termArray[bPos].exp) {
        float t = termArray[aPos].coef + p.termArray[bPos].coef;
        if (t)
          c.NewTerm(t, termArray[aPos].exp);
        aPos++;
        bPos++;
      } else if ((termArray[aPos].exp < p.termArray[bPos].exp)) {
        c.NewTerm(p.termArray[bPos].coef, p.termArray[bPos].exp);
        bPos++;
      } else {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        aPos++;
      }
    }
    for (; aPos <= finish; aPos++)
      c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos <= p.finish; bPos++)
      c.NewTerm(p.termArray[bPos].coef, p.termArray[bPos].exp);
    c.finish = free - 1;
    return c;
  }
  // - 연산자
  Polynomial operator-(const Polynomial &p) const {
    Polynomial c;
    int aPos = start, bPos = p.start;
    c.start = free;
    while ((aPos <= finish) && (bPos <= p.finish)) {
      if (termArray[aPos].exp == p.termArray[bPos].exp) {
        float t = termArray[aPos].coef - p.termArray[bPos].coef;
        if (t)
          c.NewTerm(t, termArray[aPos].exp);
        aPos++;
        bPos++;
      } else if ((termArray[aPos].exp < p.termArray[bPos].exp)) {
        c.NewTerm(-1 * p.termArray[bPos].coef, p.termArray[bPos].exp);
        bPos++;
      } else {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        aPos++;
      }
    }
    for (; aPos <= finish; aPos++)
      c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos <= p.finish; bPos++)
      c.NewTerm(-1 * p.termArray[bPos].coef, p.termArray[bPos].exp);
    c.finish = free - 1;
    return c;
  }

  // * 연산자
  Polynomial operator*(const Polynomial &p) const {
    Polynomial c;
    int aPos = start, bPos = p.start;
    c.start = free;
    for (int i = aPos; i <= finish; i++) {
      for (int j = bPos; j <= p.finish; j++) {
        float coef = termArray[i].coef * p.termArray[j].coef;
        float exp = termArray[i].exp + p.termArray[j].exp;
        if (coef)
          c.NewTerm(coef, exp);
      }
    }
    c.finish = free - 1;
    return c;
  }
  T Eval(int f) {
    int result = 0;
    int value = 0;
    for (int i = start; i <= finish; i++) {
      value = termArray[i].coef * pow(f, termArray[i].exp);
      result += value;
    }
    return result;
  }

  void NewTerm(const float theCoeff,
               const int theExp); //새로운 공간을 할당받거나 늘리는 함수

  friend ostream &operator<<(ostream &, const Polynomial<T> &);
  friend istream &operator>>(istream &, const Polynomial<T> &);

  static Term<T> *termArray;
  static int capacity;
  static int free;
  int start, finish;
  int terms;
};

template <class T>
Polynomial<T>::Polynomial() : start{-1}, finish{-1}, terms{0} {}

template <class T>
void Polynomial<T>::NewTerm(const float theCoeff, const int theExp) {
  if (terms == capacity) {
    capacity *= 2;
    Term<T> *temp = new Term<T>[capacity];
    copy(termArray, termArray + free, temp);
    delete[] termArray;
    termArray = temp;
  }
  termArray[free].coef = theCoeff;
  termArray[free++].exp = theExp;
}

// cin 연산자
template <class T>
istream &operator>>(istream &is,
                    Polynomial<T> &p) { // degree만 입력받아 난수를 생성하여
  int i, degree;
  float coef;
  int expo;
  cout << "Enter Degree Of Polynomial:";
  is >> degree;
  p.start = p.free;
  // coef를 난수를 입력받아 사용하고 화면에서 입력받지 않는 버젼으로수정한다.
  for (i = degree; i >= 0; i--) {
    coef = rand() % 10;
    expo = i;
    // cout << "coefficient of is " << coef << "\n";
    // cout << "exponent of x^ is " << i << "\n";
    p.NewTerm(coef, expo);
  }
  p.finish = p.free - 1;
  p.terms = p.finish - p.start + 1;
  return is; // degree값차식의 내림차순.
}

// cout 연산자
template <class T> ostream &operator<<(ostream &os, Polynomial<T> &p) {
  // istream ostream은 cin, cout을 하기 위한 객체다! 참고하자.
  // p.start, p.finish로 표현하자 Display와 차이점은 display는
  // this(P1임).start인데, ostream안에서는 p로 다룸.
  int aPos = p.start;
  for (; aPos <= p.finish; aPos++) {
    os << p.termArray[aPos].coef << "x^" << p.termArray[aPos].exp;
    if ((aPos - p.finish) != 0)
      cout << " + ";
  }
  return os;
}

template <class T> int Polynomial<T>::capacity = 100;

template <class T> Term<T> *Polynomial<T>::termArray = new Term<T>[ 100 ];

template <class T> int Polynomial<T>::free = 0;

int main(void) {
  int choice;
  Polynomial<int> P1, P2, P3, P4;

  cin >> P1;
  cin >> P2;
  cin >> P3;

  while (1) {
    cout << "\n****** Menu Selection ******" << endl;
    cout << "1: Addition\n2: Substraction\n3: Multiplication\n4: Eval\n0: Exit"
         << endl;
    cout << "Enter your choice:";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "\n--------------- Addition ---------------\n";
      cout << "\nPolynomial1:\n";
      cout << P1;
      cout << "\nPolynomial2:\n";
      cout << P2;
      cout << "\nPolynomial3:\n";
      cout << P3;
      cout << "\nPolynomial 1 + Polynomial 2 + Polynomial 3 : \n";
      P4 = P1 + P2 + P3;
      cout << P4;
      cout << "\n----------------------------------------\n";
      break;
    case 2:
      cout << "\n------------- Substraction -------------\n";
      cout << "\nPolynomial1:\n";
      cout << P1;
      cout << "\nPolynomial2:\n";
      cout << P2;
      cout << "\nPolynomial1 - Polynomial2 : \n";
      P4 = P1 - P2;
      cout << P4;
      cout << "\n----------------------------------------\n";
      break;
    case 3:
      cout << "\n----------- Multiplication -------------\n";
      cout << "\nPolynomial1:\n";
      cout << P1;
      cout << "\nPolynomial2:\n";
      cout << P2;
      cout << "\nPolynomial1 X Polynomial2 : \n";
      P4 = P1 * P2;
      cout << P4;
      cout << "\n----------------------------------------\n";
      break;
    case 4:
      cout << "정수를 입력하세요 : ";
      int input, eval;
      cin >> input;
      eval = P2.Eval(input); //학생 구현 실습 대상
      cout << eval;
      cout << "\n----------------------------------------\n";
      break;
    case 0:
      cout << "Good Bye…!!!" << endl;
      exit(0);
    }
  }
  return 0;
}