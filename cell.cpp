#include <stdlib.h>
#include <time.h>
#include "cell.hpp"

using namespace std;

Cell::Cell(bool active, double p, double alpha, double beta,
	   double GammaAct, double GammaQuie){
  m_active = active;
  m_p = p;
  m_alpha = alpha;
  m_beta = beta;
  m_GammaAct = GammaAct;
  m_GammaQuie = GammaQuie;
}


int Cell::updateCell(vector<bool> &newCell, bool &killCell){
  double n;

  n = (double)(rand()) / (double)(RAND_MAX);
  if (n < m_beta){
    m_active = true;
  }

  if(m_active){
    n = (double)(rand()) / (double)(RAND_MAX);
    if(n < m_GammaAct){
      killCell = true;
    }
    else{
      n = (double)(rand()) / (double)(RAND_MAX);
      if(n < m_alpha){
	newCell.at(0) = true;
	n = (double)(rand()) / (double)(RAND_MAX);
	if(n > m_p){
	  m_active = false;
	}
	n = (double)(rand()) / (double)(RAND_MAX);
	if(n < m_p){
	  newCell.at(1) = true;
	}
      }
    }
  }
  else{
    n = (double)(rand()) / (double)(RAND_MAX);
    if(n < m_GammaQuie){
      killCell = true;
    }
  }
  return 0;
}


bool Cell::getState() const{
  return m_active;
}
  
  
