#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <variant>
#include <queue> 

using namespace std;
template <class T>
class No {
public:
    T valor;
    No<T>* left;
    No<T>* right;

    No(T n) : valor(n), left(nullptr), right(nullptr) {}
};

template <class T>
class ArvoreNo {
public:
    T el;
    ArvoreNo<T> *left, *right;
    ArvoreNo() {
        left = right = nullptr;
    }
    ArvoreNo(T e, ArvoreNo<T> *l = nullptr, ArvoreNo<T> *r = nullptr) {
        el = e;
        left = l;
        right = r;
    }
};
template <class T>
class Arvore {
public:
    ArvoreNo<T> *raiz;
    int quantNos;
    int h;

    Arvore() : raiz(nullptr), quantNos(0), h(-1) {}

	void percusoExtensao() {
		queue<ArvoreNo<T>*> f;
		ArvoreNo<T>* p = raiz;

		if (p != nullptr) {
			f.push(p);

			while (!f.empty()) {
				p = f.front();
				cout << p->el << " ";
				f.pop();

				if (p->left != nullptr)
					f.push(p->left);

				if (p->right != nullptr)
					f.push(p->right);
			}
		}
	}


    int isEmpty() {
        return (raiz == nullptr);
    }

    void criaNo(T n) {
        ArvoreNo<T>* novo = new ArvoreNo<T>(n);
        raiz = novo;
    }

   void inserirSemRecursao(ArvoreNo<T> *&arv, ArvoreNo<T> *n) {
        if (isEmpty() == 1)
            raiz = n;
        else {
            ArvoreNo<T> *percorre = raiz;
            while (percorre != nullptr) {
                if (n->el < percorre->el) {
                    if (percorre->left == nullptr) {
                        percorre->left = n;
                        break;
                    } else
                        percorre = percorre->left;
                } else {
                    if (percorre->right == nullptr) {
                        percorre->right = n;
                        break;
                    } else
                        percorre = percorre->right;
                }
            }
        }
    }

    void inserirComRecursao(ArvoreNo<T>*& arv, ArvoreNo<T>* n) {
        if (arv == nullptr) {
            arv = n;
        } else {
            if (n->el < arv->el) {
                inserirComRecursao(arv->left, n);
            } else {
                inserirComRecursao(arv->right, n);
            }
        }
    }

    void calculaqtdNos(ArvoreNo<T>* arv) {
        if (arv != nullptr) {
            quantNos++;
            calculaqtdNos(arv->left);
            calculaqtdNos(arv->right);
        }
    }

    void calculaAlturaArvore(ArvoreNo<T>* arv) {
        if (arv != nullptr) {
            int altura_esq = 0, altura_dir = 0;
            calculaAlturaArvore(arv->left);
            calculaAlturaArvore(arv->right);
            altura_esq = alturaArvore(arv->left);
            altura_dir = alturaArvore(arv->right);
            h = (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
        }
    }

    int arvcompleta() {
        int altura = alturaArvore(raiz);
        return verificaCompleta(raiz, altura, 0);
    }

    int arvcheia() {
        calculaqtdNos(raiz);
        int esperado = pow(2, h + 1) - 1;
        return (quantNos == esperado);
    }

    int alturaArvore(ArvoreNo<T>* arv) {
        if (arv == nullptr)
            return 0;
        else {
            int altura_esq = alturaArvore(arv->left);
            int altura_dir = alturaArvore(arv->right);
            return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
        }
    }

    int buscarSemRecusao(ArvoreNo<T>* arvore, T el) {
        while (arvore != nullptr) {
            if (el == arvore->el)
                return arvore->el;
            else {
                if (el < arvore->el)
                    arvore = arvore->left;
                else
                    arvore = arvore->right;
            }
        }
        return 0;
    }

    int verificaCompleta(ArvoreNo<T>* arv, int altura, int nivel) {
        if (arv == nullptr)
            return 1;

        if (altura == nivel + 1)
            return 1;

        if ((arv->left == nullptr && arv->right != nullptr) || (arv->left != nullptr && arv->right == nullptr))
            return 0;

        return verificaCompleta(arv->left, altura, nivel + 1) && verificaCompleta(arv->right, altura, nivel + 1);
    }

    void preOrdem(ArvoreNo<T>* n) {
        if (n != nullptr) {
            cout << n->el << " ";
            preOrdem(n->left);
            preOrdem(n->right);
        }
    }

    void posOrdem(ArvoreNo<T>* n) {
        if (n != nullptr) {
            posOrdem(n->left);
            posOrdem(n->right);
            cout << n->el << " ";
        }
    }

    void inOrdem(ArvoreNo<T>* n) {
        if (n != nullptr) {
            inOrdem(n->left);
            cout << n->el << " ";
            inOrdem(n->right);
        }
    }
};

int main() {
    Arvore<int> *arvore = new Arvore<int>();

    // Inserindo alguns nós na árvore
    arvore->criaNo(7);
    arvore->inserirSemRecursao(arvore->raiz, new ArvoreNo<int>(3));

    arvore->inserirSemRecursao(arvore->raiz, new ArvoreNo<int>(10));
    // arvore->inserirSemRecursao(arvore->raiz, new No<int>(5));
    // arvore->inserirSemRecursao(arvore->raiz, new No<int>(1));
    arvore->inserirSemRecursao(arvore->raiz, new ArvoreNo<int>(9));
    arvore->inserirSemRecursao(arvore->raiz, new ArvoreNo<int>(12));
    arvore->buscarSemRecusao(arvore->raiz, 12);
    cout << endl;
	cout << "percurso em inOrdem" << endl;

    arvore->inOrdem(arvore->raiz);
    cout << endl;
	cout << "percurso em preOrdem" << endl;

    arvore->preOrdem(arvore->raiz);
    cout << endl;
	cout << "percurso em posOrdem" << endl;

    arvore->posOrdem(arvore->raiz);
    cout << endl;
    cout << arvore->buscarSemRecusao(arvore->raiz, 10) << endl;
    cout << arvore->buscarSemRecusao(arvore->raiz, 7) << endl;
    cout << arvore->buscarSemRecusao(arvore->raiz, 12) << endl;
    cout << arvore->buscarSemRecusao(arvore->raiz, 69) << endl;
	cout << "percurso em extensão" << endl;

	arvore->percusoExtensao();
	cout << "\n" << endl;
	// cout << arvore->alturaArvore(arvore->raiz) << endl;

    // cout << arvore->arvcompleta() << endl;

    // cout << arvore->arvcheia()  << endl;

    delete arvore;

    return 0;
}
