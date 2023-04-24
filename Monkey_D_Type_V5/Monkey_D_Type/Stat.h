#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Stat
{
	int nbcharJ_;
	int nbcharF_;
	int nbmotJ_;
	vector<double> tabscore_;
public :
	Stat();
	void setNbcharJ();
	void setNbcharF();
	void setNbmotJ();
	void setTabscore();
	int getNbcharJ() { return nbcharJ_; }
	int getNbcharF() { return nbcharF_; }
	int getNbmotJ() { return nbmotJ_; }
	vector<double> getTabscore() { return tabscore_; }
	void precision();
	void nbcharsecond();
	void nbmotminute();
	void sauvegarde();

};