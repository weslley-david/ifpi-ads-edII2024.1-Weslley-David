#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
class No
{
public:
	int valor;
	No *left;
	No *right;
	No(int n)
	{
		valor = n;
		left = NULL;
		right = NULL;
	}
};

class Arvore
{
public:
	No *raiz;
	int quantNos;
	int h;
	Arvore()
	{
		raiz = NULL;
		quantNos = 0;
		h = -1;
	}

	int isEmpty()
	{
		return (raiz == NULL);
	}

	void criaNo(int n)
	{
		No *novo = new No(n);
		raiz = novo;
	}

	void inserirSemRecursao(No *arv, No *n)
	{
		if (isEmpty() == 1)
			raiz = n;
		else
		{
			No *percorre = raiz;
			while (percorre != NULL)
			{
				if (n->valor < percorre->valor)
				{
					if (percorre->left == NULL)
					{
						percorre->left = n;
						// this->quantNos = this->quantNos + 1;
						break;
					}
					else
						percorre = percorre->left;
				}
				else
				{
					if (percorre->right == NULL)
					{
						percorre->right = n;
						// this->quantNos = this->quantNos + 1;
						break;
					}
					else
						percorre = percorre->right;
				}
			}
		}
	}
	void inserirComRecursao(No *&arv, No *n)
	{

		if (arv == NULL)
		{
			arv = n;
		}
		else
		{
			if (n->valor < arv->valor)
			{
				inserirComRecursao(arv->left, n);
			}
			else
			{
				inserirComRecursao(arv->right, n);
			}
		}
	}

	void calculaqtdNos(No *arv)
	{
		if (arv != NULL)
		{
			quantNos++;
			calculaqtdNos(arv->left);
			calculaqtdNos(arv->right);
		}
	}

	void calculaAlturaArvore(No *arv)
	{
		if (arv != NULL)
		{
			int altura_esq = 0, altura_dir = 0;
			calculaAlturaArvore(arv->left);
			calculaAlturaArvore(arv->right);
			altura_esq = alturaArvore(arv->left);
			altura_dir = alturaArvore(arv->right);
			h = (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
		}
	}

	int arvcompleta()
	{
		int altura = alturaArvore(raiz);
		return verificaCompleta(raiz, altura, 0);
	}

	int arvcheia()
	{
		calculaqtdNos(raiz);
		int esperado = pow(2, h + 1) - 1;
		return (quantNos == esperado);
	}

	int alturaArvore(No *arv)
	{
		if (arv == NULL)
			return 0;
		else
		{
			int altura_esq = alturaArvore(arv->left);
			int altura_dir = alturaArvore(arv->right);
			return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
		}
	}

	int verificaCompleta(No *arv, int altura, int nivel)
	{
		if (arv == NULL)
			return 1;

		if (altura == nivel + 1)
			return 1;

		if ((arv->left == NULL && arv->right != NULL) || (arv->left != NULL && arv->right == NULL))
			return 0;

		return verificaCompleta(arv->left, altura, nivel + 1) && verificaCompleta(arv->right, altura, nivel + 1);
	}

	void preOrdem(No *n)
	{
		if (n != NULL)
		{
			cout << n->valor << " ";
			preOrdem(n->left);
			preOrdem(n->right);
		}
	}

	void posOrdem(No *n)
	{
		if (n != NULL)
		{
			posOrdem(n->left);
			posOrdem(n->right);
			cout << n->valor << " ";
		}
	}

	void inOrdem(No *n)
	{
		if (n != NULL)
		{
			inOrdem(n->left);
			cout << n->valor << " ";
			inOrdem(n->right);
		}
	}
};

int main() {
    Arvore *arvore = new Arvore();

    // Inserindo alguns nós na árvore
    arvore->criaNo(7);
    arvore->inserirSemRecursao(arvore->raiz, new No(3));
    arvore->inserirSemRecursao(arvore->raiz, new No(10));
    // arvore->inserirSemRecursao(arvore->raiz, new No(5));
    // arvore->inserirSemRecursao(arvore->raiz, new No(1));
    // arvore->inserirSemRecursao(arvore->raiz, new No(9));
    // arvore->inserirSemRecursao(arvore->raiz, new No(12));

    arvore->inOrdem(arvore->raiz);
    cout << endl;
    arvore->preOrdem(arvore->raiz);
    cout << endl;
    arvore->posOrdem(arvore->raiz);
    cout << endl;

    cout << arvore->alturaArvore(arvore->raiz) << endl;

    cout << arvore->arvcompleta() << endl;

    cout << arvore->arvcheia()  << endl;

    delete arvore;

    return 0;
}
