#include <iostream>
#include <cstring>

///Bratosin David - Robert
///Informatica ID, grupa 2, Anul I
///Proiect matrici dreptunghiulare generice
template <typename T>
class Matrix
{
    private:
        size_t rowSize,colSize;
        T* data;

    public:
        /**
         * @brief Construieste o matrice cu dimensiuniile specificate.
         * Matricea construita nu va contine elemente (vid)
         * @param _rowSize numarul de linii
         * @param _colSize numarul de coloane
         */
        Matrix(size_t _rowSize, size_t _colSize)
        {
            ///Verificare daca matricea are dimensiunile corecte precizate.
            if(_rowSize >= 1 && _colSize >= 1)
            {
                ///Realizam alocarea dinamica asupra pointerului ce va retine adresele de memorie a elementelor stocate
                this->data = new T[_rowSize*_colSize];

                this->rowSize = _rowSize;
                this->colSize = _colSize;
            }
            else
            {
                this->rowSize = 0;
                this->colSize = 0;
                this->data = NULL;
            }
        }


        /**
         * @brief Constructor vid pentru clasa matricelor
         * Nu se va realiza nicio alocare dinamica asupra acesteia
         * Pentru alocare la initializare: folosirea operatorului de atribuire
         */
        Matrix()
        {
            data = NULL;

            this->rowSize = 0;
            this->colSize = 0;
        }

        /**
         * @brief Constructor de copiere
         * Realizarea alocarea dinamica si copiaza datele din matricea precizata ca parametru
         * @param copy Matricea din care se doreste a se copia datele
         */
        Matrix(const Matrix<T> &copy)
        {
            ///Alocam memorie in pointer-ul data
            this->data = new T[copy.rowSize*copy.colSize];
            ///Realizam copierea folosind functia copy din colectia de clase standard C++
            std::copy(copy.data,copy.data + copy.rowSize*copy.colSize,this->data);

            this->rowSize = copy.rowSize;
            this->colSize = copy.colSize;
        }

        /**
         * @brief
         * Conversie de la un obiect de tipul neprecizat dat la o matrice cu 1 linie şi 1 coloana.
         * @param var tip generic
         */
        Matrix(const T &var)
        {
            this->data = new T[1 * 1];
            *(this->data) = var;

            this->rowSize = 1;
            this->colSize = 1;
        }


        /**
         * @brief Destructorul matricii.
         * Elibereaza zona de memorie ocupata de elementele matricii
         */

        ~Matrix()
        {
            if(this->data != NULL)
                delete[] this->data;
        }

        /**
         * @brief
         * Supraincarcarea operatorului [] pentru indexare.
         * @param index linia ce se doreste a fi accesata
         * @return T* pointer la inceputul liniei al carei numar este parametru, numarandu-se incepand cu 0
         */
        T* operator[](int index)
        {
            return this->data + index * colSize;
        }

        /**
         * @brief Supraincarcarea operatorului de atribuire
         *
         * @param rhs Matricea folosita la atribuire
         * @return Matrix<T>& Matricea atribuita
         */
        Matrix<T>& operator= (const Matrix<T> &rhs)
        {
            ///Verificare pentru self-assignment (atribuire identica)
            ///Acest lucru poate duce catre un crash datorita eliberarii memoriei la atribuire
            if(this == &rhs)
                return *this;

            ///Prevenim dubla alocare a memoriei cu acest pointer
            int* tempCopy = new T[rhs.rowSize * rhs.colSize];
            std::copy(rhs.data,rhs.data + rhs.rowSize * rhs.colSize, tempCopy);

            ///Stergerea se va realiza doar daca matricea deja are elemente
            if(this->data != NULL)
                delete[] this->data;

            ///Pointer-ul temporar este transferat propietatii obiectului
            this->data = tempCopy;

            this->rowSize = rhs.rowSize;
            this->colSize = rhs.colSize;

            ///Pointerul tempCopy aici va fi eliberat automat
            return *this;
        }

         /**
         * @brief Preia stream-ul de citire pentru a salva elementele in matrice
         * @param is - stream de citire din STL
         * @param inputVar - variabila din care se citeste
         * @return std::istream&
         */
        friend std::istream& operator>>(std::istream& is, const Matrix<T>&inputVar)
        {
            for(size_t i = 0; i<inputVar.rowSize; i++)
                for(size_t j = 0; j<inputVar.colSize; j++)
                    is>>*(inputVar.data+i*inputVar.colSize+j);

            return is;
        }

        /**
         * @brief Afiseaza output-ul elementelor din matrice folosind orice stream de OUTPUT
         * @param os - stream de iesire
         * @param outputVar - variabila din care se aafiseaza
         * @return std::ostream& - returneaza stream-ul de afisare (OUTPUT)
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>&outputVar)
        {
            for(size_t i = 0; i<outputVar.rowSize; i++)
            {
                for(size_t j = 0; j<outputVar.colSize; j++)
                    os<<*(outputVar.data+i*outputVar.colSize+j)<<" ";
                os<<'\n';
            }

            return os;
        }

        /**
         * @brief Operatorul unar de +
         * Returneaza matricea pur si simplu deoarece semnul +
         * nu va schimba semnul elementelor matricii
         * @return Matrix<T> - matricea careia ii se aplica semnul
         */
        Matrix<T>& operator+()
        {
            return *this;
        }

        /**
         * @brief Operatorul unar de -
         * Fiecare element este inmultit cu -1 conform regulii matematice
         * @return Matrix<T> - matricea careia ii se aplica semnul
         */
        Matrix<T>& operator-()
        {
            for(size_t i = 0; i<this->rowSize; i++)
                for(size_t j = 0; j<this->colSize; j++)
                    *(this->data+i*this->colSize+j) *= (-1);

            return *this;
        }

        /**
         * @brief 
         * Functie ce verifica daca 2 matrici sunt egale
         * @param rhs - parametrul dreapta al matricii
         * @return true - daca matricea a == matricea b
         * @return false - daca matricea a != matricea b
         */

        bool operator==(const Matrix<T> &rhs)
        {
            ///Verificam mai intai daca marimile matricilor sunt egale
            if(this->rowSize == rhs.rowSize && this->colSize == rhs.colSize)
            {
                ///Verificam daca gasim cel putin un element care nu este identic cu ce se afla in rhs
                for(size_t i = 0; i<this->rowSize; i++)
                    for(size_t j = 0; j<this->colSize; j++)
                        if(*(this->data+i*this->colSize+j) != *(rhs.data+i*rhs.colSize + j))
                            return false;
                ///Daca nu gasim spunem ca avem egalitate
                return true;
            }
            ///Daca nu se indeplineste conditia de egalitate a marimilor, atunci matricile nu sunt egale
            return false;
        }


        /**
         * @brief Supraincarcarea operatorului de adunare (+=) la o matrice cu alta matrice
         * @param rhs - Matricea din dreapta operatorului +=
         * @return Matrix<T> - rezultatul operatiei de adunare
         */
        Matrix<T>& operator+= (const Matrix &rhs)
        {
            ///Liniile si coloanele celor doua matrici trebuie sa fie egale intre ele
            if(this->rowSize == rhs.rowSize && this->colSize == rhs.colSize)
            {
                for(size_t i = 0; i<this->rowSize; i++)
                    for(size_t j = 0; j<this->colSize; j++)
                        *(this->data+i*this->colSize+j) += *(rhs.data+i*rhs.colSize+j);
            }
            ///Daca nu se respecta regula, atunci matricea ramane neschimbata.
            return *this;
        }

        /**
         * @brief Supraincarcarea operatorului de adunare (+=) la o matrice cu un scalar
         * @param rhs - numarul (scalarul) din dreapta operatorului +=
         * @return Matrix<T> - rezultatul operatiei de adunare cu scalarul
         */
        Matrix<T>& operator+= (const T &rhs)
        {
            for(size_t i = 0; i<this->rowSize; i++)
                for(size_t j = 0; j<this->colSize; j++)
                    *(this->data+i*this->colSize+j) += rhs;

            return *this;
        }

        /**
         * @brief
         * Supraincarcarea operatorului de scadere (-=) la o matrice cu alta matrice
         * @param rhs - Matricea din dreapta operatorului -=
         * @return Matrix<T> - rezultatul operatiei de scadere
         */
        Matrix<T>& operator-= (const Matrix &rhs)
        {
            ///Liniile si coloanele celor doua matrici trebuie sa fie egale intre ele
            if(this->rowSize == rhs.rowSize && this->colSize == rhs.colSize)
            {
                for(size_t i = 0; i<this->rowSize; i++)
                    for(size_t j = 0; j<this->colSize; j++)
                        *(this->data+i*this->colSize+j) -= *(rhs.data+i*rhs.colSize+j);


            }
            ///Daca nu se respecta regula, atunci matricea ramane neschimbata.
            return *this;
        }

        /**
         * @brief
         * Supraincarcarea operatorului de scadere (-=) la o matrice cu un scalar
         * @param rhs - numarul (scalarul) din dreapta operatorului -=
         * @return Matrix<T> - rezultatul operatiei de scadere
         */
        Matrix<T>& operator-= (const T &rhs)
        {
            for(size_t i = 0; i<this->rowSize; i++)
                for(size_t j = 0; j<this->colSize; j++)
                    *(this->data+i*this->colSize+j) -= rhs;

            return *this;
        }

        /**
         * @brief
         * Supraincarcarea operatorului de inmultire (*=) la o matrice cu alta matrice
         * @param rhs - matricea din dreapta operatorului *=
         * @return Matrix<T>& - rezultatul operatiei de inmultire
         */
        Matrix<T>& operator*= (const Matrix<T> &rhs)
        {
            ///Regula pt. inmultirea a 2 matrici
            if(this->colSize == rhs.rowSize)
            {
                Matrix rslt(this->rowSize,rhs.colSize);

                for(size_t i = 0; i < this->rowSize; i++)
                    for(size_t j = 0; j<rhs.colSize; j++)
                    {
                        *(rslt.data+i*rslt.colSize+j) = 0;
                        for(size_t k = 0; k < rhs.rowSize; k++)
                            *(rslt.data+i*rslt.colSize+j) += *(this->data+i*this->colSize+j) * *(rhs.data+i*rhs.colSize+j);
                    }

                *this = rslt;

            }

            return *this;
        }

        /**
         * @brief
         * Supraincarcarea operatorului de inmultire (*=) la o matrice cu un scalar
         * @param rhs - scalar
         * @return Matrix<T>& - rezultatul operatiei de inmultire
         */
        Matrix<T>& operator*= (const T &rhs)
        {
            for(size_t i = 0; i<this->rowSize; i++)
                for(size_t j = 0; j<this->colSize; j++)
                    *(this->data+i*this->colSize+j) *= rhs;

            return *this;
        }

        /**
         * @brief Functie de adunare a doua matrici
         * Ne folosim de definitia operatorului unar += de mai sus
         * @param rhs
         * @return const Matrix<T>
         */
        const Matrix<T> operator+(const Matrix<T> &rhs)
        {
            ///Fac o copie a instantei actuale.
            Matrix result(*this);
            result += rhs; //Folosesc definitia de la +=

            return result; ///Rezultatul final
        }

        const Matrix<T> operator+(const T &rhs)
        {
            ///Fac o copie a instantei actuale.
            Matrix result(*this);
            result += rhs; //Folosesc definitia de la +=

            return result; ///Rezultatul final
        }

        const Matrix<T> operator-(const Matrix<T> &rhs)
        {
            Matrix result(*this);
            result -= rhs;

            return result;
        }

        const Matrix<T> operator-(const T &rhs)
        {
            ///Fac o copie a instantei actuale.
            Matrix result(*this);
            result -= rhs; //Folosesc definitia de la +=

            return result; ///Rezultatul final
        }

        const Matrix<T> operator*(const Matrix<T> &rhs)
        {
            Matrix result(*this);
            result *= rhs;

            return result;
        }

        const Matrix<T> operator*(const T &rhs)
        {
            Matrix result(*this);
            result *= rhs;

            return result;
        }

        /**
         * @brief
         * Functie ce calculeaza transpusa unei matrici
         * @return Matrix<T> - matricea transpusa
         */
        Matrix<T> Transpose()
        {
            Matrix<T> tempMatrix (this->colSize, this->rowSize);

            for(int i = 0; i<this->rowSize; i++)
                for(int j = 0; j<this->colSize; j++)
                    *(tempMatrix.data+j*tempMatrix.colSize+i) = *(this->data+i*this->colSize+j);

            return tempMatrix;
        }

        /**
         * @brief
         * Functie ce implementeaza transformarea Hadamard a unei matrici
         * @param rhs
         * @return Matrix<T>
         */
        Matrix<T> Hadamard(const Matrix<T> &rhs)
        {
            Matrix<T> matrixNULL(0,0);

            if(!this->rowSize || !this->colSize || !rhs.rowSize || !rhs.colSize)
                return matrixNULL;
            else
            {
                if(this->row != rhs.rowSize || this->col != rhs.colSize)
                    return matrixNULL;
                else
                {
                    Matrix<T> tempMatrix(this->rowSize, this->colSize);
                    for(size_t i = 0; i < this->rowSize; i++)
                        for(size_t j = 0; j < this->colSize; j++)
                            *(tempMatrix.data+i*tempMatrix.colSize+j) = *(this->data+i*this->colSize+j) * *(rhs.data+i*rhs.colSize+j);

                    return tempMatrix;
                }
            }

            return matrixNULL;
        }
};

int main()
{
    /**
     * @brief 
     * Program ce realizeaza suma, produsul dintre 2 matrici si verifica egalitatea dintre matrici
     */
    int n_A,n_B,m_A,m_B;

    std::cin>>n_A>>m_A;
    Matrix<int> A(n_A,m_A);
    std::cin>>A;

    std::cin>>n_B>>m_B;
    Matrix<int> B(n_B,m_B);
    std::cin>>B;

    std::cout<<A+B<<'\n';
    std::cout<<A*B<<'\n';

    if(A == B)
        std::cout<<"true";
    else
        std::cout<<"false";

    return 0;
}