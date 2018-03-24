#include <iostream>
#include "tissue.hpp"

using namespace std;

Tissue::Tissue(int numAct, int numQuie, double p, double alpha,
               double beta, double GammaAct, double GammaQuie){
    m_p = p;
    m_alpha = alpha;
    m_beta = beta;
    m_GammaAct = GammaAct;
    m_GammaQuie = GammaQuie;
    m_cells.assign(numAct, Cell(true, p, alpha, beta, GammaAct,
                                GammaQuie));
    for(int i(0); i < numQuie; i++){
        m_cells.push_back(Cell(false, p, alpha, beta, GammaAct,
                               GammaQuie));
    }
}


int Tissue::updateTissue(){
    int numCells(m_cells. size());
    vector<bool> newCell(2, false);
    bool killCell(false);

    for(int i(0); i < numCells; i++){
        (m_cells.at(i)).updateCell(newCell, killCell);
        if(killCell){
            m_cells.erase(m_cells.begin() + i);
            i--;
            numCells--;
            killCell = false;
        }

        if(newCell.at(0)){
            if(newCell.at(1)){
                m_cells.push_back(Cell(true, m_p, m_alpha, m_beta,
                                       m_GammaAct, m_GammaQuie));
            }
            else{
                m_cells.push_back(Cell(false, m_p, m_alpha, m_beta,
                                       m_GammaAct, m_GammaQuie));
            }
        }
        newCell.at(0) = false;
        newCell.at(1) = false;
    }

    return 0;
}


int Tissue::getNumAct() const{
    int numAct(0);
    for(int i(0); i < m_cells.size(); i++){
        if(m_cells.at(i).getState()){
            numAct++;
        }
    }
    return numAct;
}


int Tissue::getNumQuie() const{
    return getNumCells() - getNumAct();
}


int Tissue::getNumCells() const{
    return m_cells.size();
}
