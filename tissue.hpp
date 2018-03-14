#include <vector>
#include "cell.hpp"

class Tissue{
protected:
  std::vector<Cell> m_cells;
  int m_numAct; //number of active cells
  int m_numQuie; //number of quiescent cells
  double m_p; //probAct
  double m_alpha; //proliferation rate
  double m_beta; //quies2ActTim
  double m_GammaAct; //death rate of active cells
  double m_GammaQuie; //death rate of quiescent cells
  
public:
  Tissue(int numAct, int numQuie, double p, double alpha,
	 double beta, double GammaAct, double GammaQuie);
  int updateTissue();
  int getNumAct() const;
  int getNumQuie() const;
  int getNumCells() const;
};
  
