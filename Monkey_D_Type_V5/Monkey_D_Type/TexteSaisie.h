#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class TexteSaisie
{
	vector <Text> cont_;
public :
	void setCharfont(int n, Font& font);
	void setCont(int n, string txt);
	void setCharPosit(int n, float a, float b);
	void setCharCol(int n, Color color);
	void afficherTexte(RenderWindow& window);
	void suppchar();
	void reset();
	void addchar(Text& text);
	Text getText();
	vector <Text> getVect(){ return cont_; };
};