#include <vector>

class Cell{
protected:
  bool m_active; // 1 = active; 0 = quiescent
  double m_p; //probAct
  double m_alpha; //proliferation rate
  double m_beta; //quies2ActTim
  double m_GammaAct; //death rate of active cells
  double m_GammaQuie; //death rate of quiescent cells
  
public:
  Cell(bool active, double p, double alpha, double beta,
       double GammaAct, double GammaQuie);
  int updateCell(std::vector<bool> &newCell, bool &killCell);
  bool getState() const;
};
