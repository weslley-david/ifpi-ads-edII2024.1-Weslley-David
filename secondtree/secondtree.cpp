#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <class T>
class ArvoreNo
{
public:
    T valor;
    ArvoreNo<T> *left, *right;

    ArvoreNo(T v)
    {
        valor = v;
        left = right = nullptr;
    }
};

template <class T>
class Arvore
{
public:
    ArvoreNo<T> *raiz;

    Arvore()
    {
        raiz = nullptr;
    }

    bool isEmpty()
    {
        return (raiz == nullptr);
    }

    void inserirComRecursao(ArvoreNo<T> *&arv, ArvoreNo<T> *n)
    {
        if (arv == nullptr)
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

    void inserirSemRecursao(ArvoreNo<T> *n)
    {
        if (isEmpty())
        {
            raiz = n;
        }
        else
        {
            ArvoreNo<T> *percorre = raiz;
            while (percorre != nullptr)
            {
                if (n->valor < percorre->valor)
                {
                    if (percorre->left == nullptr)
                    {
                        percorre->left = n;
                        break;
                    }
                    else
                        percorre = percorre->left;
                }
                else
                {
                    if (percorre->right == nullptr)
                    {
                        percorre->right = n;
                        break;
                    }
                    else
                        percorre = percorre->right;
                }
            }
        }
    }

    void preOrdem(ArvoreNo<T> *n)
    {
        if (n != nullptr)
        {
            cout << n->valor << " ";
            preOrdem(n->left);
            preOrdem(n->right);
        }
    }

    void iterativePreorder()
    {
        stack<ArvoreNo<T> *> travStack;
        ArvoreNo<T> *p = raiz;

        while (p != nullptr || !travStack.empty())
        {
            while (p != nullptr)
            {
                cout << p->valor << " "; // Imprime o valor do nó
                travStack.push(p);
                p = p->left;
            }

            if (!travStack.empty())
            {
                p = travStack.top();
                travStack.pop();
                p = p->right;
            }
        }
    }

    void iterativePosorder()
    {
        stack<pair<ArvoreNo<T>*, bool>> travStack; // Stack to store nodes to be visited along with their visit status
        ArvoreNo<T> *p = raiz; // Start with the root node

        while (p != nullptr || !travStack.empty()) // Continue until there are nodes to be visited
        {
            while (p != nullptr) // Move to the leftmost node
            {
                travStack.push({p, false}); // Push the current node along with its visit status (false)
                

                p = p->left; // Move to the left child
            }

            // Check the visit status of the node at the top of the stack
            auto [node, visited] = travStack.top();
            if (!visited) // If the node has not been visited yet
            {
                travStack.top().second = true; // Update its visit status to true
                p = node->right; // Move to the right child
            }
            else // If the node has been visited
            {
                cout << node->valor << " "; // Print the value of the node
                travStack.pop(); // Pop the node from the stack
            }
        }
    }

    

    ArvoreNo<T> *removeMinimo(ArvoreNo<T> *&p)
    {
        if (p == nullptr)
        {
            return nullptr; // A árvore está vazia
        }
        else if (p->left == nullptr)
        {
            ArvoreNo<T> *temp = p;
            p = p->right;
            return temp;
        }
        else
        {
            return removeMinimo(p->left);
        }
    }

    ArvoreNo<T> *removeMaximo(ArvoreNo<T> *&p)
    {
        if (p == nullptr)
        {
            return nullptr; // A árvore está vazia
        }
        else if (p->right == nullptr)
        {
            ArvoreNo<T> *temp = p;
            p = p->left;
            return temp;
        }
        else
        {
            return removeMaximo(p->right);
        }
    }

    void removerNo(ArvoreNo<T> *&p, T valor)
    {
        if (p == nullptr)
        {
            return; // Nó não encontrado
        }

        if (valor < p->valor)
        {
            removerNo(p->left, valor);
        }
        else if (valor > p->valor)
        {
            removerNo(p->right, valor);
        }
        else
        {
            if (p->left == nullptr)
            {
                ArvoreNo<T> *temp = p->right;
                delete p;
                p = temp;
            }
            else if (p->right == nullptr)
            {
                ArvoreNo<T> *temp = p->left;
                delete p;
                p = temp;
            }
            else
            {
                ArvoreNo<T> *temp = removeMinimo(p->right);
                p->valor = temp->valor;
                delete temp;
            }
        }
    }

    ArvoreNo<T> *BuscaSemRecursao(ArvoreNo<T> *p, T el)
    {
        while (p != nullptr)
        {
            if (el == p->valor)
            {
                return p;
            }
            else if (el < p->valor)
            {
                p = p->left;
            }
            else
            {
                p = p->right;
            }
        }
        return nullptr;
    }

    ArvoreNo<T> *BuscaComRecursao(ArvoreNo<T> *p, T el)
    {
        if (p != nullptr)
        {
            if (el == p->valor)
            {
                return p;
            }
            else if (el < p->valor)
            {
                return BuscaComRecursao(p->left, el);
            }
            else
            {
                return BuscaComRecursao(p->right, el);
            }
        }
        return nullptr;
    }

    void percursoExtensao()
    {
        queue<ArvoreNo<T> *> f;
        ArvoreNo<T> *p = raiz;
        if (p != nullptr)
        {
            f.push(p);
            while (!f.empty())
            {
                p = f.front();
                cout << p->valor << " ";
                f.pop();
                if (p->left != nullptr)
                {
                    f.push(p->left);
                }
                if (p->right != nullptr)
                {
                    f.push(p->right);
                }
            }
        }
    }
};
int main()
{
    Arvore<int> arvore;

    // Inserindo elementos na árvore
    arvore.inserirComRecursao(arvore.raiz, new ArvoreNo<int>(100));
    
    arvore.inserirComRecursao(arvore.raiz, new ArvoreNo<int>(70));
    arvore.inserirComRecursao(arvore.raiz, new ArvoreNo<int>(40));
    arvore.inserirComRecursao(arvore.raiz, new ArvoreNo<int>(80));
    arvore.inserirComRecursao(arvore.raiz, new ArvoreNo<int>(220));

    // Teste BuscaSemRecursao
    /*ArvoreNo<int> *resultadoBusca = arvore.BuscaSemRecursao(arvore.raiz, 12);
    if (resultadoBusca != nullptr)
    {
        cout << "Elemento 12 encontrado na árvore." << endl;
    }
    else
    {
        cout << "Elemento 12 não encontrado na árvore." << endl;
    }*/

    // Teste BuscaComRecursao
    /*ArvoreNo<int> *resultadoBusca2 = arvore.BuscaComRecursao(arvore.raiz, 15);
    if (resultadoBusca2 != nullptr)
    {
        cout << "Elemento 15 encontrado na árvore." << endl;
    }
    else
    {
        cout << "Elemento 15 não encontrado na árvore." << endl;
    }*/

    // Teste preOrdem
    //cout << "Pre-Ordem: ";
    //arvore.preOrdem(arvore.raiz);
   // cout << endl;

    // Teste percursoExtensao
    //cout << "Percurso em extensão: ";
    //arvore.percursoExtensao();
    //cout << endl;

    // Teste iterativePreorder
    cout << "Iterative Pre-Ordem: ";
    arvore.iterativePreorder();
    cout << endl;
    cout << "Iterative Pos-Ordem: ";
    arvore.iterativePosorder();
    cout << endl;
    // Teste removerNo
    //cout << "Removendo nó 10..." << endl;
    //arvore.removerNo(arvore.raiz, 10);
    //cout << "Pre-Ordem após remoção: ";
    //arvore.preOrdem(arvore.raiz);
    //cout << endl;

    // Teste remover mínimo
    //cout << "Removendo o nó mínimo..." << endl;
   /*ArvoreNo<int> *minimoRemovido = arvore.removeMinimo(arvore.raiz);
    if (minimoRemovido != nullptr)
    {
        cout << "Nó mínimo removido: " << minimoRemovido->valor << endl;
        delete minimoRemovido;
    }
    else
    {
        cout << "A árvore está vazia ou ocorreu um erro ao remover o nó mínimo." << endl;
    }*/

    // Teste remover máximo
    /*cout << "Removendo o nó máximo..." << endl;
    ArvoreNo<int> *maximoRemovido = arvore.removeMaximo(arvore.raiz);
    if (maximoRemovido != nullptr)
    {
        cout << "Nó máximo removido: " << maximoRemovido->valor << endl;
        delete maximoRemovido;
    }
    else
    {
        cout << "A árvore está vazia ou ocorreu um erro ao remover o nó máximo." << endl;
    }*/

    return 0;
}
