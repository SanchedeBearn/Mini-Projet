#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Texte_A_Recopier
{
	Text text_;
public :
	Texte_A_Recopier(Font &font);
	Text getText() { return text_; }
	void setText(String a);
	void afficher(RenderWindow &window);

};