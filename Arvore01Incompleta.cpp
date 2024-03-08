#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
class No{
	public:
		int valor;
		No *left;
		No *right;
		No(int n){
			valor=n;
			left=NULL;
			right=NULL;
		}
};

class Arvore{
	public:
		No *raiz;
		int quantNos;
		int h;
		Arvore(){
			raiz=NULL;
			quantNos=0;
			h=-1;
		}
		
		int isEmpty(){
	   		return (raiz==NULL);
		   }
		
			
		void criaNo(char n){
			No *novo= new No(n);
			
		} 
		
		void inserirSemRecursao(No *arv,No *n){
		
		}
		
		void inserirComRecursao(No *arv,No *n){
		
		}
		
		void calculaqtdNos(No *arv){
			if (arv!=NULL){
			
			}
		}
		
		void calculaAlturaArvore(No *arv){
					
			
		}
		
		int arvcompleta(){
			
		}
		
		int arvcheia(){
			
			
		}
		
		void preordem(No *n){
			
			
			
	    }
	    
	    void posordem(No *n){
			
			
		}
		
		void inordem(No *n){
			
			
		 
	    }
};

main(){
	Arvore *arvore= new Arvore();
}

